// Local, allocation-free search for Priyom schedule events.
// Comma-separated conditions use AND, independent of their order.
// Times are always UTC (the source calendar's time zone).
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_FILTER_H
#define PRIYOM_FILTER_H
#include "priyom_parser.h"
namespace priyom {
static char filter_lower(char c){return c>='A'&&c<='Z'?(char)(c+'a'-'A'):c;}
static bool filter_space(char c){return c==' '||c=='\t'||c=='\n'||c=='\r';}
static bool filter_contains(const char*text,const char*token){
    if(!text||!token||!*token)return false;
    for(const char*p=text;*p;p++){
        const char*a=p,*b=token;
        while(*a&&*b&&filter_lower(*a)==filter_lower(*b)){a++;b++;}
        if(!*b)return true;
    }
    return false;
}
static bool filter_parse_number(const char*&p,double&value){
    if(!digit(*p)&&*p!='.')return false;
    value=0;int ndigits=0;
    while(digit(*p)){value=value*10.0+(double)(*p++-'0');ndigits++;}
    if(*p=='.'){p++;double place=.1;while(digit(*p)){value+=(double)(*p++-'0')*place;place*=.1;ndigits++;}}
    return ndigits>0;
}
static void filter_skip_spaces(const char*&p){while(filter_space(*p))p++;}
static bool filter_khz_end(const char*p){
    filter_skip_spaces(p);
    if(filter_lower(p[0])=='k'&&filter_lower(p[1])=='h'&&filter_lower(p[2])=='z')p+=3;
    filter_skip_spaces(p);
    return !*p;
}
static bool filter_range_khz(const char*token,double&low,double&high){
    const char*p=token;if(!filter_parse_number(p,low))return false;
    filter_skip_spaces(p);if(*p++!='-')return false;
    filter_skip_spaces(p);if(!filter_parse_number(p,high))return false;
    return low<=high&&filter_khz_end(p);
}
static bool filter_exact_khz(const char*token,double&khz){
    const char*p=token;if(!filter_parse_number(p,khz))return false;
    filter_skip_spaces(p);
    if(filter_lower(p[0])!='k'||filter_lower(p[1])!='h'||filter_lower(p[2])!='z')return false;
    p+=3;filter_skip_spaces(p);return !*p;
}
static bool filter_clock(const char*&p,int&minutes){
    if(!digit(*p))return false;
    int hours=(*p++-'0');
    if(digit(*p))hours=hours*10+(*p++-'0');
    if(*p++!=':'||!digit(p[0])||!digit(p[1]))return false;
    int mins=(p[0]-'0')*10+(p[1]-'0');p+=2;
    if(hours>23||mins>59)return false;
    minutes=hours*60+mins;return true;
}
static bool filter_utc_time(const char*term,int&from,int&to,bool&range){
    const char*p=term;
    if(!filter_clock(p,from))return false;
    filter_skip_spaces(p);
    if(!*p){to=from;range=false;return true;}
    if(*p++!='-')return false;
    filter_skip_spaces(p);
    if(!filter_clock(p,to))return false;
    filter_skip_spaces(p);
    range=true;return !*p;
}
static bool filter_time_matches(const Event&e,int from,int to,bool range){
    int minute=(int)((e.utc%86400+86400)%86400/60);
    if(!range)return minute==from;
    return from<=to?(minute>=from&&minute<=to):(minute>=from||minute<=to);
}
static void filter_append_number(char*dest,unsigned cap,unsigned long long n){
    char rev[24];unsigned len=0;
    do{rev[len++]=(char)('0'+n%10);n/=10;}while(n&&len<sizeof(rev));
    unsigned at=0;while(dest[at])at++;
    while(len&&at+1<cap)dest[at++]=rev[--len];
    dest[at]=0;
}
static void filter_format_frequency(const Event&e,char*out,unsigned cap){
    if(!cap)return;
    out[0]=0;if(e.search||e.hz<=0)return;
    unsigned long long hz=(unsigned long long)(e.hz+0.5);
    filter_append_number(out,cap,hz/1000);
    unsigned frac=(unsigned)(hz%1000);
    if(frac){
        unsigned at=0;while(out[at])at++;
        if(at+5<cap){
            out[at++]='.';
            out[at++]=(char)('0'+frac/100);
            out[at++]=(char)('0'+frac/10%10);
            out[at++]=(char)('0'+frac%10);
            while(out[at-1]=='0')at--;
            out[at]=0;
        }
    }
}
static bool filter_match_term(const Event&e,const char*term,const char*country,const char*frequency){
    int from=0,to=0;bool range=false;
    if(filter_utc_time(term,from,to,range))return filter_time_matches(e,from,to,range);
    double low=0,high=0;
    if(filter_range_khz(term,low,high))
        return !e.search&&e.hz>0&&e.hz/1000.0>=low&&e.hz/1000.0<=high;
    if(filter_exact_khz(term,low)){
        if(e.search||e.hz<=0)return false;
        const double difference=e.hz/1000.0-low;
        return difference>=-0.0005&&difference<=0.0005;
    }
    if(filter_contains(e.station,term)||filter_contains(e.mode,term)||
       filter_contains(frequency,term)||(country&&filter_contains(country,term)))return true;
    // Keep the original whitespace-separated AND search. Checking the entire
    // expression first also supports multi-word countries (e.g. United States).
    const char*p=term;bool found=false;
    while(*p){
        while(filter_space(*p))p++;
        if(!*p)break;
        char word[96];unsigned n=0;
        while(*p&&!filter_space(*p)){if(n+1<sizeof(word))word[n++]=*p;p++;}
        word[n]=0;if(!n)continue;
        if(n==3&&filter_lower(word[0])=='k'&&filter_lower(word[1])=='h'&&filter_lower(word[2])=='z')continue;
        if(!filter_contains(e.station,word)&&!filter_contains(e.mode,word)&&
           !filter_contains(frequency,word)&&!(country&&filter_contains(country,word)))return false;
        found=true;
    }
    return found;
}
static bool filter_match_event(const Event&e,const char*query,const char*localized_country){
    if(!query||!*query)return true;
    char frequency[48];filter_format_frequency(e,frequency,sizeof(frequency));
    const char*p=query;
    while(*p){
        while(*p==','||filter_space(*p))p++;
        if(!*p)break;
        char term[128];unsigned n=0;
        while(*p&&*p!=','){if(n+1<sizeof(term))term[n++]=*p;p++;}
        while(n&&filter_space(term[n-1]))n--;
        term[n]=0;
        if(n&&!filter_match_term(e,term,localized_country,frequency))return false;
    }
    return true;
}
}
#endif

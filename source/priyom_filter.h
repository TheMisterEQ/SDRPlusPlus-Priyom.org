// Local client-side search of parsed Priyom calendar events.
// ASCII case-insensitive, no locale dependencies and no allocations.
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_FILTER_H
#define PRIYOM_FILTER_H
#include "priyom_parser.h"
namespace priyom {
static char filter_lower(char c) { return c >= 'A' && c <= 'Z' ? (char)(c + ('a'-'A')) : c; }
static bool filter_space(char c) { return c==' ' || c=='\t' || c=='\n' || c=='\r'; }
static bool filter_contains(const char* text, const char* token) {
    if (!*token) return true;
    for (const char* p=text; *p; p++) {
        const char* a=p; const char* b=token;
        while (*a && *b && filter_lower(*a)==filter_lower(*b)) { a++; b++; }
        if (!*b) return true;
    }
    return false;
}
static bool filter_parse_number(const char*&p, double&val) {
    if (!digit(*p) && *p!='.')return false;
    val=0;int ndigits=0;
    while (digit(*p)) { val=val*10.0+(double)(*p++-'0');ndigits++; }
    if (*p=='.') {p++;double pos=0.1;while(digit(*p)){val+=(double)(*p++-'0')*pos;pos*=0.1;ndigits++;}}
    return ndigits>0;
}
static bool filter_range_khz(const char*token,double&low,double&high){
    const char*p=token;
    if(!filter_parse_number(p,low)||*p!='-')return false;
    p++;if(!filter_parse_number(p,high)||*p||low>high)return false;
    return true;
}
static void filter_append_number(char*dest,unsigned cap,unsigned long long n){
    char rev[24];unsigned len=0;
    do {rev[len++]=(char)('0'+n%10);n/=10;}while(n&&len<sizeof(rev));
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
static bool filter_match_event(const Event&e,const char*query){
    if(!query||!*query)return true;
    char frequency[48];filter_format_frequency(e,frequency,sizeof(frequency));
    const char*p=query;
    while (*p) {
        while(filter_space(*p))p++;
        if(!*p)break;
        char token[64];unsigned n=0;
        while(*p&&!filter_space(*p)){
            if(n+1<sizeof(token))token[n++]=*p;
            p++;
        }
        token[n]=0;
        // Numeric ranges use kHz, e.g. 3000-10000 kHz.
        double lo=0,hi=0;
        if(filter_range_khz(token,lo,hi)){
            if(e.search||e.hz<=0||e.hz/1000.0<lo||e.hz/1000.0>hi)return false;
            continue;
        }
        // An optional unit after a range or frequency is informational.
        if(filter_contains("khz",token)&&n==3)continue;
        if(!filter_contains(e.station,token)&&!filter_contains(e.mode,token)&&!filter_contains(frequency,token))return false;
    }
    return true;
}
}
#endif

// Priyom calendar JSON parser. Independent of SDR++ and Windows.
// Source protocol: https://github.com/priyom/calendar-web-viewer/blob/master/src/fetch-priyom.js
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_PARSER_H
#define PRIYOM_PARSER_H

namespace priyom {
typedef long long i64;
struct Event {
    i64 utc;
    double hz;
    char station[24];
    char mode[24];
    char remarks[128];
    bool search;
};
static unsigned len(const char*s){unsigned n=0;if(s)while(s[n])++n;return n;}
static bool eq(const char*a,const char*b){if(!a||!b)return false;while(*a&&*b&&*a==*b){a++;b++;}return *a==*b;}
static bool prefix(const char*a,const char*b){while(*b){if(*a++!=*b++)return false;}return true;}
static void cp(char*o,unsigned cap,const char*s){if(!cap)return;unsigned i=0;while(s&&s[i]&&i+1<cap){o[i]=s[i];i++;}o[i]=0;}
static bool digit(char c){return c>='0'&&c<='9';}
static int number(const char*s,int count){int n=0;for(int i=0;i<count;i++){if(!digit(s[i]))return -1;n=n*10+s[i]-'0';}return n;}
static i64 civil_days(int y,unsigned m,unsigned d){y-=m<=2;const int era=(y>=0?y:y-399)/400;const unsigned yoe=(unsigned)(y-era*400);const unsigned doy=(153*(m+(m>2?-3:9))+2)/5+d-1;const unsigned yoeDays=yoe*365+yoe/4-yoe/100+doy;return (i64)era*146097+(int)yoeDays-719468;}
static bool leap(int y){return y%4==0&&(y%100!=0||y%400==0);}
static bool iso_utc(const char*s,i64&out){
    if(len(s)<20||s[4]!='-'||s[7]!='-'||(s[10]!='T'&&s[10]!='t')||s[13]!=':'||s[16]!=':')return false;
    int y=number(s,4),mo=number(s+5,2),d=number(s+8,2),h=number(s+11,2),mi=number(s+14,2),sec=number(s+17,2);
    if(y<1970||y>2100||mo<1||mo>12||d<1||h<0||h>23||mi<0||mi>59||sec<0||sec>60)return false;
    static const int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(d>days[mo-1]+(mo==2&&leap(y)?1:0))return false;
    const char*p=s+19;if(*p=='.'){++p;while(digit(*p))++p;}
    int offset=0;
    if(*p=='Z'||*p=='z'){++p;}
    else if(*p=='+'||*p=='-'){
        int sign=*p=='+'?1:-1; ++p;
        int oh=number(p,2);if(oh<0||oh>23)return false;p+=2;
        if(*p==':')++p;
        int om=number(p,2);if(om<0||om>59)return false;p+=2;
        offset=sign*(oh*3600+om*60);
    }else return false;
    if(*p)return false;
    out=civil_days(y,(unsigned)mo,(unsigned)d)*86400+(i64)h*3600+mi*60+sec-offset;
    return true;
}
struct Reader{const char*p;const char*end;};
static void ws(Reader&r){while(r.p<r.end&&(*r.p==' '||*r.p=='\n'||*r.p=='\r'||*r.p=='\t'))++r.p;}
static bool str(Reader&r,char*out,unsigned cap){
    ws(r);if(r.p==r.end||*r.p!='"')return false;++r.p;unsigned i=0;
    while(r.p<r.end){unsigned char c=(unsigned char)*r.p++;
        if(c=='"'){if(cap)out[i<cap?i:cap-1]=0;return true;}
        if(c<0x20)return false;
        if(c=='\\'){
            if(r.p==r.end)return false;
            c=(unsigned char)*r.p++;
            switch(c){case '"':case '\\':case '/':break;case 'b':c='\b';break;case 'f':c='\f';break;
                case 'n':c='\n';break;case 'r':c='\r';break;case 't':c='\t';break;
                case 'u':{if(r.end-r.p<4)return false;int n=0;for(int k=0;k<4;k++){
                    char q=*r.p++;int x=digit(q)?q-'0':(q>='a'&&q<='f'?q-'a'+10:(q>='A'&&q<='F'?q-'A'+10:-1));if(x<0)return false;n=n*16+x;}
                    c=n>=32&&n<=126?(unsigned char)n:'?';break;}
                default:return false;
            }
        }
        if(i+1<cap)out[i++]=(char)c;
    }
    return false;
}
static bool skip(Reader&r,int depth){
    if(depth>24)return false;
    ws(r);
    if(r.p==r.end)return false;
    if(*r.p=='"'){char sink[1];return str(r,sink,1);}
    if(*r.p=='{'||*r.p=='['){char open=*r.p++,close=open=='{'?'}':']';ws(r);
        if(r.p<r.end&&*r.p==close){++r.p;return true;}
        while(r.p<r.end){if(open=='{'){char key[2];if(!str(r,key,2))return false;ws(r);if(r.p==r.end||*r.p++!=':')return false;}
            if(!skip(r,depth+1))return false;
            ws(r);
            if(r.p==r.end)return false;
            if(*r.p==close){++r.p;return true;}if(*r.p++!=',')return false;
        }return false;
    }
    const char*start=r.p;while(r.p<r.end&&*r.p!=','&&*r.p!=']'&&*r.p!='}'&&*r.p!=' '&&*r.p!='\n'&&*r.p!='\r'&&*r.p!='\t')++r.p;
    return r.p>start;
}
static bool start_object(Reader&r,char*iso,unsigned cap){
    ws(r);if(r.p==r.end||*r.p++!='{')return false;ws(r);
    while(r.p<r.end&&*r.p!='}'){
        char key[48];if(!str(r,key,sizeof(key)))return false;ws(r);if(r.p==r.end||*r.p++!=':')return false;
        if(eq(key,"dateTime")){if(!str(r,iso,cap))return false;}
        else if(!skip(r,0))return false;
        ws(r);if(r.p<r.end&&*r.p==','){++r.p;ws(r);}else break;
    }
    if(r.p==r.end||*r.p++!='}')return false;
    return true;
}
static void parse_summary(const char*summary,i64 utc,Event*out,int&count,int cap){
    char station[24]={0};const char*p=summary;int sn=0;
    while(*p&&*p!=' '&&sn<22){char c=*p++;if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')||digit(c)))return;station[sn++]=c;}
    if(*p!=' '||!sn)return;
    station[sn]=0;while(*p==' ')++p;
    if(prefix(p,"Search")){
        if(count>=cap)return;
        Event&e=out[count++];e.utc=utc;e.hz=0;e.search=true;cp(e.station,sizeof(e.station),station);cp(e.mode,sizeof(e.mode),"-");cp(e.remarks,sizeof(e.remarks),p+6);return;
    }
    // The official calendar frontend treats the portion ending in the last kHz as
    // a comma-separated frequency list, then a mode token and optional remarks.
    const char*last=0;for(const char*q=p;*q;q++)if(q[0]=='k'&&q[1]=='H'&&q[2]=='z')last=q+3;
    if(!last)return;
    const char*mode=last;while(*mode==' ')++mode;
    char modebuf[24]={0};int mn=0;while(*mode&&*mode!=' '&&mn<22)modebuf[mn++]=*mode++;
    if(!mn)return;
    modebuf[mn]=0;while(*mode==' ')++mode;
    for(const char*q=p;q<last&&count<cap;){
        while(q<last&&!digit(*q))++q;
        if(q==last)break;
        double khz=0;while(q<last&&digit(*q)){khz=khz*10+(*q++-'0');}
        if(q<last&&*q=='.'){++q;double place=.1;while(q<last&&digit(*q)){khz+=(*q++-'0')*place;place*=.1;}}
        if(khz<.001||khz>3000000)continue;
        Event&e=out[count++];e.utc=utc;e.hz=khz*1000.0;e.search=false;
        cp(e.station,sizeof(e.station),station);cp(e.mode,sizeof(e.mode),modebuf);cp(e.remarks,sizeof(e.remarks),mode);
    }
}
static bool event_object(Reader&r,Event*out,int&count,int cap){
    ws(r);if(r.p==r.end||*r.p++!='{')return false;ws(r);
    char summary[384]={0},iso[80]={0};
    while(r.p<r.end&&*r.p!='}'){
        char key[48];if(!str(r,key,sizeof(key)))return false;ws(r);if(r.p==r.end||*r.p++!=':')return false;
        if(eq(key,"summary")){if(!str(r,summary,sizeof(summary)))return false;}
        else if(eq(key,"start")){if(!start_object(r,iso,sizeof(iso)))return false;}
        else if(!skip(r,0))return false;
        ws(r);if(r.p<r.end&&*r.p==','){++r.p;ws(r);}else break;
    }
    if(r.p==r.end||*r.p++!='}')return false;
    i64 utc=0;if(summary[0]&&iso_utc(iso,utc))parse_summary(summary,utc,out,count,cap);
    return true;
}
static int parse(const char*json,unsigned length,Event*out,int cap){
    if(!json||!out||cap<=0||length==0||length>4*1024*1024)return -1;
    Reader r={json,json+length};ws(r);if(r.p==r.end||*r.p++!='{')return -1;
    bool found=false;int count=0;ws(r);
    while(r.p<r.end&&*r.p!='}'){
        char key[48];if(!str(r,key,sizeof(key)))return -1;ws(r);if(r.p==r.end||*r.p++!=':')return -1;
        if(eq(key,"items")){
            ws(r);if(r.p==r.end||*r.p++!='[')return -1;found=true;ws(r);
            while(r.p<r.end&&*r.p!=']'){
                if(!event_object(r,out,count,cap))return -1;
                ws(r);if(r.p<r.end&&*r.p==','){++r.p;ws(r);}else break;
            }
            if(r.p==r.end||*r.p++!=']')return -1;
        }else if(!skip(r,0))return -1;
        ws(r);if(r.p<r.end&&*r.p==','){++r.p;ws(r);}else break;
    }
    if(r.p==r.end||*r.p++!='}')return -1;
    ws(r);if(r.p!=r.end||!found)return -1;
    // Insertion sort: calendar results are usually already ordered, but this
    // also handles out-of-order API responses without allocating memory.
    for(int i=1;i<count;i++){Event key=out[i];int j=i;while(j>0&&out[j-1].utc>key.utc){out[j]=out[j-1];j--;}out[j]=key;}
    return count;
}
}
#endif

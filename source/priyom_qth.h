// Country catalog from Priyom's own /number-stations/{category} HTML tables.
// Unknown countries remain unknown; never infer country from language or prefix.
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_QTH_H
#define PRIYOM_QTH_H
namespace priyom { namespace qth {
struct Entry {char station[24];char country[48];};
static bool white(char c){return c==' '||c=='\t'||c=='\r'||c=='\n';}
static char lower(char c){return c>='A'&&c<='Z'?c+('a'-'A'):c;}
static bool equals(const char*a,const char*b){while(*a&&*b&&*a==*b){++a;++b;}return !*a&&!*b;}
static bool tag_match(const char*p,const char*end,const char*tag){
    if(p>=end||*p!='<')return false;++p;
    while(*tag&&p<end){if(lower(*p)!=*tag)return false;++p;++tag;}
    if(*tag)return false;
    return p<end&&(white(*p)||*p=='>'||*p=='/');
}
static const char*seek_tag(const char*p,const char*end,const char*tag){
    for(;p<end;p++)if(*p=='<'&&tag_match(p,end,tag))return p;
    return end;
}
static const char*after_tag(const char*p,const char*end){while(p<end&&*p!='>')++p;return p<end?p+1:end;}
static bool alpha(char c){return (c>='A'&&c<='Z')||(c>='a'&&c<='z');}
static bool digit(char c){return c>='0'&&c<='9';}
static void strip_cell(const char*start,const char*end,char*out,unsigned cap){
    unsigned n=0;bool pending=false;
    for(const char*p=start;p<end&&n+1<cap;){
        if(*p=='<'){p=after_tag(p,end);pending=n>0;continue;}
        if(*p=='&'){
            if(end-p>=6&&p[1]=='n'&&p[2]=='b'&&p[3]=='s'&&p[4]=='p'&&p[5]==';'){p+=6;pending=n>0;continue;}
            if(end-p>=5&&p[1]=='a'&&p[2]=='m'&&p[3]=='p'&&p[4]==';')p+=5;
            else if(end-p>=4&&p[1]=='#'){
                const char*q=p+2;int v=0;while(q<end&&digit(*q)){v=v*10+*q++-'0';if(v>255)break;}
                if(q<end&&*q==';'&&v>=32&&v<=127){p=q+1;if(pending&&n+1<cap){out[n++]=' ';pending=false;}out[n++]=(char)v;continue;}
                ++p;continue;
            }else {++p;continue;}
            if(pending&&n+1<cap){out[n++]=' ';pending=false;}out[n++]='&';continue;
        }
        char c=*p++;
        if(white(c)){pending=n>0;continue;}
        if(pending&&n+1<cap){out[n++]=' ';pending=false;}
        out[n++]=c;
    }
    while(n&&out[n-1]==' ')--n;
    out[n]=0;
}
static bool station_id(const char*s){
    int n=0;bool number=false;
    for(;*s;s++,n++){if(n>=20||!((alpha(*s))||digit(*s)))return false;if(digit(*s))number=true;}
    // Digital modes XPA/XPB/XP do not contain digits but are valid IDs.
    return (n>=2&&number)||(n>=2&&n<=4&&s[-n]=='X');
}
static bool valid_country(const char*country){
    // Priyom tables sometimes omit a Country cell entirely: then the HTML
    // next cell contains counterpart station IDs, NOT a country. Reject those.
    unsigned letters=0;bool has_lowercase=false;
    if(!country||!country[0])return false;
    for(const char*p=country;*p;p++){
        const char ch=*p;
        if(digit(ch)||ch==','||ch=='/'||ch==';'||ch=='<'||ch=='>')return false;
        if(alpha(ch)){++letters;if(ch>='a'&&ch<='z')has_lowercase=true;}
        else if(!white(ch)&&ch!='-'&&ch!='\''&&ch!='('&&ch!=')'&&ch!='?'&&ch!='*')return false;
    }
    return letters>=3 && has_lowercase && !equals(country,"Unknown");
}
static void set(Entry*out,int&count,int cap,const char*station,const char*country){
    if(!station_id(station)||!country[0])return;
    char clean[48];int n=0;
    for(;country[n]&&n<46;n++)clean[n]=country[n];clean[n]=0;
    while(n&&(clean[n-1]=='*'||white(clean[n-1])))clean[--n]=0;
    if(!n||n>=46||!valid_country(clean))return;
    for(int i=0;i<count;i++)if(equals(out[i].station,station)){
        // Last nonempty value wins only if it is supplied by Priyom.
        for(int j=0;j<=n;j++)out[i].country[j]=clean[j];return;
    }
    if(count>=cap)return;
    unsigned j=0;for(;station[j]&&j<23;j++)out[count].station[j]=station[j];out[count].station[j]=0;
    for(j=0;clean[j]&&j<47;j++)out[count].country[j]=clean[j];out[count].country[j]=0;
    ++count;
}
static bool starts_cell(const char*p,const char*end){return tag_match(p,end,"td")||tag_match(p,end,"th");}
static int country_header_index(const char*p,const char*end){
    int col=0;
    while(p<end){
        while(p<end&&(*p!='<'||!starts_cell(p,end)))++p;
        if(p>=end)break;
        const char*body=after_tag(p,end);
        const char*close=seek_tag(body,end,"/th");
        const char*close_td=seek_tag(body,end,"/td");
        if(close_td<close)close=close_td;
        if(close>=end)break;
        char heading[40]={0};strip_cell(body,close,heading,sizeof(heading));
        const char expected[]="Country";
        int j=0;while(expected[j]&&heading[j]&&lower(expected[j])==lower(heading[j]))++j;
        if(!expected[j]&&!heading[j])return col;
        ++col;p=after_tag(close,end);
    }
    return -1;
}
static int parse_index(const char*html,unsigned length,int countryColumn,Entry*out,int&count,int cap){
    if(!html||length<64||length>1024*1024||!out||countryColumn<1||countryColumn>3)return 0;
    const char*end=html+length;const char*table=html;int added=0;
    while((table=seek_tag(table,end,"table"))<end){
        const char*start=after_tag(table,end);
        const char*table_end=seek_tag(start,end,"/table");if(table_end==end)break;
        // Parse only Priyom tables that explicitly have a Country heading.
        // Unrelated tables on the page cannot accidentally contribute a QTH.
        const char*header=seek_tag(start,table_end,"tr");
        const char*header_end=header<table_end?seek_tag(after_tag(header,table_end),table_end,"/tr"):table_end;
        if(header_end==table_end){table=after_tag(table_end,end);continue;}
        // Derive the index from Priyom's ACTUAL headings, rather than assuming
        // digital and voice pages always use the same layout.
        const int real_country_col=country_header_index(header,header_end);
        if(real_country_col<1||real_country_col>4){table=after_tag(table_end,end);continue;}
        const char*p=after_tag(header_end,table_end);
        while((p=seek_tag(p,table_end,"tr"))<table_end){
            p=after_tag(p,table_end);const char*rowend=seek_tag(p,table_end,"/tr");if(rowend==table_end)break;
            const char*cell=p;int col=0;char station[48]={0},country[72]={0};
            while(cell<rowend){
                while(cell<rowend&&(*cell!='<'||!starts_cell(cell,rowend)))++cell;
                if(cell>=rowend)break;
                const char*body=after_tag(cell,rowend);const char*close=seek_tag(body,rowend,"/td");
                const char*close_th=seek_tag(body,rowend,"/th");if(close_th<close)close=close_th;
                if(close>=rowend)break;
                if(col==0)strip_cell(body,close,station,sizeof(station));
                if(col==real_country_col)strip_cell(body,close,country,sizeof(country));
                ++col;cell=after_tag(close,rowend);
            }
            int before=count;
            if(col>real_country_col&&station_id(station))set(out,count,cap,station,country);
            added+=count-before;p=after_tag(rowend,table_end);
        }
        table=after_tag(table_end,end);
    }
    return added;
}
// Country from Priyom operators list for modes that have an empty Country
// field on their own index (e.g. XPA2), without inventing a location.
static const char*find(const Entry*,int,const char*); // forward declaration
static void add_modes(Entry*out,int&count,int cap,const char*list,const char*country){
    for(const char*p=list;*p;){
        while(*p&&!alpha(*p))++p;
        if(!*p)break;
        char token[24]={0};int n=0;
        while((alpha(*p)||digit(*p))&&n<23)token[n++]=*p++;
        while(alpha(*p)||digit(*p))++p; // discard oversized names
        if(station_id(token)&&!find(out,count,token))set(out,count,cap,token,country);
    }
}
static int parse_operators(const char*html,unsigned length,Entry*out,int&count,int cap){
    if(!html||!out||length<64||length>1024*1024)return 0;
    const char*end=html+length;const char*table=html;
    int before=count;
    while((table=seek_tag(table,end,"table"))<end){
        const char*start=after_tag(table,end);
        const char*table_end=seek_tag(start,end,"/table");if(table_end==end)break;
        const char*header=seek_tag(start,table_end,"tr");
        const char*header_end=header<table_end?seek_tag(after_tag(header,table_end),table_end,"/tr"):table_end;
        if(header_end==table_end||country_header_index(header,header_end)!=1){table=after_tag(table_end,end);continue;}
        const char*row=after_tag(header_end,table_end);
        while((row=seek_tag(row,table_end,"tr"))<table_end){
            const char*cell=after_tag(row,table_end);
            const char*rowend=seek_tag(cell,table_end,"/tr");if(rowend==table_end)break;
            int col=0;char country[72]={0},active[400]={0},inactive[400]={0};
            while(cell<rowend){
                while(cell<rowend&&(*cell!='<'||!starts_cell(cell,rowend)))++cell;
                if(cell>=rowend)break;
                const char*body=after_tag(cell,rowend);
                const char*close=seek_tag(body,rowend,"/td");
                const char*close_th=seek_tag(body,rowend,"/th");if(close_th<close)close=close_th;
                if(close>=rowend)break;
                if(col==1)strip_cell(body,close,country,sizeof(country));
                if(col==2)strip_cell(body,close,active,sizeof(active));
                if(col==3)strip_cell(body,close,inactive,sizeof(inactive));
                ++col;cell=after_tag(close,rowend);
            }
            if(valid_country(country)){add_modes(out,count,cap,active,country);add_modes(out,count,cap,inactive,country);}
            row=after_tag(rowend,table_end);
        }
        table=after_tag(table_end,end);
    }
    return count-before;
}
static const char*find(const Entry*entries,int count,const char*station){
    for(int i=0;i<count;i++)if(equals(entries[i].station,station))return entries[i].country;
    return 0;
}
// The ISO code is only for flag display. Country text ALWAYS comes from Priyom.
struct Code {const char*country;const char*iso;};
static const char*country_code(const char*country){
    static const Code c[]={
        {"Poland","PL"},{"Russia","RU"},{"Ukraine","UA"},{"United States","US"},
        {"United Kingdom(?)","GB"},{"Czechia","CZ"},
        {"United Kingdom","GB"},{"Germany","DE"},{"Austria","AT"},{"Romania","RO"},
        {"Taiwan","TW"},{"China","CN"},{"North Korea","KP"},{"South Korea","KR"},
        {"Vietnam","VN"},{"Egypt","EG"},{"Cuba","CU"},{"Israel","IL"},
        {"Bulgaria","BG"},{"Sweden","SE"},{"France","FR"},{"Spain","ES"},
        {"Italy","IT"},{"Belarus","BY"},{"Serbia","RS"},{"Czech Republic","CZ"},
        {"Moldova","MD"},{"Hungary","HU"},{"Australia","AU"},{"Canada","CA"},
        {"Iran","IR"},{"India","IN"},{"Turkey","TR"},{"Japan","JP"},
        {"Slovakia","SK"},{"Lithuania","LT"},{"Latvia","LV"},{"Estonia","EE"}
    };
    if(!country)return 0;
    for(unsigned i=0;i<sizeof(c)/sizeof(c[0]);i++)if(equals(c[i].country,country))return c[i].iso;
    return 0;
}
// Text fallback for platforms without graphical flags. No unsupported emoji.
static void label(const char*country,bool compact,char*out,unsigned cap){
    if(!cap)return;
    const char*iso=country_code(country);
    const char*value=(country&&country[0])?(compact&&iso?iso:country):"-";
    unsigned n=0;while(value[n]&&n+1<cap){out[n]=value[n];++n;}out[n]=0;
}
}} // namespace priyom::qth
#endif

// UTC auto-tuning logic, portable for deterministic unit tests.
#ifndef PRIYOM_SCHEDULER_H
#define PRIYOM_SCHEDULER_H
#include "priyom_parser.h"
namespace priyom {
struct Key {i64 utc; i64 hz; char station[24]; char mode[24];};
static Key key_of(const Event&e){Key k={};k.utc=e.utc;k.hz=(i64)(e.hz+0.5);cp(k.station,sizeof(k.station),e.station);cp(k.mode,sizeof(k.mode),e.mode);return k;}
static bool key_equal(const Key&a,const Key&b){return a.utc==b.utc&&a.hz==b.hz&&eq(a.station,b.station)&&eq(a.mode,b.mode);}
static bool eligible(const Event&e,i64 now){return !e.search&&e.hz>0&&now>=e.utc-10&&now<e.utc;}
static int choose_next(const Event*events,int count,const Key*armed,int armed_count,const Key*fired,int fired_count,i64 now){
    int best=-1;
    for(int i=0;i<count;i++){
        if(!eligible(events[i],now))continue;
        Key k=key_of(events[i]);bool a=false,done=false;
        for(int j=0;j<armed_count;j++)if(key_equal(armed[j],k)){a=true;break;}
        if(!a)continue;
        for(int j=0;j<fired_count;j++)if(key_equal(fired[j],k)){done=true;break;}
        if(done)continue;
        if(best<0||events[i].utc<events[best].utc)best=i;
    }
    return best;
}
}
#endif
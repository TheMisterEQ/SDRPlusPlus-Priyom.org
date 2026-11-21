// URL routing for Priyom station pages and station-specific schedules.
// Pure, allocation-free C++ helper; shared by the SDR++ UI and native tests.
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_LINKS_H
#define PRIYOM_LINKS_H
namespace priyom {
static bool build_station_url(const char* station, bool schedule, char* out, unsigned cap) {
    if (!station || !out || cap == 0) return false;
    const char base[] = "https://priyom.org/number-stations/";
    unsigned idlen = 0;
    for (; station[idlen]; ++idlen) {
        char c = station[idlen];
        if (idlen >= 22 || !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) {
            out[0] = 0;
            return false;
        }
    }
    if (!idlen) { out[0] = 0; return false; }
    const char* category = "digital/";
    if (idlen >= 3 && (station[0]=='F' || station[0]=='P') && station[1]=='0' && station[2]=='3') {
        category = "operators/polish-11/digital-modes";
        idlen = 0; // F03 and P03 are part of the shared Polish 11 schedule.
    } else {
        switch (station[0]) {
            case 'E': category = "english/"; break;
            case 'G': category = "german/"; break;
            case 'S': category = "slavic/"; break;
            case 'V': category = "other/"; break;
            case 'M': category = "morse/"; break;
            default: break;
        }
    }
    unsigned pos = 0;
    const char* parts[] = {base, category};
    for (unsigned k=0; k<2; ++k) {
        for (const char* p=parts[k]; *p; ++p) {
            if (pos+1>=cap) { out[0]=0; return false; }
            out[pos++]=*p;
        }
    }
    for (unsigned i=0; i<idlen; ++i) {
        char c = station[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
        if (pos+1>=cap) { out[0]=0; return false; }
        out[pos++]=c;
    }
    if (schedule) {
        const char suffix[] = "/schedule";
        for (const char* p=suffix; *p; ++p) {
            if (pos+1>=cap) { out[0]=0; return false; }
            out[pos++]=*p;
        }
    }
    out[pos]=0;
    return true;
}
}
#endif

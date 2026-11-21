// Per-event UTC countdown for Priyom. Pure, allocation-free C++ helper.
// SPDX-License-Identifier: MIT
#ifndef PRIYOM_COUNTDOWN_H
#define PRIYOM_COUNTDOWN_H
#include "priyom_parser.h"
namespace priyom {
static void countdown_format(i64 event_utc, i64 now, char* out, unsigned cap) {
    if (!out || !cap) return;
    out[0] = 0;
    // The UI keeps recently started entries for 60 seconds; no end time is
    // provided by the Priyom calendar, so we say START, not "TRWA".
    if (event_utc <= now) {
        cp(out, cap, "START");
        return;
    }
    i64 remaining = event_utc - now;
    // Three-day calendar normally fits in two-digit hours. For unusually
    // distant events use all available hour digits rather than wrapping.
    unsigned long long hours = (unsigned long long)(remaining / 3600);
    unsigned minutes = (unsigned)((remaining / 60) % 60);
    unsigned seconds = (unsigned)(remaining % 60);
    char reverse[24]; unsigned n = 0;
    do { reverse[n++] = (char)('0' + hours % 10); hours /= 10; } while (hours && n < sizeof(reverse));
    if (n < 2) reverse[n++] = '0';
    unsigned at = 0;
    while (n) { if (at + 1 >= cap) { out[at] = 0; return; } out[at++] = reverse[--n]; }
    const char tail[6] = {':', (char)('0'+minutes/10), (char)('0'+minutes%10), ':', (char)('0'+seconds/10), (char)('0'+seconds%10)};
    for (unsigned i=0; i<6; ++i) { if (at + 1 >= cap) { out[at] = 0; return; } out[at++] = tail[i]; }
    out[at] = 0;
}
}
#endif

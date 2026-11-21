// Priyom 2.3 interface strings. Keep the actual Priyom QTH source data
// unchanged; the Polish build translates known country display names only.
#pragma once
#ifndef PRIYOM_LANG_EN
#define PRIYOM_LANG_EN 0
#endif
#if PRIYOM_LANG_EN
#define PRIYOM_REFRESH "Refresh"
#define PRIYOM_NO_UPDATE "No successful update from priyom.org"
#define PRIYOM_LAST_UPDATE "Last update from priyom.org:\n"
#define PRIYOM_LAST_FAILED "\nLast fetch attempt failed"
#define PRIYOM_AUTO_TUNE "Automatic tuning"
#define PRIYOM_TOOLTIP_MASTER "Master automatic tuning switch.\nDoes not change individual Auto selections.\nClicking a frequency still tunes manually."
#define PRIYOM_TOOLTIP_CLOCK "%s\nClick to open main Priyom.org schedule"
#define PRIYOM_SEARCH_HINT "Search: E11, USB, 3756, 3000-10000 kHz"
#define PRIYOM_HIDE_WINDOW "Hide window"
#define PRIYOM_SHOW_WINDOW "Show window"
#define PRIYOM_TOOLTIP_AUTO "Automatically tune selected transmissions"
#define PRIYOM_HEADER_STATION "Station"
#define PRIYOM_HEADER_FREQ "kHz / mode"
#define PRIYOM_HEADER_COUNTDOWN "Starts in"
#define PRIYOM_TOOLTIP_QTH "Country per Priyom.org: %s (not necessarily the transmitter site)"
#define PRIYOM_TOOLTIP_QTH_MISSING "No QTH data from Priyom.org (unknown or not yet fetched)"
#define PRIYOM_TOOLTIP_SCHEDULE "Station %s schedule at Priyom.org"
#define PRIYOM_TOOLTIP_COUNTDOWN "Countdown to transmission start (UTC)"
#define PRIYOM_WINDOW_TITLE "Priyom - UTC schedule"
#define PRIYOM_TOOLTIP_OPACITY "Window opacity"
static const char*priyom_display_country(const char*country){return country?country:"-";}
#else
#define PRIYOM_REFRESH "Odswiez"
#define PRIYOM_NO_UPDATE "Brak udanej aktualizacji z priyom.org"
#define PRIYOM_LAST_UPDATE "Ostatnia aktualizacja z priyom.org:\n"
#define PRIYOM_LAST_FAILED "\nOstatnia proba pobrania nieudana"
#define PRIYOM_AUTO_TUNE "Automatyczne strojenie"
#define PRIYOM_TOOLTIP_MASTER "Globalny wlacznik automatycznego strojenia.\nNie zmienia zaznaczonych emisji Auto.\nKlikniecie czestotliwosci nadal stroi recznie."
#define PRIYOM_TOOLTIP_CLOCK "%s\nKliknij, aby otworzyc glowny harmonogram Priyom.org"
#define PRIYOM_SEARCH_HINT "Szukaj: E11, USB, 3756, 3000-10000 kHz"
#define PRIYOM_HIDE_WINDOW "Ukryj okno"
#define PRIYOM_SHOW_WINDOW "Pokaz okno"
#define PRIYOM_TOOLTIP_AUTO "Automatyczne strojenie zaznaczonych emisji"
#define PRIYOM_HEADER_STATION "Stacja"
#define PRIYOM_HEADER_FREQ "kHz / tryb"
#define PRIYOM_HEADER_COUNTDOWN "Start za"
#define PRIYOM_TOOLTIP_QTH "Kraj wg Priyom.org: %s (niekoniecznie lokalizacja nadajnika)"
#define PRIYOM_TOOLTIP_QTH_MISSING "Brak danych QTH z Priyom.org (nieznane lub jeszcze niepobrane)"
#define PRIYOM_TOOLTIP_SCHEDULE "Harmonogram stacji %s na Priyom.org"
#define PRIYOM_TOOLTIP_COUNTDOWN "Odliczanie do rozpoczecia transmisji (UTC)"
#define PRIYOM_WINDOW_TITLE "Priyom - Harmonogram UTC"
#define PRIYOM_TOOLTIP_OPACITY "Przezroczystosc okna"
static const char*priyom_display_country(const char*country){
    if(!country)return "-";
    struct Localized{const char*english;const char*polish;};
    static constexpr Localized known[]={
        {"Poland","Polska"},{"Russia","Rosja"},{"Ukraine","Ukraina"},
        {"United States","Stany Zjednoczone"},{"United Kingdom","Wielka Brytania"},
        {"United Kingdom(?)","Wielka Brytania(?)"},
        {"Czechia","Czechy"},{"Czech Republic","Czechy"},
        {"Germany","Niemcy"},{"Austria","Austria"},{"Romania","Rumunia"},
        {"Taiwan","Tajwan"},{"China","Chiny"},{"North Korea","Korea Polnocna"},
        {"South Korea","Korea Poludniowa"},{"Vietnam","Wietnam"},
        {"Egypt","Egipt"},{"Cuba","Kuba"},{"Israel","Izrael"},
        {"Bulgaria","Bulgaria"},{"Sweden","Szwecja"},{"France","Francja"},
        {"Spain","Hiszpania"},{"Italy","Wlochy"},{"Belarus","Bialorus"},
        {"Serbia","Serbia"},{"Moldova","Moldawia"},{"Hungary","Wegry"},
        {"Australia","Australia"},{"Canada","Kanada"},{"Iran","Iran"},
        {"India","Indie"},{"Turkey","Turcja"},{"Japan","Japonia"},
        {"Slovakia","Slowacja"},{"Lithuania","Litwa"},{"Latvia","Lotwa"},
        {"Estonia","Estonia"}
    };
    for(unsigned i=0;i<sizeof(known)/sizeof(known[0]);i++){
        const char*a=country,*b=known[i].english;
        while(*a&&*b&&*a==*b){++a;++b;}
        if(!*a&&!*b)return known[i].polish;
    }
    return country; // full Priyom name if Polish translation not known
}
#endif
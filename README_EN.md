
# Priyom V2.3 — EN — Single INI & Free Resize

SDR++ 1.3.2, Windows x64. This is based on the last working V2.3 10px-margin version.

## Changes

- **Only one active configuration file:** `priyom.ini`, created **next to `sdrpp.exe`** (the SDR++ program directory), just like the Essential++ configuration style. The file stores floating window width/height, opacity, six widths for both floating and sidebar tables, global automatic tuning and individually selected auto-tune events.
- The plugin reads existing legacy settings from `%LOCALAPPDATA%\SDRpp\Priyom\` **once**, only if `priyom.ini` does not exist, and writes the unified configuration. Subsequent changes are written exclusively to `priyom.ini`; existing legacy files are left untouched for safety.
- Initial column widths remain **100 / 125 / 100 / 70 / 80 / 40 px** (Station, kHz/mode, QTH, UTC, Countdown, Auto). Default floating window size remains **542 × 320 px**, with **10 px margins** on both sides at 100% display scaling.
- A widened floating window now also widens the actual table: its QTH column grows by the same amount. The change is applied **only when the window is resized**, not continuously. Thus all column separators, including QTH, can still be adjusted manually without the adjustment being automatically undone.
- Shrinking the window below the total column width is allowed; the table provides horizontal scrolling only if genuinely necessary. There is no arbitrary 1200px column maximum or 4096px window maximum.
- The two language builds use the **same configuration format and filename**.

## Installation

1. Close SDR++.
2. Back up your existing `modules/priyom.dll`.
3. Extract this archive; copy `priyom.dll` to `modules/`, replacing the old DLL.
4. Run SDR++ and open Priyom. The `priyom.ini` file will be created in the folder containing `sdrpp.exe`.

**Important:** SDR++ needs write permission in its program directory. If installed under a protected `Program Files` directory, move the portable installation to a user-writable location or grant appropriate permissions. Do not leave multiple Priyom DLL versions in `modules`.

## Example `priyom.ini` (created automatically)

```ini
[Window]
width=542
height=320
opacity=90

[Table]
sidebar=100,125,100,70,80,40
floating=100,125,100,70,80,40

[AutoTune]
global_auto=1
; optional lines for manually selected transmissions:
; event=1795267800,6849000,E11,USB
```

The contents are plain text and can be edited with SDR++ closed. The actual auto-tune events are written by the plugin; the event above is a *format example only*.

## Source & build

`source/build.py --lang en` with Python 3, LLVM clang and lld-link. Output: `source/build_en/priyom.dll`.

No changes to Priyom network parsing, station links, scheduler, graphical flags or the Essential++ module.

Compiled the Windows x64 DLL and validated the PE exports/imports; the SDR++ core imports are unchanged. **The final UI must be confirmed in SDR++ on Windows**, which was not available for live testing here.
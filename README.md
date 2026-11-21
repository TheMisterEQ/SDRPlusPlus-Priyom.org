# Priyom for SDR++ — V2.3

**Live numbers-station schedules, one-click tuning, UTC countdowns and automatic frequency switching — directly inside SDR++.**

Priyom is an unofficial plugin for [SDR++](https://github.com/AlexandreRouma/SDRPlusPlus) that brings [Priyom.org](https://priyom.org/) transmission schedules into the receiver interface. Browse upcoming broadcasts, identify stations, tune a listed frequency with a click, and optionally arm individual transmissions for automatic tuning shortly before they begin.

> **Compatibility:** SDR++ 1.3.2 on Windows x64. Tested by compilation and binary import checks; verify runtime behavior with your own SDR++ build. SDR++ plugin compatibility can depend on the exact build.

## Features

- **Live schedule:** Retrieve upcoming numbers-station transmissions from the Priyom calendar, with manual refresh and a tooltip indicating the last successful update.
- **UTC timing:** Live UTC clock, scheduled transmission times and a per-row countdown to the next broadcast. Times shown by the plugin are UTC.
- **Search and filtering:** Find entries by station name, frequency, modulation or frequency range (for example `E11`, `USB`, `3756`, or `3000-10000`).
- **One-click tuning:** Click a frequency/mode entry to tune the currently selected SDR++ radio. Click a station name to open its Priyom page, or a UTC time to open that station's schedule.
- **Automatic tuning:** Tick **Auto** for individual transmissions. When the master **Auto** switch is enabled and the radio is ready, the plugin attempts tuning about 10 seconds before a selected transmission. The global switch does not erase individual selections.
- **QTH and flags:** Full country names and small graphical flags, sourced from Priyom.org where available. Missing or unknown country information is shown as `–` rather than guessed. **QTH indicates the country attributed to the station in Priyom; it does not necessarily identify the physical transmitter site.**
- **Two display modes:** An integrated SDR++ sidebar panel and an independently resizable floating schedule window. Press **P** to show or hide the floating window when SDR++ has keyboard focus and no text input is active.
- **Adjustable layout:** Drag the edges of all six columns to resize them. Resize the floating window freely; the table expands with the window. Adjustable opacity (20–100%).
- **Persistent settings:** A single editable `priyom.ini` file in the SDR++ application directory stores the floating window dimensions, column widths, opacity and automatic-tuning selections.
- **Efficient rendering:** Only visible schedule rows are rendered, helping keep the interface responsive.

## Interface

| Column | Function | Default width |
|---|---|---:|
| Station | Station identifier and link to the Priyom station page | 100 px |
| kHz / mode | Transmit frequency, modulation and click-to-tune | 125 px |
| QTH | Country name and flag when available | 100 px |
| UTC | Scheduled start time; click for the station schedule | 70 px |
| Starts in | Live countdown until the broadcast | 80 px |
| Auto | Arm or disarm automatic tuning for that entry | 40 px |

The total default column width is **515 px**, with a **10 px initial margin** on each side of the table at 100% display scaling. These are **defaults, not fixed limits**: window and column sizes can be changed and saved. The default floating window size is **542 × 320 px**.

## Installation

1. Close SDR++.
2. Back up any existing `modules/priyom.dll`.
3. Download the English V2.3 ZIP and extract `priyom.dll` into the SDR++ `modules` directory, replacing the old version.
4. Start SDR++ and enable/open **Priyom** from the module interface if necessary.
5. The plugin automatically creates `priyom.ini` next to `sdrpp.exe` when settings are saved.

**Important:** The SDR++ application directory must be writable to save `priyom.ini`. For portable SDR++ installations, a folder in your user directory is usually easiest. Keep only one Priyom DLL in `modules` to prevent duplicate loading.

## Configuration

Configuration is stored in **`priyom.ini` next to `sdrpp.exe`**, not scattered across multiple user-profile files. Example:

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
```

The plugin also stores individually armed transmissions under `[AutoTune]`. If no `priyom.ini` is present, V2.3 attempts to import previous settings once from `%LOCALAPPDATA%\SDRpp\Priyom\` and then uses the new file exclusively. For manual edits, close SDR++ first.

## Build from source

The release archive includes the Windows x64 DLL and the full plugin source. With Python 3 and LLVM (Clang and `lld-link`) available:

```powershell
python source/build.py --lang en
```

The resulting DLL is placed in `source/build_en/priyom.dll`. The source build depends on the SDR++ binary interface used by the supported build.

## Notes and limitations

- Priyom schedule information depends on third-party services. If a refresh fails, the plugin retains the last successfully downloaded schedule.
- QTH data is informational and may be incomplete. A country designation must not be taken as proof of transmitter location.
- Automatic tuning requires a ready SDR++ radio/source. It does not start a receiver that has not been configured.
- The plugin is **unofficial** and is not affiliated with Priyom.org or the SDR++ project.

## Credits

Schedule and station metadata: [Priyom.org](https://priyom.org/). SDR application: [SDR++](https://github.com/AlexandreRouma/SDRPlusPlus).
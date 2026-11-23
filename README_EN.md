# Priyom for SDR++ — V2.4

**Live numbers-station schedules, one-click tuning, UTC countdowns and automatic frequency switching — directly inside SDR++.**

Priyom is an unofficial plugin for [SDR++](https://github.com/AlexandreRouma/SDRPlusPlus) that brings [Priyom.org](https://priyom.org/) transmission schedules into the receiver interface. Browse upcoming broadcasts, identify stations, tune a listed frequency with a click, and optionally arm individual transmissions for automatic tuning shortly before they begin.

> **Compatibility:** SDR++ 1.3.2 on Windows x64. Tested by compilation and binary import checks; verify runtime behavior with your own SDR++ build. SDR++ plugin compatibility can depend on the exact build.

## Features

- **Live schedule:** Retrieve upcoming numbers-station transmissions from the Priyom calendar, with manual refresh and a tooltip indicating the last successful update.
- **UTC timing:** Live UTC clock, scheduled transmission times and a per-row countdown to the next broadcast. Times shown by the plugin are UTC.
- **Search and filtering:** Combine station ID, modulation, exact frequency or frequency range, Priyom QTH country and UTC start time (or time range) using commas in any order. Every condition must match (AND).
- **One-click tuning:** Click a frequency/mode entry to tune the currently selected SDR++ radio. Click a station name to open its Priyom page, or a UTC time to open that station's schedule.
- **Automatic tuning:** Tick **Auto** for individual transmissions. When the master **Auto** switch is enabled and the radio is ready, the plugin attempts tuning about 10 seconds before a selected transmission. The global switch does not erase individual selections.
- **QTH and flags:** Full country names and small graphical flags, sourced from Priyom.org where available. Missing or unknown country information is shown as `–` rather than guessed. **QTH indicates the country attributed to the station in Priyom; it does not necessarily identify the physical transmitter site.**
- **Two display modes:** An integrated SDR++ sidebar panel and an independently resizable floating schedule window. Press **P** to show or hide the floating window when SDR++ has keyboard focus and no text input is active.
- **Adjustable layout:** Drag the edges of all six columns to resize them. Resize the floating window freely; the table expands with the window. Adjustable opacity (20–100%).
- **Persistent settings:** A single editable `priyom.ini` file in the SDR++ application directory stores the floating window dimensions, column widths, opacity and automatic-tuning selections.
- **Efficient rendering:** Only visible schedule rows are rendered, helping keep the interface responsive.

## Search syntax

Type filters into the search field in the sidebar or floating window. Separate conditions with **commas**; their order does not matter. All conditions are combined using **AND**.

| Input | Matches |
|---|---|
| `M12` | Station name / identifier |
| `CW` | Modulation |
| `10446` or `10446kHz` | Frequency (a `kHz` suffix makes it an exact frequency match) |
| `3000-10000 kHz` | Inclusive frequency range in kHz |
| `Poland` | The country attributed to a station by Priyom.org, in English |
| `16:30` | Transmissions starting at 16:30 **UTC** |
| `16:30-17:00` | Transmissions starting between 16:30 and 17:00 **UTC**, inclusive |
| `M12, CW, 10446kHz, 16:30-17:00` | All four conditions must match; any order is valid |
| `M12, Poland, 16:30-17:00` | Station, QTH country and UTC time together |

Single hours and ranges are matched against the **transmission start time**, not the current clock or the remaining countdown. A time range that crosses midnight (for example `23:30-01:00`) is supported.

Country names come exclusively from Priyom's QTH metadata. If that information is unavailable, no country is invented; the matching table refreshes automatically when QTH information arrives. The English DLL uses English country names (for example `Poland`); the separate Polish DLL accepts Polish country names (for example `Polska`). Existing space-separated filtering remains available for simple station/mode/frequency searches.

## Interface

| Column | Function |
|---|---|
| Station | Station identifier and link to the Priyom station page |
| kHz / mode | Transmit frequency, modulation and click-to-tune |
| QTH | Country name and flag when available |
| UTC | Scheduled start time; click for the station schedule |
| Starts in | Live countdown until the broadcast |
| Auto | Arm or disarm automatic tuning for that entry |

The table and floating window can be resized freely, with layout preferences saved automatically.

## Installation

1. Close SDR++.
2. Back up any existing `modules/priyom.dll`.
3. Download the English V2.4 ZIP and extract `priyom.dll` into the SDR++ `modules` directory, replacing the old version.
4. Start SDR++ and enable/open **Priyom** from the module interface if necessary.
5. The plugin automatically creates `priyom.ini` next to `sdrpp.exe` when settings are saved.

**Important:** The SDR++ application directory must be writable to save `priyom.ini`. For portable SDR++ installations, a folder in your user directory is usually easiest. Keep only one Priyom DLL in `modules` to prevent duplicate loading.

## Configuration

Configuration is stored in **`priyom.ini` next to `sdrpp.exe`**, not scattered across multiple user-profile files. It contains window and table preferences, opacity and automatic-tuning settings.

The plugin also stores individually armed transmissions under `[AutoTune]`. If no `priyom.ini` is present, V2.4 attempts to import previous settings once from `%LOCALAPPDATA%\SDRpp\Priyom\` and then uses the new file exclusively. For manual edits, close SDR++ first.

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
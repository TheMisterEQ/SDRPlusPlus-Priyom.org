// Priyom SDR++ plugin v2.3 load-fix - Windows x64, SDR++ 1.3.2 nightly (2026-11-18)
// Independent of Essential++; does not patch the SDR++ core or toolbar.
// Priyom calendar protocol: https://github.com/priyom/calendar-web-viewer/blob/master/src/fetch-priyom.js
// SPDX-License-Identifier: MIT
#define CORE_ALIAS(sym) __asm__(sym)
#define DLLIMPORT extern "C" __declspec(dllimport)
#define EXPORT extern "C" __declspec(dllexport)
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef decltype(sizeof(0)) usize;
struct ImVec2 {float x,y;ImVec2(float X=0,float Y=0):x(X),y(Y){}};
struct ImDrawList;
namespace ModuleManager {
 struct ModuleInfo_t {const char*name;const char*description;const char*author;const int versionMajor,versionMinor,versionBuild,maxInstances;};
 class Instance {public:virtual ~Instance(){};virtual void postInit()=0;virtual void enable()=0;virtual void disable()=0;virtual bool isEnabled()=0;};
}
struct alignas(8) CoreString {u8 bytes[32];};
struct ContextHook {u32 HookId;int Type;u32 Owner;void(*Callback)(void*,ContextHook*);void*UserData;};
static_assert(sizeof(CoreString)==32&&sizeof(ContextHook)==32,"SDR++/ImGui x64 ABI");

DLLIMPORT u8 core_waterfall[] CORE_ALIAS("waterfall");
DLLIMPORT u8 core_mod_com[] CORE_ALIAS("modComManager");
DLLIMPORT u8 core_vfo_manager[] CORE_ALIAS("vfoManager");
DLLIMPORT u8 core_menu[] CORE_ALIAS("menu");
DLLIMPORT void* core_stringCopy(void*,const void*) CORE_ALIAS("??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QEAA@AEBV01@@Z");
DLLIMPORT void* core_stringFromText(void*,const char*) CORE_ALIAS("??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QEAA@QEBD@Z");
DLLIMPORT void core_stringDestroy(void*) CORE_ALIAS("??1?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QEAA@XZ");
DLLIMPORT void menu_register(void*,void*,void(*)(void*),void*,ModuleManager::Instance*) CORE_ALIAS("?registerEntry@Menu@@QEAAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@P6AXPEAX@Z1PEAVInstance@ModuleManager@@@Z");
DLLIMPORT void menu_remove(void*,void*) CORE_ALIAS("?removeEntry@Menu@@QEAAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
DLLIMPORT bool com_exists(void*,void*) CORE_ALIAS("?interfaceExists@ModuleComManager@@QEAA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
DLLIMPORT void* com_moduleName(void*,void*,void*) CORE_ALIAS("?getModuleName@ModuleComManager@@QEAA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V23@@Z");
DLLIMPORT bool com_call(void*,void*,int,void*,void*) CORE_ALIAS("?callInterface@ModuleComManager@@QEAA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@HPEAX1@Z");
DLLIMPORT void core_tune(int,void*,double) CORE_ALIAS("?tune@tuner@@YAXHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@N@Z");
DLLIMPORT double wf_getCenterFrequency(void*) CORE_ALIAS("?getCenterFrequency@WaterFall@ImGui@@QEAANXZ");
DLLIMPORT void** wf_vfo_index(void*,void*) CORE_ALIAS("??A?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVWaterfallVFO@ImGui@@U?$less@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEAVWaterfallVFO@ImGui@@@std@@@2@@std@@QEAAAEAPEAVWaterfallVFO@ImGui@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@@Z");
DLLIMPORT void* ui_GetContext() CORE_ALIAS("?GetCurrentContext@ImGui@@YAPEAUImGuiContext@@XZ");
DLLIMPORT const char* ui_GetVersion() CORE_ALIAS("?GetVersion@ImGui@@YAPEBDXZ");
DLLIMPORT u32 ui_AddHook(void*,const ContextHook*) CORE_ALIAS("?AddContextHook@ImGui@@YAIPEAUImGuiContext@@PEBUImGuiContextHook@@@Z");
DLLIMPORT void ui_RemoveHook(void*,u32) CORE_ALIAS("?RemoveContextHook@ImGui@@YAXPEAUImGuiContext@@I@Z");
DLLIMPORT bool ui_Begin(const char*,bool*,int) CORE_ALIAS("?Begin@ImGui@@YA_NPEBDPEA_NH@Z");
DLLIMPORT void ui_End() CORE_ALIAS("?End@ImGui@@YAXXZ");
DLLIMPORT void ui_SetNextWindowPos(const ImVec2&,int,const ImVec2&) CORE_ALIAS("?SetNextWindowPos@ImGui@@YAXAEBUImVec2@@H0@Z");
DLLIMPORT void ui_SetNextWindowSize(const ImVec2&,int) CORE_ALIAS("?SetNextWindowSize@ImGui@@YAXAEBUImVec2@@H@Z");
DLLIMPORT ImVec2 ui_GetContentRegionAvail() CORE_ALIAS("?GetContentRegionAvail@ImGui@@YA?AUImVec2@@XZ");
DLLIMPORT ImVec2 ui_GetWindowPos() CORE_ALIAS("?GetWindowPos@ImGui@@YA?AUImVec2@@XZ");
DLLIMPORT ImVec2 ui_GetWindowSize() CORE_ALIAS("?GetWindowSize@ImGui@@YA?AUImVec2@@XZ");
DLLIMPORT void ui_SetNextWindowSizeConstraints(const ImVec2&,const ImVec2&,void*,void*) CORE_ALIAS("?SetNextWindowSizeConstraints@ImGui@@YAXAEBUImVec2@@0P6AXPEAUImGuiSizeCallbackData@@@ZPEAX@Z");
DLLIMPORT bool ui_Button(const char*,const ImVec2&) CORE_ALIAS("?Button@ImGui@@YA_NPEBDAEBUImVec2@@@Z");
DLLIMPORT bool ui_Checkbox(const char*,bool*) CORE_ALIAS("?Checkbox@ImGui@@YA_NPEBDPEA_N@Z");
DLLIMPORT bool ui_Selectable(const char*,bool,int,const ImVec2&) CORE_ALIAS("?Selectable@ImGui@@YA_NPEBD_NHAEBUImVec2@@@Z");
DLLIMPORT void ui_SameLine(float,float) CORE_ALIAS("?SameLine@ImGui@@YAXMM@Z");
DLLIMPORT void ui_Separator() CORE_ALIAS("?Separator@ImGui@@YAXXZ");
DLLIMPORT void ui_TextUnformatted(const char*,const char*) CORE_ALIAS("?TextUnformatted@ImGui@@YAXPEBD0@Z");
DLLIMPORT void ui_TextColored(const struct ImVec4&,const char*,...) CORE_ALIAS("?TextColored@ImGui@@YAXAEBUImVec4@@PEBDZZ");
DLLIMPORT bool ui_BeginTable(const char*,int,int,const ImVec2&,float) CORE_ALIAS("?BeginTable@ImGui@@YA_NPEBDHHAEBUImVec2@@M@Z");
DLLIMPORT void ui_EndTable() CORE_ALIAS("?EndTable@ImGui@@YAXXZ");
DLLIMPORT void ui_TableSetupColumn(const char*,int,float,u32) CORE_ALIAS("?TableSetupColumn@ImGui@@YAXPEBDHMI@Z");
DLLIMPORT void ui_TableHeadersRow() CORE_ALIAS("?TableHeadersRow@ImGui@@YAXXZ");
DLLIMPORT void ui_TableNextRow(int,float) CORE_ALIAS("?TableNextRow@ImGui@@YAXHM@Z");
DLLIMPORT bool ui_TableNextColumn() CORE_ALIAS("?TableNextColumn@ImGui@@YA_NXZ");
// V2.3 added five optional ImGui imports. Importing any unavailable export
// in the PE import table prevents Windows LoadLibrary from loading Priyom at all
// (error 127) even if the feature isn't used. Resolve these at runtime instead.
using FnTableColumnWidth = float(*)(int);
using FnCursorScreenPos = ImVec2(*)();
using FnWindowDrawList = ImDrawList*(*)();
using FnDummy = void(*)(const ImVec2&);
using FnAddRectFilled = void(*)(ImDrawList*,const ImVec2&,const ImVec2&,u32,float,int);
using FnGetCursorPosX = float(*)();
using FnSetCursorPosX = void(*)(float);
static FnGetCursorPosX g_fn_get_cursor_x=nullptr;
static FnSetCursorPosX g_fn_set_cursor_x=nullptr;
static FnTableColumnWidth g_fn_column_width=nullptr;
static FnCursorScreenPos g_fn_cursor_pos=nullptr;
static FnWindowDrawList g_fn_draw_list=nullptr;
static FnDummy g_fn_dummy=nullptr;
static FnAddRectFilled g_fn_rect=nullptr;
static bool optional_flag_drawing_available(){
    return g_fn_cursor_pos && g_fn_draw_list && g_fn_dummy && g_fn_rect;
}

DLLIMPORT void ui_PushID(int) CORE_ALIAS("?PushID@ImGui@@YAXH@Z");
DLLIMPORT void ui_PopID() CORE_ALIAS("?PopID@ImGui@@YAXXZ");
DLLIMPORT void ui_SetNextItemWidth(float) CORE_ALIAS("?SetNextItemWidth@ImGui@@YAXM@Z");

DLLIMPORT ImVec2 ui_GetMousePos() CORE_ALIAS("?GetMousePos@ImGui@@YA?AUImVec2@@XZ");
DLLIMPORT void* ui_GetIO() CORE_ALIAS("?GetIO@ImGui@@YAAEAUImGuiIO@@XZ");
DLLIMPORT int ui_GetFrameCount() CORE_ALIAS("?GetFrameCount@ImGui@@YAHXZ");
DLLIMPORT bool ui_IsItemDeactivatedAfterEdit() CORE_ALIAS("?IsItemDeactivatedAfterEdit@ImGui@@YA_NXZ");
DLLIMPORT bool ui_IsKeyPressed(int,bool) CORE_ALIAS("?IsKeyPressed@ImGui@@YA_NH_N@Z");
DLLIMPORT bool ui_IsAnyItemActive() CORE_ALIAS("?IsAnyItemActive@ImGui@@YA_NXZ");
DLLIMPORT bool ui_InputTextWithHint(const char*,const char*,char*,usize,int,int(*)(void*),void*) CORE_ALIAS("?InputTextWithHint@ImGui@@YA_NPEBD0PEAD_KHP6AHPEAUImGuiInputTextCallbackData@@@ZPEAX@Z");
DLLIMPORT bool ui_IsMouseDown(int) CORE_ALIAS("?IsMouseDown@ImGui@@YA_NH@Z");
DLLIMPORT bool ui_SliderFloat(const char*,float*,float,float,const char*,int) CORE_ALIAS("?SliderFloat@ImGui@@YA_NPEBDPEAMMM0H@Z");
DLLIMPORT void ui_PushStyleVarFloat(int,float) CORE_ALIAS("?PushStyleVar@ImGui@@YAXHM@Z");
DLLIMPORT void ui_PopStyleVar(int) CORE_ALIAS("?PopStyleVar@ImGui@@YAXH@Z");
DLLIMPORT bool ui_IsItemHovered(int) CORE_ALIAS("?IsItemHovered@ImGui@@YA_NH@Z");
DLLIMPORT void ui_SetTooltip(const char*,...) CORE_ALIAS("?SetTooltip@ImGui@@YAXPEBDZZ");
struct ImGuiListClipper { int DisplayStart,DisplayEnd,ItemsCount;float ItemsHeight,StartPosY;void* TempData; };
static_assert(sizeof(ImGuiListClipper)==32,"ImGui 1.87 clipper ABI");
DLLIMPORT void ui_ClipperCtor(ImGuiListClipper*) CORE_ALIAS("??0ImGuiListClipper@@QEAA@XZ");
DLLIMPORT void ui_ClipperDtor(ImGuiListClipper*) CORE_ALIAS("??1ImGuiListClipper@@QEAA@XZ");
DLLIMPORT void ui_ClipperBegin(ImGuiListClipper*,int,float) CORE_ALIAS("?Begin@ImGuiListClipper@@QEAAXHM@Z");
DLLIMPORT bool ui_ClipperStep(ImGuiListClipper*) CORE_ALIAS("?Step@ImGuiListClipper@@QEAA_NXZ");
extern "C" void* __cdecl malloc(usize);
extern "C" void __cdecl free(void*);

// WinAPI imports. Network I/O happens exclusively on a worker thread.
struct WinFileTime {u32 lo,hi;};
struct WinSystemTime {unsigned short year,month,dayOfWeek,day,hour,minute,second,milliseconds;};
DLLIMPORT void __stdcall GetSystemTimeAsFileTime(WinFileTime*);
DLLIMPORT void __stdcall GetSystemTime(WinSystemTime*);
DLLIMPORT void* __stdcall GetModuleHandleA(const char*);
DLLIMPORT u32 __stdcall GetModuleFileNameA(void*,char*,u32);
DLLIMPORT void* __stdcall GetProcAddress(void*,const char*);
DLLIMPORT u32 __stdcall GetEnvironmentVariableA(const char*,char*,u32);
DLLIMPORT int __stdcall CreateDirectoryA(const char*,void*);
DLLIMPORT void* __stdcall CreateFileA(const char*,u32,u32,void*,u32,u32,void*);
DLLIMPORT int __stdcall ReadFile(void*,void*,u32,u32*,void*);
DLLIMPORT int __stdcall WriteFile(void*,const void*,u32,u32*,void*);
DLLIMPORT int __stdcall CloseHandle(void*);
DLLIMPORT void* __stdcall CreateThread(void*,usize,u32(__stdcall*)(void*),void*,u32,u32*);
DLLIMPORT u32 __stdcall WaitForSingleObject(void*,u32);
DLLIMPORT void __stdcall Sleep(u32);
// x64 Windows does NOT export InterlockedExchange/InterlockedCompareExchange
// from KERNEL32.dll. They must be compiler intrinsics (the old import
// caused LoadLibraryA to fail with ERROR_PROC_NOT_FOUND / error 127).
// Sequentially consistent atomics preserve the required full memory barrier.
static long InterlockedExchange(volatile long* p, long value) {
    return __atomic_exchange_n(p, value, __ATOMIC_SEQ_CST);
}
static long InterlockedCompareExchange(volatile long* p, long value, long expected) {
    __atomic_compare_exchange_n(p, &expected, value, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    return expected;
}
DLLIMPORT void __stdcall AcquireSRWLockExclusive(void*);
DLLIMPORT void __stdcall ReleaseSRWLockExclusive(void*);
DLLIMPORT void __stdcall AcquireSRWLockShared(void*);
DLLIMPORT void __stdcall ReleaseSRWLockShared(void*);
DLLIMPORT void* __stdcall ShellExecuteA(void*,const char*,const char*,const char*,const char*,int);
DLLIMPORT void* __stdcall WinHttpOpen(const wchar_t*,u32,const wchar_t*,const wchar_t*,u32);
DLLIMPORT void* __stdcall WinHttpConnect(void*,const wchar_t*,unsigned short,u32);
DLLIMPORT void* __stdcall WinHttpOpenRequest(void*,const wchar_t*,const wchar_t*,const wchar_t*,const wchar_t*,const wchar_t* const*,u32);
DLLIMPORT int __stdcall WinHttpSetTimeouts(void*,int,int,int,int);
DLLIMPORT int __stdcall WinHttpSendRequest(void*,const wchar_t*,u32,void*,u32,u32,usize);
DLLIMPORT int __stdcall WinHttpReceiveResponse(void*,void*);
DLLIMPORT int __stdcall WinHttpQueryHeaders(void*,u32,const wchar_t*,void*,u32*,u32*);
DLLIMPORT int __stdcall WinHttpReadData(void*,void*,u32,u32*);
DLLIMPORT int __stdcall WinHttpCloseHandle(void*);

#include "priyom_scheduler.h"
#include "priyom_links.h"
#include "priyom_countdown.h"
#include "priyom_filter.h"
#include "priyom_qth.h"
#include "priyom_flags.h"
#include "priyom_language.h"
struct ImVec4 {float x,y,z,w;};
static bool g_enabled=true,g_supported=false,g_menu_bound=false,g_float_open=false;
static char g_station_filter[96]={0};
static unsigned g_filter_revision=0;
// Global master switch: disables ONLY scheduled tuning, not individual selections
// or manual clicks. Default ON preserves v1.5 behavior for existing users.
static bool g_auto_global=true;
static void* g_context=0;static u32 g_tick_hook=0,g_window_hook=0;
static void* g_thread=0;static volatile long g_stop=0,g_force_refresh=0;
static void* g_lock=0; // SRWLOCK (SRWLOCK_INIT is zero)
static priyom::Event g_events[1024];static int g_count=0,g_fetch_state=0;
static priyom::i64 g_last_fetch=0;
static priyom::qth::Entry g_qth_catalog[256];static int g_qth_count=0;
static volatile int g_qth_generation=0;
static volatile priyom::i64 g_last_qth_fetch=0;
static priyom::Key g_armed[512];static int g_armed_count=0;
static priyom::Key g_fired[512];static int g_fired_count=0;
// No transient status strings are rendered; only schedule and compact controls.
static char g_settings_path[1024]={0}; // legacy read-only location
static char g_ini_path[1024]={0}; // sole active configuration file: next to sdrpp.exe
static void save_ini();
static bool load_ini();
static float g_floating_rect[4]={0,0,0,0};
static float g_opacity_percent=90.0f;
static char g_opacity_path[1024]={0};
static char g_auto_global_path[1024]={0};
static char g_column_width_path[1024]={0};
static char g_floating_size_path[1024]={0};
// Independent weight presets for sidebar (0) and floating window (1).
// Every column has WidthStretch and can be resized by dragging its header border.
// Full country names are preserved and the outer table ends at Auto.
// These are initial widths; dragging all column dividers remains enabled.
// Fixed *content* widths (ImGui adds its normal cell padding separately).
// ImGui adds per-cell padding and borders to the requested content widths.
static float g_column_widths[2][6]={{100,125,100,70,80,40},{100,125,100,70,80,40}};
static float g_column_prev[2][6]={{0}};
static bool g_column_dirty=false;
// Remember the floating window size across SDR++ restarts. The persisted
// geometry is independent of the ImGui window title and of the PL/EN build.
// Desired visible grid: six column widths + seven 1px boundaries = 522px.
// Border-to-grid margins: 10px left and 10px right, at 100% UI scale.
static ImVec2 g_floating_size(542.0f,320.0f);
static ImVec2 g_last_floating_size(0.0f,0.0f);
static bool g_floating_size_observed=false,g_floating_size_dirty=false;
// Apply the saved/default width once with ImGuiCond_Always to override old
// imgui.ini layouts. Subsequent frames permit user resizing as normal.
static bool g_apply_floating_size_first_frame=true;

// Both panels share one UTC clock cache, formatted at most once per second.
static priyom::i64 g_utc_clock_second=-1;
static char g_utc_clock_text[24]="UTC --:--:--";
static char g_utc_clock_full[48]={0};
// ImGuiIO layout for SDR++ 1.3.2 (unchanged in 2026-11-18 nightly):
// MousePos=0xD04, MouseWheel=0xD14. Check MousePos against GetMousePos()
// before writing; do not touch VFO or re-tune as an input workaround.
static constexpr usize IO_MOUSE_POS=0xD04, IO_MOUSE_WHEEL=0xD14;
static bool g_overlay_drag=false,g_overlay_masked=false,g_after_window_mask=false;
static ImVec2 g_saved_mouse;
static float g_saved_wheel=0;
static int g_mask_frame=-1;
static u32 g_input_hook=0,g_restore_hook=0;
static bool g_opacity_dirty=false;
static volatile int g_generation=0;
static void restore_overlay_mouse(bool restore_wheel){
    if(!g_overlay_masked&&!g_after_window_mask)return;
    u8*io=(u8*)ui_GetIO();
    if(io&&g_mask_frame==ui_GetFrameCount()){
        *(ImVec2*)(io+IO_MOUSE_POS)=g_saved_mouse;
        if(restore_wheel)*(float*)(io+IO_MOUSE_WHEEL)=g_saved_wheel;
    }
    g_overlay_masked=false;g_after_window_mask=false;
}
static bool in_floating_rect(ImVec2 p){
    return g_float_open&&g_floating_rect[2]>0&&g_floating_rect[3]>0&&
        p.x>=g_floating_rect[0]&&p.x<=g_floating_rect[0]+g_floating_rect[2]&&
        p.y>=g_floating_rect[1]&&p.y<=g_floating_rect[1]+g_floating_rect[3];
}
// Runs AFTER ImGui's own hover, scrolling and window-drag processing,
// but BEFORE SDR++ waterfall and Essential++ read mouse coordinates.
// Thus the floating window keeps normal interactions, while the spectrum
// underneath cannot respond to the same click/wheel/drag.
static void input_begin_frame(void*,ContextHook*){
    restore_overlay_mouse(false); // defensive recovery after an interrupted frame
    if(!g_supported||!g_enabled||!g_float_open){g_overlay_drag=false;return;}
    ImVec2 mouse=ui_GetMousePos();
    bool down=ui_IsMouseDown(0)||ui_IsMouseDown(1)||ui_IsMouseDown(2);
    bool inside=in_floating_rect(mouse);
    if(inside&&down)g_overlay_drag=true;
    bool own=inside||g_overlay_drag;
    if(!down)g_overlay_drag=false;
    if(!own)return;
    u8*io=(u8*)ui_GetIO();
    if(!io)return;
    ImVec2 actual=*(ImVec2*)(io+IO_MOUSE_POS);
    // ABI safety check: fail closed rather than corrupt an unexpected ImGuiIO.
    if(actual.x!=mouse.x||actual.y!=mouse.y)return;
    g_saved_mouse=mouse;
    g_saved_wheel=*(float*)(io+IO_MOUSE_WHEEL);
    g_mask_frame=ui_GetFrameCount();
    *(ImVec2*)(io+IO_MOUSE_POS)=ImVec2(-100000.0f,-100000.0f);
    *(float*)(io+IO_MOUSE_WHEEL)=0.0f;
    g_overlay_masked=true;
}
// Called at EndFramePost. ImGui has already handled the window and resets
// MouseWheel itself. Restore only MousePos, never revive a consumed wheel.
static void input_end_frame(void*,ContextHook*){restore_overlay_mouse(false);}

static char g_settings_write_buf[60000];
static char g_settings_read_buf[60000];

static usize slen(const char*s){usize i=0;if(s)while(s[i])i++;return i;}
static bool seq(const char*a,const char*b){return priyom::eq(a,b);}
static void copy(char*d,usize cap,const char*s){priyom::cp(d,(unsigned)cap,s);}
static void append(char*d,usize cap,const char*s){usize n=slen(d);if(n<cap)copy(d+n,cap-n,s);}
static void lower(char*s){for(;*s;s++)if(*s>='A'&&*s<='Z')*s=(char)(*s-'A'+'a');}
static void append_int(char*d,usize cap,u64 v){char t[32];int n=0;do{t[n++]=(char)('0'+v%10);v/=10;}while(v&&n<31);char s[32];int j=0;while(n)s[j++]=t[--n];s[j]=0;append(d,cap,s);}
static void append_pad(char*d,usize cap,unsigned n,int digits){char tmp[24];int i=0;do{tmp[i++]=(char)('0'+n%10);n/=10;}while(n&&i<23);while(i<digits)tmp[i++]='0';char t[24];int k=0;while(i)t[k++]=tmp[--i];t[k]=0;append(d,cap,t);}
static void append_date(char*d,usize cap,priyom::i64 days){
    // Civil date from days since 1970-01-01 (UTC, Gregorian calendar).
    days+=719468;const priyom::i64 era=(days>=0?days:days-146096)/146097;
    const unsigned doe=(unsigned)(days-era*146097);const unsigned yoe=(doe-doe/1460+doe/36524-doe/146096)/365;
    int y=(int)yoe+(int)era*400;const unsigned doy=doe-(365*yoe+yoe/4-yoe/100);
    const unsigned mp=(5*doy+2)/153;const unsigned day=doy-(153*mp+2)/5+1;
    const unsigned mon=mp+(mp<10?3:-9);y+=(mon<=2);
    append_pad(d,cap,(unsigned)y,4);append(d,cap,"-");append_pad(d,cap,mon,2);append(d,cap,"-");append_pad(d,cap,day,2);
}
static priyom::i64 utc_now(){WinFileTime f;GetSystemTimeAsFileTime(&f);u64 ticks=((u64)f.hi<<32)|f.lo;return (priyom::i64)(ticks/10000000ULL)-11644473600LL;}
static void append_utc_hms(char*out,usize cap,priyom::i64 epoch){
    priyom::i64 sec=epoch%86400;
    append_pad(out,cap,(unsigned)(sec/3600),2);append(out,cap,":");
    append_pad(out,cap,(unsigned)((sec/60)%60),2);append(out,cap,":");
    append_pad(out,cap,(unsigned)(sec%60),2);
}
static void update_utc_clock(priyom::i64 now){
    if(now==g_utc_clock_second)return;
    g_utc_clock_second=now;
    copy(g_utc_clock_text,sizeof(g_utc_clock_text),"UTC ");
    append_utc_hms(g_utc_clock_text,sizeof(g_utc_clock_text),now);
    g_utc_clock_full[0]=0;
    append_date(g_utc_clock_full,sizeof(g_utc_clock_full),now/86400);
    append(g_utc_clock_full,sizeof(g_utc_clock_full)," ");
    append_utc_hms(g_utc_clock_full,sizeof(g_utc_clock_full),now);
    append(g_utc_clock_full,sizeof(g_utc_clock_full)," UTC");
}
static void event_time(const priyom::Event&e,char*out,usize cap){out[0]=0;priyom::i64 day=e.utc/86400,sec=e.utc%86400;append_date(out,cap,day);append(out,cap," ");append_pad(out,cap,(unsigned)(sec/3600),2);append(out,cap,":");append_pad(out,cap,(unsigned)((sec/60)%60),2);}
static void event_freq(const priyom::Event&e,char*out,usize cap){out[0]=0;if(e.search||e.hz<=0){copy(out,cap,"Search");return;}
    u64 hz=(u64)(e.hz+0.5);append_int(out,cap,hz/1000);if(hz%1000){append(out,cap,".");append_pad(out,cap,(unsigned)(hz%1000),3);while(slen(out)&&out[slen(out)-1]=='0')out[slen(out)-1]=0;}
    append(out,cap," kHz ");append(out,cap,e.mode);
}
static bool supported_core(){
    u8*p=(u8*)GetModuleHandleA("sdrpp_core.dll");if(!p||*(unsigned short*)p!=0x5A4D)return false;
    u32 pe=*(u32*)(p+0x3C);if(pe>=4096||*(u32*)(p+pe)!=0x4550)return false;
    u32 stamp=*(u32*)(p+pe+8),size=*(u32*)(p+pe+24+56);
    // Verified Windows x64 SDR++ 1.3.2 nightlies. Keep prior builds
    // supported without weakening the ABI guard for unknown binaries:
    // 2026-11-07: PE image 0x817000, timestamp 0x6AEE9887.
    // 2026-11-18: PE image 0x819000, timestamp 0x6AFE16EB.
    // MainWindow, WaterFall, radio and ImGui interfaces are unchanged
    // between these source revisions; native exports are checked in tests.
    bool known_build = (size==0x817000&&(stamp==0x6A49A9F8||stamp==0x6AEE9887))
                    || (size==0x819000&&stamp==0x6AFE16EB);
    return known_build&&seq(ui_GetVersion(),"1.87");
}
// Optional feature symbol lookup. All required SDR++ V2.2 symbols remain
// normal imports; only the five newer UI exports can be missing safely.
static void resolve_optional_imgui(){
    void*core=GetModuleHandleA("sdrpp_core.dll");
    if(!core)return;
    g_fn_column_width=(FnTableColumnWidth)GetProcAddress(core,"?TableGetColumnWidth@ImGui@@YAMH@Z");
    g_fn_get_cursor_x=(FnGetCursorPosX)GetProcAddress(core,"?GetCursorPosX@ImGui@@YAMXZ");
    g_fn_set_cursor_x=(FnSetCursorPosX)GetProcAddress(core,"?SetCursorPosX@ImGui@@YAXM@Z");
    g_fn_cursor_pos=(FnCursorScreenPos)GetProcAddress(core,"?GetCursorScreenPos@ImGui@@YA?AUImVec2@@XZ");
    g_fn_draw_list=(FnWindowDrawList)GetProcAddress(core,"?GetWindowDrawList@ImGui@@YAPEAUImDrawList@@XZ");
    g_fn_dummy=(FnDummy)GetProcAddress(core,"?Dummy@ImGui@@YAXAEBUImVec2@@@Z");
    g_fn_rect=(FnAddRectFilled)GetProcAddress(core,"?AddRectFilled@ImDrawList@@QEAAXAEBUImVec2@@0IMH@Z");
}
static void* selected_vfo(){
    // Only read the verified WaterFall x64 layout. Never create map entries for an absent VFO.
    u64 name_length=*(u64*)(core_waterfall+0x40);if(!name_length||name_length>255)return 0;
    void* name=core_waterfall+0x30;void* map=core_waterfall+0x20;
    // The std::map operator[] can insert if the selected name is missing, as in native SDR++.
    void**ptr=wf_vfo_index(map,name);return ptr?*ptr:0;
}
static bool radio_ready(){
    if(!selected_vfo())return false;
    CoreString name;core_stringCopy(&name,core_waterfall+0x30);
    if(!com_exists(core_mod_com,&name))return false;
    CoreString module;core_stringCopy(&name,core_waterfall+0x30);
    com_moduleName(core_mod_com,&module,&name);
    const char*str=*(u64*)(module.bytes+24)>=16?*(const char**)module.bytes:(const char*)module.bytes;
    bool ready=seq(str,"radio");core_stringDestroy(&module);return ready;
}
static bool radio_cmd(int code,void*in,void*out){CoreString name;core_stringCopy(&name,core_waterfall+0x30);return com_call(core_mod_com,&name,code,in,out);}
static int mode_for(const char*name){
    // SDR++ radio enum: NFM=0,WFM=1,AM=2,DSB=3,USB=4,CW=5,LSB=6,RAW=7.
    if(seq(name,"NFM")||seq(name,"FM"))return 0;
    if(seq(name,"WFM"))return 1;
    if(seq(name,"AM"))return 2;
    if(seq(name,"DSB"))return 3;
    if(seq(name,"LSB"))return 6;
    if(seq(name,"CW"))return 5;
    if(seq(name,"RAW"))return 7;
    if(priyom::prefix(name,"USB"))return 4;
    // Priyom digital modes (RTTY, FSK, PSK etc.) are received through USB.
    if(seq(name,"RTTY")||seq(name,"FSK")||seq(name,"PSK")||seq(name,"MFSK")||seq(name,"DIGITAL"))return 4;
    return -1; // Do not silently choose a wrong mode for unknown entries.
}
static bool tune(const priyom::Event&e){
    // Always use the SDR++ NORMAL tuning mode; no separate UI checkbox.
    // Keep the waterfall center when the requested VFO fits on screen.
    int mode=mode_for(e.mode);
    if(mode<0||e.search||e.hz<=0||!radio_ready())return false;
    int current=-1;
    if(!radio_cmd(0,0,&current))return false;
    if(current!=mode){
        if(!radio_cmd(1,&mode,0))return false;
        current=-1;
        if(!radio_cmd(0,0,&current)||current!=mode)return false;
    }
    CoreString name;core_stringCopy(&name,core_waterfall+0x30);
    // NORMAL mode moves the VFO without recentering while it fits in the
    // visible bandwidth. SDR++ itself handles retuning outside that range.
    core_tune(1,&name,e.hz); // Always NORMAL: retain the waterfall center when VFO fits.
    return true;
}
// All Priyom links use one station-aware URL builder.  Never send a row's
// UTC click to the generic schedule: the selected station determines its page.
static void open_station_page(const char*station,bool schedule){
    char url[256];
    if(priyom::build_station_url(station,schedule,url,sizeof(url)))
        ShellExecuteA(0,"open",url,0,0,1);
}
static void open_station(const char*station){open_station_page(station,false);}
static void open_station_schedule(const char*station){open_station_page(station,true);}
static void open_schedule(){ShellExecuteA(0,"open","https://priyom.org/number-stations/station-schedule",0,0,1);}

static void build_settings_path(){
    // The active configuration is ALWAYS adjacent to the running SDR++ EXE,
    // regardless of the current working directory or where modules live.
    char exe[1024]={0};
    u32 bytes=GetModuleFileNameA(GetModuleHandleA(nullptr),exe,sizeof(exe));
    if(bytes>0&&bytes<sizeof(exe)){
        u32 pos=bytes;
        while(pos&&exe[pos-1]!='\\'&&exe[pos-1]!='/')--pos;
        exe[pos]=0;
        copy(g_ini_path,sizeof(g_ini_path),exe);
        append(g_ini_path,sizeof(g_ini_path),"priyom.ini");
    }
    // Legacy files are used ONE TIME only, for migration on first install.
    // They are never written to by this version.
    char root[768];u32 n=GetEnvironmentVariableA("LOCALAPPDATA",root,sizeof(root));if(!n||n>=sizeof(root))return;
    append(root,sizeof(root),"\\SDRpp\\Priyom");
    copy(g_settings_path,sizeof(g_settings_path),root);append(g_settings_path,sizeof(g_settings_path),"\\auto_tune.txt");
    copy(g_opacity_path,sizeof(g_opacity_path),root);append(g_opacity_path,sizeof(g_opacity_path),"\\window_opacity.txt");
    copy(g_auto_global_path,sizeof(g_auto_global_path),root);append(g_auto_global_path,sizeof(g_auto_global_path),"\\global_auto.txt");
    copy(g_column_width_path,sizeof(g_column_width_path),root);append(g_column_width_path,sizeof(g_column_width_path),"\\column_widths_100_125_100_70_80_40_margin10.txt");
    copy(g_floating_size_path,sizeof(g_floating_size_path),root);append(g_floating_size_path,sizeof(g_floating_size_path),"\\floating_size_v23_margin10.txt");
}
static void save_opacity(){save_ini();}
static void load_opacity(){
    if(!g_opacity_path[0])return;
    void*h=CreateFileA(g_opacity_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return;
    char value[16]={0};u32 got=0;bool ok=ReadFile(h,value,sizeof(value)-1,&got,0)!=0;CloseHandle(h);
    if(!ok||!got)return;
    int n=0;for(u32 i=0;i<got&&value[i]>='0'&&value[i]<='9';i++)n=n*10+value[i]-'0';
    if(n>=20&&n<=100)g_opacity_percent=(float)n;
}
static void save_global_auto(){save_ini();}
static void load_global_auto(){
    if(!g_auto_global_path[0])return;
    void*h=CreateFileA(g_auto_global_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return;
    char value[4]={0};u32 got=0;bool ok=ReadFile(h,value,sizeof(value),&got,0)!=0;CloseHandle(h);
    if(ok&&got>0&&(value[0]=='0'||value[0]=='1'))g_auto_global=value[0]=='1';
}
// Persist widths for each view. The table uses NoHostExtendX to avoid
// drawing empty row backgrounds to the window edge. A new settings filename
// resets only the badly stretched compact layout from earlier builds.
static void save_column_widths(){save_ini();}
static void load_column_widths(){
    if(!g_column_width_path[0])return;
    void*h=CreateFileA(g_column_width_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return;
    char content[240]={0};u32 got=0;
    bool ok=ReadFile(h,content,sizeof(content)-1,&got,0)!=0;CloseHandle(h);
    if(!ok||!got)return;
    content[got]=0;const char*p=content;
    float decoded[2][6];
    for(int view=0;view<2;view++)for(int col=0;col<6;col++){
        while(*p==' '||*p=='\r'||*p=='\n')++p;
        if(*p<'0'||*p>'9')return;
        unsigned n=0;
        while(*p>='0'&&*p<='9'){
            unsigned digit=(unsigned)(*p++-'0');
            if(n>(0xffffffffu-digit)/10u)return;
            n=n*10u+digit;
        }
        if(n<20)return;decoded[view][col]=(float)n;
    }
    for(int view=0;view<2;view++)for(int col=0;col<6;col++)g_column_widths[view][col]=decoded[view][col];
}
// Window size: plain text two numbers, both validated on read. Writes are
// deferred until the mouse is released (or SDR++ shuts down) to avoid writing
// on every frame while dragging the bottom-right window resize grip.
static void save_floating_size(){save_ini();}
static void load_floating_size(){
    if(!g_floating_size_path[0])return;
    void*h=CreateFileA(g_floating_size_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return;
    char content[64]={0};u32 got=0;
    bool ok=ReadFile(h,content,sizeof(content)-1,&got,0)!=0;CloseHandle(h);
    if(!ok||!got)return;
    content[got]=0;const char*p=content;
    unsigned decoded[2]={0};
    for(int k=0;k<2;k++){
        while(*p==' '||*p=='\r'||*p=='\n'||*p=='\t')++p;
        if(*p<'0'||*p>'9')return;
        while(*p>='0'&&*p<='9'){
            unsigned digit=(unsigned)(*p++-'0');
            if(decoded[k]>(0xffffffffu-digit)/10u)return;
            decoded[k]=10u*decoded[k]+digit;
        }
    }
    while(*p==' '||*p=='\r'||*p=='\n'||*p=='\t')++p;
    if(*p||decoded[0]<410u||decoded[1]<175u)return;
    // Independent v23_margin10 profile: saved user dimensions from this
    // edition are restored, earlier broken window widths are not reused.
    g_floating_size=ImVec2((float)decoded[0],(float)decoded[1]);
}
static void track_floating_size(ImVec2 measured,bool is_open){
    if(measured.x<410.0f||measured.y<175.0f)return;
    if(!g_floating_size_observed){
        g_floating_size_observed=true;
        g_last_floating_size=measured;
        // A saved window can be wider than its saved columns (older builds).
        // Give the difference to QTH ONCE, not on every frame. Otherwise
        // users could never manually shrink this column: each shrink would
        // be immediately undone by an equal auto-expansion.
        float painted=7.0f;
        for(int c=0;c<6;c++)painted+=g_column_widths[1][c];
        float missing=measured.x-20.0f-painted;
        if(missing>0.75f){g_column_widths[1][2]+=missing;g_column_dirty=true;}
        return;
    }
    float dx=measured.x-g_last_floating_size.x;
    float dy=measured.y-g_last_floating_size.y;
    if(dx>0.75f||dx<-0.75f||dy>0.75f||dy<-0.75f){
        g_floating_size=measured;
        g_floating_size_dirty=true;
        if(dx>0.75f||dx<-0.75f){
            // Window resize grows/shrinks visible QTH by exactly the drag.
            // All user-edited column widths remain independently changeable.
            const float target=g_column_widths[1][2]+dx;
            const float bounded=(target<28.0f?28.0f:target);
            if(bounded!=g_column_widths[1][2]){
                g_column_widths[1][2]=bounded;g_column_dirty=true;
            }
        }
    }
    g_last_floating_size=measured;
    if((g_floating_size_dirty||g_column_dirty)&&(!ui_IsMouseDown(0)||!is_open))save_ini();
}
static void track_column_widths(bool floating){
    // When missing, let Dear ImGui persist resizes through its own table
    // settings; do not invoke an unavailable sdrpp_core.dll export.
    if(!g_fn_column_width)return;
    int view=floating?1:0;
    bool mouse_down=ui_IsMouseDown(0);
    for(int col=0;col<6;col++){
        float current=g_fn_column_width(col);
        if(current<1.0f)continue;
        float previous=g_column_prev[view][col];
        if(mouse_down&&previous>0.0f&&(current>previous+0.8f||current<previous-0.8f)){
            // Store widths of all six columns, not just QTH. Only an active drag
            // persists changed ratios; window auto-scaling alone isn't saved.
            for(int j=0;j<6;j++){
                float width=g_fn_column_width(j);
                // TableGetColumnWidth reports the inner content width;
                // persisted values represent the full visible column width.
                if(width>=20.0f)g_column_widths[view][j]=width+8.0f;
            }
            g_column_dirty=true;
        }
        g_column_prev[view][col]=current;
    }
    if(g_column_dirty&&!mouse_down)save_column_widths();
}
static void paint_qth_flag(const char*country){
    const char*iso=priyom::qth::country_code(country);
    if(!priyom::flags::get(iso) || !optional_flag_drawing_available())return;
    ImVec2 p=g_fn_cursor_pos();
    ImDrawList*draw=g_fn_draw_list();
    if(!draw)return;
    constexpr float w=20.0f,h=13.0f;
    priyom::flags::draw(iso,[&](unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned color){
        g_fn_rect(draw,ImVec2(p.x+w*x0/24.0f,p.y+1.0f+h*y0/16.0f),
            ImVec2(p.x+w*x1/24.0f,p.y+1.0f+h*y1/16.0f),color,0,0);
    });
    g_fn_dummy(ImVec2(20.0f,15.0f));ui_SameLine(0.0f,3.0f);
}
static bool armed(const priyom::Key&k){for(int i=0;i<g_armed_count;i++)if(priyom::key_equal(g_armed[i],k))return true;return false;}
static void save_ini(){
    if(!g_ini_path[0])return;
    char*buf=g_settings_write_buf;buf[0]=0;
    append(buf,60000,"; SDR++ Priyom V2.3 - all plugin settings in one file\r\n");
    append(buf,60000,"[Window]\r\nwidth=");
    append_int(buf,60000,(unsigned)(g_floating_size.x+0.5f));
    append(buf,60000,"\r\nheight=");
    append_int(buf,60000,(unsigned)(g_floating_size.y+0.5f));
    append(buf,60000,"\r\nopacity=");
    append_int(buf,60000,(unsigned)(g_opacity_percent+0.5f));
    append(buf,60000,"\r\n\r\n[Table]\r\nsidebar=");
    for(int view=0;view<2;view++){
        if(view==1)append(buf,60000,"floating=");
        for(int col=0;col<6;col++){
            append_int(buf,60000,(unsigned)(g_column_widths[view][col]+0.5f));
            append(buf,60000,col==5?"\r\n":",");
        }
    }
    append(buf,60000,"\r\n[AutoTune]\r\nglobal_auto=");
    append(buf,60000,g_auto_global?"1\r\n":"0\r\n");
    for(int i=0;i<g_armed_count;i++){
        const priyom::Key&k=g_armed[i];
        append(buf,60000,"event=");append_int(buf,60000,(u64)k.utc);append(buf,60000,",");
        append_int(buf,60000,(u64)k.hz);append(buf,60000,",");
        append(buf,60000,k.station);append(buf,60000,",");append(buf,60000,k.mode);append(buf,60000,"\r\n");
    }
    // The only write destination used by Priyom is priyom.ini.
    void*h=CreateFileA(g_ini_path,0x40000000,0,0,2,0x80,0);
    if((usize)h==(usize)-1)return;
    u32 written=0;usize n=slen(buf);
    bool ok=WriteFile(h,buf,(u32)n,&written,0)!=0;
    CloseHandle(h);
    if(ok&&written==n){g_column_dirty=false;g_floating_size_dirty=false;}
}
static void save_settings(){save_ini();}
static bool parse_int(const char*&p,priyom::i64&n){if(!priyom::digit(*p))return false;n=0;while(priyom::digit(*p)){n=n*10+(*p++-'0');}return true;}
static bool read_token(const char*&p,char*dest,int cap){int i=0;while(*p&&*p!=' '&&*p!='\n'&&*p!='\r'){if(i+1>=cap)return false;dest[i++]=*p++;}dest[i]=0;return i>0;}
static void load_settings(){
    if(!g_settings_path[0])return;void*h=CreateFileA(g_settings_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return;char*buf=g_settings_read_buf;u32 got=0;bool ok=ReadFile(h,buf,60000-1,&got,0)!=0;CloseHandle(h);
    if(!ok||!got)return;buf[got]=0;const char*p=buf;
    // V1.0/V1.1 wrote a global 0/1 switch on the first line.
    // Ignore it on migration: in V1.2 only per-event checkboxes control tuning.
    if((*p=='0'||*p=='1')&&p[1]=='\n')p+=2;
    else if((*p=='0'||*p=='1')&&p[1]=='\r'&&p[2]=='\n')p+=3;
    while(*p&&g_armed_count<512){priyom::Key k={};
        if(!parse_int(p,k.utc)||*p++!=' '||!parse_int(p,k.hz)||*p++!=' '||!read_token(p,k.station,sizeof(k.station))||*p++!=' '||!read_token(p,k.mode,sizeof(k.mode)))break;
        while(*p=='\r'||*p=='\n')p++;
        if(k.utc>utc_now()-30LL*86400&&k.utc<utc_now()+366LL*86400)g_armed[g_armed_count++]=k;
    }
}
// Strict decimal reader used by the single-INI loader.
static bool ini_number(const char*&p,unsigned&out){
    if(*p<'0'||*p>'9')return false;
    out=0;
    while(*p>='0'&&*p<='9'){
        unsigned digit=(unsigned)(*p++-'0');
        if(out>(0xffffffffu-digit)/10u)return false;
        out=out*10u+digit;
    }
    return true;
}
static bool ini_six(const char*value,float out[6]){
    float tmp[6];const char*p=value;
    for(int i=0;i<6;i++){
        unsigned v=0;
        if(!ini_number(p,v)||v<20||v>1000000)return false;
        tmp[i]=(float)v;
        if(i<5){if(*p++!=',')return false;}
    }
    if(*p)return false;
    for(int i=0;i<6;i++)out[i]=tmp[i];
    return true;
}
static bool load_ini(){
    if(!g_ini_path[0])return false;
    void*h=CreateFileA(g_ini_path,0x80000000,1,0,3,0x80,0);
    if((usize)h==(usize)-1)return false;
    char*buf=g_settings_read_buf;u32 got=0;
    bool ok=ReadFile(h,buf,60000-1,&got,0)!=0;CloseHandle(h);
    if(!ok)return false;
    buf[got]=0;int section=0;
    g_armed_count=0;
    for(char*line=buf;*line;){
        char*next=line;while(*next&&*next!='\n'&&*next!='\r')++next;
        char*after=next;
        if(*after=='\r')++after;
        if(*after=='\n')++after;
        *next=0;
        if(seq(line,"[Window]"))section=1;
        else if(seq(line,"[Table]"))section=2;
        else if(seq(line,"[AutoTune]"))section=3;
        else if(*line&&*line!=';'&&*line!='#'){
            char*sep=line;while(*sep&&*sep!='=')++sep;
            if(*sep=='='){
                *sep=0;const char*value=sep+1;
                unsigned n=0;const char*end=value;
                if(section==1&&ini_number(end,n)&&!*end){
                    if(seq(line,"width")&&n>=180&&n<=1000000)g_floating_size.x=(float)n;
                    else if(seq(line,"height")&&n>=120&&n<=1000000)g_floating_size.y=(float)n;
                    else if(seq(line,"opacity")&&n>=20&&n<=100)g_opacity_percent=(float)n;
                }else if(section==2){
                    if(seq(line,"sidebar"))ini_six(value,g_column_widths[0]);
                    else if(seq(line,"floating"))ini_six(value,g_column_widths[1]);
                }else if(section==3){
                    if(seq(line,"global_auto")&&ini_number(end,n)&&!*end&&n<=1)g_auto_global=n!=0;
                    else if(seq(line,"event")&&g_armed_count<512){
                        const char*p=value;priyom::Key k={};priyom::i64 v=0;
                        if(parse_int(p,v)&&*p++==','){
                            k.utc=v;
                            if(parse_int(p,v)&&*p++==','){
                                k.hz=v;
                                int j=0;while(*p&&*p!=','&&j<(int)sizeof(k.station)-1)k.station[j++]=*p++;
                                k.station[j]=0;
                                if(*p++==','){
                                    j=0;while(*p&&j<(int)sizeof(k.mode)-1)k.mode[j++]=*p++;
                                    k.mode[j]=0;
                                    if(!*p&&k.station[0]&&k.mode[0]&&k.utc>utc_now()-30LL*86400&&k.utc<utc_now()+366LL*86400)
                                        g_armed[g_armed_count++]=k;
                                }
                            }
                        }
                    }
                }
            }
        }
        line=after;
    }
    return true;
}
static void set_armed(const priyom::Key&k,bool value){
    for(int i=0;i<g_armed_count;i++)if(priyom::key_equal(g_armed[i],k)){
        if(!value){for(int j=i+1;j<g_armed_count;j++)g_armed[j-1]=g_armed[j];g_armed_count--;save_settings();}return;
    }
    if(value&&g_armed_count<512){g_armed[g_armed_count++]=k;save_settings();}
}
static bool was_fired(const priyom::Key&k){for(int i=0;i<g_fired_count;i++)if(priyom::key_equal(g_fired[i],k))return true;return false;}
static void mark_fired(const priyom::Key&k){if(was_fired(k))return;if(g_fired_count==512){for(int i=1;i<512;i++)g_fired[i-1]=g_fired[i];g_fired_count=511;}g_fired[g_fired_count++]=k;}

static bool fetch_json(char*body,u32 cap,u32&used){
    used=0;void*session=WinHttpOpen(L"SDRpp-Priyom/1.9",0,0,0,0);if(!session)return false;
    WinHttpSetTimeouts(session,5000,5000,5000,5000);
    void*conn=WinHttpConnect(session,L"calendar.priyom.org",443,0);if(!conn){WinHttpCloseHandle(session);return false;}
    char url[256]="/events?timeMin=";priyom::i64 day=utc_now()/86400;
    append_date(url,sizeof(url),day);append(url,sizeof(url),"T00:00:00Z&timeMax=");
    append_date(url,sizeof(url),day+3);append(url,sizeof(url),"T00:00:00Z");
    wchar_t wide[256];int i=0;for(;url[i]&&i<255;i++)wide[i]=(wchar_t)(unsigned char)url[i];wide[i]=0;
    void*req=WinHttpOpenRequest(conn,L"GET",wide,0,0,0,0x00800000);
    bool ok=false;
    if(req){WinHttpSetTimeouts(req,5000,5000,5000,5000);
        if(WinHttpSendRequest(req,0,0,0,0,0,0)&&WinHttpReceiveResponse(req,0)){
            u32 status=0,len=sizeof(status);
            if(WinHttpQueryHeaders(req,19|0x20000000,0,&status,&len,0)&&status==200){
                ok=true;while(used+1<cap){u32 got=0;u32 avail=cap-1-used;if(avail>32768)avail=32768;
                    if(!WinHttpReadData(req,body+used,avail,&got)){ok=false;break;}
                    if(!got)break;used+=got;
                }
                if(used+1>=cap)ok=false;
            }
        }
        WinHttpCloseHandle(req);
    }
    WinHttpCloseHandle(conn);WinHttpCloseHandle(session);body[used]=0;return ok;
}
// Priyom's country metadata is published on its own station-category pages,
// not in the calendar JSON. Read the official Country column once per day or
// when Refresh is pressed. Never guess a location from station ID or language.
static bool fetch_qth_page(const wchar_t*path,char*body,u32 cap,u32&used){
    used=0;body[0]=0;
    void*session=WinHttpOpen(L"SDRpp-Priyom/2.3",0,0,0,0);if(!session)return false;
    WinHttpSetTimeouts(session,5000,5000,5000,6000);
    void*conn=WinHttpConnect(session,L"priyom.org",443,0);
    if(!conn){WinHttpCloseHandle(session);return false;}
    void*req=WinHttpOpenRequest(conn,L"GET",path,0,0,0,0x00800000);
    bool ok=false;
    if(req){
        WinHttpSetTimeouts(req,5000,5000,5000,6000);
        if(WinHttpSendRequest(req,0,0,0,0,0,0)&&WinHttpReceiveResponse(req,0)){
            u32 status=0,len=sizeof(status);
            if(WinHttpQueryHeaders(req,19|0x20000000,0,&status,&len,0)&&status==200){
                ok=true;bool complete=false;
                while(used+1<cap){
                    u32 got=0,avail=cap-1-used;if(avail>16384)avail=16384;
                    if(!WinHttpReadData(req,body+used,avail,&got)){ok=false;break;}
                    if(!got){complete=true;break;}used+=got;
                }
                if(!complete)ok=false;
            }
        }
        WinHttpCloseHandle(req);
    }
    WinHttpCloseHandle(conn);WinHttpCloseHandle(session);
    body[used]=0;return ok;
}
static bool refresh_qth_catalog(){
    struct Index{const wchar_t*path;int country_column;};
    static const Index pages[]={
      {L"/number-stations/english",2},{L"/number-stations/german",2},
      {L"/number-stations/slavic",2},{L"/number-stations/other",2},
      {L"/number-stations/morse",1},{L"/number-stations/digital",1}
    };
    static char html[512*1024];static priyom::qth::Entry parsed[256];
    int count=0,successful=0;
    for(unsigned i=0;i<sizeof(pages)/sizeof(pages[0]);i++){
        if(InterlockedCompareExchange(&g_stop,0,0))return false;
        u32 used=0;
        if(!fetch_qth_page(pages[i].path,html,sizeof(html),used))continue;
        if(priyom::qth::parse_index(html,used,pages[i].country_column,parsed,count,256)>0)++successful;
    }
    // Optional Priyom operators mapping supplies countries for modes with
    // empty Country cells (e.g. XPA2 / Russian 7). Never overwrite explicit
    // countries from the individual station indexes.
    if(!InterlockedCompareExchange(&g_stop,0,0)){
        u32 used=0;
        if(fetch_qth_page(L"/number-stations/operators",html,sizeof(html),used))
            priyom::qth::parse_operators(html,used,parsed,count,256);
    }
    if(!successful)return false;
    AcquireSRWLockExclusive(&g_lock);
    // Merge results: failures on individual pages do not delete known QTH.
    for(int i=0;i<count;i++)priyom::qth::set(g_qth_catalog,g_qth_count,256,parsed[i].station,parsed[i].country);
    __atomic_store_n(&g_last_qth_fetch,utc_now(),__ATOMIC_RELEASE);
    __atomic_add_fetch(&g_qth_generation,1,__ATOMIC_RELEASE);
    ReleaseSRWLockExclusive(&g_lock);
    return true;
}
static u32 __stdcall worker(void*){
    static char body[4*1024*1024];static priyom::Event parsed[1024];
    while(!InterlockedCompareExchange(&g_stop,0,0)){
        u32 length=0;bool ok=fetch_json(body,sizeof(body),length);
        int n=ok?priyom::parse(body,length,parsed,1024):-1;
        AcquireSRWLockExclusive(&g_lock);
        if(n>=0){g_count=n;for(int i=0;i<n;i++)g_events[i]=parsed[i];g_fetch_state=1;g_last_fetch=utc_now();__atomic_add_fetch(&g_generation,1,__ATOMIC_RELEASE);}
        else g_fetch_state=2; // keep last good schedule on transient failure
        ReleaseSRWLockExclusive(&g_lock);
        // Refresh country metadata separately. Errors do not affect calendar.
        priyom::i64 now=utc_now();
        priyom::i64 last_qth=__atomic_load_n(&g_last_qth_fetch,__ATOMIC_ACQUIRE);
        if(!last_qth||now-last_qth>=86400){
            if(!refresh_qth_catalog()&&!__atomic_load_n(&g_last_qth_fetch,__ATOMIC_ACQUIRE))
                __atomic_store_n(&g_last_qth_fetch,now-86400+900,__ATOMIC_RELEASE);
        }
        for(int tick=0;tick<1200&&!InterlockedCompareExchange(&g_stop,0,0);tick++){
            if(InterlockedExchange(&g_force_refresh,0))break;
            Sleep(250);
        }
    }
    return 0;
}
static void request_refresh(){__atomic_store_n(&g_last_qth_fetch,0,__ATOMIC_RELEASE);InterlockedExchange(&g_force_refresh,1);}

// ImGui 1.87 named-key index (P=561, not legacy ASCII 80).
// Run once per NewFrame, independently from auto-tuning state.
static void shortcut_frame(){
    if(!g_supported||!g_enabled)return;
    const u8*io=(const u8*)ui_GetIO();
    if(!io||io[0xCA]||ui_IsAnyItemActive())return; // text input and active widgets
    // Ctrl, Shift, Alt, Super: do not steal ordinary application shortcuts.
    if(io[0xD1C]||io[0xD1D]||io[0xD1E]||io[0xD1F])return;
    if(ui_IsKeyPressed(561,false))g_float_open=!g_float_open;
}
static void auto_frame(void*,ContextHook*){
    shortcut_frame();
    if(!g_enabled||!g_auto_global||!g_armed_count)return;
    priyom::i64 now=utc_now();
    static priyom::i64 last_checked=-1;
    if(now==last_checked)return;
    last_checked=now;priyom::Event chosen={};bool found=false;
    AcquireSRWLockShared(&g_lock);
    for(int i=0;i<g_count;i++){
        const priyom::Event&e=g_events[i];if(!priyom::eligible(e,now))continue;
        priyom::Key k=priyom::key_of(e);if(!armed(k)||was_fired(k))continue;
        if(mode_for(e.mode)<0)continue;
        chosen=e;found=true;break; // deterministic first eligible row when timestamps collide
    }
    ReleaseSRWLockShared(&g_lock);
    if(!found)return;
    // Do not consume a scheduled event if the radio is not ready yet.
    // Keep trying within its 10-second window.  Once tuning succeeds, mark
    // all colliding selected rows as handled (one receiver, one frequency).
    bool ok=tune(chosen);
    if(ok){
        AcquireSRWLockShared(&g_lock);
        for(int i=0;i<g_count;i++)if(g_events[i].utc==chosen.utc && priyom::eligible(g_events[i],now)){
            priyom::Key other=priyom::key_of(g_events[i]);
            if(armed(other))mark_fired(other);
        }
        ReleaseSRWLockShared(&g_lock);
    }
}

static void event_clock(const priyom::Event&e,priyom::i64 now,char*out,usize cap){
    out[0]=0;
    priyom::i64 day=e.utc/86400,seconds=e.utc%86400;
    if(day!=now/86400){
        char date[24]={0};append_date(date,sizeof(date),day);
        // Day and month distinguish upcoming UTC dates without wasting table width.
        char dm[8]={date[8],date[9],'.',date[5],date[6],0};
        append(out,cap,dm);append(out,cap," ");
    }
    append_pad(out,cap,(unsigned)(seconds/3600),2);append(out,cap,":");
    append_pad(out,cap,(unsigned)((seconds/60)%60),2);
}
static void opacity_slider(bool floating){
    ui_SameLine(0,5);
    ImVec2 avail=ui_GetContentRegionAvail();
    float width=avail.x-5.0f;
    if(floating&&width>120.0f)width=120.0f;
    if(!floating&&width>120.0f)width=120.0f;
    if(width<52.0f)width=52.0f;
    ui_SetNextItemWidth(width);
    if(ui_SliderFloat(floating?"##priyom_alpha_float":"##priyom_alpha_side",&g_opacity_percent,20.0f,100.0f,"%.0f%%",0)){
        g_opacity_dirty=true;
    }
    if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_OPACITY);
    // Save only after releasing the slider, never during window dragging.
    if(g_opacity_dirty&&ui_IsItemDeactivatedAfterEdit()){
        save_opacity();g_opacity_dirty=false;
    }
}
static priyom::qth::Entry g_ui_qth[256];static int g_ui_qth_count=0;static int g_ui_qth_generation=-1;
static priyom::Event g_ui_snapshot[1024];
static int g_ui_rows[1024];
static int g_ui_snapshot_count=0,g_ui_row_count=0;
// Cache countdown text once per UTC second across the sidebar and floating view.
static char g_ui_countdowns[1024][24];
static priyom::i64 g_ui_countdown_second=-1;
static int g_ui_generation=-1;
static priyom::i64 g_ui_rows_second=-1;
static unsigned g_ui_filter_revision=~0u;
static void update_ui_cache(priyom::i64 now){
    int qgeneration=__atomic_load_n(&g_qth_generation,__ATOMIC_ACQUIRE);
    if(qgeneration!=g_ui_qth_generation){
        AcquireSRWLockShared(&g_lock);
        g_ui_qth_count=g_qth_count;
        for(int i=0;i<g_qth_count;i++)g_ui_qth[i]=g_qth_catalog[i];
        g_ui_qth_generation=__atomic_load_n(&g_qth_generation,__ATOMIC_RELAXED);
        ReleaseSRWLockShared(&g_lock);
    }
    int generation=__atomic_load_n(&g_generation,__ATOMIC_ACQUIRE);
    if(generation!=g_ui_generation){
        AcquireSRWLockShared(&g_lock);
        generation=__atomic_load_n(&g_generation,__ATOMIC_RELAXED);
        g_ui_snapshot_count=g_count;
        for(int i=0;i<g_count;i++)g_ui_snapshot[i]=g_events[i];
        ReleaseSRWLockShared(&g_lock);
    }
    if(generation!=g_ui_generation||now!=g_ui_rows_second||g_filter_revision!=g_ui_filter_revision){
        g_ui_row_count=0;
        for(int i=0;i<g_ui_snapshot_count&&g_ui_row_count<1024;i++){
            if(g_ui_snapshot[i].utc>now-60&&priyom::filter_match_event(g_ui_snapshot[i],g_station_filter))
                g_ui_rows[g_ui_row_count++]=i;
        }
        g_ui_generation=generation;g_ui_rows_second=now;g_ui_filter_revision=g_filter_revision;
        g_ui_countdown_second=-1;
    }
    if(now!=g_ui_countdown_second){
        for(int row=0;row<g_ui_row_count;row++)
            priyom::countdown_format(g_ui_snapshot[g_ui_rows[row]].utc,now,
                                     g_ui_countdowns[row],sizeof(g_ui_countdowns[row]));
        g_ui_countdown_second=now;
    }
}
// Both Refresh buttons share one tooltip, based on the timestamp of the
// LAST SUCCESSFULLY downloaded AND parsed Priyom calendar. A failed attempt
// never replaces that timestamp. All displayed strings are ASCII only.
static void refresh_button(){
    if(ui_Button(PRIYOM_REFRESH,ImVec2()))request_refresh();
    if(!ui_IsItemHovered(0))return;
    priyom::i64 last=0;
    int fetch_state=0;
    AcquireSRWLockShared(&g_lock);
    last=g_last_fetch;
    fetch_state=g_fetch_state;
    ReleaseSRWLockShared(&g_lock);
    if(last<=0){
        ui_SetTooltip(PRIYOM_NO_UPDATE);
        return;
    }
    char tooltip[160]=PRIYOM_LAST_UPDATE;
    append_date(tooltip,sizeof(tooltip),last/86400);
    append(tooltip,sizeof(tooltip)," ");
    append_utc_hms(tooltip,sizeof(tooltip),last);
    append(tooltip,sizeof(tooltip)," UTC");
    if(fetch_state==2)append(tooltip,sizeof(tooltip),PRIYOM_LAST_FAILED);
    ui_SetTooltip("%s",tooltip);
}
static void global_auto_and_clock(bool floating,priyom::i64 now){
    // One persisted master state, two independent ImGui IDs. The per-event
    // checkboxes remain selected when the master switch is turned OFF.
    ImVec2 width=ui_GetContentRegionAvail();
    if(ui_Checkbox(floating?PRIYOM_AUTO_TUNE "##priyom_master_float":
                           PRIYOM_AUTO_TUNE "##priyom_master_side",&g_auto_global)){
        save_global_auto(); // one disk write per user change, never per frame
    }
    if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_MASTER);
    // Avoid clipping the clock in narrow SDR++ sidebars.
    if(width.x>=320.0f)ui_SameLine(0,12);
    update_utc_clock(now);
    // ### keeps the ImGui ID stable when the displayed seconds change.
    // Both views use the same URL but have independent widget IDs.
    char clock_label[80];copy(clock_label,sizeof(clock_label),g_utc_clock_text);
    append(clock_label,sizeof(clock_label),floating?"###priyom_utc_clock_float":"###priyom_utc_clock_side");
    if(ui_Selectable(clock_label,false,0,ImVec2()))open_schedule();
    if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_CLOCK,g_utc_clock_full);
}
static void station_search(bool floating){
    // One shared filter for floating and sidebar views; no network calls.
    ui_SetNextItemWidth(-1.0f);
    if(ui_InputTextWithHint(floating?"##priyom_search_float":"##priyom_search_side",
             PRIYOM_SEARCH_HINT,
             g_station_filter,sizeof(g_station_filter),0,0,0)){
        ++g_filter_revision;
    }
}
// Priyom widths (100,125,100,70,80,40) describe the total visible
// column dimensions, NOT just the space available to text. Dear ImGui
// TableSetupColumn expects an inner width and adds CellPaddingX (4px * 2)
// on top. Compensating for it keeps Auto close to 40px, not ~49px.
static float content_width_from_visible(float visible){
    const float w=visible-8.0f;
    return w>=20.0f?w:20.0f;
}
// The table needs just six visual column widths plus a scrollbar, not
// six *additional* 12px padding allowances as in the older AUTO FIX.
static float table_required_outer_width(int view){
    float total=0.0f;
    for(int i=0;i<6;i++)total+=g_column_widths[view][i];
    return total+16.0f; // scrollbar on ScrollY table
}
static float floating_minimum_width(){
    // Default width remains 542px. The user may resize freely, even below
    // the default table size (then ScrollX becomes available).
    return 180.0f;
}
static void draw_panel(bool floating){
    // Only controls and table. Both panels share the same opacity and schedule.
    priyom::i64 now=utc_now();
    if(!floating){
        if(ui_Button(g_float_open?PRIYOM_HIDE_WINDOW:PRIYOM_SHOW_WINDOW,ImVec2()))g_float_open=!g_float_open;
        ui_SameLine(0,5);
        refresh_button();
        opacity_slider(false);
    }else{
        refresh_button();
        ui_SameLine(0,7);
        if(ui_Checkbox("Auto##priyom_master_float",&g_auto_global))save_global_auto();
        if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_AUTO);
        ui_SameLine(0,7);
        update_utc_clock(now);
        char label[80];copy(label,sizeof(label),g_utc_clock_text);
        append(label,sizeof(label),"###priyom_utc_clock_float");
        // An auto-width ImGui Selectable occupies all remaining row width.
        // Give UTC a fixed hitbox so it cannot intercept slider clicks.
        if(ui_Selectable(label,false,0,ImVec2(105.0f,0.0f)))open_schedule();
        opacity_slider(true); // inserts its own SameLine once

    }
    if(!floating){
        global_auto_and_clock(false,now);
    }
    station_search(floating);
    update_ui_cache(now);
    int row_count=g_ui_row_count;
    const int*rows=g_ui_rows;
    const priyom::Event*snap=g_ui_snapshot;
    ImVec2 avail=ui_GetContentRegionAvail();
    // Six fixed-width, independently resizable columns.  In ImGui 1.87
    // NoHostExtendX (1<<16) makes the TABLE end after the last column,
    // instead of painting a phantom blank stripe after Auto.  WidthFixed
    // (1<<2) for every column avoids StretchSame redistributing space and
    // squeezing UTC. The user can resize each separator as before.
    // Flags: Resizable(0), NoSavedSettings(4), RowBg(6), Borders(7-10),
    // SizingFixedFit(13), NoHostExtendX(16), ScrollY(26).
    const int base_flags=(1<<0)|(g_fn_column_width?(1<<4):0)|(1<<6)|
                    (1<<7)|(1<<8)|(1<<9)|(1<<10)|(1<<13)|(1<<16)|(1<<26);
    float table_height=floating?avail.y-3.0f:320.0f;
    if(table_height<90)table_height=90;
    const int view=floating?1:0;
    // DO NOT center the table or shift its cursor X. ImGui already places
    // it 10px inside the window at 100% SDR++ scale. The ScrollY table's
    // own viewport is ~9px wider than its painted six-column grid; this
    // extra space must be allowed to extend into the right window padding,
    // not counted as a seventh column or as a visual right margin.
    // For a floating window with exact minimum width, avoid clamping
    // outer_width to the slightly smaller content-region width: clamping
    // would cut off Auto to make room for the invisible scroll gutter.
    // A fixed BeginTable width was the actual resize blocker: the frame
    // grew but the table viewport remained hard-coded to 531px.
    // Keep 10px window margins: visible grid = outer_width - 9px gutter.
    const float natural_outer=table_required_outer_width(view);
    float window_outer=floating?ui_GetWindowSize().x-11.0f:avail.x;
    if(window_outer<80.0f)window_outer=80.0f;
    const int flags=base_flags|((window_outer<natural_outer-0.5f)?(1<<25):0); // ScrollX only if smaller than table
    // No stretching of a specific column on every frame: resize logic is
    // handled once when the floating window size actually changes.
    const float actual_width=floating?(natural_outer<window_outer?natural_outer:window_outer)
                                     :(natural_outer<avail.x?natural_outer:avail.x);
    if(ui_BeginTable(floating?"##priyom_float_table_margin10":"##priyom_side_table_margin10",6,flags,ImVec2(actual_width,table_height),0)){
        ui_TableSetupColumn(PRIYOM_HEADER_STATION,1<<2,content_width_from_visible(g_column_widths[view][0]),0);
        ui_TableSetupColumn(PRIYOM_HEADER_FREQ,1<<2,content_width_from_visible(g_column_widths[view][1]),0);
        ui_TableSetupColumn("QTH",1<<2,content_width_from_visible(g_column_widths[view][2]),0);
        ui_TableSetupColumn("UTC",1<<2,content_width_from_visible(g_column_widths[view][3]),0);
        ui_TableSetupColumn(PRIYOM_HEADER_COUNTDOWN,1<<2,content_width_from_visible(g_column_widths[view][4]),0);
        ui_TableSetupColumn("Auto",1<<2,content_width_from_visible(g_column_widths[view][5]),0);
        ui_TableHeadersRow();
        track_column_widths(floating);
        // Dear ImGui clipper renders only rows visible in the table viewport.
        // Previously up to 250 rows were built every frame, even during dragging.
        ImGuiListClipper clip={};ui_ClipperCtor(&clip);
        ui_ClipperBegin(&clip,row_count,-1.0f);
        while(ui_ClipperStep(&clip))for(int row=clip.DisplayStart;row<clip.DisplayEnd;row++){
            int i=rows[row];const priyom::Event&e=snap[i];
            ui_PushID(i);ui_TableNextRow(0,0);
            ui_TableNextColumn();if(ui_Selectable(e.station,false,0,ImVec2()))open_station(e.station);
            ui_TableNextColumn();char f[64];event_freq(e,f,sizeof(f));
            if(!e.search){
                // Unit "kHz" is already in the header, so never repeat it in
                // each row. This also saves width for longer frequencies.
                for(usize n=0;f[n];n++)if(f[n]==' '&&f[n+1]=='k'&&f[n+2]=='H'&&f[n+3]=='z'&&f[n+4]==' '){
                    usize j=n+1;while(f[j+4]){f[j]=f[j+4];j++;}f[j]=0;break;
                }
            }
            if(ui_Selectable(f,false,0,ImVec2())&&!e.search)tune(e);
            ui_TableNextColumn();
            const char*country=priyom::qth::find(g_ui_qth,g_ui_qth_count,e.station);
            paint_qth_flag(country);
            // QTH ALWAYS displays full Priyom country name; never ISO abbreviations.
            ui_TextUnformatted(priyom_display_country(country),0);
            if(ui_IsItemHovered(0))ui_SetTooltip(country?PRIYOM_TOOLTIP_QTH:PRIYOM_TOOLTIP_QTH_MISSING,country?priyom_display_country(country):"");
            ui_TableNextColumn();char t[48];event_clock(e,now,t,sizeof(t));
            if(ui_Selectable(t,false,0,ImVec2()))open_station_schedule(e.station);
            if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_SCHEDULE,e.station);
            ui_TableNextColumn();ui_TextUnformatted(g_ui_countdowns[row],0);
            if(ui_IsItemHovered(0))ui_SetTooltip(PRIYOM_TOOLTIP_COUNTDOWN);
            ui_TableNextColumn();priyom::Key k=priyom::key_of(e);
            bool checked=armed(k);
            if(e.search||mode_for(e.mode)<0)ui_TextUnformatted("-",0);
            else if(ui_Checkbox("##armed",&checked))set_armed(k,checked);
            ui_PopID();
        }
        ui_ClipperDtor(&clip);
        ui_EndTable();
    }
}
static void menu_frame(void*){if(g_supported&&g_enabled)draw_panel(false);}
static void window_frame(void*,ContextHook*){
    // Restore actual mouse and wheel before building Priyom's controls.
    // ImGui already applied the wheel to the hovered child table at NewFrame.
    restore_overlay_mouse(true);
    if(!g_supported||!g_enabled||!g_float_open){g_floating_rect[2]=g_floating_rect[3]=0;return;}
    ui_SetNextWindowPos(ImVec2(300,180),2,ImVec2());
    const float min_width=floating_minimum_width();
    // Minimum width is based on the six actually painted columns plus
    // 10px per side; no invisible scrollbar strip is counted as a margin.
    // User-chosen larger sizes remain savable in this new geometry profile.
    if(g_floating_size.x<min_width){
        g_floating_size.x=min_width;
        g_floating_size_dirty=true;
    }
    ui_SetNextWindowSize(g_floating_size,g_apply_floating_size_first_frame?1:2);
    g_apply_floating_size_first_frame=false;
    ui_SetNextWindowSizeConstraints(ImVec2(min_width,175),ImVec2(3.402823e38f,3.402823e38f),0,0);
    // ImGuiStyleVar_Alpha (0) affects EVERY element including title bar,
    // borders, text, widgets, table headers, rows and scrollbars.
    // Unlike SetNextWindowBgAlpha, this is not limited to the table/window bg.
    float alpha=g_opacity_percent/100.0f;
    ui_PushStyleVarFloat(0,alpha);
    // Only the table owns vertical scrolling; the outer floating window should
    // not reserve a second scrollbar (it created the broad blank right stripe).
    const int floating_window_flags=(1<<3); // ImGuiWindowFlags_NoScrollbar
    bool visible=ui_Begin(PRIYOM_WINDOW_TITLE "##priyom_floating",&g_float_open,floating_window_flags);
    if(g_float_open){
        ImVec2 pos=ui_GetWindowPos(),sz=ui_GetWindowSize();
        track_floating_size(sz,g_float_open);
        g_floating_rect[0]=pos.x;g_floating_rect[1]=pos.y;
        g_floating_rect[2]=sz.x;g_floating_rect[3]=sz.y;
    }else {
        g_floating_rect[2]=g_floating_rect[3]=0;
        if(g_floating_size_dirty)save_floating_size();
    }
    if(visible)draw_panel(true);
    ui_End();
    ui_PopStyleVar(1);
    // Essential++ V28 draws the green marker using GetForegroundDrawList.
    // If its EndFramePre callback runs after ours, it sees an off-screen
    // mouse position and cannot draw through Priyom. If it ran earlier,
    // it already saw the masked position from NewFramePost.
    if(g_float_open&&g_mask_frame==ui_GetFrameCount()){
        u8*io=(u8*)ui_GetIO();
        if(io){
            *(ImVec2*)(io+IO_MOUSE_POS)=ImVec2(-100000.0f,-100000.0f);
            g_after_window_mask=true;
        }
    }
}
static ModuleManager::Instance* g_menu_instance=0;
static void bind_ui(){
    if(g_menu_bound)return;
    CoreString name;core_stringFromText(&name,"Priyom");
    menu_register(core_menu,&name,menu_frame,0,g_menu_instance);g_menu_bound=true;
    g_context=ui_GetContext();
    if(g_context){
        ContextHook h={0,1,0,input_begin_frame,0};g_input_hook=ui_AddHook(g_context,&h);
        h.Callback=auto_frame;g_tick_hook=ui_AddHook(g_context,&h);
        h.Type=2;h.Callback=window_frame;g_window_hook=ui_AddHook(g_context,&h);
        h.Type=3;h.Callback=input_end_frame;g_restore_hook=ui_AddHook(g_context,&h);
    }
}
static void unbind_ui(){
    restore_overlay_mouse(false);
    if(g_context){
        if(g_input_hook)ui_RemoveHook(g_context,g_input_hook);
        if(g_tick_hook)ui_RemoveHook(g_context,g_tick_hook);
        if(g_window_hook)ui_RemoveHook(g_context,g_window_hook);
        if(g_restore_hook)ui_RemoveHook(g_context,g_restore_hook);
        g_input_hook=g_tick_hook=g_window_hook=g_restore_hook=0;g_context=0;
    }
    if(g_menu_bound){CoreString name;core_stringFromText(&name,"Priyom");menu_remove(core_menu,&name);g_menu_bound=false;}
}
class PriyomInstance:public ModuleManager::Instance{
public:
    ~PriyomInstance()override{}
    void postInit()override{}
    void enable()override{g_enabled=true;}
    void disable()override{g_enabled=false;g_overlay_drag=false;restore_overlay_mouse(false);}
    bool isEnabled()override{return g_enabled&&g_supported;}
};
alignas(16) static u8 g_instance_buf[128];static PriyomInstance*g_instance=0;
void* operator new(usize,void*p) noexcept{return p;}
void operator delete(void*) noexcept{}
void operator delete(void*,usize) noexcept{}
extern "C" {int _fltused=0;}
EXPORT const ModuleManager::ModuleInfo_t _INFO_={"Priyom","Priyom station schedules, UTC clock/countdown, global/per-event auto-tune","OpenAI",2,3,0,1};
EXPORT void _INIT_(){
    g_supported=supported_core();if(!g_supported)return;
    resolve_optional_imgui();
    build_settings_path();
    if(!load_ini()){
        load_settings();load_opacity();load_global_auto();load_column_widths();load_floating_size();
        save_ini(); // one-time migration from historical LOCALAPPDATA text files
    }
    // Register the sidebar at module initialization, even if SDR++ has not
    // created a module instance. V2.0 had moved this to _CREATE_INSTANCE_
    // and the Priyom entry disappeared on installations without that instance.
    if(!g_instance)g_instance=new((void*)g_instance_buf) PriyomInstance();
    g_menu_instance=g_instance;
    bind_ui();
    InterlockedExchange(&g_stop,0);InterlockedExchange(&g_force_refresh,0);
    g_thread=CreateThread(0,0,worker,0,0,0);
    if(!g_thread){AcquireSRWLockExclusive(&g_lock);g_fetch_state=2;ReleaseSRWLockExclusive(&g_lock);}
}
EXPORT ModuleManager::Instance* _CREATE_INSTANCE_(void*){
    if(!g_instance){g_instance=new((void*)g_instance_buf) PriyomInstance();}
    g_menu_instance=g_instance;bind_ui();return g_instance;
}
EXPORT void _DELETE_INSTANCE_(ModuleManager::Instance*){
    // The sidebar keeps an instance pointer for its native enable checkbox.
    // Unregister before freeing the instance so the pointer never dangles.
    unbind_ui();g_menu_instance=0;
    if(g_instance){g_instance->~PriyomInstance();g_instance=0;}
}
EXPORT void _END_(){
    g_enabled=false;InterlockedExchange(&g_stop,1);
    if(g_thread){WaitForSingleObject(g_thread,0xFFFFFFFF);CloseHandle(g_thread);g_thread=0;}
    unbind_ui();g_menu_instance=0;
    if(g_instance){g_instance->~PriyomInstance();g_instance=0;}
    save_ini();g_opacity_dirty=false;g_supported=false;
}
"""Compile standalone Priyom SDR++ Windows x64 DLL with LLVM/lld."""
from pathlib import Path
import re, subprocess, shutil, argparse
parser=argparse.ArgumentParser()
parser.add_argument('--lang',choices=('pl','en'),default='en')
args=parser.parse_args()
root=Path(__file__).resolve().parent
out=root/('build_'+args.lang);out.mkdir(exist_ok=True)
def run(*args):
    subprocess.run(list(map(str,args)),check=True)
def tool(n):
    t=shutil.which(n)
    if not t: raise SystemExit('Missing '+n)
    return t
text=(root/'priyom.cpp').read_text()
core=sorted(set(re.findall(r'CORE_ALIAS\("([^"]+)"\)',text)))
imports={
 'sdrpp_core.dll':core,
 'KERNEL32.dll':['GetSystemTimeAsFileTime','GetSystemTime','GetModuleHandleA','GetModuleFileNameA','GetProcAddress','GetEnvironmentVariableA','CreateDirectoryA','CreateFileA','ReadFile','WriteFile','CloseHandle','CreateThread','WaitForSingleObject','Sleep','AcquireSRWLockExclusive','ReleaseSRWLockExclusive','AcquireSRWLockShared','ReleaseSRWLockShared'],
 'SHELL32.dll':['ShellExecuteA'],
 'api-ms-win-crt-string-l1-1-0.dll':['memcpy','memset'],
 'api-ms-win-crt-heap-l1-1-0.dll':['malloc','free'],
 'WINHTTP.dll':['WinHttpOpen','WinHttpConnect','WinHttpOpenRequest','WinHttpSetTimeouts','WinHttpSendRequest','WinHttpReceiveResponse','WinHttpQueryHeaders','WinHttpReadData','WinHttpCloseHandle'],
}
libs=[]
for dll,symbols in imports.items():
    stem=dll[:-4];deffile=out/(stem+'.def');lib=out/(stem+'.lib')
    deffile.write_text('LIBRARY "'+dll+'"\nEXPORTS\n'+''.join('  "'+s+'"'+(' DATA' if s in ('waterfall','mainWindow','modComManager','vfoManager','menu') else '')+'\n' for s in symbols))
    run(tool('lld-link'),'/dll','/noentry','/machine:x64',f'/def:{deffile}',f'/out:{out/(stem+".dll")}',f'/implib:{lib}','/nodefaultlib')
    libs.append(lib)
obj=out/'priyom.obj'
run(tool('clang'),'--target=x86_64-pc-windows-msvc','-std=c++17','-O2','-fno-exceptions','-fno-rtti','-fno-stack-protector','-ffreestanding','-fno-builtin','-Wno-return-type-c-linkage',f'-DPRIYOM_LANG_EN={1 if args.lang == "en" else 0}','-c',root/'priyom.cpp','-o',obj)
run(tool('lld-link'),'/dll','/noentry','/machine:x64','/subsystem:windows','/nodefaultlib','/opt:ref','/opt:icf','/timestamp:0',f'/out:{out/"priyom.dll"}',obj,*libs)
print('Built',args.lang,out/'priyom.dll')
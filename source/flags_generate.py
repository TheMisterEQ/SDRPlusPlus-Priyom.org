"""Generate flag geometry for native ImGui drawing; requires Pillow only when regenerating.
Compiled priyom_flags.h is self-contained and does not load fonts, textures or assets.
Icons are 24x16 tiny vector-like pixel approximations of sovereign flags.
"""
from PIL import Image, ImageDraw
from pathlib import Path
from math import pi, cos, sin
W,H=24,16
pal={
    '.':(255,255,255),'r':(218,36,52),'d':(168,17,36),'b':(0,65,151),
    'n':(10,31,103),'l':(70,153,221),'k':(17,19,24),'y':(255,208,37),
    'g':(0,140,83),'h':(0,101,65),'o':(244,138,34),'s':(204,43,58),
    'c':(27,117,188),'e':(119,4,37),'f':(245,239,224),'a':(122,74,39),
    'v':(40,87,177),'m':(132,185,243),'x':(250,244,80),
}
flags={}
def image(background):
    im=Image.new('RGB',(W,H),pal[background]); return im,ImageDraw.Draw(im)
def rect(d,box,c):d.rectangle(box,fill=pal[c])
def poly(d,points,c):d.polygon(points,fill=pal[c])
def circ(d,box,c):d.ellipse(box,fill=pal[c])
def star(d,cx,cy,r,c,inner=.45,points=5):
    p=[]
    for i in range(points*2):
        a=-pi/2 + i*pi/points
        rad = r if i%2==0 else r*inner
        p.append((cx+rad*cos(a),cy+rad*sin(a)))
    poly(d,p,c)
def add(code,draw):
    im,d=image('.');draw(im,d);flags[code]=im

def horiz(cs):
    def draw(im,d):
        for i,c in enumerate(cs):rect(d,(0,int(i*H/len(cs)),W-1,int((i+1)*H/len(cs))-1),c)
    return draw
def vert(cs):
    def draw(im,d):
        for i,c in enumerate(cs):rect(d,(int(i*W/len(cs)),0,int((i+1)*W/len(cs))-1,H-1),c)
    return draw
for code,col in {
'PL':'r','UA':'y','RU':'r','DE':'y','AT':'r','FR':'r','IT':'r','RO':'r',
'BG':'r','HU':'g','NL':'b','BE':'r','IE':'o','LT':'r','LV':'e','EE':'.',
'VN':'r','EG':'k','IR':'r','IN':'g','RS':'.','LU':'l','TH':'r','CO':'r',
}.items():
    pass
for code,colors in {
'PL':'.r','UA':'by','RU':'.br','DE':'kry','AT':'r.r','FR':'b.r',
'IT':'g.r','RO':'byr','BG':'.gr','HU':'r.g','NL':'r.b',
'BE':'kyr','IE':'g.o','LT':'ygr','LV':'e.e','EE':'lk.',
'VN':'r','EG':'r.k','IR':'g.r','IN':'o.g','RS':'rb.',
'LU':'r.l','TH':'rb.r','CO':'yrb','ID':'r.',
}.items():
    add(code, vert(colors) if code in ('FR','IT','RO','BE','IE') else horiz(colors))

def czech(im,d):
    horiz('.r')(im,d);poly(d,[(0,0),(12,8),(0,15)],'b')
add('CZ',czech)
def slovak(im,d):
    horiz('.br')(im,d);rect(d,(6,5,11,12),'r');rect(d,(7,5,10,8),'.');rect(d,(8,7,9,10),'b')
add('SK',slovak)
def croatia(im,d):
    horiz('r.b')(im,d);rect(d,(10,5,14,10),'.');rect(d,(11,5,13,7),'r')
add('HR',croatia)
def slovenia(im,d):
    horiz('.br')(im,d);rect(d,(6,2,10,7),'r');rect(d,(7,3,9,5),'b')
add('SI',slovenia)
def sweden(im,d):
    rect(d,(0,0,23,15),'b');rect(d,(7,0,10,15),'y');rect(d,(0,6,23,9),'y')
add('SE',sweden)
def finland(im,d):
    rect(d,(7,0,11,15),'b');rect(d,(0,6,23,10),'b')
add('FI',finland)
def denmark(im,d):
    rect(d,(0,0,23,15),'r');rect(d,(7,0,10,15),'.');rect(d,(0,6,23,9),'.')
add('DK',denmark)
def norway(im,d):
    rect(d,(0,0,23,15),'r');rect(d,(6,0,12,15),'.');rect(d,(0,5,23,11),'.');rect(d,(8,0,10,15),'b');rect(d,(0,7,23,9),'b')
add('NO',norway)
def uk(im,d):
    rect(d,(0,0,23,15),'n')
    for y in range(16):
        x=int(y*23/15)
        rect(d,(max(0,x-2),y,min(23,x+2),y),'.')
        x2=23-x
        rect(d,(max(0,x2-2),y,min(23,x2+2),y),'.')
    rect(d,(0,5,23,10),'.');rect(d,(9,0,14,15),'.')
    rect(d,(0,7,23,8),'r');rect(d,(11,0,12,15),'r')
add('GB',uk)
def usa(im,d):
    for i in range(13):
        y1=int(i*H/13);y2=int((i+1)*H/13)-1
        rect(d,(0,y1,23,max(y1,y2)),'r' if i%2==0 else '.')
    rect(d,(0,0,10,8),'n')
    for j in range(4):
        for i in range(5):rect(d,(1+i*2+(j%2),1+j*2,1+i*2+(j%2),1+j*2),'.')
add('US',usa)
def taiwan(im,d):
    rect(d,(0,0,23,15),'r');rect(d,(0,0,12,8),'n')
    star(d,6,4,4,'.',inner=.78,points=12);circ(d,(4,2,8,6),'.')
add('TW',taiwan)
def china(im,d):
    rect(d,(0,0,23,15),'r');star(d,5,5,4,'y')
    for x,y in [(12,2),(15,4),(15,8),(12,10)]:star(d,x,y,1.3,'y')
add('CN',china)
def japan(im,d):circ(d,(7,3,17,13),'r')
add('JP',japan)
def korea(im,d):
    circ(d,(8,3,16,12),'r');rect(d,(8,8,16,12),'b')
    for x,y in [(2,3),(2,11),(19,3),(19,11)]:rect(d,(x,y,x+3,y+1),'k')
add('KR',korea)
def north_korea(im,d):
    rect(d,(0,0,23,15),'b');rect(d,(0,3,23,12),'r');rect(d,(0,2,23,2),'.');rect(d,(0,13,23,13),'.')
    circ(d,(3,4,12,11),'.');star(d,7.5,7.5,3.7,'r')
add('KP',north_korea)
def vietnam(im,d):
    rect(d,(0,0,23,15),'r');star(d,12,8,6,'y')
add('VN',vietnam)
def turkey(im,d):
    rect(d,(0,0,23,15),'r');circ(d,(4,3,14,13),'.');circ(d,(7,3,16,13),'r');star(d,17,8,3,'.')
add('TR',turkey)
def israel(im,d):
    rect(d,(0,2,23,4),'b');rect(d,(0,11,23,13),'b')
    poly(d,[(12,4),(8,10),(16,10)],'b');poly(d,[(12,12),(8,6),(16,6)],'b')
    poly(d,[(12,6),(10,9),(14,9)],'.')
add('IL',israel)
def cuba(im,d):
    horiz('b.b.b')(im,d);poly(d,[(0,0),(11,8),(0,15)],'r');star(d,4,8,3.3,'.')
add('CU',cuba)
def canada(im,d):
    vert('r.r')(im,d);star(d,12,8,5,'r',points=7)
add('CA',canada)
def australia(im,d):
    rect(d,(0,0,23,15),'n');rect(d,(0,0,12,8),'n');rect(d,(0,3,12,5),'.');rect(d,(5,0,7,8),'.')
    rect(d,(0,4,12,4),'r');rect(d,(6,0,6,8),'r')
    for x,y in [(17,3),(19,10),(14,12),(9,12)]:star(d,x,y,2,'.')
add('AU',australia)
def egypt(im,d):
    horiz('r.k')(im,d);rect(d,(11,6,13,10),'y')
add('EG',egypt)
def india(im,d):
    horiz('o.g')(im,d);circ(d,(10,5,14,10),'n');circ(d,(11,6,13,9),'.')
add('IN',india)
def iran(im,d):
    horiz('g.r')(im,d);rect(d,(11,6,13,10),'r')
add('IR',iran)
def moldova(im,d):
    vert('byr')(im,d);rect(d,(11,5,13,10),'a');rect(d,(11,5,13,5),'y')
add('MD',moldova)
def belarus(im,d):
    rect(d,(0,0,23,15),'r');rect(d,(0,10,23,15),'g');rect(d,(0,0,3,15),'.')
    for y in range(1,16,3):rect(d,(1,y,2,y),'r')
add('BY',belarus)
def serbia(im,d):
    horiz('rb.')(im,d);rect(d,(6,4,10,9),'y');rect(d,(7,6,9,9),'r')
add('RS',serbia)
def greece(im,d):
    horiz('b.b.b.b.')(im,d);rect(d,(0,0,9,9),'b');rect(d,(4,0,5,9),'.');rect(d,(0,4,9,5),'.')
add('GR',greece)
def switzerland(im,d):
    rect(d,(0,0,23,15),'r');rect(d,(10,3,14,12),'.');rect(d,(7,6,17,9),'.')
add('CH',switzerland)
# Generate smallest contiguous rectangles for each same-color palette region.
# Color runs on a scanline that repeat in the next row are merged vertically.
entries=[];allrect=[]
for code in sorted(flags):
    im=flags[code];active={};done=[]
    for y in range(H):
        row=[];x=0
        while x<W:
            pix=im.getpixel((x,y))
            c=next((k for k,v in pal.items() if v==pix),None)
            if c is None:raise ValueError((code,x,y,pix))
            x2=x+1
            while x2<W and im.getpixel((x2,y))==pix:x2+=1
            row.append((x,x2,c));x=x2
        new={}
        for key in row:
            if key in active:
                x1,x2,y1,_,c=active.pop(key)
                new[key]=(x1,x2,y1,y+1,c)
            else:new[key]=(key[0],key[1],y,y+1,key[2])
        done.extend(active.values());active=new
    done.extend(active.values())
    entries.append((code,len(allrect),len(done)))
    allrect.extend((x1,y1,x2,y2,c) for x1,x2,y1,y2,c in done)
print('flag count',len(flags),'rect total',len(allrect),'max',max((n,code) for code,_,n in entries))
path=Path(__file__).parent/'priyom_flags.h'
lines=['// Tiny national flag icons drawn into ImGui via AddRectFilled: no emoji glyphs, no textures.',
       '// Auto-generated by flags_generate.py; shipping this header requires no Python or Pillow.',
       '// Icons approximate the national flags at 24x16 px, transparent only at no locations.',
       '#ifndef PRIYOM_FLAGS_H','#define PRIYOM_FLAGS_H','namespace priyom {namespace flags {',
       'typedef unsigned char byte;','struct Rect {byte x0,y0,x1,y1,palette;};',
       'struct Flag {char iso[3];unsigned short start,count;};',
       'static const unsigned width=24,height=16;',
       'static const unsigned palette[]={']
for k,v in pal.items():
    r,g,b=v;lines.append('  0xff%02x%02x%02xu, // %s'% (b,g,r,k))
lines.append('};')
ids={k:i for i,k in enumerate(pal.keys())}
lines.append('static const Rect shapes[]={')
for x1,y1,x2,y2,c in allrect:lines.append(f'  {{{x1},{y1},{x2},{y2},{ids[c]}}},')
lines.append('};')
lines.append('static const Flag catalog[]={')
for code,idx,n in entries:lines.append(f'  {{"{code}",{idx},{n}}},')
lines.extend(['};',
  'static bool equal(const char*a,const char*b){return a&&b&&a[0]==b[0]&&a[1]==b[1]&&!a[2]&&!b[2];}',
  'static const Flag*get(const char*iso){if(!iso)return 0;for(unsigned i=0;i<sizeof(catalog)/sizeof(catalog[0]);i++)if(equal(catalog[i].iso,iso))return &catalog[i];return 0;}',
  'template<typename Paint> static bool draw(const char*iso,Paint paint){',
  ' const Flag*f=get(iso);if(!f)return false;',
  ' for(unsigned i=f->start;i<f->start+f->count;i++){const Rect &r=shapes[i];paint(r.x0,r.y0,r.x1,r.y1,palette[r.palette]);}',
  ' return true;',
  '}',
  '}}','#endif'])
path.write_text('\n'.join(lines)+'\n',encoding='utf-8')

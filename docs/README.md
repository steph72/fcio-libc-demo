# A FCIO tutorial


### What is FCIO?

*fcio* is a lightweight C library providing full colour mode support for C programmers on the MEGA65:

- standard text input/output facilities (fc_puts, fc_printf, fc_input...)
- text window support (fc_makewin, fc_setwin...)
- dynamically loading and displaying bitmap images (fc_loadFCI, fc_displayFCI...)
- palette manipulation (fc_loadPalette, fc_setPalette, fc_fadePalette...)
- and some various other bells and whistles

Since *fcio* is now a part of [mega65-libc](https://github.com/MEGA65/mega65-libc), I figured people might be interested in how to load and display pictures and text using the fcio library. So this is a little tutorial showing how to accomplish exactly that.

### What is Full Colour Mode?

Full Colour Mode (FCM for short) is a new screen mode of the MEGA65's video controller (the VIC-IV). Full Colour Mode allows you to  mix text and 24 bit graphics on the same screen, as well as performing all kinds of neat tricks with the display, such as overlaying additional content, flipping and mirroring character cells and much more.

Since in FCM, each 8x8 pixel character cell on the screen is referenced by a 16 bit pointer, it is not compatible to 'traditional' C64 text modes and therefore not accessible via standard console libraries, such as mega65-libc's own *conio.h*. This is where *fcio* comes in.

Please note that at the moment, FCIO "only" supports displaying graphics and text, but this might very well change in the future.

## The Tutorial

### 1. Hello FCIO

Let's start with something really simple: Switching the screen to full colour mode and displaying some text. In order to do so, simply clone the mega65-libc to a convenient location, type in the following code and save it at **test.c**.

```c
#include <fcio.h>

void main() {
   fc_init(0,0,0,0,0);
   fc_puts("Hello world!");
   while(1);
}
```
Assuming you have the mega65-libc in the same folder as the test program, compile your program with

```
cl65 -Imega65-libc/cc65/include -o test test.c mega65-libc/cc65/src/fcio.c mega65-libc/cc65/src/memory.c
```

(you need to compile both `fcio.c` and `memory.c`, because `fcio.c` depends on `memory.c`. In the later stages of this tutorial, we'll use `SCons` to do the grunt work for us; but for now, calling CC65's compile and link utility `cl65` directly will suffice)

After `cl65` has done its magic, there should be a new `test` binary in your current folder. You can now transfer it to your MEGA65 using your trusty `m65` utility like so:

```
m65 -4 test -l /dev/ttyUSB2
```

or, if your MEGA65 got stuck in the mail, fire up your xemu emulator:

```
xemu-xmega65 -prg ./test
```

In any case, the result should be the same: A green 'hello world' on a black background.

<img src="tut0.png" width="384"/><br/>

Nothing much, you might think, but you have just successfully initialized a full colour mode screen and put some text on it. Now, lets make things a little bit more interesting, shall we?

### 2. Configuring the screen

At initialization time, there is a lot of things going on behind the scenes. 
The prototype of `fcio_init` is:

```c
void fc_init(byte h640, byte v400, fcioConf *config, byte rows, char *reservedBitmapFile);
```

So, when initializing the library with `fc_init(0,0,0,0,0)`, here is what actually happens:

- the H640 and V400 flags are set to 0, giving us a low resolution (320x200) screen.
- by passing "0" as the "config" parameter, the standard memory configuration is selected (fcio allows you to place bitmap and character data anywhere in memory, but it can also handle those things for you when you pass '0')
- by passing "0" as the "rows" parameter, a standard screen with 25 character rows is created. Unlike the C64, the MEGA65 allows arbitrary screen configurations. In PAL mode, it is possible to have up to 33 character rows in non-V400 modes
- and finally, by passing "0" as the reservedBitmapFile parameter, no reserved bitmap is loaded at initialization. Don't worry about that now, we'll be looking at reserved bitmaps later.

So, with that knowledge, it's quite easy to set up a high resolution screen with a few extra columns to play with:

```c
#include <fcio.h>

void main() {
   byte i;
   fc_init(1,1,0,60,0);
   POKE(0xd020u,5);
   for (i=0;i<60;++i) {
      fc_textcolor(1+(i%14));
      fc_putsxy(i,i,"Hello world!");
   }
   while(1);
}
```


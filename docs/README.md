# A FCIO tutorial


### What is FCIO?

*fcio* is a lightweight C library providing full colour mode support for C programmers on the MEGA65:

- standard text input/output facilities (fc_puts, fc_printf, fc_input...)
- dynamically loading and displaying bitmap images (fc_loadFCI, fc_displayFCI...)
- palette manipulation (fc_loadPalette, fc_setPalette, fc_fadePalette...)
- and some varous other bells and whistles

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



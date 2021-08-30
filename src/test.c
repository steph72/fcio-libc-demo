#include <conio.h>
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <fcio.h>
#include <c64.h>
#include <cbm.h>


void main(void)
{
    byte i;

    cbm_k_bsout(13);  // issue CR to cancel leftover quote mode from wrapper (or whatever?)
    cbm_k_bsout(14);  // lowercase
    cbm_k_bsout(147); // clr

    // === using CONIO for standard console display ===
    mega65_io_enable();
    conioinit();
    setscreensize(80, 25);
    setscreenaddr(0x14000);
    clrscr();
    bordercolor(0);
    textcolor(0);
    bgcolor(5);
    cprintf("this is a little demo program to show\n"
            "conio.h and fcio.h coexisting peacefully.\n\n"
            "press any key to switch to full colour mode...");
    cgetc();
    clrscr();

    // === FCIO stuff starts here ===

    fc_init(true, false, NULL, 32, NULL);
    fc_textcolor(COLOUR_YELLOW);
    bordercolor(COLOR_BLUE);

    for (i = 0; i < 31; ++i)
    {
        fc_gotoxy(i, i);
        fc_textcolor(i&15);
        fc_puts("well hello from fcio!!");
    }
    fc_displayFCIFile("luna2.fci", 40, 3);
    fc_textcolor(5);
    fc_putsxy(0,31," -- press any key --");
    cgetc();
    fc_clrscr();

    while (1)
        ;
}
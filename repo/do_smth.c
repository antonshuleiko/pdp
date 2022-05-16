#include <stdio.h>
#include "all.h"
#include<stdlib.h>


word reg[8]; //регистры R0 .. R7

void do_clr()
{
    reg[dd.adr] = 0;
}
void do_halt()
{
    trace("THE END!!!\n");
    for( int i = 0; i < 7; i ++)
        printf("r%d:%o ", i, reg[i]);
    exit(0);
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov, 011},
    {0170000, 0060000, "add", do_add, 011},
    {0177777, 0000000, "halt", do_halt, 0},
    {0177000, 0077000, "sob", do_sob, 0},
    {0007700, 0005000, "clr", do_clr, 001},
    {0000000, 0000000, "unknown", do_nothing, 0}
};
void do_mov() {
    w_write(dd.adr, ss.val);
    trace("_________%06o_______", dd.adr);
}
void do_add() 
{
    w_write(dd.adr, ss.val + dd.val);     // w & 7 это dd.adr
}
void do_nothing()
{
    printf("nothing\n");
}

void regs_print()
{
    printf("\t\t\t\t");
    for(int i = 0; i < 8; i++)
        printf("%d:%06o ", i, reg[i]);
    printf("\n");
}

void do_sob()
{
    word mw = w_read(pc - 2);
    int x = mw & 63;
    int re = (mw >> 6) & 7;
    if (--reg[re])
        reg[7] -= x * 2;
}
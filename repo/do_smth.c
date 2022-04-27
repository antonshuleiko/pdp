#include <stdio.h>
#include "all.h"
#include<stdlib.h>


word reg[8]; //регистры R0 .. R7

void do_halt()
{
    trace("THE END!!!\n");
    for( int i = 0; i < 7; i ++)
        printf("r%d:%o ", i, reg[i]);
    exit(0);
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177777, 0000000, "halt", do_halt},
    {0000000, 0000000, "unknown", do_nothing}
};
void do_mov() {
    w_write(dd.adr, ss.val);
}
void do_add() {}
void do_nothing() {}
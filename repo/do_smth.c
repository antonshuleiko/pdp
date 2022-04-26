#include <stdio.h>
#include "all.h"
#include<stdlib.h>


word reg[8]; //регистры R0 .. R7

void do_halt()
{
    trace("THE END!!!\n");
    exit(0);
}

Command cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
    {0177777, 0000000, "halt", do_halt},
};
void do_mov() {}
void do_add() {}
void do_nothing() {}
#include <stdio.h>
#include "pdp.c"
#include<stdlib.h>
#include "do_smth.c"

void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        if (w == 0)
        {
            trace("halt ");
            do_halt();
        }
    }
}
#include <stdio.h>
#include<stdlib.h>
#include "all.h"


void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        int word_points = 0;
        if (w == 0)
        {
            trace("halt ");
            do_halt();
        }
        for(int i = 0; i < 4; i++)
        {
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s ", cmd[i].name);
                cmd[i].do_func();
                word_points += 1;
            }
        }
        if(word_points == 0)
        {
            trace("unknown");
            do_nothing();
        }
    }
}
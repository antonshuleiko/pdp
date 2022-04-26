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
        for(int i = 0; ; i++)
        {
            /*if(cmd[i].name == (char *)("unknown"))
            {
                trace("AAAAAunknown\n");
                break;
            }*/
            if (w == 0)
            {
                trace("halt\n");
                do_halt();
            }
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s\n", cmd[i].name);
                cmd[i].do_func();
                word_points += 1;
                break;
            }
        }
    }
}
#include <stdio.h>
#include<stdlib.h>
#include "all.h"

Arg ss, dd;

Arg get_mr(word w, int forwhat)
{
    int diff = 0;           //сдвиг при проверке, байтовая ли операция 
    if(forwhat == GET_MR_DD)
        diff = 10;
    else
        diff = 16;
    Arg res;
    int r = w & 7;
    int mode = (w >> 3) & 7;
    switch (mode)
    {
    case 0:     //R3
        res.adr = r;
        res.val = reg[r];
        trace("R%o ", r);
        break;
    case 1:     //(R3)
        res.adr = reg[r];
        //res.val = w_read(res.adr);   //b_read
        if((w >> diff) == 0)
            res.val = w_read(res.adr);
        else if((w >> diff) == 1)
            res.val = b_read(res.adr);
        else
            trace("Something  incomprehensible case1\n");
        trace("(R%o) ", r);
        break;
    case 2:     //(R3)+     #3
        res.adr = reg[r];
        res.val = w_read(res.adr);  //todo b_read
        if((w >> diff) == 0)
        {
            res.val = w_read(res.adr);
            reg[r] += 2;
        }
        else if((w >> diff) == 1)
        {
            res.val = b_read(res.adr);
            reg[r] += 1;
        }
        else
            trace("Something  incomprehensible case2\n");
        trace("(R%o) ", r);
        if(r == 7)
            trace("#%o ", res.val);
        else
            trace("(R%o)+ ", r);
        break;
    default:
        fprintf(stderr, "Mode %o NOT IMPLEMENTED YET\n", mode);
        exit(1);
    }
    return res;
}

void run()
{
    pc = 01000;
    while(1)
    {
        word w = w_read(pc);
        trace("%06o %06o: ", pc, w);
        pc += 2;
        for(int i = 0; ; i++)
        {
            /*if(cmd[i].name == (char *)("unknown"))
            {
                trace("AAAAAunknown\n");
                break;
            }
            if (w == 0)
            {
                trace("halt\n");
                do_halt();
            }*/
            if((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace("%s\n", cmd[i].name);
                ss = get_mr(w >> 6, GET_MR_SS);
                dd = get_mr(w, GET_MR_DD);
                cmd[i].do_func();
                regs_print();
                break;
            }
        }
    }
}
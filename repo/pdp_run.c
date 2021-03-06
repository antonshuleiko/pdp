#include <stdio.h>
#include<stdlib.h>
#include "all.h"

Arg ss, dd;

int word_li_func(word w, int forwhat)
{
    int diff = 0;           //сдвиг при проверке, байтовая ли операция 
    if(forwhat == GET_MR_DD)
        diff = 10;
    else
        diff = 16;
    if((w >> diff) == 0)
        return 1;
    if((w >> diff) == 1)
        return 0; 
}

Arg get_mr(word w, int word_li)
{
    Arg res;
    int r = w & 7;
    int mode = (w >> 3) & 7;
    printf("-------%d-------\n", mode);
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
        if(word_li)
            res.val = w_read(res.adr);
        else if(word_li == 0)
            res.val = b_read(res.adr);
        else
            trace("Something  incomprehensible case1\n");
        trace("(R%o) ", r);
        break;
    case 2:     //(R3)+     #3
        res.adr = reg[r];
        res.val = w_read(res.adr);  //todo b_read
        if(word_li)
        {
            res.val = w_read(res.adr);
            reg[r] += 2;
        }
        else if(word_li == 0 && (r == 6 || r == 7))
        {
            res.val = b_read(res.adr);
            reg[r] += 1;
        }
        else
            trace("Something  incomprehensible case2\n");
        // trace("(R%o)## ", r);
        if(r == 7)
            trace("#%o ", res.val);
        else
            trace("(R%o)+ ", r);
        break;
    case 3:
        res.adr = w_read(reg[r]);
        if(word_li)
        {
            res.val = w_read(res.adr);
        }
        else if(word_li == 0 && (r == 6 || r == 7))
        {
            res.val = b_read(res.adr);
        }
        else
            trace("Something  incomprehensible case3\n");
        // trace("(R%o)## ", r);
        reg[r] += 2;
        if (r == 7) 
            trace(" @#%06o,", res.adr);
        else
            trace("@(R%o)+ ", r);
        break;
    default:
        fprintf(stderr, "Mode %o NOT IMPLEMENTED YET\n", mode);
        exit(1);
    }
    
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
                trace("%s ", cmd[i].name);
                if ((cmd[i].ssdd & 1) == 1)
                    dd = get_mr(w, word_li_func(w, GET_MR_DD));
                if (((cmd[i].ssdd >> 1) & 1) == 1)
                    ss = get_mr(w >> 6, word_li_func(w, GET_MR_SS));
                // trace("ss.a = %o ss.val=%o dd.a=%o dd.val=%o ", ss.adr, ss.val, dd.adr, dd.val);
                cmd[i].do_func();
                trace("\n");
                regs_print();
                break;
            }
        }
    }
}
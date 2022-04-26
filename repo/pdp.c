#include<stdio.h>
#include<assert.h>
#include<stdarg.h>
#include<errno.h>
#include<string.h>
#include "all.h"
#include<stdlib.h>

word mem[MEMSIZE];


/*void log(int log_level, const char * format, ...)
{
    va_list ap;
    va_start(ap, log level);

 
}*/
void mem_dump(Adress start, word n)
{
    Adress i;
    for(i = 0; i < n; i+=2) {
        word w = w_read(start + i);
        printf("%06ho : %06ho\n", start + i, w);
    }
}
void trace(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}
word w_read(Adress adr)
{
    assert(adr % 2 == 0);
    return mem[adr];
}
void w_write(Adress adr, word w)
{
    assert(adr % 2 == 0);
    mem[adr] = w;
}

byte b_read(Adress adr)
{
    byte b;
    if(adr % 2 == 0)
        b = mem[adr] & 0xFF; //b = (byte)mem[a]
    else
        b = mem[adr-1] >> 8 & 0xFF;
    return b;
}
void test_mem()
{
    word w0 = 0x0a;
    w_write(2, w0);
    word w_res = w_read(2);
    printf("%02hhx = %02hhx\n", w0, w_res);
    assert(w0 == w_res);

    Adress a = 6;
    byte b1 = 0xcb;
    byte b0 = 0x0a;
    word w = 0xcb0a;
    w_write(a, w);
    word wres = w_read(a);
    word b0res = b_read(a);
    word b1res = b_read(a+1);
    printf("ww/br \t %04hx = %02hhx%02hhx\n", wres, b1res, b0res);
    assert(b0 == b0res);
    assert(b1 == b1res);
}
void mytest_mem()
{
    w_write(01000, 0010101);
    w_write(01002, 0110101);
    w_write(01004, 0);
}
int main(int argc, char * argv[]) 
{
    char * filename = argv[argc - 1];
    FILE * fin  = fopen(filename, "r");
    if (fin == NULL)
    {
        perror(filename);
        return errno;
    }
    mytest_mem();
    run();
    fclose(fin);
    return 0;
}
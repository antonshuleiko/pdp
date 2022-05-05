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
    trace("_________%06o_______", dd.adr);
}
void do_add() {
    word m_w = w_read(pc - 2);
    w_write(m_w & 7, sum(ss.val, dd.val));     // w & 7 это dd.adr
}
void do_nothing() {
    printf("nothing\n");
}

void regs_print()
{
    for(int i = 0; i < 8; i++)
        printf("%d:%06o ", i, reg[i]);
    printf("\n");
}

unsigned sum(unsigned int a, unsigned int b)
{
    unsigned s = 0;
    unsigned carryin = 0; // перенос из предыдущего разряда
    unsigned k = 1; // маска для получения самого младшего бита
    unsigned temp_a = a;
    unsigned temp_b = b;
    while (temp_a || temp_b)
    {
        // извлечение самых младших битов
        unsigned ak = a & k, bk = b & k;

        // вычисляем бит который переносится в следующий разряд
        unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);

        // комбинация двух складываемых битов
        // и бита перенесенного из предыдущего разряда
        s |= (ak ^ bk ^ carryin);

        // то что будет перенесено в следующий разряд
        carryin = carryout << 1;

        // сдвигаем маску на один бит влево
        k <<= 1;

        // отрезаем уже обработанные младшие биты
        // остатки используются для контроля продолжения цикла
        temp_a >>= 1, temp_b >>= 1;
    }

    return s | carryin;
}
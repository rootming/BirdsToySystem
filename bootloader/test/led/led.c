#include "../include/s5pc110.h"

void delay()
{
    volatile int c = 0x100000;
    while (c--);
}

int main(void)
{
    volatile int i = 1;
     *(volatile unsigned int *)GPH0CON = 0x1111;
    while (1){
        *(volatile unsigned int *)GPH0DAT = i;
        i = i << 1;
        if(i == 0x100)
            i = 0x01;
        delay();
    }

    return 0;
}


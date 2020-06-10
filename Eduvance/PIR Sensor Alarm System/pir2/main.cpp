#include "mbed.h"
DigitalIn pir(PTA4);
DigitalOut led(LED1);
DigitalOut buzzer(PTD2);

int main()
{
    if(pir.read()==1)
    {
        led=0;
        buzzer=1;
        wait(5);  
        led=1;
        buzzer=0;
        }
        if(pir.read()==0)
        {
        led=1;
        buzzer=0;
            }
    }


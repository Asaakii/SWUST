#include "config.h"
#include "led.h"

int main()
{
    LedInit();
    LedPrint(0x12345678);
    while(1)
    {
        LedScan();
    }
    return (0);
}
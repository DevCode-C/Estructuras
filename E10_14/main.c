#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint32_t reverseBit(uint32_t number);

int main(void)
{
    uint32_t valor = 0;

    scanf("%u",&valor);
    reverseBit(valor);

    return 0;
}

uint32_t reverseBit(uint32_t number)
{
    uint32_t displayMask = 1<<31;
    uint32_t value = number;
    // uint32_t j = 31;
    printf("Valor sin modificar: %lu\tHex: %x\t\t bin: ",number,number);
    for (uint8_t i = 1; i <= 32; ++i)
    {
        if (value & displayMask)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
        value <<= 1;
        if (i % 8 == 0)
        {
            printf("  ");
        }
    }
    printf("\n");
    value = 0;
    uint8_t bit = 31;
    for (uint8_t j = 0; j <= 31; j++)
    {
        
        value |= (number & (1<<bit))<<bit;
        bit--;
    }

    printf("Valor sin modificar: %lu\tHex: %x\t\t bin: ",value,value);
    for (uint8_t i = 1; i <= 32; i++)
    {
        if (value & displayMask)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
        value <<= 1;
        if (i % 8 == 0)
        {
            printf("  ");
        }
    }
    printf("\n");
    

    return number;
}

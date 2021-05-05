#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    char character = 0;
    uint32_t word = 0;
    // printf("Introduce el caracter que desee:\t");
    // scanf("%c",&character);
    
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("Introduce el caracter que desee:\t");
        fflush(stdin);
        scanf("%c",&character);

        word |= character << (8 * i);
    }
    printf("%x\n",word);

    for (uint8_t j = 0; j < 4; j++)
    {
        character = (word>>(8*j)) & 0xff;
        // character = word & 0xff;
        printf("word: %x\t,%d\t",word,j);
        printf("Character: %c\n",character);
    }
    

    return 0;
}
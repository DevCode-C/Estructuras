#include "SML.h"
#define _OPEN_SYS_ITOA_EXT
#include <stdlib.h>

// extern void itoa();
void welcome(void)
{
    printf("*** Welcome to Simpletron! ***\n"\
            "*** Please enter your program one instruction ***\n"\
            "*** (or data word) at a time. I will type the ***\n"\
            "*** location number and a question mark (?). ***\n"\
            "*** You then type the word for that location. ***\n"\
            "*** Type the sentinel -99999 to stop entering ***\n"
            "*** your program. ***\n");
}

void read(double *memory, int16_t *operand, uint16_t *counter)
{
    scanf("%lf",&memory[*operand]);
    printf("%0.2lf\n",memory[*operand]);
    *counter += 1;
}

void write(double *memory, int16_t *operand, uint16_t *counter)
{
    printf("%0.2lf",memory[*operand]);
    *counter += 1;
}

void readString(double *memory, int16_t *operand, uint16_t *counter)
{
    String_t dataString = {{0},0,0,0};
    if (*operand < 20)
    {
        *operand = 100;
        printf("\tSet Default location pos: 100\n");
        dataString.counter = *counter;
        dataString.operand = *operand;
        printf("\tIntroduce el string:\n");
        fflush(stdin);
        scanf("%[^\n]",dataString.stringInput);
        // scanf("%s",dataString.stringInput);
        dataString.sizeString = strlen((const char *)dataString.stringInput);
        // printf("Antes de la funcion\n");
        packgetChar(memory,&dataString); 
    }
    else
    {
        dataString.counter = *counter;
        dataString.operand = *operand;
        printf("\tIntroduce el string:\n");
        fflush(stdin);
        scanf("%s",dataString.stringInput);
        dataString.sizeString = strlen((const char *)dataString.stringInput);
        packgetChar(memory,&dataString);
    }
    
    *counter +=1;
}

void load(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator = memory[*operand];
    *counter += 1;
}

void newline(double *memory,uint16_t *counter)
{
    *counter += 1; 
}

void store(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    memory[*operand] = *accumulator;
    *counter += 1;
}

void add(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator += memory[*operand];
    *counter += 1;
}

void substract(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator -= memory[*operand];
    *counter += 1;
}

void divide(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    if (memory[*operand] != 0)
    {
        *accumulator /= memory[*operand];
        *counter += 1; 
    }
    else
    {
        perror("*** Attempt to divide by zero ***\n"\
                "*** Simpletron execution abnormally terminated ***\n");
    }
    
    
}

void multiply(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator *= memory[*operand];
    *counter += 1;
}

void remaind(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator = remainderl(*accumulator,memory[*operand]);
    // *accumulator %= memory[*operand];
    *counter += 1;
}

void exponetation(double *memory, int16_t *operand, double *accumulator, uint16_t *counter)
{
    *accumulator = pow((double)*accumulator,(double)memory[*operand]);
    *counter += 1;
}

void branch(double *memory, int16_t *operand, uint16_t *counter)
{
    *counter = *operand;
}

void branchNeg(double *memory, int16_t *operand, uint16_t *counter, double *accumulator)
{
    if (*accumulator < 0)
    {
        *counter = *operand;
    }
    else
    {
        *counter += 1;
    }
    
    
}

void branchZero(double *memory, int16_t *operand, uint16_t *counter, double *accumulator)
{
    if (*accumulator == 0)
    {
        *counter = *operand;
    }
    else
    {
        *counter += 1;
    }
    
    
}

void halt(void)
{
    printf("*** Simpletron execution terminated ***\n");
}

int16_t ConversionHex_to_Dec(char character)
{
    if (isdigit(character))
    {
        return character - '0';
    }
    return (10 +(toupper(character) - 'A'));
    
}

void packgetChar(double *memory, String_t *data)
{
    memory[data->operand] = data->sizeString - 1;
    data->operand++;
    bool flag = true;
    uint16_t increment = 0;
    uint8_t charCounter = 0;
    do
    {
        data->packchar |= data->stringInput[increment] << (8*charCounter);
        memory[data->operand] = data->packchar; 
        charCounter++;
        increment++;

        if (charCounter == 4)
        {
            charCounter = 0;
            data->packchar = 0;
            data->counter++;
            data->operand++;
        }

        if (data->stringInput[increment] == '@')
        {
            flag = false;
        }
        else if (increment == data->sizeString)
        {
            flag = false;
        }
    } while (flag != false);
    
    
}

void loadImplementation(double  *memory, SML *information)
{
    uint32_t word       = 0;
    uint16_t counter     = 0;
    uint8_t palabra[6] = {0};
    do
    {
        printf("%d ?  ",counter);
        fflush(stdin);
        // scanf("%d",&word);
        scanf("%s",palabra);
        word = 0;
        // scanf("%d",palabra);
        for (uint8_t i = 0; i < strlen((const char *)palabra); i++)
        {
            if (i>0)
            {
                word = word << 4;
            }
            word += ConversionHex_to_Dec(palabra[i]);
        }
        memory[counter] = (double)word;
        counter++;

    } while (word != 1048575 /*|| word != -9999*/);
    printf("*** Program loading completed ***\n");
    printf("*** Program execution begins *** \n\n");
}

void executeImplementation(double *memory, SML *information)
{
    do
    {   
        
        // char characterHex[6] = {0};
        // itoa(memory[*instructionCounter],characterHex,16);

        // printf("%s\n",characterHex);

        
        information->instructionRegister     = (int32_t)memory[information->instructionCounter];
        information->operationCode           = information->instructionRegister / 1000;
        information->operand                 = information->instructionRegister % 1000;
        printf("%d ?  %d\t",information->instructionCounter,information->instructionRegister);
        switch (information->operationCode)
        {
        case READ:
            read(memory,&information->operand,&information->instructionCounter);
            break;
        case WRITE:
            write(memory,&information->operand,&information->instructionCounter);
            break;
        case READ_STRING:
            readString(memory, &information->operand, &information->instructionCounter);
            break;
        case LOAD:
            load(memory, &information->operand, &information->accumulator , &information->instructionCounter);
            break;
        case STORE:
            store(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case ADD:
            add(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case SUBTRACT:
            substract(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case DIVIDE:
            divide(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case MULTIPLY:
            multiply(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case REMAINDER:
            remaind(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case EXPONENTIATION:
            exponetation(memory,&information->operand,&information->accumulator, &information->instructionCounter);
            break;
        case BRANCH:
            branch(memory,&information->operand,&information->instructionCounter);
            break;
        case BRANCHNEG:
            branchNeg(memory,&information->operand,&information->instructionCounter,&information->accumulator);
            break;
        case BRANCHZERO:
            branchZero(memory,&information->operand,&information->instructionCounter,&information->accumulator);
            break;
        case HALT:
            halt();
            information->operationCode = HALT;
            break;

        default:
            // operatioCode = HALT;
            printf("No existe el comando\n");
            information->instructionCounter += 1;
            if (information->instructionCounter > 999)
            {
                information->operationCode = HALT;
            }
            
            break;
        }
        printf("\n");
    } while ((information->operationCode != HALT ));
}

void dumpImplementation(double *memory,  SML *information)
{
    printf("Acummulator: \t\t%+05.02f\n",information->accumulator);
    printf("instructionCounter:\t %+05ld\n",information->instructionCounter);
    printf("instructionRegister:\t%+05ld\n",information->instructionRegister);
    printf("operatioCode:\t\t%02ld\n",information->operationCode);
    printf("operand:\t\t%02ld\n\n",information->operand);

    printf("MEMORY:\n");
    for (uint16_t i = 0; i < SIZE; i++){
        if(i%20==0){
            printf("\n");
            printf("%d",i);
        }
        // printf("\t %+05ld",(int64_t)memory[i]);
        printf("\t %+#05.2f",memory[i]);
    }
    printf("\n");
}
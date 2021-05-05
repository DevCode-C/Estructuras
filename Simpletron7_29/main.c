#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "SML.h"

/*Arrays*/
double memoryRegisters[SIZE] = {0};
/**/

/*Private variables*/
SML data = {0,0,0,0,0};
/**/


int main(void){
    welcome();
    
    loadImplementation(memoryRegisters,&data);

    executeImplementation(memoryRegisters,&data);

    dumpImplementation(memoryRegisters,&data);
    
}
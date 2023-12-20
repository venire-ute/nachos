#include "syscall.h"

int main()
{   
    char c;
    GetChar(&c);
    // PutChar(c);
    Halt();
    return 0;
    
}

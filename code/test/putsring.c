#include "syscall.h"
#define MAX_STRING_SIZE 128

int main()
{
    PutString("Hello World!\n");
    Halt();

    return 0;
}

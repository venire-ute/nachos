#include "syscall.h"
#define MAX_STRING_SIZE 11

int main()
{
    char c[MAX_STRING_SIZE];
    GetString(c, MAX_STRING_SIZE);

    Halt();
    return 0;
}

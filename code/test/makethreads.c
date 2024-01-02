#include "syscall.h"

void print(char c)
{
    
    PutChar('a');
    PutString("Hello World!\n");

    
    PutChar('\n');
    ThreadExit();
}

int main() {
  

    char c = 'a';
    int res = ThreadCreate((void *)print, (void *)&c);
     res = ThreadCreate((void *)print, (void *)&c);
    // ThreadExit();
    // print(c);
    // PutString("Hello World!\n");
    


   

    Halt();
    return 0;
    


}


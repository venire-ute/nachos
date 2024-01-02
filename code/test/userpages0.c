#include "syscall.h"

void afficheString(char* s) {
	int nb = 10;
	int i;
	for(i=0;i<nb;i++)
        PutString(s);

    ThreadExit();
}

int main() {
    int tid1 = ThreadCreate((void *)afficheString, (void *)"Hello World!\n");
    int tid2 = ThreadCreate((void *)afficheString, (void *)"Hello World!\n");

    Halt();
    return 0;
}
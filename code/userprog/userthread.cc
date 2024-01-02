#ifdef CHANGED
#include "userthread.h"
#include "system.h"
#include <cstdint>

struct schmurtz_t
{
    int f;
    int arg;
};



static void StartUserThread(void *schmurtz){
    schmurtz_t *schmurtz2 = (schmurtz_t *)schmurtz;
    int f = schmurtz2->f;
    int arg = schmurtz2->arg;
    delete schmurtz2;

    int i;

    for (i = 0; i < NumTotalRegs; i++)
        machine->WriteRegister (i, 0);

    // On charge le programme
    machine->WriteRegister(PCReg, f);
    // On charge les arguments
    machine->WriteRegister(4, arg);
    // On charge le pointeur de pile
    machine->WriteRegister(NextPCReg, f+4);
    machine->WriteRegister(StackReg, currentThread->space->AllocateUserStack());
    // On sauvegarde la mémoire
    currentThread->Yield();  




    machine->DumpMem("threads.svg"); // Mémoire avant l'exécution
    // On lance le programme
    machine->Run();


}

int ThreadCreate(void f(void *arg), void *arg){


    return do_ThreadCreate((intptr_t)f, (intptr_t)arg);


}

void ThreadExit(void){
    do_ThreadExit();
}
int do_ThreadCreate(int f, int arg){
    schmurtz_t *schmurtz = new schmurtz_t;
    schmurtz->f = f;
    schmurtz->arg = arg;

    Thread *t = new Thread("thread");
    t->space = currentThread->space;
    t->Start(StartUserThread, schmurtz);
    currentThread->Yield();
    
    

    return 0;


}
void do_ThreadExit(void){

    currentThread->space->FreeEndMain();
    currentThread->space->DeallocateUserStack();
    
    currentThread->Finish();
}

#endif // CHANGED
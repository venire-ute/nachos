#ifdef CHANGED
#include "userthread.h"
#include "system.h"


static void StartUserThread(int f){
    currentThread->space->InitRegisters();
    machine->WriteRegister(PCReg, f);
    machine->WriteRegister(NextPCReg, f+4);
    machine->Run();
}

int ThreadCreate(int f, int arg){
    Thread *t = new Thread("thread");
    t->space = currentThread->space;
    t->Fork(StartUserThread, f);
    return 0;
}

void ThreadExit(void){
    currentThread->Finish();
}
extern int do_ThreadCreate(int f, int arg); // Defined in userprog/exception.cc
int ThreadCreate(int f, int arg) {
    return do_ThreadCreate(f, arg);
}

#endif // CHANGED
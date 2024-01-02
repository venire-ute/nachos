#ifdef CHANGED
#include "thread.h"
#include "synch.h"

#ifndef USERTHREAD_H
#define USERTHREAD_H


extern int do_ThreadCreate(int f, int arg); 
extern void do_ThreadExit(void); 
int ThreadCreate(void f(void *arg), void *arg);
void ThreadExit(void);

#endif // CHANGED
#endif // USERTHREAD_H
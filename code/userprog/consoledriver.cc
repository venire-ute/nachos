#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"
static Semaphore *readAvail;
static Semaphore *writeDone;
Semaphore *writeChar;
Semaphore *readChar;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }
ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
readAvail = new Semaphore("read avail", 0);
writeDone = new Semaphore("write done", 0);
console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, NULL);
writeChar = new Semaphore("write char", 1);
readChar = new Semaphore("read char", 1);

}
ConsoleDriver::~ConsoleDriver()
{
delete console;
delete writeDone;
delete readAvail;
}
void ConsoleDriver::PutChar(int ch)
{  
    writeChar->P();
    console->TX(ch);
    writeDone->P();
    writeChar->V();
}
int ConsoleDriver::GetChar()
{
    readChar->P();
    readAvail->P();
    char c = console->RX();
    readChar->V();
    return c;

}
void ConsoleDriver::PutString(const char *s)
{ 

    while(*s != '\0'){
        PutChar(*s);
        s++;
    }
}
void ConsoleDriver::GetString(char *s, int n)
{

    int i = 0;
    char c;
    while(i < n &&(c = GetChar()) != EOF && c != '\n'){
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}
unsigned ConsoleDriver::copyStringFromMachine( int from, char *to, unsigned size){
    unsigned i = 0;
    int c;
    while(i < size){
        machine->ReadMem(from+i, 1, &c);
        to[i] = (char) c;
        if(c == '\0'){
            break;
        }
        i++;
    }
    return i;
}
void ConsoleDriver::copyStringToMachine( char *from, int to, unsigned size){
    unsigned i = 0;
    int c;
    while(i < size){
        c = (int) from[i];
        machine->WriteMem(to+i, 1, c);
        if(c == '\0'){
            break;
        }
        i++;
    }
}
void ConsoleDriver::PutInt(int n){
    char s[12];
    snprintf(s, 12, "%d", n);
    PutString(s);
    
}
void ConsoleDriver::GetInt(int *n){
    int* i = new int;
    char* s = new char[12];

    
    GetString(s, 12);
    sscanf(s, "%d", i);
    machine->WriteMem(*n, 4, *i);
    delete i;
    delete[] s;
}
#endif // CHANGED
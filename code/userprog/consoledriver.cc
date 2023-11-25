#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"
static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }
ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
readAvail = new Semaphore("read avail", 0);
writeDone = new Semaphore("write done", 0);
console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}
ConsoleDriver::~ConsoleDriver()
{
delete console;
delete writeDone;
delete readAvail;
}
void ConsoleDriver::PutChar(int ch)
{
    console->TX(ch);
    writeDone->P();
}
int ConsoleDriver::GetChar()
{
    readAvail->P();
    return console->RX();

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
    while(i < n){
        c = GetChar();
        if(c == EOF){
            break;
        }
        s[i] = c;
        i++;
    }
    s[i] = '\0';
}
void ConsoleDriver::copyStringFromMachine( int from, char *to, unsigned size){
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
}
#endif // CHANGED
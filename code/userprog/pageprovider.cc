#ifdef CHANGED

#include "bitmap.h"
#include "pageprovider.h"
#include "system.h"

PageProvider::PageProvider(int numPages){
    bitmap = new BitMap(numPages);
}

PageProvider::~PageProvider(){
    delete bitmap;
}

//méthode GetEmptyPage : derécupérer le numéro d’une page physique libre et d’initialiser le contenu de la page physique correspondante à 0 grâce à la fonction memset; 
int PageProvider::GetEmptyPage(){
    int numPage = bitmap->Find();
    memset(&(machine->mainMemory[numPage * PageSize]), 0, PageSize);
    return numPage;
}

//méthode ReleasePage : libérer une page physique en mettant à 0 le bit correspondant dans le bitmap;
void PageProvider::ReleasePage(int numPage){
    bitmap->Clear(numPage);
}

//méthode NumAvailPage : renvoyer le nombre de pages physiques libres;
int PageProvider::NumAvailPage(){
    return bitmap->NumClear();
}

#endif // CHANGED
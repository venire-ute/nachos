#ifdef CHANGED

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"



class PageProvider {
    public:
        PageProvider(int numPages);
        ~PageProvider();
        int GetEmptyPage();
        void ReleasePage(int numPage);
        int NumAvailPage();
    private:
        BitMap* bitmap;
};

#endif // PAGEPROVIDER_H
#endif // CHANGED
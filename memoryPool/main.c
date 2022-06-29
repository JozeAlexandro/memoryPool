#include <stdio.h>

#include "memoryPoolImpl/linearMemoryPool/h/linearMemoryPool.h"

int main()
{


    sMemoryPoolIface * pPool = linearMemoryPoolMake();
    tempPrint();
    void *a50 = pPool->allocate(50);

    tempPrint();
    void *a30 = pPool->allocate(30);

    tempPrint();
    void *a70 = pPool->allocate(70);

    tempPrint();
    void *a90 = pPool->allocate(90);

    tempPrint();
    void *a2 = pPool->allocate(2);

/*
    tempPrint();
    pPool->deallocate(a50);

    tempPrint();
    pPool->deallocate(a30);

    tempPrint();
    pPool->deallocate(a70);

    tempPrint();
    pPool->deallocate(a90);

    tempPrint();
    pPool->deallocate(a2);*/


    tempPrint();
    pPool->deallocate(a50);

    tempPrint();
    pPool->deallocate(a70);

    tempPrint();
    a70 = pPool->allocate(30);
    tempPrint();
    pPool->deallocate(a70);


    tempPrint();
    pPool->deallocate(a30);

    tempPrint();
    pPool->deallocate(a90);

    tempPrint();
    pPool->deallocate(a2);


    tempPrint();

    return 0;
}

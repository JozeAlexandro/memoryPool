#include <stdio.h>

#include "memoryPoolImpl/linearMemoryPool/h/linearMemoryPool.h"

int main()
{
    sMemoryPoolIface * pPool = linearMemoryPoolMake();
    tempPrint();
    void *a1 = pPool->allocate(10);

    tempPrint();
    void *a2 = pPool->allocate(20);

    tempPrint();
    void *a3 = pPool->allocate(30);

    tempPrint();
    void *a4 = pPool->allocate(40);

    tempPrint();
    void *a5 = pPool->allocate(50);

    tempPrint();
    pPool->deallocate(a1);

    tempPrint();
    pPool->deallocate(a2);

    tempPrint();
    pPool->deallocate(a3);

    tempPrint();
    pPool->deallocate(a4);

    tempPrint();
    pPool->deallocate(a5);

    tempPrint();

    return 0;
}

#include <stdio.h>

#include "memoryPoolImpl/linearMemoryPool/h/linearMemoryPool.h"

int main()
{

    /// @todo @bug Увеличивается на кол-во выделений/освобождений * 0x10


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
    pPool->deallocate(a1);

    tempPrint();
    pPool->deallocate(a2);

    tempPrint();
    pPool->deallocate(a3);

    tempPrint();
    pPool->deallocate(a4);

    tempPrint();

    return 0;
}

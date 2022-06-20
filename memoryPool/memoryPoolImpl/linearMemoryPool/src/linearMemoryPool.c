#include "../h/linearMemoryPool.h"
#include "linearMemoryPoolP.h"
#include "memoryPoolImpl/linkedList/h/linkedList.h"
#include <string.h>

/// public

sMemoryPoolIface *linearMemoryPoolMake( void )
{
    mLinearMemoryPool.allocate = linearMemoryPoolAllocate;
    mLinearMemoryPool.deallocate = linearMemoryPoolDeallocate;


    sMemoryBlockHeader initBlock =
        { true, LINEAR_POOL_SIZE - sizeof ( sMemoryBlockHeader ) };

    memcpy( mMemoryPool, &initBlock, sizeof ( sMemoryBlockHeader ) );
    return &mLinearMemoryPool;
}



/// private



static void *linearMemoryPoolAllocate( size_t size )
{
    sMemoryBlockHeader *pMemoryDescriptor = (sMemoryBlockHeader *) mMemoryPool;

    while( !pMemoryDescriptor->isAvail && ( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) ) )
        pMemoryDescriptor = ( sMemoryBlockHeader * )( (uint8_t *)pMemoryDescriptor + pMemoryDescriptor->size + sizeof(sMemoryBlockHeader) );

    if( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) )
    {
        sMemoryBlockHeader newBlockDescriptor = { true, pMemoryDescriptor->size - size };

        pMemoryDescriptor->isAvail = false;
        pMemoryDescriptor->size = size;

        memcpy( ( ( uint8_t* )pMemoryDescriptor) + pMemoryDescriptor->size + sizeof(sMemoryBlockHeader),
                &newBlockDescriptor,
                sizeof( sMemoryBlockHeader ) );

        return ((uint8_t*) pMemoryDescriptor) + sizeof( sMemoryBlockHeader );
    }
    else
    {
        return NULL;
    }
}


static bool linearMemoryPoolDeallocate( void *pData )
{
    sMemoryBlockHeader *pMemoryDescriptor = (sMemoryBlockHeader *)(( (uint8_t *)pData ) - sizeof( sMemoryBlockHeader ));
    pMemoryDescriptor->isAvail = true;

    /// @todo Взад-назад доталова
    sMemoryBlockHeader *nextDescriptor = (sMemoryBlockHeader *)( ( ( uint8_t* )pMemoryDescriptor ) + (pMemoryDescriptor->size + sizeof( sMemoryBlockHeader ) ) );
    while(nextDescriptor->isAvail && ( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) ) )
    {
        pMemoryDescriptor->size += nextDescriptor->size + sizeof( sMemoryBlockHeader );
        nextDescriptor = (sMemoryBlockHeader *)( ( ( uint8_t* )nextDescriptor ) + (nextDescriptor->size + sizeof( sMemoryBlockHeader ) ) );
    }

    sMemoryBlockHeader *prevDescriptor = (sMemoryBlockHeader *)( ( ( uint8_t* )pMemoryDescriptor ) - ( pMemoryDescriptor->size + sizeof( sMemoryBlockHeader ) ) );
    while(prevDescriptor->isAvail && ( ( uint8_t* )prevDescriptor > mMemoryPool ) )
    {
        prevDescriptor->size += pMemoryDescriptor->size + sizeof( sMemoryBlockHeader );
        pMemoryDescriptor = prevDescriptor;
        prevDescriptor = (sMemoryBlockHeader *)( ( ( uint8_t* )nextDescriptor ) - ( nextDescriptor->size + sizeof( sMemoryBlockHeader ) ) );
    }

    return true;
}


#include <stdio.h>
void tempPrint()
{
    sMemoryBlockHeader *pMemoryDescriptor = (sMemoryBlockHeader *)(mMemoryPool);
    printf("Memory:\n");
    while( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) )
    {
        printf("Block %p iavail = %d, size = 0x%zx\n", pMemoryDescriptor, pMemoryDescriptor->isAvail, pMemoryDescriptor->size );
        pMemoryDescriptor = (sMemoryBlockHeader*)((uint8_t*)pMemoryDescriptor + ( pMemoryDescriptor->size + sizeof (sMemoryBlockHeader)));
    }
}




sMemoryDescriptor findMemoryBlock( size_t size, eAlgMatch algrtm )
{
  /*  switch( algrtm )
    {
    case ALG_FIRST_MATCH:
        return findFirstMatchMemoryBlock( size );
        break;

    case ALG_LAST_MATCH:
        return findLastMatchMemoryBlock( size );
        break;

    case ALG_BEST_MATCH:
        return findBestMatchMemoryBlock( size );
        break;
    }*/
}

uint8_t *findFirstMatchMemoryBlock( size_t size )
{

}

uint8_t *findBestMatchMemoryBlock( size_t size )
{

}

uint8_t *findLastMatchMemoryBlock( size_t size )
{

}

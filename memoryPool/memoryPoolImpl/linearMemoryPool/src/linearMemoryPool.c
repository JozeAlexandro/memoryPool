#include "../h/linearMemoryPool.h"
#include "linearMemoryPoolP.h"
#include <string.h>

/// public

/// @todo add algorithm
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
    sMemoryBlockHeader *pMemoryDescriptor = findMemoryBlock( size, ALG_FIRST_MATCH );

    /// @todo external checking if( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) )
    if( pMemoryDescriptor )
    {
        sMemoryBlockHeader newBlockDescriptor = { true, pMemoryDescriptor->size - size - sizeof( sMemoryBlockHeader ) };

        pMemoryDescriptor->isAvail = false;
        pMemoryDescriptor->size = size;

        memcpy( ( ( uint8_t* )pMemoryDescriptor) + pMemoryDescriptor->size + sizeof(sMemoryBlockHeader),
                &newBlockDescriptor,
                sizeof( sMemoryBlockHeader ) );

        return ( ( uint8_t* ) pMemoryDescriptor ) + sizeof( sMemoryBlockHeader );
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

    /// @todo Взад-назад до талова
    sMemoryBlockHeader *nextDescriptor = (sMemoryBlockHeader *)( ( ( uint8_t* )pMemoryDescriptor ) + (pMemoryDescriptor->size + sizeof( sMemoryBlockHeader ) ) );
    while(nextDescriptor->isAvail && ( ( uint8_t* )nextDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) ) )
    {
        pMemoryDescriptor->size += nextDescriptor->size + sizeof( sMemoryBlockHeader );
        nextDescriptor = getNextMemBlock( nextDescriptor );
    }

    sMemoryBlockHeader *pPrevMemoryDescriptor = getFirstMemBlock();
    size_t lastSize = 0;
    while( pPrevMemoryDescriptor != pMemoryDescriptor )
    {
        lastSize = pPrevMemoryDescriptor->size;
        pPrevMemoryDescriptor = getNextMemBlock( pPrevMemoryDescriptor );
    }

    pPrevMemoryDescriptor = ( sMemoryBlockHeader * )(((uint8_t*)pPrevMemoryDescriptor) - lastSize - sizeof( sMemoryBlockHeader ) );

    if( pPrevMemoryDescriptor->isAvail )
        pPrevMemoryDescriptor->size += pMemoryDescriptor->size + sizeof( sMemoryBlockHeader );



    return true;
}






/// @test
#include <stdio.h>
void tempPrint()
{
    sMemoryBlockHeader *pMemoryDescriptor = getFirstMemBlock();
    printf("Memory:\n");
    while( ( uint8_t* )pMemoryDescriptor < ( mMemoryPool + LINEAR_POOL_SIZE ) )
    {
        printf("Block %p iavail = %d, size = %zu\n", pMemoryDescriptor, pMemoryDescriptor->isAvail, pMemoryDescriptor->size );
        pMemoryDescriptor = (sMemoryBlockHeader*)((uint8_t*)pMemoryDescriptor + ( pMemoryDescriptor->size + sizeof (sMemoryBlockHeader)));
    }
}




sMemoryBlockHeader * findMemoryBlock( size_t size, eAlgMatch algrtm )
{
    switch( algrtm )
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
    }
}




sMemoryBlockHeader *findFirstMatchMemoryBlock( size_t size )
{
    sMemoryBlockHeader *pMemoryDescriptor = getFirstAvailMemBlock();

    while( isMemoryRange( ( uint8_t* )pMemoryDescriptor ) &&
           !isSuitable( pMemoryDescriptor, size ) )
    {
        pMemoryDescriptor = getNextAvailMemBlock( pMemoryDescriptor );
    };

    return pMemoryDescriptor;
}

/// @todo Нужно бы избавиться от вечных циклов
sMemoryBlockHeader *findBestMatchMemoryBlock( size_t size )
{
    sMemoryBlockHeader *pMemoryDescriptor = findFirstMatchMemoryBlock(size); /// @todo Такую же сделать для последнеего подходящего

    sMemoryBlockHeader *best = pMemoryDescriptor;

    while( isMemoryRange( ( uint8_t* )pMemoryDescriptor )  )
    {
        if(NULL == pMemoryDescriptor)
            return best;
        else if( isSuitable( pMemoryDescriptor, size ) && best->size > pMemoryDescriptor->size )
            best = pMemoryDescriptor;

        pMemoryDescriptor = getNextAvailMemBlock( pMemoryDescriptor );
    };

    return pMemoryDescriptor;
}

sMemoryBlockHeader *findLastMatchMemoryBlock( size_t size )
{
    sMemoryBlockHeader *pMemoryDescriptor = getFirstAvailMemBlock();

    sMemoryBlockHeader *last = NULL;

    while( true )
    {
        if(NULL == pMemoryDescriptor)
            return last;
        else if( !isMemoryRange( ( uint8_t* )pMemoryDescriptor ) )
            return NULL;
        else if( isSuitable( pMemoryDescriptor, size ) )
            last = pMemoryDescriptor;

        pMemoryDescriptor = getNextAvailMemBlock( pMemoryDescriptor );
    };

    return pMemoryDescriptor;
}

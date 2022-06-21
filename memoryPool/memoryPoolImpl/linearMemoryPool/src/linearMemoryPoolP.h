#ifndef LINEAR_MEMORY_POOLP_H
#define LINEAR_MEMORY_POOLP_H

#include <stdint.h>
#include "memoryPoolIface.h"
#include "memoryPoolImpl/linkedList/h/linkedList.h"

#include "../../linkedList/h/linkedList.h"

// enum { LINEAR_POOL_SIZE = 256 };


typedef enum
{
    ALG_FIRST_MATCH,
    ALG_LAST_MATCH,
    ALG_BEST_MATCH
} eAlgMatch;

typedef struct
{
    bool isAvail;
    size_t size;
} sMemoryBlockHeader;

static void *linearMemoryPoolAllocate( size_t size );
static bool linearMemoryPoolDeallocate( void *pData );

void tempPrint();

static sMemoryPoolIface mLinearMemoryPool;

static uint8_t mMemoryPool[ LINEAR_POOL_SIZE ];


/// @todo проверки мапы текущих блоков памяти


/// @brief Получение указателя на первый блок памяти
static inline sMemoryBlockHeader * getFirstMemBlock( void )
{
    return ( sMemoryBlockHeader * ) mMemoryPool;
}

/// @brief Получение указателя на следующий блок памяти
static inline sMemoryBlockHeader * getNextMemBlock( const sMemoryBlockHeader * const crntMemBlock )
{
    return ( sMemoryBlockHeader * )( (uint8_t *)crntMemBlock + crntMemBlock->size + sizeof(sMemoryBlockHeader) );
}


static inline bool isMemoryRange( const uint8_t * const addr )
{
    return ( addr >= mMemoryPool ) && ( addr <= mMemoryPool + LINEAR_POOL_SIZE );
}

/// @brief Получение указателя на первый свободный блок памяти
static inline sMemoryBlockHeader * getFirstAvailMemBlock( void )
{
    sMemoryBlockHeader *pMemoryDescriptor = getFirstMemBlock();
    while( !pMemoryDescriptor->isAvail && isMemoryRange( ( uint8_t * )pMemoryDescriptor ) )
        pMemoryDescriptor = getNextMemBlock( pMemoryDescriptor );

    if( !isMemoryRange( ( uint8_t* )pMemoryDescriptor ) )
        pMemoryDescriptor = NULL;

    return pMemoryDescriptor;
}

/// @brief Получение указателя на следующий свободный блок памяти
static inline sMemoryBlockHeader * getNextAvailMemBlock( const sMemoryBlockHeader * const crntMemBlock )
{
    sMemoryBlockHeader *pMemoryDescriptor = getNextMemBlock( crntMemBlock );
    while( !pMemoryDescriptor->isAvail && isMemoryRange( ( uint8_t * )pMemoryDescriptor ) )
        pMemoryDescriptor = getNextMemBlock( pMemoryDescriptor );

    if( !isMemoryRange( ( uint8_t* )pMemoryDescriptor ) )
        pMemoryDescriptor = NULL;

    return pMemoryDescriptor;
}

/// @brief Получение указателя на предыдущий блок памяти
/** @todo static inline sMemoryBlockHeader * getPrevMemBlock( const sMemoryBlockHeader * const crntMemBlock )
{

}*/







sMemoryBlockHeader * findMemoryBlock( size_t size, eAlgMatch algrtm );

sMemoryBlockHeader *findFirstMatchMemoryBlock( size_t size );
sMemoryBlockHeader *findBestMatchMemoryBlock( size_t size );
sMemoryBlockHeader *findLastMatchMemoryBlock( size_t size );

#endif // LINEAR_MEMORY_POOLP_H

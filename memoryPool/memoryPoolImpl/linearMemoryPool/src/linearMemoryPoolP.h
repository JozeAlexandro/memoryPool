#ifndef LINEAR_MEMORY_POOLP_H
#define LINEAR_MEMORY_POOLP_H

#include <stdint.h>
#include "memoryPoolIface.h"
#include "memoryPoolImpl/linkedList/h/linkedList.h"

enum { LINEAR_POOL_SIZE = 256 };

typedef enum
{
    ALG_FIRST_MATCH,
    ALG_LAST_MATCH,
    ALG_BEST_MATCH
} eAlgMatch;

static sMemoryPoolIface mLinearMemoryPool;






static uint8_t mMemoryPool[ LINEAR_POOL_SIZE ];

typedef struct
{
    bool isAvail;
    size_t size;
} sMemoryBlockHeader;





static void *linearMemoryPoolAllocate( size_t size );
static bool linearMemoryPoolDeallocate( void *pData );

void tempPrint();


sMemoryDescriptor findMemoryBlock( size_t size, eAlgMatch algrtm );

uint8_t *findFirstMatchMemoryBlock( size_t size );
uint8_t *findBestMatchMemoryBlock( size_t size );
uint8_t *findLastMatchMemoryBlock( size_t size );

#endif // LINEAR_MEMORY_POOLP_H

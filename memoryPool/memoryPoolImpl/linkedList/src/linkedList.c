#include "../h/linkedList.h"

static void reset( void );
static void push( uint8_t *data );
static uint8_t * pop( void );
static void clear( void );


sStack stack = { .reset = reset, .push = push, .pop = pop, .clear = clear };



#ifndef LINEAR_POOL_SIZE
#error не определен LINEAR_POOL_SIZE
#endif // LINEAR_POOL_SIZE

/// @todo
#define STACK_MAX_SIZE \
    LINEAR_POOL_SIZE / sizeof (int)


uint8_t* stackMem[ STACK_MAX_SIZE ];

static uint8_t **mpStackHead;

static void reset( void )
{
    mpStackHead = stackMem;
}

static void push( uint8_t *data )
{
    *mpStackHead++ = data;
}

static uint8_t * pop( void )
{
    uint8_t *data = *mpStackHead--;
    return data;
}
/// @todo size..
static void clear( void )
{

}

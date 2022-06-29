#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define LINEAR_POOL_SIZE 2560

#define LINKED_LIST_DATA_TYPE_T sMemoryDescriptor

#ifndef LINKED_LIST_DATA_TYPE_T
#error Macro LINKED_LIST_DATA_TYPE_T is not defined!
#endif // LINKED_LIST_DATA_TYPE_T




typedef struct sLinkedListNode
{
  struct sLinkedListNode *mpPrevNode;
  struct sLinkedListNode *mpNextNode;
} sLinkedListNode;




typedef struct
{
  void ( *reset )( void );
  void ( *push )( uint8_t *data );
  uint8_t *( *pop )( void );
  void ( *clear )( void );
} sStack;

extern sStack stack;

#endif // LINKED_LIST_H

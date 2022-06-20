#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/// @todo
typedef struct
{
    uint8_t *mpAddress;
    size_t mSize;
} sMemoryDescriptor;

#define LINKED_LIST_DATA_TYPE_T sMemoryDescriptor

#ifndef LINKED_LIST_DATA_TYPE_T
#error Macro LINKED_LIST_DATA_TYPE_T is not defined!
#endif // LINKED_LIST_DATA_TYPE_T




typedef struct sLinkedListNode
{
  struct sLinkedListNode *mpPrevNode;
  struct sLinkedListNode *mpNextNode;
  LINKED_LIST_DATA_TYPE_T mData;
} sLinkedListNode;



#endif // LINKED_LIST_H

/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_GENERIC_STRUCTURES_H
#define SRC_SYSTEM_GENERIC_STRUCTURES_H

#include "../macros.h"
#include "onewaylist.h"

/***** GENERIC QUEUE *****/

typedef OWL_List generic_Queue;

/*
 * Initialize queue.
 *
 * Parameters:
 *   INPUT: queue - Pointer to queue.
 */
public void generic_InitializeQueue(generic_Queue *queue);

/*
 * Add item to queue. First Input - First Output
 *
 * Parameters:
 *   INPUT: queue - Pointer to queue.
 *   INPUT: data - Pointer to your data structure.
 */
public void generic_Enqueue(generic_Queue *queue, void *data);

/*
 * Delete item from queue.
 *
 * Parameters:
 *   INPUT: queue - Pointer to queue.
 *
 * Result:
 *   Pointer to your data structure.
 */
public void *generic_Dequeue(generic_Queue *queue);

/***** GENERIC STACK *****/

typedef OWL_List generic_Stack;

/*
 * Initialize stack.
 *
 * Parameters:
 *   INPUT: stack - Pointer to stack.
 */
public void generic_InitializeStack(generic_Stack *stack);

/*
 * Push item to stack. First Input - Last Output
 *
 * Parameters:
 *   INPUT: stack - Pointer to stack.
 *   INPUT: data - Pointer to your data structure.
 */
public void generic_PushStack(generic_Stack *stack, void *data);

/*
 * Pop item from stack.
 *
 * Parameters:
 *   INPUT: stack - Pointer to stack.
 *
 * Result:
 *   Pointer to your data structure.
 */
public void *generic_PopStack(generic_Stack *stack);

#endif /* SRC_SYSTEM_GENERIC_STRUCTURES_H */

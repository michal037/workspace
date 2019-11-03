/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdlib.h>

#include "generic_structures.h"
#include "common.h"

public void generic_InitializeQueue(generic_Queue *queue)
{
    OWL_InitializeList(queue);
} /* generic_InitializeQueue */

public void generic_Enqueue(generic_Queue *queue, void *data)
{
    OWL_AddTail(queue, data);
} /* generic_Enqueue */

public void *generic_Dequeue(generic_Queue *queue)
{
//    if(queue == NULL)
//    {
//        print_logs(1, "generic_Queue queue pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

    void *data;

    if(queue->head == NULL)
    {
        data = NULL;
    } else if(queue->head == queue->tail){
        data = queue->head->data;
        free(queue->head);
        queue->head = queue->tail = NULL;
    } else {
        OWL_Node *tmp;

        data = queue->head->data;
        tmp = queue->head;
        queue->head = queue->head->next;
        free(tmp);
    }

    return data;
} /* generic_Dequeue */

public void generic_InitializeStack(generic_Stack *stack)
{
    OWL_InitializeList(stack);
} /* generic_InitializeStack */

public void generic_PushStack(generic_Stack *stack, void *data)
{
    OWL_AddHead(stack, data);
} /* generic_PushStack */

public void *generic_PopStack(generic_Stack *stack)
{
    return generic_Dequeue(stack);
} /* generic_PopStack */

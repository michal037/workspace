/* MIT License
 *
 * Copyright (c) 2021, Michal Kozakiewicz, github.com/michal037
 */

#include <stdbool.h> /* bool, true, false */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <stdio.h> /* printf */


/* the struct for stack's nodes */
typedef struct stack_node {
    /* a pointer for a previous node */
    struct stack_node *previous;
    
    /* a pointer for data */
    void *ptr_data;
} stack_node_t;

/* the struct for a stack */
typedef struct stack {
    /* max length of a stack */
    const unsigned int MAX_LENGTH;
    
    /* current length of a stack */
    unsigned int length;
    
    /* a top node */
    stack_node_t *top_node;
} stack_t;


/* create a new stack
 * 
 * Parameters:
 *   max_length - maximum length of a new stack, which is greater than 0
 *
 * Return:
 *   on success: a pointer for a new stack
 *   on failure: NULL
 */
stack_t * stack_create(const unsigned int max_length) {
    /* the max_length have to be greater than 0 */
    if(max_length == 0) {
        return NULL;
    }
    
    /* allocate a new memory block for a new stack */
    void * const stack = malloc(sizeof(stack_t));
    
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return NULL;
    }
    
    /* the stack with the init data */
    const stack_t init = {
        .MAX_LENGTH = max_length,
        .length = 0,
        .top_node = NULL
    };
    
    /* initialize the new stack */
    memcpy(stack, &init, sizeof(stack_t));
    
    /* return the new stack */
    return stack;
}

/* destroy a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *   callback - a pointer to a function that will destroy your objects
 *     Parameters:
 *       void * const ptr_data - a pointer to your object
 *     Return:
 *       on success: true - the callback has successfully freed memory
 *       on failure: false - the callback has not successfully freed memory
 *
 * Return:
 *   on success: true
 *   on failure: false
 */
bool stack_destroy(stack_t * const stack,
         bool (* const callback)(void * const)) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return false;
    }
    
    /* if the stack is not empty then destroy nodes with their data */
    if(stack->top_node != NULL) {
        /* callback is needed, so check the pointer */
        if(callback == NULL) {
            return false;
        }
        
        void *ptr_data;
        stack_node_t *previous;

        /* destroy nodes with their data */
        while(stack->top_node != NULL) {
            /* copy pointers from the top node of the stack */
            ptr_data = stack->top_node->ptr_data;
            previous = stack->top_node->previous;
            
            /* free the memory block previously allocated in push */
            free(stack->top_node);
            
            /* update the top_node pointer to latest */
            stack->top_node = previous;
            
            /* free user's object through his callback */
            if(!callback(ptr_data)) {
                return false;
            }
        }
    }
    
    /* free the memory block previously allocated in stack_create */
    free(stack);
    
    /* correctly destroyed */
    return true;
}

/* push a pointer to data to a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *   ptr_data - a pointer to data to push on a stack
 *
 * Return:
 *   on success: true - a pointer to data has been placed on a stack
 *   on failure: false - a pointer to data has not been placed on a stack
 */
bool stack_push(stack_t * const stack, void * const ptr_data) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return false;
    }

    /* the data pointer have to be different than NULL */
    if(ptr_data == NULL) {
        return false;
    }

    /* overflow prevention */
    if(stack->length >= stack->MAX_LENGTH) {
        return false;
    }

    /* allocate a new memory block for a node */
    stack_node_t * const new_node = malloc(sizeof(stack_node_t));

    /* the new_node pointer have to be different than NULL */
    if(new_node == NULL) {
        return false;
    }

    /* write pointers to the node */
    new_node->previous = stack->top_node;
    new_node->ptr_data = ptr_data;

    /* update the address of top node of the stack */
    stack->top_node = new_node;

    /* increase the length of the stack */
    stack->length++;

    /* correctly pushed */
    return true;
}

/* pop a pointer to data from a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: a pointer to data
 *   on failure: NULL
 */
void * stack_pop(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return NULL;
    }
    
    /* the stack cannot be empty */
    if(stack->top_node == NULL) {
        return NULL;
    }
    
    /* copy pointers from the top node of the stack */
    void *ptr_data = stack->top_node->ptr_data;
    stack_node_t *previous = stack->top_node->previous;
    
    /* free the memory block previously allocated in push */
    free(stack->top_node);
    
    /* update the top_node pointer to latest */
    stack->top_node = previous;
    
    /* decrease the length of the stack */
    stack->length--;
    
    /* return the pointer to data from the popped node */
    return ptr_data;
}

/* peek a data pointer from top of a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: a data pointer from top of a stack
 *   on failure: NULL (It is possible that the stack is empty.)
 */
void * stack_peek(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return NULL;
    }

    /* the stack cannot be empty */
    if(stack->top_node == NULL) {
        return NULL;
    }

    return stack->top_node->ptr_data;
}

/* get a length of a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: a length, which can also be 0
 *   on failure: 0 (unable to check, the stack pointer is NULL)
 */
unsigned int stack_get_length(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return 0;
    }

    return stack->length;
}

/* get a maximum length of a stack
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: a maximum length that is greater than 0
 *   on failure: 0 (unable to check, the stack pointer is NULL)
 */
unsigned int stack_get_max_length(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return 0;
    }

    return stack->MAX_LENGTH;
}

/* Check if a stack is empty
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: true or false
 *   on failure: true (unable to check, the stack pointer is NULL)
 */
bool stack_is_empty(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return true;
    }

    /* Check if a stack's length is 0 (empty) */
    if(stack->length == 0) {
        return true;
    }

    /* when the stack pointer is not NULL and the stack's length is greater
     * than zero, so the stack is not empty
     */
    return false;
}

/* Check if a stack is full
 * 
 * Parameters:
 *   stack - a stack on which the operation will be performed
 *
 * Return:
 *   on success: true or false
 *   on failure: false (unable to check, the stack pointer is NULL)
 */
bool stack_is_full(stack_t * const stack) {
    /* the stack pointer have to be different than NULL */
    if(stack == NULL) {
        return false;
    }

    /* if the stack's length is it's maximum length then is full */
    if(stack->length >= stack->MAX_LENGTH) {
       return true; 
    }

    /* when the stack pointer is not NULL and it's length is not 
     * maximum then it's not full
     */
    return false;
}

/* EXAMPLE **************************************** */

bool destroy_my_obj_callback(void * const ptr_data) {
    printf("destroyed: %p\n", ptr_data);

    return true;
}

int main() {
    bool result;
    stack_t *stack = stack_create(2);
    
    /* check */
    printf("max len: %u\n", stack_get_max_length(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("peek: %p\n", stack_peek(stack));
    printf("\n");
    
    /* push new pointer */
    result = stack_push(stack, (void *)0x10);
    printf("added?: %s\n", result ? "yes" : "no");
    printf("peek: %p\n", stack_peek(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");
    
    /* is_empty is_full */
    printf("is_empty: %s\n", stack_is_empty(stack) ? "yes" : "no");
    printf("is_full: %s\n", stack_is_full(stack) ? "yes" : "no");
    printf("\n");
    
    /* push new pointer */
    result = stack_push(stack, (void *)0x11);
    printf("added?: %s\n", result ? "yes" : "no");
    printf("peek: %p\n", stack_peek(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");
    
    /* try to overflow */
    result = stack_push(stack, (void *)0x12);
    printf("added?: %s\n", result ? "yes" : "no");
    printf("peek: %p\n", stack_peek(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");
    
    /* is_empty is_full */
    printf("is_empty: %s\n", stack_is_empty(stack) ? "yes" : "no");
    printf("is_full: %s\n", stack_is_full(stack) ? "yes" : "no");
    printf("\n");
    
    /* pop pointer */
    printf("pop: %p\n", stack_pop(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");
    
    /* pop pointer */
    printf("pop: %p\n", stack_pop(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");
    
    /* try to pop empty stack */
    printf("pop: %p\n", stack_pop(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");

    /* is_empty is_full */
    printf("is_empty: %s\n", stack_is_empty(stack) ? "yes" : "no");
    printf("is_full: %s\n", stack_is_full(stack) ? "yes" : "no");
    printf("\n");

    /* push new pointer */
    result = stack_push(stack, (void *)0x13);
    printf("added?: %s\n", result ? "yes" : "no");
    printf("peek: %p\n", stack_peek(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");

    /* push new pointer */
    result = stack_push(stack, (void *)0x14);
    printf("added?: %s\n", result ? "yes" : "no");
    printf("peek: %p\n", stack_peek(stack));
    printf("len: %u\n", stack_get_length(stack));
    printf("\n");

    /* destroy the non-empty stack */
    stack_destroy(stack, destroy_my_obj_callback);
    
    return 0;
}

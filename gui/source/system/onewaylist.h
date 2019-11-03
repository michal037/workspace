/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef SRC_SYSTEM_ONEWAYLIST_H
#define SRC_SYSTEM_ONEWAYLIST_H

#include "../macros.h"

/* List node */
typedef struct _owl_node
{
    void *data; /* Pointer for your structure. */
    struct _owl_node *next; /* Next node. */
} OWL_Node;

/* List structure */
typedef struct _owl_list
{
    OWL_Node *head; /* Head of list. */
    OWL_Node *tail; /* Tail of list. */
    OWL_Node *current; /* Pointer for current node. For your use. */
} OWL_List;

/* Callbacks */
typedef int(*OWL_CALLBACK_COMPARE)(void *dataA, void *dataB);
typedef void(*OWL_CALLBACK_DOONLIST)(void *dataA);

/* Functions */
/*
 * Inilialize One Way List.
 *
 * Parameters:
 *   INPUT: list - Pointer to list.
 */
public void OWL_InitializeList(OWL_List *list);

/*
 * Create node on head of list, add data to it.
 *
 * Paramaters:
 *   INPUT: list - Pointer to list.
 *   INPUT: data - Pointer to your data structure.
 */
public void OWL_AddHead(OWL_List *list, void *data);

/*
 * Create node on tail of list, add data to it.
 *
 * Paramaters:
 *   INPUT: list - Pointer to list.
 *   INPUT: data - Pointer to your data structure.
 */
public void OWL_AddTail(OWL_List *list, void *data);

/*
 * Find and get pointer to node in list.
 *
 * Paramaters:
 *   INPUT: list - Pointer to list.
 *   OUTPUT: callback - callback for compare data. If data is equal, return 0 (node is found).
 *   INPUT: data - Pointer to your data structure.
 *
 * Result:
 *   Pointer to node if success, else NULL.
 */
public OWL_Node *OWL_GetNode(OWL_List *list, OWL_CALLBACK_COMPARE callback, void *data);

/*
 * Delete and free node from list. Before it, free memory in your data structure.
 *
 * Paramaters:
 *   INPUT: list - Pointer to list.
 *   INPUT: node - Pointer to node.
 */
public void OWL_DeleteNode(OWL_List *list, OWL_Node *node);

/*
 * Do callback on every node in list.
 *
 * Paramaters:
 *   INPUT: list - Pointer to list.
 *   OUTPUT: callback - Pointer for callback.
 */
public void OWL_DoOnList(OWL_List *list, OWL_CALLBACK_DOONLIST callback);

#endif /* SRC_SYSTEM_ONEWAYLIST_H */

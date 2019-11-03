/*
 * MIT License
 * Copyright (c) from 2017, Michal Kozakiewicz, github.com/michal037
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "onewaylist.h"

void OWL_InitializeList(OWL_List *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
} /* OWL_InitializeList */

void OWL_AddHead(OWL_List *list, void *data)
{
    if(list == NULL)
    {
        fprintf(stderr, "OWL list pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if(data == NULL)
    {
        fprintf(stderr, "OWL data pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }

    OWL_Node *node = (OWL_Node*) malloc(sizeof(OWL_Node));

    if(node == NULL)
    {
        fprintf(stderr, "Out of RAM memory!\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;

    if(list->head == NULL)
    {
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }

    list->head = node;
} /* OWL_AddHead */

void OWL_AddTail(OWL_List *list, void *data)
{
    if(list == NULL)
    {
        fprintf(stderr, "OWL list pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if(data == NULL)
    {
        fprintf(stderr, "OWL data pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }

    OWL_Node *node = (OWL_Node*) malloc(sizeof(OWL_Node));

    if(node == NULL)
    {
        fprintf(stderr, "Out of RAM memory!\n");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->next = NULL;

    if(list->head == NULL)
    {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
} /* OWL_AddTail */

OWL_Node *OWL_GetNode(OWL_List *list, OWL_CALLBACK_COMPARE callback, void *data)
{
    if(list == NULL)
    {
        fprintf(stderr, "OWL list pointer is NULL!\n");
        return NULL;
    }
    if(callback == NULL)
    {
        fprintf(stderr, "OWL callback pointer is NULL!\n");
        return NULL;
    }
    if(data == NULL)
    {
        fprintf(stderr, "OWL data pointer is NULL!\n");
        return NULL;
    }

    OWL_Node *node = list->head;
    while(node != NULL)
    {
        if(callback(node->data, data) == 0)
        {
            return node;
        }
        node = node->next;
    }

    return NULL;
} /* OWL_GetNode */

void OWL_DeleteNode(OWL_List *list, OWL_Node *node)
{
    if(list == NULL)
    {
        fprintf(stderr, "OWL list pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if(node == NULL)
    {
        fprintf(stderr, "OWL node pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }

    if(node == list->head)
    {
        if(list->head->next == NULL)
        {
            list->head = list->tail = NULL;
        } else {
            list->head = list->head->next;
        }
    } else {
        OWL_Node *tmp = list->head;

        while(tmp != NULL && tmp->next != node)
        {
            tmp = tmp->next;
        }
        if(tmp != NULL)
        {
            tmp->next = node->next;
        }
    }

    free(node);
} /* OWL_DeleteNode */

void OWL_DoOnList(OWL_List *list, OWL_CALLBACK_DOONLIST callback)
{
    if(list == NULL)
    {
        fprintf(stderr, "OWL list pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }
    if(callback == NULL)
    {
        fprintf(stderr, "OWL callback pointer is NULL!\n");
        exit(EXIT_FAILURE);
    }

    OWL_Node *current = list->head;

    while(current != NULL)
    {
        callback(current->data);
        current = current->next;
    }
} /* OWL_DoOnList */

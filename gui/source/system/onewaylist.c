/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#include <stdio.h>
#include <stdlib.h>

#include "onewaylist.h"
#include "common.h"

public void OWL_InitializeList(OWL_List *list)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
} /* OWL_InitializeList */

public void OWL_AddHead(OWL_List *list, void *data)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }
//    if(data == NULL)
//    {
//        print_logs(1, "OWL data pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

    OWL_Node *node = (OWL_Node*) safe_Malloc(sizeof(OWL_Node));

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

public void OWL_AddTail(OWL_List *list, void *data)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }
//    if(data == NULL)
//    {
//        print_logs(1, "OWL data pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

    OWL_Node *node = (OWL_Node*) safe_Malloc(sizeof(OWL_Node));

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

public OWL_Node *OWL_GetNode(OWL_List *list, OWL_CALLBACK_COMPARE callback, void *data)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        return NULL;
//    }
//    if(callback == NULL)
//    {
//        print_logs(1, "OWL callback pointer is NULL!");
//        return NULL;
//    }
//    if(data == NULL)
//    {
//        print_logs(1, "OWL data pointer is NULL!");
//        return NULL;
//    }

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

public void OWL_DeleteNode(OWL_List *list, OWL_Node *node)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }
//    if(node == NULL)
//    {
//        print_logs(1, "OWL node pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

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

public void OWL_DoOnList(OWL_List *list, OWL_CALLBACK_DOONLIST callback)
{
//    if(list == NULL)
//    {
//        print_logs(1, "OWL list pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }
//    if(callback == NULL)
//    {
//        print_logs(1, "OWL callback pointer is NULL!");
//        exit(EXIT_FAILURE);
//    }

    OWL_Node *current = list->head;

    while(current != NULL)
    {
        callback(current->data);
        current = current->next;
    }
} /* OWL_DoOnList */

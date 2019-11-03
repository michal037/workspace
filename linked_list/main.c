/*
 * MIT License
 * Copyright (c) from 2017, Michal Kozakiewicz, github.com/michal037
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "onewaylist.h"

typedef struct _employee
{
    char name[32];
    unsigned char age;
} Employee;

int compareEmployee(Employee *e1, Employee *e2)
{
    /* If equal return 0 */
    return strcmp(e1->name, e2->name);
} /* compareEmployee */

void displayEmployee(Employee *employee)
{
    printf("%s, %d\n", employee->name, employee->age);
} /* displayEmployee */

int main(int argc, char *argv[])
{
    /* Create example data */
    Employee *jan = (Employee*) malloc(sizeof(Employee));
    strcpy(jan->name, "Jan");
    jan->age = 32;

    Employee *anna = (Employee*) malloc(sizeof(Employee));
    strcpy(anna->name, "Anna");
    anna->age = 28;

    Employee *katarzyna = (Employee*) malloc(sizeof(Employee));
    strcpy(katarzyna->name, "Katarzyna");
    katarzyna->age = 45;

    /* Create list */
    OWL_List list1;

    /* Initialize list */
    OWL_InitializeList(&list1);

    /* Add data to list */
    OWL_AddHead(&list1, jan);
    OWL_AddHead(&list1, anna);
    OWL_AddHead(&list1, katarzyna);

    /* Display data from every node */
    OWL_DoOnList(&list1, (OWL_CALLBACK_DOONLIST) displayEmployee);

    /* Remove one node */
    OWL_DeleteNode(&list1, OWL_GetNode(&list1, (OWL_CALLBACK_COMPARE)compareEmployee, anna));

    /* Display data from every node */
    printf("\n");
    OWL_DoOnList(&list1, (OWL_CALLBACK_DOONLIST) displayEmployee);

    /* Remove nodes */
    OWL_DeleteNode(&list1, OWL_GetNode(&list1, (OWL_CALLBACK_COMPARE)compareEmployee, jan));
    OWL_DeleteNode(&list1, OWL_GetNode(&list1, (OWL_CALLBACK_COMPARE)compareEmployee, katarzyna));

    /* Free example data */
    free(jan);
    free(anna);
    free(katarzyna);
    return 0;
} /* main */

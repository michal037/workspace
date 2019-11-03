//
// Created by Michal on 02-11-2016.
//

#include <stdio.h>

int NWD(int g_First, int g_Second)
{
	int g_Third;
	
	while(g_Second != 0)
	{
		g_Third = g_First % g_Second;
		g_First = g_Second;
		g_Second = g_Third;
	}
	
	return g_First;
}		

int main(){

	int g_First, g_Second, g_Result;
		
	printf("Podaj pierwsza liczbe:\n");
	scanf("%d", &g_First);
	
	printf("\nPodaj druga liczbe:\n");
	scanf("%d", &g_Second);
	
	g_Result = NWD(g_First, g_Second);
	printf("\nNWD: %d", g_Result);

	return 0;
}
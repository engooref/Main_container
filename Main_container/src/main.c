/*
 ============================================================================
 Name        : Main.c
 Author      : eleve
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#ifdef WIN32
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#endif // _DEBUG
#endif // WIN32

#include <stdio.h>
#include <stdlib.h>
#include "./Container/container.h"
#include "elem.h"

int main(int argc, char* argv[]) {
#ifdef WIN32
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG
#endif // WIN32

	struct s_container * pC = NULL;
	int test = 3;


	printf("============================ENTER AppContainer============================\r\n");

	pC = ContainerNew(NULL);

	ContainerPushback(pC, (int) &test);

	pC = ContainerDel(pC);

	printf("============================EXIT  AppContainer============================\r\n");
	return EXIT_SUCCESS;
}

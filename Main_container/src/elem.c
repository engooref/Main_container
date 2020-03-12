/*
 * elem.c
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elem.h"

#define _CRT_SECURE_NO_WARNINGS

struct s_elem{
	int 	iVar;
	double 	dVar;
	char*	pStr;
};

struct s_elem*ElemNew(int i, double d, char*pSstr) {
	struct s_elem* elemNew;

	elemNew = (struct s_elem*) malloc(sizeof(struct s_elem));
	elemNew->pStr = (char*) malloc((strlen(pSstr) + 1) * sizeof(char));

	elemNew->dVar = d;
	elemNew->iVar = i;
	strcpy(elemNew->pStr, pSstr);

	return elemNew;
}

struct s_elem*ElemDel(struct s_elem*pElem){
	free(pElem->pStr);
	free(pElem);

	return NULL;
}

struct s_elem*ElemPrint(struct s_elem*pElem, void*Param){
	printf("Elem @: %p\n", pElem);
	printf("  i: %d\n", pElem->iVar);
	printf("  d: %f\n", pElem->dVar);
	printf("Str: %s\n", pElem->pStr);

	return NULL;
}


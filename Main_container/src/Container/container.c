/*
 * container.c
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "container.h"

typedef struct tt_node {
	struct tt_node* pPrev;
	struct tt_node* pNext;
	void*			pElem;
}t_node;

t_node* NodeNew(t_node*pPrev, t_node*pNext, void*pElem) {

	 t_node*pNewNode;

	pNewNode = (t_node*) malloc ( sizeof(t_node*) );

	assert(pNewNode != NULL);

	pNewNode->pNext = pNext;
	pNewNode->pPrev = pPrev;
	pNewNode->pElem = pElem;

	if(pNext != NULL)
		pNext->pPrev = pNewNode;

	if(pPrev != NULL)
		pPrev->pNext = pNewNode;


	return pNewNode;
}

t_node* NodeDel(t_node*pNode, t_ptfV pDelElemFunc) {

	t_node* pNextNode;
	pNextNode = pNode->pNext;

	if(pDelElemFunc != NULL){ pDelElemFunc(pNode->pElem); }
	else 					{ free(pNode->pElem); }

	if(pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	if(pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;



	free(pNode);

	return pNextNode;
}

struct s_container {
	int			nCard;
	t_node*		pHead;
	t_node*		pTail;
	t_ptfV		pDelElemFunc;
};

struct s_container* ContainerNew(t_ptfV pDelElemFunc) {
	struct s_container* pNewContainer;

	pNewContainer = (struct s_container*) malloc( sizeof(struct s_container*) );

	if(pNewContainer != NULL) {
		pNewContainer->nCard = 0;
		pNewContainer->pHead = NULL;
		pNewContainer->pTail = NULL;
		pNewContainer->pDelElemFunc = pDelElemFunc;
	}

	return pNewContainer;
}

struct s_container* ContainerDel(struct s_container*pContainer) {

	t_node* pScan;
	pScan = pContainer->pHead;

	while(pScan != NULL) { pScan = NodeDel( pScan, pContainer->pDelElemFunc );  }

	pContainer->pHead = NULL;
	pContainer->pTail = NULL;
	pContainer->pDelElemFunc = NULL;

	free(pContainer);

	return pContainer;
}


void* ContainerPushback(struct s_container*pContainer, void*pElem){

	assert(pContainer != NULL);

	t_node* nodePushBack;
	nodePushBack = NodeNew(pContainer->pTail, NULL, pElem);

	if(nodePushBack != NULL){
		if(pContainer->nCard == 0)
			pContainer->pHead = nodePushBack;

		pContainer->pTail = nodePushBack;
	}

	pContainer->nCard++;
	return nodePushBack;
}

void* ContainerPushfront(struct s_container*pContainer, void*pElem){
	t_node* nodePushFront;
	nodePushFront = NodeNew(NULL, pContainer->pHead, pElem);

	if(nodePushFront != NULL){

		if(pContainer->nCard == 0)
			pContainer->pTail = nodePushFront;

		pContainer->pHead = nodePushFront;
	}

	pContainer->nCard++;
	return nodePushFront;

}

void* ContainerPushat(struct s_container*pContainer, void*pElem, int nAt){

		if(nAt <= pContainer->nCard){
		t_node* nodePushAt, *pScan;
		int k = 0;
		pScan = pContainer->pHead;

		while(k != nAt) { pScan = pScan->pNext; k++; }
		nodePushAt = NodeNew(pScan, pScan->pNext, pElem);

		if(nodePushAt != NULL) { return nodePushAt; }
		else {return NULL; }
	}
	else { return NULL; }
}


void* ContainerGetback(struct s_container*pContainer){
	t_node* pNodeTail;
	pNodeTail = pContainer->pTail;

	return pNodeTail->pElem;
}

void* ContainerGetfront(struct s_container*pContainer){
	t_node* pNodeHead;
		pNodeHead = pContainer->pHead;

		return pNodeHead->pElem;
}

void* ContainerGetat(struct s_container*pContainer, int nAt){
	if(nAt <= pContainer->nCard){
		t_node* pNodeAt;
		pNodeAt = pContainer->pHead;

		while (--nAt != 0) { pNodeAt = pNodeAt->pNext; }
		return pNodeAt->pElem;
	}
	else { return NULL;}
}

void* ContainerPopback(struct s_container*pContainer){

}
void* ContainerPopfront(struct s_container*pContainer){

}
void* ContainerPopat(struct s_container*pContainer, int nAt){

}

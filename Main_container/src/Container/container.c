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

	pNewNode = (t_node*) malloc ( sizeof(t_node) );

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

	if(pDelElemFunc != NULL){ pDelElemFunc(pNode->pElem); }
	else 					{ free(pNode->pElem); }

	if(pNode->pPrev != NULL)
		pNode->pPrev->pNext = pNode->pNext;
	if(pNode->pNext != NULL)
		pNode->pNext->pPrev = pNode->pPrev;



	free(pNode);

	return NULL;
}

struct s_container {
	int			nCard;
	t_node*		pHead;
	t_node*		pTail;
	t_ptfV		pDelElemFunc;
};

struct s_container* ContainerNew(t_ptfV pDelElemFunc) {
	struct s_container* pNewContainer;

	pNewContainer = (struct s_container*) malloc( sizeof(struct s_container) );

	if(pNewContainer != NULL) {
		pNewContainer->nCard = 0;
		pNewContainer->pHead = NULL;
		pNewContainer->pTail = NULL;
		pNewContainer->pDelElemFunc = pDelElemFunc;
	}

	return pNewContainer;
}

struct s_container* ContainerDel(struct s_container*pContainer) {

	while(pContainer->pHead != NULL){
		pContainer->pTail = pContainer->pHead;
		pContainer->pHead = pContainer->pHead->pNext;
		NodeDel(pContainer->pTail, pContainer->pDelElemFunc);
		pContainer->nCard--;
	}

	pContainer->pHead = NULL;
	pContainer->pTail = NULL;
	pContainer->pDelElemFunc = NULL;

	free(pContainer);

	return NULL;
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
	return nodePushBack->pElem;
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
	return nodePushFront->pElem;

}

void* ContainerPushat(struct s_container*pContainer, void*pElem, int nAt){

		if(nAt <= pContainer->nCard){
			t_node* nodePushAt, *pScan;
			pScan = pContainer->pHead;

		while(--nAt) { pScan = pScan->pNext; }
		nodePushAt = NodeNew(pScan, pScan->pNext, pElem);

		return nodePushAt->pElem;
	}
	else { return NULL; }
}


void* ContainerGetback(struct s_container*pContainer){
	if(pContainer->pTail->pElem)
		return pContainer->pTail->pElem;
	else
		return NULL;
}

void* ContainerGetfront(struct s_container*pContainer){
	if(pContainer->pHead->pElem)
			return pContainer->pHead->pElem;
		else
			return NULL;
}

void* ContainerGetat(struct s_container*pContainer, int nAt){
	if(nAt <= pContainer->nCard){
		t_node* pScan = pContainer->pHead;
		while (--nAt != 0) { pScan = pScan->pNext; }
		if(pScan->pElem)
			return pScan->pElem;
		else
			return NULL;
	}
	else { return NULL;}
}

void* ContainerPopback(struct s_container*pContainer){
	if(pContainer->pTail->pElem) {

		t_node* pTailC = pContainer->pTail->pPrev;
		void* pElem = pContainer->pTail->pElem;
		NodeDel(pContainer->pTail, pContainer->pDelElemFunc);
		pContainer->pTail = pTailC;
		pContainer->nCard--;
		return pElem;

	} else { return NULL; }
}
void* ContainerPopfront(struct s_container*pContainer){
	if(pContainer->pHead->pElem) {

		t_node* pHeadC = pContainer->pHead->pNext;

		void* pElem = pContainer->pHead->pElem;
		NodeDel(pContainer->pHead, pContainer->pDelElemFunc);
		pContainer->pHead = pHeadC;
		pContainer->nCard--;
		return pElem;

	} else { return NULL; }
}
void* ContainerPopat(struct s_container*pContainer, int nAt){
	if(nAt <= pContainer->nCard){
			t_node* pScan = pContainer->pHead;
			while (--nAt != 0) { pScan = pScan->pNext; }
			if(pScan->pElem) {

				void* pElem = pScan->pElem;
				NodeDel(pScan, pContainer->pDelElemFunc);
				pContainer->nCard--;
				return pElem;

			} else { return NULL; }
		}
		else { return NULL; }
}

void* ContainerParse(struct s_container*pContainer, t_ptfVV pfParseFunc, void*pParam){

	t_node* pScan;
	pScan = pContainer->pHead;
	while(pScan != NULL) {
		pfParseFunc(pScan->pElem, pParam);
		pScan = pScan->pNext;
	}
	return NULL;
}

void* ContainerSort(struct s_container*pContainer, t_ptfVVV pSortFunc, void*pParam) {
	t_node* pScan;
	pScan = pContainer->pHead;
	
	while (pScan != NULL){
		pSortFunc(pScan);
		pScan = pScan->pNext;
	}

	return pScan;

}

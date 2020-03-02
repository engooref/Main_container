/*
 * error.c
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

#include "error.h"

void Exit(char* pMsg, char* file, int line){
	printf("\r\n******* SORTIE D'APPLICATION IRRECUPERABLE ! *********\r\n");
	printf(pMsg);
	printf("in file \"%s\" at line %d\r\n\n", file, line);
	exit(-1);
}

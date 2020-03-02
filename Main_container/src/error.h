/*
 * error.h
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

void Exit(char *pMsg, char *file, int line);
#define AppExit(pMsg)		Exit(pMsg, __FILE__, __LINE__);

/*
 * elem.h
 *
 *  Created on: 2 mars 2020
 *      Author: eleve
 */

struct s_elem*ElemNew(int i, double d, char*pSstr);
struct s_elem*ElemDel(struct s_elem*pElem);
struct s_elem*ElemPrint(struct s_elem*pElem, void*Param);


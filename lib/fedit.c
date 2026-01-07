#include <ctype.h>
#include <stdlib.h>
#include "tBasic.h"
#include "error.h"
#include "fedit.h"

tfeditCheck * editFunciones = NULL;

int FEDIT_checkEdit(int tipo, int * caracter)
{
   switch (tipo)
   {
     case E_NONE: return 0;
     case E_NUMERIC: 
	return (*caracter >= 48 && *caracter <= 57)?0:1; 
     case E_ALFNUMERIC: 
	return ((*caracter >= 48 && *caracter <= 57) ||
	        (*caracter >= 65 && *caracter <= 90) ||
	        (*caracter >= 97 && *caracter <= 122))?0:1;
       
     case E_7ASCII:
	return (*caracter >= 32 && *caracter <= 126)?0:1;
     case E_UPPER:
        *caracter= toupper(*caracter);
	return 0;
     case E_LOWER:
        *caracter= tolower(*caracter);
	return 0;
     default:
        return FEDIT_checkPersonal(tipo,caracter);
   }
  return 0;
}

int FEDIT_checkPersonal(int tipo, int * caracter)
{
 tfeditCheck *aux;

  aux=editFunciones;
  while (aux != NULL){
    if (aux->tipo == tipo)
      return aux->checkEdit(caracter);
    aux=aux->siguiente;
  }
  return -1;
}

static int FEDIT_alignPersonal(int tipo){
 tfeditCheck *aux;

  aux=editFunciones;
  while (aux != NULL){
    if (aux->tipo == tipo)
      return aux->align;
    aux=aux->siguiente;
  }
  return A_Left;
}

static int FEDIT_insertPersonal(int tipo){
 tfeditCheck *aux;

  aux=editFunciones;
  while (aux != NULL){
    if (aux->tipo == tipo)
      return aux->insert;
    aux=aux->siguiente;
  }
  return Insert;
}

int FEDIT_getAlign(int tipo )
{
   switch (tipo)
   {
     case E_NONE: 
     case E_ALFNUMERIC: 
     case E_7ASCII:
     case E_UPPER:
     case E_LOWER:
		return A_Left;
     case E_NUMERIC: 
		return A_Right;
     default:
        if (tipo > E_PERSONAL) 
         return FEDIT_alignPersonal(tipo);
        return A_Left;
   }
  return 0;
}

int FEDIT_getInsert(int tipo )
{
   switch (tipo)
   {
     case E_NONE: 
     case E_ALFNUMERIC: 
     case E_7ASCII:
     case E_UPPER:
     case E_LOWER:
     case E_NUMERIC: 
		return Replace;
     default:
        if (tipo > E_PERSONAL) 
         return FEDIT_insertPersonal(tipo);
        return Replace;
   }
  return 0;
}

int FEDIT_addCheck(unsigned short tipo, unsigned short align, 
		unsigned short insert,	int (*checkEdit)(int * caracter))
{
tfeditCheck * aux,*aux2;

  if (tipo < E_PERSONAL) return -1;
  
  aux= (tfeditCheck *) malloc(sizeof(tfeditCheck));
  if (aux == NULL) 
    ERR_fatalError(ERR_MEM,"Error in malloc %d\n",sizeof(tfeditCheck));

  aux->siguiente = NULL;
  aux->tipo=tipo;
  aux->align=align;
  aux->insert=insert;
  aux->checkEdit=checkEdit;

  if (editFunciones == NULL){ editFunciones = aux; return 0;}

  aux2=editFunciones;
  while (aux2->siguiente != NULL){
    aux2 = aux2->siguiente;
  }
  aux2->siguiente=aux;

  return 0;
}





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <text.h>
#include <lview.h>
#include <component.h>

#include <tparser.h>
#include <tfunc.h>

#define MAX_N_FUNCTION  50

static tXmlFuncionesPtr cabListaFunciones=NULL;
static tXmlFuncionesPtr ultListaFunciones=NULL;

static tXmlFuncionesPtr FUNC_searchType(enum E_TIPOF tipo);
static tXmlFuncionesPtr FUNC_search(enum E_TIPOF tipo, char * name);

void FUNC_set(tXmlFuncionesPtr cab, tXmlFuncionesPtr ult)
{
  cabListaFunciones = cab;
  ultListaFunciones = ult;
}

tXmlFuncionesPtr FUNC_get()
{
  return cabListaFunciones;
}

void FUNC_reset()
{
  tXmlFuncionesPtr aux;
  aux = cabListaFunciones;
  while (aux != NULL) {
    cabListaFunciones = cabListaFunciones->siguiente;
    free(aux);
    aux=cabListaFunciones;
  }
  cabListaFunciones = ultListaFunciones = NULL;
}

static tXmlFuncionesPtr FUNC_searchType(enum E_TIPOF tipo)
{
  tXmlFuncionesPtr aux;

  aux = cabListaFunciones;
  while (aux!=NULL) {
    if (aux->tipo == tipo) return aux;
    aux=aux->siguiente;
  }
  return NULL;
}

static tXmlFuncionesPtr FUNC_search(enum E_TIPOF tipo, char * name)
{
  tXmlFuncionesPtr aux;

  aux = cabListaFunciones;
  while (aux!=NULL) {
    if (strcmp(aux->name,name)==0) return aux;
    aux=aux->siguiente;
  }
  return NULL;
}

int FUNC_addListaFuncion(enum E_TIPOF tipo, char * name)
{
  tXmlFuncionesPtr aux;

  if (tipo == F_INIT || tipo == F_END) {
     aux = FUNC_searchType(tipo);
     if (aux != NULL) {strcpy(aux->name,name); return 0;}
  }
  else 
    aux = FUNC_search(tipo, name);

  if (aux!=NULL) {
    if (aux->tipo == tipo){aux->nroUses++; return 0;}
    return -1;
  }

  aux = (tXmlFuncionesPtr) malloc(sizeof(tXmlFunciones));
  if (aux == NULL){
     ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlFunciones));
     return -1;
  }
  aux->tipo=tipo;
  strcpy(aux->name,name);
  aux->nroUses=1;
  aux->siguiente = aux->anterior = NULL;
  if (cabListaFunciones == NULL) cabListaFunciones = ultListaFunciones = aux;
  else {
    ultListaFunciones->siguiente = aux;
    aux->anterior=ultListaFunciones;
    ultListaFunciones = aux;
  }
  return 0;
}

int FUNC_delListaFuncion(enum E_TIPOF tipo, char * name)
{
  tXmlFuncionesPtr aux;

  aux = cabListaFunciones;
  while (aux!=NULL) {
    if (strcmp(aux->name,name)==0) {
      aux->nroUses--; break; }
    aux=aux->siguiente;
  }

  if (aux==NULL || aux->nroUses > 0) return 0;

  if (aux->anterior != NULL)
    aux->anterior->siguiente = aux->siguiente;
  if (aux->siguiente != NULL)
    aux->siguiente->anterior = aux->anterior;

  free(aux);
  return 0;
}


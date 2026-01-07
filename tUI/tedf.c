
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
#include <tedf.h>

#define MAX_N_FUNCTION  50

static tXmlCEdFunctionPtr cabCEdFunctions = NULL;
static tXmlCEdFunctionPtr ultCEdFunctions = NULL;

static int EDF_deleteList(char * name);

void EDF_set(tXmlCEdFunctionPtr cab, tXmlCEdFunctionPtr ult)
{
  cabCEdFunctions = cab;
  ultCEdFunctions = ult;
}

tXmlCEdFunctionPtr EDF_get()
{
  return cabCEdFunctions;
}

void EDF_reset()
{
  tXmlCEdFunctionPtr aux;
  aux = cabCEdFunctions;
  while (aux != NULL) {
    cabCEdFunctions = cabCEdFunctions->siguiente;
    free(aux);
    aux=cabCEdFunctions;
  }
  cabCEdFunctions = ultCEdFunctions = NULL;
}

trAction* EDF_load (tComponent * component,int key){
static trAction action;
 tComponent * auxList;
 tXmlCEdFunctionPtr aux;

  initAction(action);

 auxList = (tComponent *)LVIEW_getElement("frmEFunction","frmEFlist");
 COMPONENT_clean(auxList);
 aux = cabCEdFunctions;
 while (aux!=NULL) {
  COMPONENT_addText(auxList,aux->name);
  aux = aux->siguiente;
 }

 return &action;
}

trAction* EDF_new (tComponent * component,int key){
static trAction action;
 tComponent * auxName,*aux;
 tComponent * auxList;
 char * value;
 int new = 0;
 tXmlCEdFunctionPtr auxFunction = NULL;

  initAction(action);

 auxList = (tComponent *)LVIEW_getElement(NULL,"frmEFlist");
 auxName = (tComponent *)LVIEW_getElement(NULL,"frmEFname");
 if (auxName != NULL && auxList != NULL) {
   value = COMPONENT_getValue(auxName);
   if (value == NULL || strcmp(value,"")==0) return &action;
   if ((auxFunction=EDF_search(value)) != NULL){
    if (MSG_create(M_WARNING,CENTER_VIEW,"Function already exist, rewrite ?")) 
     return &action;
   }
   else{
     new = 1;
     auxFunction = (tXmlCEdFunctionPtr)malloc(sizeof(tXmlCEdFunction));
     if (auxFunction == NULL)
       ERR_fatalError(ERR_MEM,"Error malloc %d\n",sizeof(tXmlCEdFunction));
   }
   strcpy(auxFunction->name,value);
   aux = (tComponent *)LVIEW_getElement(NULL,"frmEFAlign");
   if (aux!=NULL){
    value = COMPONENT_getValue(aux);
    if (strcmp(value,"LEFT")==0)
	auxFunction->align=A_Left; else auxFunction->align=A_Right;
   }
   aux = (tComponent *)LVIEW_getElement(NULL,"frmEFMode");
   if (aux!=NULL){
       value = COMPONENT_getValue(aux);
       if (strcmp(value,"INSERT")==0)
	auxFunction->insert=Insert; else auxFunction->insert=Replace;
   }
   if (new) {
    auxFunction->siguiente=NULL;
    auxFunction->anterior=NULL;
     if (ultCEdFunctions == NULL)
      cabCEdFunctions = ultCEdFunctions = auxFunction;
     else
     {
       auxFunction->anterior=ultCEdFunctions;
       ultCEdFunctions->siguiente = auxFunction;
       ultCEdFunctions = auxFunction;
     }
     TEXT_addSimpleLine(auxList->text,auxFunction->name);
   }
   COMPONENT_show(auxList);
   COMPONENT_changeText(auxName,"");
 }
 else
    MSG_create(M_ERROR,CENTER_VIEW,"Components not found");

 return &action;
}

trAction* EDF_delete (tComponent * component,int key){
static trAction action;
 tComponent * aux;
 tComponent * auxList;
 char * value;

  initAction(action);

 auxList = (tComponent *)LVIEW_getElement(NULL,"frmEFlist");
 aux = (tComponent *)LVIEW_getElement(NULL,"frmEFname");
 if (aux != NULL && auxList != NULL) {
   value = COMPONENT_getValue(aux);
   if (value == NULL || strcmp(value,"")==0){
     MSG_create(M_ERROR,CENTER_VIEW,"Select the Function to delete");
     return &action;
   }
   if (!EDF_search(value)){
     MSG_create(M_WARNING,CENTER_VIEW,"Function don't exists");
   }
   else{
     EDF_deleteList(value);
     TEXT_delLineText(auxList->text,value);
     COMPONENT_show(auxList);
     COMPONENT_changeText(aux,"");
   }
 }
 else
     MSG_create(M_ERROR,CENTER_VIEW,"Components not found");

 return &action;
}

tXmlCEdFunctionPtr  EDF_search(char * name)
{
tXmlCEdFunctionPtr aux;

   aux = cabCEdFunctions;
   while (aux != NULL) {
    if (strcmp(aux->name,name)==0) return aux;
    aux = aux->siguiente;
   }
  return 0;
}

static int EDF_deleteList(char * name)
{
tXmlCEdFunctionPtr aux;

   aux = cabCEdFunctions;
   while (aux != NULL) {
    if (strcmp(aux->name,name)==0) {
       if (aux == cabCEdFunctions) {
         if (cabCEdFunctions->siguiente == NULL)
          cabCEdFunctions=ultCEdFunctions = NULL;
         else{
          cabCEdFunctions->siguiente->anterior = NULL;
          cabCEdFunctions=cabCEdFunctions->siguiente;
         }
       }
       else{
         aux->anterior->siguiente = aux->siguiente;
         if (aux->siguiente!=NULL)aux->siguiente->anterior=aux->anterior;
       }
       free(aux);
    }
    aux = aux->siguiente;
   }
  return 0;
}


trAction* EDF_select (tComponent * component,int key){
static trAction action;
 tComponent * aux;
 tXmlCEdFunctionPtr auxFunction = NULL;
 char * value;int select;

 initAction(action);

  value= COMPONENT_getValue(component);
  if ((auxFunction=EDF_search(value)) == NULL) return &action;
  aux = (tComponent *)LVIEW_getElement(NULL,"frmEFname");
  COMPONENT_changeText(aux,value);
  aux = (tComponent *)LVIEW_getElement(NULL,"frmEFAlign");
  select = (auxFunction->align == A_Left)?0:1;
  COMPONENT_setSelectValue(aux,select,NULL);
  COMPONENT_refresh(aux);
  aux = (tComponent *)LVIEW_getElement(NULL,"frmEFMode");
  select = (auxFunction->insert == Insert)?0:1;
  COMPONENT_setSelectValue(aux,select,NULL);
  COMPONENT_refresh(aux);

 return &action;
}

int OneTo9(int * caracter)
{
 return (*caracter >= 49 && *caracter <= 57)?0:1;
}



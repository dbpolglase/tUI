
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <text.h>
#include <edit.h>
#include <table.h>
#include <lview.h>
#include <component.h>

#include <tparser.h>
#include <tproyect.h>
#include <tcolor.h>

#define MAX_N_COLOR  50

static tXmlcolorPtr cabColores;
static tXmlcolorPtr ultColores;


void COLOR_set(tXmlcolorPtr cab, tXmlcolorPtr ult){
  cabColores = cab;
  ultColores = ult;
}

void COLOR_reset()
{
  tXmlcolorPtr aux;

  aux = cabColores;
  while (aux != NULL) {
   cabColores = cabColores->siguiente;
   free(aux);
   aux = cabColores;
 }
  cabColores = ultColores = NULL;
}

tXmlcolorPtr COLOR_getXml()
{
  return cabColores;
}
 

void COLOR_load () {
tXmlcolorPtr aux;
tComponent * auxC;
char * data;

 data = TEXT_recv();

 if (data != NULL){
   aux = cabColores;
   while (aux!=NULL && (strcmp(aux->name,data)!=0)) aux = aux->siguiente;
   if (aux == NULL) {
        MSG_create(M_INFO,CENTER_VIEW,"COLOR <%s> not found",data);
   }
   else
   {
     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCname");
     COMPONENT_setValue(auxC,aux->name);

     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCbcolor");
     COMPONENT_setSelectValue(auxC,aux->bcolor,NULL);
     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCfcolor");
     COMPONENT_setSelectValue(auxC,aux->fcolor,NULL);
     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCtext");
     COMPONENT_setSelectValue(auxC,0,COLOR_textoChTipo(aux->attr));
     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCdelete");
     COMPONENT_display(auxC,DIS_NORMAL);
   }
 }
 else{
     auxC = (tComponent *)LVIEW_getElement("frmColor","frmCdelete");
   COMPONENT_display(auxC,DIS_HIDDEN);
 }
}


trAction* COLOR_new (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * dato;
int new=0;
tXmlcolorPtr auxColor=NULL;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"frmCname");
 dato = COMPONENT_getValue(auxC);
 
 if (dato==NULL || strcmp(dato,"")==0){
   MSG_create(M_ERROR,CENTER_VIEW,"Color Name Needed");
   action.error=1;
   action.made=1;
   return &action;
 }

 if ((auxColor = COLOR_searchColor(dato)) != NULL)
 {
   if (MSG_create(M_WARNING,CENTER_VIEW,"The Color Name already exists, update?"))
   {
    action.error=1;
    action.made=1;
    return &action;
   }
 }

 if (auxColor == NULL) {
   auxColor =(tXmlcolor *)malloc(sizeof(tXmlcolor));
   if (auxColor == NULL) ERR_fatalError(ERR_MEM,"Out of memory");
   strcpy(auxColor->name,dato);
   new = 1;
 }
 auxColor->bcolor=0;
 auxColor->fcolor=0;
 auxColor->attr=0;

 auxC = (tComponent *)LVIEW_getElement(NULL,"frmCbcolor");
 if (auxC != NULL) {
  dato = COMPONENT_getValue(auxC);
  auxColor->bcolor=dato[0]-'0';
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"frmCfcolor");
 if (auxC != NULL) {
  dato = COMPONENT_getValue(auxC);
  auxColor->fcolor=dato[0]-'0';
 }

 auxC = (tComponent *)LVIEW_getElement(NULL,"frmCtext");
 if (auxC != NULL) auxColor->attr= COLOR_tipoChTexto(COMPONENT_getValue(auxC));

 if (new) {
   auxColor->siguiente=NULL;
   auxColor->anterior=ultColores;

   if (cabColores == NULL) {
	cabColores = ultColores = auxColor;
   }
   else {
     ultColores->siguiente = auxColor;
     ultColores = auxColor;
   }
 }

  
 MSG_create(M_INFO,CENTER_VIEW,"Done!!");

 return &action;
}

trAction* COLOR_delete (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * nomColor;
tXmlcolorPtr auxColor;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"frmCname");
 if (auxC==NULL){
   MSG_create(M_ERROR,CENTER_VIEW,"Color Name not found");
   action.error=1;
   return &action;
 }

 nomColor = COMPONENT_getValue(auxC);
 
 if (nomColor==NULL || strcmp(nomColor,"")==0){
   MSG_create(M_ERROR,CENTER_VIEW,"Color Name Needed");
   action.error=1;
   return &action;
 }

 if ((auxColor = COLOR_searchColor(nomColor)) == NULL)
 {
   MSG_create(M_ERROR,CENTER_VIEW,"The Color Name don't exists");
   action.error=1;
   action.made=1;
   return &action;
 }

 if (auxColor==cabColores) cabColores=cabColores->siguiente;
 if (auxColor==ultColores) ultColores=ultColores->anterior;

 if (auxColor->anterior!=NULL) auxColor->anterior->siguiente=auxColor->siguiente;
 if (auxColor->siguiente!=NULL) auxColor->siguiente->anterior=auxColor->anterior;

 free(auxColor);

 return &action;
}

trAction* COLOR_change (tComponent * component,int key){
static trAction action;
 initAction(action);

 if (!PROY_isColor())
   MSG_create(M_ERROR,CENTER_VIEW,"Proyect without colors");

 if (cabColores == NULL) {
   MSG_create(M_ERROR,CENTER_VIEW,"The aren't colors defined");
   action.error=1;
 }
 else {
   TEXT_send("frmColor:frmCname",1);
   TEXT_send("COLOR",0);
   TEXT_send("-:",0);
 }

 return &action;
}

void COLOR_loadTColor(tTable * table){
 tXmlcolorPtr auxColor;
 auxColor=cabColores;

 while (auxColor != NULL){
    TEXT_addData(table->text,auxColor->name);
    auxColor = auxColor->siguiente;
 }

return ;
}

void COLOR_loadChange(tPanel * panel){
  char * color;
  tComponent * aux;

   aux = (tComponent *)LVIEW_getElement("fnccolor","fncncolor");
   color = TEXT_recv();
  
   COMPONENT_changeText(aux,color);
return ;
}



chtype COLOR_tipoChTexto(char * datoTipo)
{
if (strcmp("WA_ATTRIBUTES",datoTipo)==0) return   WA_ATTRIBUTES;
if (strcmp("WA_NORMAL",datoTipo)==0) return       WA_NORMAL;
if (strcmp("WA_STANDOUT",datoTipo)==0) return     WA_STANDOUT;
if (strcmp("WA_UNDERLINE",datoTipo)==0) return    WA_UNDERLINE;
if (strcmp("WA_REVERSE",datoTipo)==0) return      WA_REVERSE;
if (strcmp("WA_BLINK",datoTipo)==0) return        WA_BLINK;
if (strcmp("WA_DIM",datoTipo)==0) return          WA_DIM;
if (strcmp("WA_BOLD",datoTipo)==0) return         WA_BOLD;
if (strcmp("WA_ALTCHARSET",datoTipo)==0) return   WA_ALTCHARSET;
if (strcmp("WA_INVIS",datoTipo)==0) return        WA_INVIS;
if (strcmp("WA_PROTECT",datoTipo)==0) return      WA_PROTECT;
if (strcmp("WA_HORIZONTAL",datoTipo)==0) return   WA_HORIZONTAL;
if (strcmp("WA_LEFT",datoTipo)==0) return         WA_LEFT;
if (strcmp("WA_LOW",datoTipo)==0) return          WA_LOW;
if (strcmp("WA_RIGHT",datoTipo)==0) return        WA_RIGHT;
if (strcmp("WA_TOP",datoTipo)==0) return          WA_TOP;
if (strcmp("WA_VERTICAL",datoTipo)==0) return     WA_VERTICAL;
if (strcmp("WA_ITALIC",datoTipo)==0) return       WA_ITALIC;
return 0;
}

char * COLOR_textoChTipo(int tipo)
{
  switch (tipo)
  {
	 case  WA_ATTRIBUTES: return "WA_ATTRIBUTES";
	 case  WA_NORMAL: return "WA_NORMAL";
	 case  WA_STANDOUT: return "WA_STANDOUT";
	 case  WA_UNDERLINE: return "WA_UNDERLINE";
	 case  WA_REVERSE: return "WA_REVERSE";
	 case  WA_BLINK: return "WA_BLINK";
	 case  WA_DIM: return "WA_DIM";
	 case  WA_BOLD: return "WA_BOLD";
	 case  WA_ALTCHARSET: return "WA_ALTCHARSET";
	 case  WA_INVIS: return "WA_INVIS";
	 case  WA_PROTECT: return "WA_PROTECT";
	 case  WA_HORIZONTAL: return "WA_HORIZONTAL";
	 case  WA_LEFT: return "WA_LEFT";
	 case  WA_LOW: return "WA_LOW";
	 case  WA_RIGHT: return "WA_RIGHT";
	 case  WA_TOP: return "WA_TOP";
	 case  WA_VERTICAL: return "WA_VERTICAL";
	 case  WA_ITALIC: return "WA_ITALIC";
    default: return "WA_NORMAL";
  }
return "WA_NORMAL";
}

tXmlcolorPtr COLOR_searchColor(char * name)
{
 tXmlcolorPtr aux;
 aux = cabColores;
 while (aux != NULL) {
   if (strcmp(aux->name,name)==0) return aux;
   aux = aux->siguiente;
 }
 return NULL;
}


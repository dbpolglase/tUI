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
#include <tview.h>
#include <tcolor.h>
#include <tkeymap.h>
#include <tedf.h>
#include <tcomp.h>

static int newComp=0;
static int update=0;
static char ATRAS_DOS[5]="-2:";
static tXmlComponentPtr cabComps;
static tXmlComponentPtr ultComps;
static tXmlComponent actComp;

static char frmToLaunch[50];
static char selectToLaunch[50];
static void COMP_insertText(char * texto);
static void COMP_borraText();
static void COMP_replaceComp();

extern SCREEN * scrSTD;

void COMP_set(tXmlComponentPtr cab, tXmlComponentPtr ult){
  cabComps = cab;
  ultComps = ult;
}

void COMP_reset()
{
  tXmlComponentPtr aux;

  aux = cabComps;
  while (aux != NULL) {
   cabComps = cabComps->siguiente;
   free(aux);
   aux = cabComps;
 }
 cabComps = ultComps = NULL;
}

tXmlComponentPtr COMP_get()
{
  return cabComps;
}

trAction* COMP_out (tComponent * component,int key){
static trAction action;
tCaller * llamante;

 initAction(action);
 llamante = LVIEW_getCaller(); 
 if (strcmp(llamante->View,"tselect")==0 || newComp){
   action.made = 1;
   action.componentNext = ATRAS_DOS;
 }
 return &action;
}


tXmlComponentPtr COMP_searchComp(char * panel, char * name)
{
 tXmlComponentPtr aux;
 aux = cabComps;
 while (aux != NULL) {
   if (strcmp(aux->panelName,panel)==0 && strcmp(aux->name,name)==0) return aux;
   aux = aux->siguiente;
 }
 return NULL;
}

static void COMP_replaceComp()
{
 tXmlComponentPtr aux;
 tTable * auxT;
 char * datosAct[2];
 aux = COMP_searchComp(actComp.panelName,actComp.name);
 if (aux != NULL) {
   memcpy(aux,&actComp,sizeof(tXmlComponent));
 } else {
   aux = (tXmlComponentPtr) malloc(sizeof(tXmlComponent)); 
   memcpy(aux,&actComp,sizeof(tXmlComponent));
   aux->siguiente = aux->anterior = NULL;
   COMP_addComp(aux); 
   PANEL_addComp(aux->panelName, aux);
   if (update){
      auxT = (tTable *)LVIEW_getElement("tcomp",NULL);
      datosAct[0] = aux->panelName;
      datosAct[1] = aux->name;
      TEXT_addLine(auxT->text,2,datosAct);
      LVIEW_refresh("tcomp");
   }
 }
 actComp.text = NULL;
}

void COMP_addComp(tXmlComponentPtr comp)
{
  if (cabComps == NULL)
   cabComps=ultComps=comp;
  else {
   comp->anterior=ultComps;
   ultComps->siguiente = comp;
   ultComps=comp;
  }
}

void COMP_delComp(tXmlComponentPtr comp)
{
 tXmlComponent * aux;

  aux = cabComps;
  
  if (cabComps == comp) cabComps = cabComps->siguiente;
  if (ultComps == comp)  ultComps = ultComps->anterior;
  while (aux != NULL){
    if (aux == comp){
      if (aux->anterior != NULL) aux->anterior->siguiente=aux->siguiente;
      if (aux->siguiente != NULL) aux->siguiente->anterior=aux->anterior;
      free(aux);
      return;
    }
    aux = aux->siguiente;
  }
}

trAction* COMP_delete(tComponent * component,int key){
static trAction action;
char * panel;
char * ncomp;
tCaller * llamante;
tComponent * auxC;
tXmlComponent * auxComp;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 ncomp = COMPONENT_getValue(auxC); 
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 panel = COMPONENT_getValue(auxC); 

 auxComp=COMP_searchComp(panel,ncomp);
 if (auxComp == NULL)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Component not found ");
  action.error=1;
  return &action;
 }
 PANEL_delComp(VIEW_searchPanel(panel),auxComp);
 COMP_delComp(auxComp);

 llamante = LVIEW_getCaller(); 
 if (strcmp(llamante->View,"tselect")==0){
   action.made = 1;
   action.componentNext = ATRAS_DOS;
 }

 return &action;
}

trAction* COMP_labelDoIt (tComponent * component,int key){
static trAction action;
char * value;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLid");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.id= atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.name,value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Name not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0 && strcmp(value,"NEW")!=0)
  strcpy(actComp.panelName,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLVisible");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.visible=(value==NULL)?DIS_HIDDEN:DIS_NORMAL;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLColor");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.visual.color,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBorder");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.dimension.border=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLX");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.x= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLY");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.y= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLWidth");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.ancho= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLHigh");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.alto= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLText");
 value = COMPONENT_getValue(auxC); 
 COMP_borraText();
 COMP_insertText(value);

 COMP_replaceComp();

 
 MSG_create(M_INFO, CENTER_VIEW,"Done !!");
 return &action;
}

trAction* COMP_buttonDoIt (tComponent * component,int key){
static trAction action;
char * value, * value2;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBid");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.id= atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.name,value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Name not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0 && strcmp(value,"NEW")!=0)
  strcpy(actComp.panelName,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBVisible");
 value = COMPONENT_getValue(auxC); 
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBSelect");
 value2 = COMPONENT_getValue(auxC); 
 if (value != NULL){
   if (value2 != NULL) actComp.visual.visible=DIS_NORMAL;
   else actComp.visual.visible = DIS_NO_SELECT;
 } else {
   actComp.visual.visible = DIS_HIDDEN;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoTKeymap");
 value = COMPONENT_getValue(auxC); 
 if (value == NULL || strcmp(value,"Default") ==0)
  strcpy(actComp.mapkey,""); else strcpy(actComp.mapkey,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBColor");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.visual.color,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBBorder");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.dimension.border=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBX");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.x= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBY");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.y= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBWidth");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.ancho= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBHigh");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.alto= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoBText");
 value = COMPONENT_getValue(auxC); 
 COMP_borraText();
 COMP_insertText(value);

 COMP_replaceComp();
 MSG_create(M_INFO, CENTER_VIEW,"Done !!");
 return &action;
}

trAction* COMP_ckbuttonDoIt (tComponent * component,int key){
static trAction action;
char * value,*value2;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBid");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.id= atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.name,value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Name not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0 && strcmp(value,"NEW")!=0)
  strcpy(actComp.panelName,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBVisible");
 value = COMPONENT_getValue(auxC); 
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBSelect");
 value2 = COMPONENT_getValue(auxC); 
 if (value != NULL){
   if (value2 != NULL) {
      actComp.visual.visible=DIS_NORMAL;
   }
   else actComp.visual.visible = DIS_NO_SELECT;
 } else {
   actComp.visual.visible = DIS_HIDDEN;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBColor");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.visual.color,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoTKeymap");
 value = COMPONENT_getValue(auxC); 
 if (value == NULL || strcmp(value,"Default") ==0)
  strcpy(actComp.mapkey,""); else strcpy(actComp.mapkey,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBBorder");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.dimension.border=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBX");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.x= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBY");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.y= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBWidth");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.ancho= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBHigh");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.alto= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBText");
 value = COMPONENT_getValue(auxC); 
 COMP_borraText();
 COMP_insertText(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBisCheck");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.isCheck=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBchcheck");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.chCheck=(value==NULL)?0:value[0];
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBchischeck");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.chIsCheck=(value==NULL)?0:value[0];
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBchncheck");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.chNoCheck=(value==NULL)?0:value[0];

 COMP_replaceComp();
 MSG_create(M_INFO, CENTER_VIEW,"Done !!");
 return &action;
}

trAction* COMP_lsbuttonDoIt (tComponent * component,int key){
static trAction action;
char * value;
int linea,i;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBid");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.id= atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.name,value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Name not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0 && strcmp(value,"NEW")!=0)
  strcpy(actComp.panelName,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoDisplay");
 value = COMPONENT_getValue(auxC); 
 COMPONENT_getSelectValue(auxC,&linea);
 actComp.visual.visible = linea;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBColor");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.visual.color,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoTKeymap");
 value = COMPONENT_getValue(auxC); 
 if (value == NULL || strcmp(value,"Default") ==0)
  strcpy(actComp.mapkey,""); else strcpy(actComp.mapkey,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBBorder");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.dimension.border=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBX");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.x= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBY");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.y= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBWidth");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.ancho= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBHigh");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.alto= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
   action.error=1;
   return &action;
 }
 COMP_borraText();
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBData");
 for (i=0;value!=NULL;i++)
 {
   value = TEXT_getData(auxC->text,i,0);
   COMP_insertText(value);
 }

 COMP_replaceComp();
 MSG_create(M_INFO, CENTER_VIEW,"Done !!");
 return &action;
}

trAction* COMP_addList (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * value;

 initAction(action);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBText");
 value = COMPONENT_getValue(auxC);

 if (value != NULL && strcmp(value,"")!=0){
  auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBData");
  if (!COMPONENT_isValue(auxC,value)){
   COMPONENT_addText(auxC,value);
   COMPONENT_refresh(auxC);
  }
 }

return &action;
}

trAction* COMP_lbData (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * value;

 initAction(action);
 value = COMPONENT_getValue(component);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBText");
 COMPONENT_setValue(auxC,value);
 COMPONENT_refresh(auxC);

 return &action;
}

trAction* COMP_delList (tComponent * component,int key){
static trAction action;
char * value;
tComponent * auxC;

 initAction(action);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBText");
 value = COMPONENT_getValue(auxC);

 if (value != NULL && strcmp(value,"")!=0){
  auxC = (tComponent *)LVIEW_getElement(NULL,"CoLBData");
  if (COMPONENT_isValue(auxC,value)){
     COMPONENT_delText(auxC,value);
     COMPONENT_refresh(auxC);
  }
 }

return &action;
}


trAction* COMP_fieldDoIt (tComponent * component,int key){
static trAction action;
char * value,*value2;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDid");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.id= atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"cname");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.name,value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Name not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"cpanel");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0 && strcmp(value,"NEW")!=0)
  strcpy(actComp.panelName,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDVisible");
 value = COMPONENT_getValue(auxC); 
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDSelect");
 value2 = COMPONENT_getValue(auxC); 
 if (value != NULL){
   if (value2 != NULL) actComp.visual.visible=DIS_NORMAL;
   else actComp.visual.visible = DIS_NO_SELECT;
 } else {
   actComp.visual.visible = DIS_HIDDEN;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDColor");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.visual.color,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoTKeymap");
 value = COMPONENT_getValue(auxC); 
 if (value == NULL || strcmp(value,"Default") ==0)
  strcpy(actComp.mapkey,""); else strcpy(actComp.mapkey,value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDAuto");
 value = COMPONENT_getValue(auxC); 
 actComp.editMode.autoComplet=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDSecret");
 value = COMPONENT_getValue(auxC); 
 actComp.editMode.secret=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDmode");
 value = COMPONENT_getValue(auxC); 
 actComp.editMode.chToEDIT=(value==NULL)?CHAR_TO_EDIT:value[0];
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDTEFunction");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  strcpy(actComp.editMode.editFunction,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDBorder");
 value = COMPONENT_getValue(auxC); 
 actComp.visual.dimension.border=(value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDX");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.x= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDY");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.y= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDWidth");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.ancho= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDHigh");
 value = COMPONENT_getValue(auxC); 
 if (value != NULL && strcmp(value,"")!=0)
  actComp.visual.dimension.alto= atoi(value);
 else{
   MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
   action.error=1;
   return &action;
 }
 auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDText");
 value = COMPONENT_getValue(auxC); 
 COMP_borraText();
 COMP_insertText(value);

 COMP_replaceComp();
 MSG_create(M_INFO, CENTER_VIEW,"Done !!");
 return &action;
}

static void COMP_borraText(){
 tXmlTextPtr auxText,aux2Text;
 aux2Text = auxText = actComp.text;

  while (auxText != NULL) {
   auxText = auxText->siguiente;
   free(aux2Text->texto);
   aux2Text = auxText;
  }
  actComp.text=NULL;
}

static void COMP_insertText(char * texto){
  tXmlTextPtr auxText;
  tXmlTextPtr aux2Text;

  auxText = (tXmlTextPtr) malloc(sizeof(tXmlText));
  if (texto == NULL) auxText->texto = NULL;
  else {
    auxText->texto = (char *) malloc(strlen(texto+3));
    strcpy(auxText->texto,texto);
  }
  auxText->siguiente = auxText->anterior = NULL;
  if (actComp.text == NULL)
   actComp.text=auxText;
  else{
   aux2Text = actComp.text;
   while (aux2Text->siguiente != NULL) aux2Text=aux2Text->siguiente;
   aux2Text->siguiente=auxText;
   auxText->anterior=aux2Text;
  }
}

trAction* COMP_reqCalls(tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send(actComp.name,1);
 TEXT_send("CALL_COMPONENT",0);

 return &action;
}

tXmlFApplication * COMP_getCalls(){
 return &actComp.personalFComponent;
}

trAction* COMP_reqMoves (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send(actComp.name,1);
 TEXT_send(actComp.panelName,0);
 TEXT_send("COMP_MOVE",0);

 return &action;
}

tXmlMove * COMP_getCompMove(char * dato){
  return &actComp.move;
}

tXmlMove * COMP_getCompAppMove(char * dato){
  return &actComp.personalAction;
}


trAction* COMP_callFrm (tComponent * component,int key){
static trAction action;
 initAction(action);
 
 action.made=1;
 action.opToMade=OP_HIDE;
 action.componentNext=frmToLaunch;

return &action;
}


void COMP_loadLABEL()
{
tComponent * auxC;
static char * ncomp;
static char * panel;
char * lcomp;
char * lpanel;
char auxdata[400];
tXmlcolorPtr auxColor;
tXmlTextPtr auxText;
tXmlComponentPtr auxComp;

 auxC = (tComponent *)LVIEW_getElement("CoL","CoLColor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 newComp =0;
 strcpy(auxdata,"");
 lcomp = TEXT_recv();
 lpanel = TEXT_recv();
 if (lcomp != NULL) ncomp=lcomp;
 if (lpanel != NULL) panel=lpanel;
 update=TEXT_recv()==NULL?0:1;

 memset(&actComp,'\0',sizeof(tXmlComponent));
 actComp.type=C_LABEL;
 if (ncomp != NULL && strcmp(ncomp,"NEW") !=0){
   auxComp=COMP_searchComp(panel,ncomp);
   if (auxComp != NULL) 
   {
     memcpy(&actComp,auxComp,sizeof(tXmlComponent));
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLid");
     sprintf(auxdata,"%d",actComp.id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoL","cname");
     COMPONENT_setValue(auxC,actComp.name);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLColor");
     COMPONENT_setValue(auxC,actComp.visual.color);
     auxC = (tComponent *)LVIEW_getElement("CoL","cpanel");
     COMPONENT_setValue(auxC,actComp.panelName);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLVisible");
     if (actComp.visual.visible != DIS_HIDDEN) COMPONENT_setValue(auxC,"Y");
        else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLBorder");
     actComp.visual.dimension.border?COMPONENT_setValue(auxC,"1"):COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLX");
     sprintf(auxdata,"%d",actComp.visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLY");
     sprintf(auxdata,"%d",actComp.visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLWidth");
     sprintf(auxdata,"%d",actComp.visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLHigh");
     sprintf(auxdata,"%d",actComp.visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoL","CoLText");
     auxText=actComp.text;
   
     if (auxText != NULL) {
       strcpy(auxdata,"");
     
       if (auxText->texto != NULL) strcpy(auxdata,auxText->texto);
       auxText = auxText->siguiente; 
       while (auxText != NULL){
        strcat(auxdata,"\n");
        if (auxText->texto != NULL) strcpy(auxdata,auxText->texto);
        auxText = auxText->siguiente;
       }
     }
     COMPONENT_setValue(auxC,auxdata);
   }
 }
 else{
   newComp =1;
   auxC = (tComponent *)LVIEW_getElement("CoL","cpanel");
   COMPONENT_setValue(auxC,panel);
   strcpy(actComp.panelName,panel);
 }
}

void COMP_loadButton()
{
tComponent * auxC;
char * lcomp;
char * lpanel;
static char * ncomp;
static char * panel;
char auxdata[400];
tXmlcolorPtr auxColor;
tXmlTextPtr auxText;
tXmlComponentPtr auxComp;
tXmlMapKeyPtr auxKeymap;

 strcpy(auxdata,"");
 auxC = (tComponent *)LVIEW_getElement("CoB","CoLKeymap");
 COMPONENT_clean(auxC); 
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("CoB","CoBColor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 newComp =0;
 lcomp = TEXT_recv();
 lpanel = TEXT_recv();
 update=TEXT_recv()==NULL?0:1;
 
 if (lcomp != NULL) ncomp=lcomp;
 if (lpanel != NULL) panel=lpanel;

 memset(&actComp,'\0',sizeof(tXmlComponent));
 actComp.type=C_BUTTON;
 if (ncomp != NULL && strcmp(ncomp,"NEW") !=0){
   auxComp=COMP_searchComp(panel,ncomp);
   if (auxComp != NULL) 
   {
     memcpy(&actComp,auxComp,sizeof(tXmlComponent));
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBid");
     sprintf(auxdata,"%d",actComp.id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoB","cname");
     COMPONENT_setValue(auxC,actComp.name);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBColor");
     COMPONENT_setValue(auxC,actComp.visual.color);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoLKeymap");
     if (COMPONENT_setValue(auxC,actComp.mapkey) >= 0){
        auxC = (tComponent *)LVIEW_getElement("CoB","CoTKeymap");
        COMPONENT_setValue(auxC,actComp.mapkey);
     }

     auxC = (tComponent *)LVIEW_getElement("CoB","cpanel");
     COMPONENT_setValue(auxC,actComp.panelName);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBVisible");
     if (actComp.visual.visible != DIS_HIDDEN) 
	    COMPONENT_setValue(auxC,"Y");
     else 
          COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBSelect");
     if (actComp.visual.visible != DIS_HIDDEN) 
 	 COMPONENT_display(auxC,DIS_NORMAL);
     else
 	 COMPONENT_display(auxC,DIS_NO_SELECT);
     if (actComp.visual.visible != DIS_HIDDEN &&
         actComp.visual.visible != DIS_NO_SELECT) 
        COMPONENT_setValue(auxC,"Y");
     else 
	COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBBorder");
     actComp.visual.dimension.border?COMPONENT_setValue(auxC,"1"):COMPONENT_setValue(auxC,NULL);

     auxC = (tComponent *)LVIEW_getElement("CoB","CoBX");
     sprintf(auxdata,"%d",actComp.visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBY");
     sprintf(auxdata,"%d",actComp.visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBWidth");
     sprintf(auxdata,"%d",actComp.visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBHigh");
     sprintf(auxdata,"%d",actComp.visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoB","CoBText");
     auxText=actComp.text;
   
     strcpy(auxdata,"");
     if (auxText != NULL) 
       {if (auxText->texto != NULL) strcpy(auxdata,auxText->texto);auxText = auxText->siguiente; }
     while (auxText != NULL){
        if (auxText->texto != NULL) {
          strcat(auxdata,"\n");
          strcat(auxdata,auxText->texto);
        }
        auxText = auxText->siguiente;
     }
     COMPONENT_setValue(auxC,auxdata);
   }
 }
 else{
   newComp =1;
   auxC = (tComponent *)LVIEW_getElement("CoB","cpanel");
   COMPONENT_setValue(auxC,panel);
   strcpy(actComp.panelName,panel);
 }
}

void COMP_loadCkButton()
{
tComponent * auxC;
static char * ncomp;
static char * panel;
char * lcomp;
char * lpanel;
char auxdata[400];
tXmlcolorPtr auxColor;
tXmlTextPtr auxText;
tXmlComponentPtr auxComp;
tXmlMapKeyPtr auxKeymap;

 strcpy(auxdata,"");
 auxC = (tComponent *)LVIEW_getElement("CoCB","CoLKeymap");
 COMPONENT_clean(auxC); 
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBColor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 newComp =0;
 lcomp = TEXT_recv();
 lpanel = TEXT_recv();
 if (lcomp != NULL) ncomp=lcomp;
 if (lpanel != NULL) panel=lpanel;
 update=TEXT_recv()==NULL?0:1;

 memset(&actComp,'\0',sizeof(tXmlComponent));
 actComp.type=C_CKBUTTON;
 if (ncomp != NULL && strcmp(ncomp,"NEW") !=0){
   auxComp=COMP_searchComp(panel,ncomp);
   if (auxComp != NULL) 
   {
     memcpy(&actComp,auxComp,sizeof(tXmlComponent));
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBid");
     sprintf(auxdata,"%d",actComp.id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","cname");
     COMPONENT_setValue(auxC,actComp.name);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBColor");
     COMPONENT_setValue(auxC,actComp.visual.color);
     auxC = (tComponent *)LVIEW_getElement("CoCB","cpanel");
     COMPONENT_setValue(auxC,actComp.panelName);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBVisible");
     if (actComp.visual.visible != DIS_HIDDEN) COMPONENT_setValue(auxC,"Y");
     else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBSelect");
     if (actComp.visual.visible==DIS_HIDDEN) 
	COMPONENT_display(auxC,DIS_NO_SELECT);
     else
        COMPONENT_display(auxC,DIS_NORMAL);
     if (actComp.visual.visible != DIS_HIDDEN && 
	 actComp.visual.visible != DIS_NO_SELECT) 
     {
        COMPONENT_setValue(auxC,"Y");
     }
     else {
        COMPONENT_setValue(auxC,NULL);
     }

     if (COMPONENT_setValue(auxC,actComp.mapkey) >= 0){
        auxC = (tComponent *)LVIEW_getElement("CoCB","CoTKeymap");
        COMPONENT_setValue(auxC,actComp.mapkey);
     }

     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBisCheck");
     if (actComp.visual.isCheck) COMPONENT_setValue(auxC,"Y");
        else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBchcheck");
     sprintf(auxdata,"%c",actComp.visual.chCheck);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBchischeck");
     sprintf(auxdata,"%c",actComp.visual.chIsCheck);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBchncheck");
     sprintf(auxdata,"%c",actComp.visual.chNoCheck);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBBorder");
     actComp.visual.dimension.border?COMPONENT_setValue(auxC,"1"):COMPONENT_setValue(auxC,NULL);

     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBX");
     sprintf(auxdata,"%d",actComp.visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBY");
     sprintf(auxdata,"%d",actComp.visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBWidth");
     sprintf(auxdata,"%d",actComp.visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBHigh");
     sprintf(auxdata,"%d",actComp.visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoCB","CoCBText");
     auxText=actComp.text;
   
     strcpy(auxdata,"");
     if (auxText != NULL) 
       {if (auxText->texto != NULL) strcpy(auxdata,auxText->texto);auxText = auxText->siguiente; }
     while (auxText != NULL){
        if (auxText->texto != NULL) {
         strcat(auxdata,"\n");
         strcat(auxdata,auxText->texto);
        }
        auxText = auxText->siguiente;
     }
     COMPONENT_setValue(auxC,auxdata);
   }
 }
 else{
   newComp =1;
   auxC = (tComponent *)LVIEW_getElement("CoCB","cpanel");
   COMPONENT_setValue(auxC,panel);
   strcpy(actComp.panelName,panel);
 }
}

void COMP_loadLsButton()
{
tComponent * auxC;
static char * ncomp;
static char * panel;
char * lcomp;
char * lpanel;
char auxdata[400];
tXmlcolorPtr auxColor;
tXmlTextPtr auxText;
tXmlComponentPtr auxComp;
tXmlMapKeyPtr auxKeymap;

 strcpy(auxdata,"");
 auxC = (tComponent *)LVIEW_getElement("CoLB","CoLKeymap");
 COMPONENT_clean(auxC); 
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBColor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 newComp =0;
 lcomp = TEXT_recv();
 lpanel = TEXT_recv();
 update=TEXT_recv()==NULL?0:1;
 if (lcomp != NULL) ncomp=lcomp;
 if (lpanel != NULL) panel=lpanel;

 memset(&actComp,'\0',sizeof(tXmlComponent));
 actComp.type=C_LSBUTTON;
 if (ncomp != NULL && strcmp(ncomp,"NEW") !=0){
   auxComp=COMP_searchComp(panel,ncomp);
   if (auxComp != NULL) 
   {
     memcpy(&actComp,auxComp,sizeof(tXmlComponent));
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBid");
     sprintf(auxdata,"%d",actComp.id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoLB","cname");
     COMPONENT_setValue(auxC,actComp.name);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBColor");
     COMPONENT_setValue(auxC,actComp.visual.color);
     if (COMPONENT_setValue(auxC,actComp.mapkey) >= 0){
        auxC = (tComponent *)LVIEW_getElement("CoLB","CoTKeymap");
        COMPONENT_setValue(auxC,actComp.mapkey);
     }
     auxC = (tComponent *)LVIEW_getElement("CoLB","cpanel");
     COMPONENT_setValue(auxC,actComp.panelName);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoDisplay");
     COMPONENT_setSelectValue(auxC,actComp.visual.visible,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBBorder");
     actComp.visual.dimension.border?COMPONENT_setValue(auxC,"1"):COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBX");
     sprintf(auxdata,"%d",actComp.visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBY");
     sprintf(auxdata,"%d",actComp.visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBWidth");
     sprintf(auxdata,"%d",actComp.visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBHigh");
     sprintf(auxdata,"%d",actComp.visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBText");
     COMPONENT_setValue(auxC,"");

     auxC = (tComponent *)LVIEW_getElement("CoLB","CoLBData");
     auxText = actComp.text; 
     strcpy(auxdata,"");
     if (auxText != NULL) 
     while (auxText != NULL){
        if (auxText->texto != NULL) {
         COMPONENT_addText(auxC,auxText->texto);
        }
        auxText = auxText->siguiente;
     }
   }
 }
 else{
   newComp =1;
   auxC = (tComponent *)LVIEW_getElement("CoLB","cpanel");
   COMPONENT_setValue(auxC,panel);
   strcpy(actComp.panelName,panel);
 }
}

void COMP_loadField()
{
tComponent * auxC;
static char * ncomp;
static char * panel;
char * lcomp;
char * lpanel;
char auxdata[400];
tXmlcolorPtr auxColor;
tXmlTextPtr auxText;
tXmlComponentPtr auxComp;
tXmlMapKeyPtr auxKeymap;
tXmlCEdFunctionPtr auxEDF;

 strcpy(auxdata,"");
 auxC = (tComponent *)LVIEW_getElement("CoED","CoLKeymap");
 COMPONENT_clean(auxC); 
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }


 auxC = (tComponent *)LVIEW_getElement("CoED","CoEDColor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("CoED","CoEDLEFunction");
 auxEDF=EDF_get();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"none");
 COMPONENT_addText(auxC,"7ascii");
 COMPONENT_addText(auxC,"numeric");
 COMPONENT_addText(auxC,"alpha");
 COMPONENT_addText(auxC,"alfnumeric");
 COMPONENT_addText(auxC,"upper");
 COMPONENT_addText(auxC,"lower");
 while (auxEDF !=NULL){
     COMPONENT_addText(auxC,auxEDF->name);
    auxEDF = auxEDF->siguiente;
 }

 newComp =0;
 lcomp = TEXT_recv();
 lpanel = TEXT_recv();
 update=TEXT_recv()==NULL?0:1;

 if (lcomp != NULL) ncomp=lcomp;
 if (lpanel != NULL) panel=lpanel;

 memset(&actComp,'\0',sizeof(tXmlComponent));
 actComp.type=C_EDIT;
 if (ncomp != NULL && strcmp(ncomp,"NEW") !=0){
   auxComp=COMP_searchComp(panel,ncomp);
   if (auxComp != NULL) 
   {
     memcpy(&actComp,auxComp,sizeof(tXmlComponent));
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDid");
     sprintf(auxdata,"%d",actComp.id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoED","cname");
     COMPONENT_setValue(auxC,actComp.name);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDColor");
     COMPONENT_setValue(auxC,actComp.visual.color);
     if (COMPONENT_setValue(auxC,actComp.mapkey) >= 0){
        auxC = (tComponent *)LVIEW_getElement("CoED","CoTKeymap");
        COMPONENT_setValue(auxC,actComp.mapkey);
     }
     auxC = (tComponent *)LVIEW_getElement("CoED","cpanel");
     COMPONENT_setValue(auxC,actComp.panelName);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDVisible");
     if (actComp.visual.visible != DIS_HIDDEN) COMPONENT_setValue(auxC,"Y");
     else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDSelect");
     if (actComp.visual.visible==DIS_HIDDEN) 
	COMPONENT_display(auxC,DIS_NO_SELECT);
     else
        COMPONENT_display(auxC,DIS_NORMAL);
     if (actComp.visual.visible != DIS_HIDDEN &&
         actComp.visual.visible != DIS_NO_SELECT) {
        COMPONENT_setValue(auxC,"Y");
        COMPONENT_display(auxC,DIS_NORMAL);
     }
     else {
	COMPONENT_setValue(auxC,NULL);
        COMPONENT_display(auxC,DIS_NO_SELECT);
     }
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDAuto");
     if (actComp.editMode.autoComplet) COMPONENT_setValue(auxC,"Y");
        else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDSecret");
     if (actComp.editMode.secret) COMPONENT_setValue(auxC,"Y");
        else COMPONENT_setValue(auxC,NULL);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDmode");
     sprintf(auxdata,"%c",actComp.editMode.chToEDIT);
     COMPONENT_setValue(auxC,auxdata);
     
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDBorder");
     actComp.visual.dimension.border?COMPONENT_setValue(auxC,"1"):COMPONENT_setValue(auxC,NULL);

     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDX");
     sprintf(auxdata,"%d",actComp.visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDY");
     sprintf(auxdata,"%d",actComp.visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDWidth");
     sprintf(auxdata,"%d",actComp.visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDHigh");
     sprintf(auxdata,"%d",actComp.visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("CoED","CoEDText");
     auxText=actComp.text;
   
     strcpy(auxdata,"");
     if (auxText != NULL) 
        {if (auxText->texto != NULL) strcpy(auxdata,auxText->texto);auxText = auxText->siguiente; }
     while (auxText != NULL){
       if (auxText->texto != NULL){
        strcat(auxdata,"\n");
        strcat(auxdata,auxText->texto);
       }
       auxText = auxText->siguiente;
     }
     COMPONENT_setValue(auxC,auxdata);
   }
 }
 else{
   newComp =1;
   auxC = (tComponent *)LVIEW_getElement("CoED","cpanel");
   COMPONENT_setValue(auxC,panel);
   strcpy(actComp.panelName,panel);
 }
}

void COMP_loadCopy()
{
tComponent * auxC;
char * data;

 data = TEXT_recv();
 auxC = (tComponent *)LVIEW_getElement("frmCCopy","fromComponent");
 COMPONENT_setValue(auxC,data);
}


trAction* COMP_callSelect (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send(frmToLaunch,1);
 TEXT_send(selectToLaunch,0);

return &action;
}

trAction * COMP_addTableColumn (tComponent * component,int key){
 static trAction action;
 tComponent * auxC;
 int len;
 char * value;
 char auxText[50];

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tlcolumn");
 value=COMPONENT_getValue(auxC);
 if (value==NULL || strcmp(value,"")==0)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Wrong column Length");
  action.error=1;
  return &action;
 }
 len=atoi(value);
 
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"tcolumn");
 value=COMPONENT_getValue(auxC);
 if (value==NULL || strcmp(value,"")==0)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Wrong column name");
  action.error=1;
  return &action;
 }
 sprintf(auxText,"%3.3d-%-s",len,value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"tElemens");
 COMPONENT_addText(auxC,auxText);
 COMPONENT_refresh(auxC);

 return &action;
}

trAction * COMP_selTableColumn (tComponent * component,int key){
 static trAction action;
 tComponent * auxC;
 char len[5];
 char elem[21];
 char * value;

 initAction(action);

 value=COMPONENT_getValue(component);
 strncpy(len,value,3);
 strcpy(elem,value+4);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"tlcolumn");
 COMPONENT_setValue(auxC,len);
 COMPONENT_refresh(auxC);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tcolumn");
 COMPONENT_setValue(auxC,elem);
 COMPONENT_refresh(auxC);

 return &action;
}

trAction * COMP_delTableColumn (tComponent * component,int key){
 static trAction action;
 tComponent * auxC;
 int len;
 char * value;
 char auxText[50];

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tlcolumn");
 value=COMPONENT_getValue(auxC);
 if (value==NULL || strcmp(value,"")==0)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Wrong column Length");
  action.error=1;
  return &action;
 }
 len=atoi(value);
 
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"tcolumn");
 value=COMPONENT_getValue(auxC);
 if (value==NULL || strcmp(value,"")==0)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Wrong column name");
  action.error=1;
  return &action;
 }

 sprintf(auxText,"%3.3d-%-s",len,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tElemens");
 COMPONENT_delText(auxC,auxText);
 COMPONENT_refresh(auxC);

 return &action;
}

void COMP_preEnterPanel(tComponent *  component){
  char * aux;
  
  aux = TEXT_recv();
  if (aux!=NULL)
   COMPONENT_setText(component,aux);
return;
}

unsigned short int COMP_searchUseEdf(char * edf)
{
 tXmlComponentPtr aux;
 aux = cabComps;
 while (aux != NULL) {
   if (strcmp(aux->editMode.editFunction,edf)==0) return 1;
   aux = aux->siguiente;
 }
 return 0;
}

unsigned short int COMP_searchUseKeymap(char * keymap)
{
 tXmlComponentPtr aux;
 aux = cabComps;
 while (aux != NULL) {
   if (strcmp(aux->mapkey,keymap)==0) return 1;
   aux = aux->siguiente;
 }
 return 0;
}

unsigned short int COMP_searchUseColor(char * color)
{
 tXmlComponentPtr aux;
 aux = cabComps;
 while (aux != NULL) {
   if (strcmp(aux->visual.color,color)==0) return 1;
   aux = aux->siguiente;
 }
 return 0;
}

trAction* COMP_selectKEYM (tComponent * component,int key){
static trAction action;

  initAction(action);
  if (KEYM_get() == NULL){
       MSG_create(M_INFO,CENTER_VIEW,"No Keymaps available");
       action.error=1;
  }
  return &action;
}

trAction* COMP_Visible (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * value;

 initAction(action);

 value = COMPONENT_getValue(component); 

 if (strcmp(component->name,"CoBVisible")==0){
    auxC = (tComponent *)LVIEW_getElement(NULL,"CoBSelect");
 }
 if (strcmp(component->name,"CoCBVisible")==0){
    auxC = (tComponent *)LVIEW_getElement(NULL,"CoCBSelect");
 }
 if (strcmp(component->name,"CoEDVisible")==0){
    auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDSelect");
 }

 if (value != NULL) {
   COMPONENT_setValue(auxC,NULL);
   COMPONENT_display(auxC,DIS_NO_SELECT);
   COMPONENT_refresh(auxC);
 }else 
   COMPONENT_display(auxC,DIS_NORMAL);

return &action;
}


void COMP_deselectKEYM(tComponent * component){
tComponent * auxC;

  auxC = (tComponent *)LVIEW_getElement(NULL,"CoTKeymap");
  COMPONENT_setValue(auxC,COMPONENT_getValue(component));
  COMPONENT_refresh(auxC);
}

void COMP_deselectEdFunc(tComponent * component){
tComponent * auxC;

  auxC = (tComponent *)LVIEW_getElement(NULL,"CoEDTEFunction");
  COMPONENT_setValue(auxC,COMPONENT_getValue(component));
  COMPONENT_refresh(auxC);
}

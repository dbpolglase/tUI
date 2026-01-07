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
#include <tkeymap.h>
#include <tproyect.h>
#include <tcolor.h>
#include <tcomp.h>
#include <tview.h>

static tXmlPanelPtr cabPanels;
static tXmlPanelPtr ultPanels;
static tXmlPanelPtr actPanel=NULL;

static tXmlTablePtr cabTables;
static tXmlTablePtr ultTables;
static tXmlTablePtr actTable=NULL;

static tXmlEditPtr cabEdits;
static tXmlEditPtr ultEdits;
static tXmlEditPtr actEdit=NULL;

extern SCREEN * scrSTD;
static tXmlPanel auxEditPanel;
static tXmlTable auxEditTable;
static tXmlEdit  auxEditEdit;

enum CViews actEditView;

static void VIEW_addPanel(tXmlPanelPtr newP);
static void VIEW_addTable(tXmlTablePtr newP);
static void VIEW_addEdit(tXmlEditPtr newE);
static int VIEW_delPanel(char * name);
static int VIEW_delTable(char * name);
static int VIEW_delEdit(char * name);
tXmlPanelPtr VIEW_searchPanel(char * name);
tXmlTablePtr VIEW_searchTable(char * name);
tXmlEditPtr VIEW_searchEdit(char * name);
static void VIEW_addTableElemens(tXmlTablePtr auxTable);
static void VIEW_copyComponents(tXmlPanelPtr newPanel,tXmlPanelPtr oldPanel,
          unsigned short cMove,unsigned short caMove,unsigned short caCall);
static void VIEW_deleteComponents(tXmlPanelPtr panel);

void PANEL_set(tXmlPanelPtr cab, tXmlPanelPtr ult){
  cabPanels = cab;
  ultPanels = ult;
}

void PANEL_addComp(char * panel, tXmlComponentPtr comp){
 tXmlPanelPtr aux=cabPanels;
 tXmlCompPanel * elComp;

  elComp=(tXmlCompPanel *) malloc (sizeof(tXmlCompPanel));
  elComp->componente=comp;
  elComp->siguiente =NULL;
  while (aux != NULL){
   if (strcmp(aux->name,comp->panelName)==0){
     elComp->siguiente = aux->elements;
     aux->elements=elComp;
     return;
   } 
   aux = aux->siguiente;
  }
}

void PANEL_delComp(tXmlPanelPtr panel,tXmlComponentPtr comp)
{
 tXmlCompPanel * elComp;

  elComp=panel->elements;
  
  if (elComp->componente == comp){
    panel->elements = elComp->siguiente;
    return;
  }

  while (elComp->siguiente != NULL){
   if (elComp->siguiente->componente == comp){
     elComp->siguiente = elComp->siguiente->siguiente;
     return;
   } 
   elComp = elComp->siguiente;
  }
}

void TABLE_set(tXmlTablePtr cab, tXmlTablePtr ult){
  cabTables = cab;
  ultTables = ult;
}

void EDIT_set(tXmlEditPtr cab, tXmlEditPtr ult){
  cabEdits = cab;
  ultEdits = ult;
}


void PANEL_reset()
{
  tXmlPanelPtr aux;

  aux = cabPanels;
  while (aux != NULL) {
   cabPanels = cabPanels->siguiente;
   free(aux);
   aux = cabPanels;
 }
 cabPanels = ultPanels = NULL;
}

void TABLE_reset()
{
  tXmlTablePtr aux;

  aux = cabTables;
  while (aux != NULL) {
   cabTables = cabTables->siguiente;
   free(aux);
   aux = cabTables;
 }
 cabTables = ultTables = NULL;
}

void EDIT_reset()
{
  tXmlEditPtr aux;

  aux = cabEdits;
  while (aux != NULL) {
   cabEdits = cabEdits->siguiente;
   free(aux);
   aux = cabEdits;
 }
 cabEdits = ultEdits = NULL;
}

tXmlPanelPtr PANEL_get()
{
  return cabPanels;
}
 
tXmlTablePtr TABLE_get()
{
  return cabTables;
}
 
tXmlEditPtr EDIT_get()
{
  return cabEdits;
}
 
void PANEL_load () {
tXmlPanelPtr aux;
tComponent * auxC;
char * data;
char auxdata[20];
tXmlcolorPtr auxColor;
tXmlMapKeyPtr auxKeymap;

 actPanel=NULL;
 data = TEXT_recv();

 actEditView=V_Panel;

 auxC = (tComponent *)LVIEW_getElement("fnpanel","pcolor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }
 auxC = (tComponent *)LVIEW_getElement("fnpanel","pkeymap");
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"NONE");
 auxKeymap = KEYMAP_get();
 while (auxKeymap !=NULL){
    COMPONENT_addText(auxC,auxKeymap->name);
    auxKeymap = auxKeymap->siguiente;
 }


 memset(&auxEditPanel,'\0',sizeof(auxEditPanel));

 if (data != NULL && (strcmp(data,"NEW") != 0)){
   aux = cabPanels;
   while (aux!=NULL && (strcmp(aux->name,data)!=0)) aux = aux->siguiente;
   if (aux == NULL) {
        MSG_create(M_INFO,CENTER_VIEW,"PANEL <%s> not found",data);
   }
   else
   {
     actPanel=aux;
     memcpy(&auxEditPanel,aux,sizeof(auxEditPanel));
     
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pid");
     sprintf(auxdata,"%d",aux->id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","fnpnombre");
     COMPONENT_setValue(auxC,aux->name);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","plevel");
     sprintf(auxdata,"%d",aux->level);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","ptitle");
     COMPONENT_setValue(auxC,aux->title);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pop");
     COMPONENT_setSelectValue(auxC,aux->opToMade,NULL);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pcolor");
     COMPONENT_setSelectValue(auxC,-1,aux->visual.color);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","fnpborder");
     if (aux->visual.dimension.border) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pX");
     sprintf(auxdata,"%d",aux->visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pY");
     sprintf(auxdata,"%d",aux->visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pWidth");
     sprintf(auxdata,"%d",aux->visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnpanel","pHigh");
     sprintf(auxdata,"%d",aux->visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
   }
 }
 else{
;
 }
}

void TABLE_load () {
tXmlTablePtr aux;
tComponent * auxC,*auxC2;
char * data;
char auxdata[200];
tXmlcolorPtr auxColor;
tXmlMapKeyPtr auxKeymap;
tXmlElemsTable * auxElems;

 actTable=NULL;
 data = TEXT_recv();
 actEditView=V_Table;

 auxC = (tComponent *)LVIEW_getElement("fntable","thcolor");
 auxC2 = (tComponent *)LVIEW_getElement("fntable","tdcolor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_clean(auxC2);
 COMPONENT_addText(auxC,"noColor");
 COMPONENT_addText(auxC2,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
     COMPONENT_addText(auxC2,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("fntable","CoLKeymap");
 COMPONENT_clean(auxC);
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }

 memset(&auxEditTable,'\0',sizeof(auxEditTable));

 if (data != NULL && (strcmp(data,"NEW") != 0)){
   aux = cabTables;
   while (aux!=NULL && (strcmp(aux->name,data)!=0)) aux = aux->siguiente;
   if (aux == NULL) {
        MSG_create(M_INFO,CENTER_VIEW,"TABLE <%s> not found",data);
   }
   else
   {
     actTable=aux;
     memcpy(&auxEditTable,aux,sizeof(auxEditTable));
     
     auxC = (tComponent *)LVIEW_getElement("fntable","tpid");
     sprintf(auxdata,"%d",aux->id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","fntnombre");
     COMPONENT_setValue(auxC,aux->name);
     auxC = (tComponent *)LVIEW_getElement("fntable","tlevel");
     sprintf(auxdata,"%d",aux->level);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","ttitle");
     COMPONENT_setValue(auxC,aux->title);
     auxC = (tComponent *)LVIEW_getElement("fntable","top");
     COMPONENT_setSelectValue(auxC,aux->opToMade,NULL);
     auxC = (tComponent *)LVIEW_getElement("fntable","thcolor");
     COMPONENT_setSelectValue(auxC,-1,aux->visual.color);
     auxC = (tComponent *)LVIEW_getElement("fntable","tdcolor");
     COMPONENT_setSelectValue(auxC,-1,aux->visual.colorData);
     auxC = (tComponent *)LVIEW_getElement("fntable","CoTKeymap");
     if (strcmp(aux->mapkey,""))
     COMPONENT_setValue(auxC,aux->mapkey);
     auxC = (tComponent *)LVIEW_getElement("fntable","head");
     if (aux->visual.thead) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fntable","vline");
     if (aux->visual.vline) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fntable","hline");
     if (aux->visual.hline) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fntable","tborder");
     if (aux->visual.dimension.border) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fntable","tX");
     sprintf(auxdata,"%d",aux->visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","tY");
     sprintf(auxdata,"%d",aux->visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","tWidth");
     sprintf(auxdata,"%d",aux->visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","tHigh");
     sprintf(auxdata,"%d",aux->visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fntable","tElemens");
     COMPONENT_clean(auxC);
     auxElems= actTable->elements;
     while (auxElems !=NULL){
       sprintf(auxdata,"%3.3d-%-20s",auxElems->len,auxElems->title);
       COMPONENT_addText(auxC,auxdata);
       auxElems = auxElems->siguiente;
     }
   }
 }
 else{
;
 }
}

void EDIT_load () {
tXmlEditPtr aux;
tComponent * auxC;
char * data;
char auxdata[200];
tXmlcolorPtr auxColor;
tXmlMapKeyPtr auxKeymap;

 actEdit=NULL;
 data = TEXT_recv();
 actEditView=V_Edit;

 auxC = (tComponent *)LVIEW_getElement("fnedit","ecolor");
 auxColor = COLOR_getXml();
 COMPONENT_clean(auxC);
 COMPONENT_addText(auxC,"noColor");
 while (auxColor !=NULL){
     COMPONENT_addText(auxC,auxColor->name);
    auxColor = auxColor->siguiente;
 }

 auxC = (tComponent *)LVIEW_getElement("fnedit","CoLKeymap");
 COMPONENT_clean(auxC);
 auxKeymap = KEYM_get();
 COMPONENT_addText(auxC,"Default");
 while (auxKeymap != NULL){
     COMPONENT_addText(auxC,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
 }

 memset(&auxEditEdit,'\0',sizeof(auxEditEdit));

 if (data != NULL && (strcmp(data,"NEW") != 0)){
   aux = cabEdits;
   while (aux!=NULL && (strcmp(aux->name,data)!=0)) aux = aux->siguiente;
   if (aux == NULL) {
        MSG_create(M_INFO,CENTER_VIEW,"TABLE <%s> not found",data);
   }
   else
   {
     actEdit=aux;
     memcpy(&auxEditEdit,aux,sizeof(auxEditEdit));
     
     auxC = (tComponent *)LVIEW_getElement("fnedit","epid");
     sprintf(auxdata,"%d",aux->id);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","fnenombre");
     COMPONENT_setValue(auxC,aux->name);
     auxC = (tComponent *)LVIEW_getElement("fnedit","elevel");
     sprintf(auxdata,"%d",aux->level);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","etitle");
     COMPONENT_setValue(auxC,aux->title);
     auxC = (tComponent *)LVIEW_getElement("fnedit","eop");
     COMPONENT_setSelectValue(auxC,aux->opToMade,NULL);
     auxC = (tComponent *)LVIEW_getElement("fnedit","ecolor");
     COMPONENT_setSelectValue(auxC,-1,aux->visual.color);
     auxC = (tComponent *)LVIEW_getElement("fnedit","CoTKeymap");
     if (strcmp(aux->mapkey,""))
     COMPONENT_setValue(auxC,aux->mapkey);
     auxC = (tComponent *)LVIEW_getElement("fnedit","fneborder");
     if (aux->visual.dimension.border) COMPONENT_setValue(auxC,"1");
     auxC = (tComponent *)LVIEW_getElement("fnedit","eX");
     sprintf(auxdata,"%d",aux->visual.dimension.x);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","eY");
     sprintf(auxdata,"%d",aux->visual.dimension.y);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","eWidth");
     sprintf(auxdata,"%d",aux->visual.dimension.ancho);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","eHigh");
     sprintf(auxdata,"%d",aux->visual.dimension.alto);
     COMPONENT_setValue(auxC,auxdata);
     auxC = (tComponent *)LVIEW_getElement("fnedit","efile");
     COMPONENT_setValue(auxC,aux->fileName);
     auxC = (tComponent *)LVIEW_getElement("fnedit","eread");
     if (aux->visual.eMode==R_ONLY) COMPONENT_setValue(auxC,"1");
     else COMPONENT_setValue(auxC,NULL);
   }
 }
 else{
;
 }
}

void VIEW_copyLoad () {
tComponent * auxC;
char * data;

 actTable=NULL;
 data = TEXT_recv();

 auxC = (tComponent *)LVIEW_getElement("frmVCopy","fromView");
 COMPONENT_setValue(auxC,data);
}

trAction* VIEW_copyDoIt (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char * from;
char * to;
unsigned short cComp=0,cMove=0,caMove=0,caCall=0;
tXmlPanelPtr auxPanel=NULL,newPanel;
tXmlTablePtr auxTable=NULL,newTable;
tXmlEditPtr auxEdit=NULL,newEdit;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"fromView");
 from = COMPONENT_getValue(auxC);
 auxC = (tComponent *)LVIEW_getElement(NULL,"toView");
 to = COMPONENT_getValue(auxC);
 auxC = (tComponent *)LVIEW_getElement(NULL,"component");
 cComp=COMPONENT_getValue(auxC)==NULL?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"moves");
 cMove=COMPONENT_getValue(auxC)==NULL?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"appMoves");
 caMove=COMPONENT_getValue(auxC)==NULL?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"appCalls");
 caCall=COMPONENT_getValue(auxC)==NULL?0:1;

 auxPanel = VIEW_searchPanel(from);
 if (auxPanel == NULL) {auxTable = VIEW_searchTable(from);
    if (auxTable == NULL) auxEdit = VIEW_searchEdit(from); }

 if (auxPanel == NULL && auxTable == NULL  && auxEdit ==NULL)
 {
   MSG_create(M_ERROR,CENTER_VIEW,"From View don't exists ");
   action.error=1;
   return &action;
 }

 if (VIEW_searchPanel(to)!= NULL ||
     VIEW_searchTable(to)!= NULL ||
     VIEW_searchEdit(to)!= NULL )
 {
   MSG_create(M_ERROR,CENTER_VIEW,"Destination View already exists ");
   action.error=1;
   return &action;
 }
 
 if (auxPanel != NULL) {
    newPanel = (tXmlPanelPtr) malloc(sizeof(tXmlPanel));
    memcpy(newPanel,auxPanel,sizeof(tXmlPanel));
    strcpy(newPanel->name,to);
    if (!cMove) memset(&newPanel->move,'\0',sizeof(tXmlMove));
    if (!caMove) memset(&newPanel->personalAction,'\0',sizeof(tXmlMove));
    if (!caCall) memset(&newPanel->personalFPanel,'\0',sizeof(tXmlFApplication));

    if (cComp) VIEW_copyComponents(newPanel,auxPanel,cMove,caMove,caCall);
    else newPanel->elements=NULL;

    newPanel->siguiente=newPanel->anterior=NULL;
    VIEW_addPanel(newPanel);
 }
 if (auxTable != NULL) {
    newTable = (tXmlTablePtr) malloc(sizeof(tXmlTable));
    memcpy(newTable,auxTable,sizeof(tXmlTable));
    strcpy(newTable->name,to);
    if (!cMove) memset(&newTable->move,'\0',sizeof(tXmlMove));
    if (!caMove) memset(&newTable->personalAction,'\0',sizeof(tXmlMove));
    if (!caCall) memset(&newTable->personalFTable,'\0',sizeof(tXmlFApplication));
    newTable->elements=NULL;
    newTable->siguiente=newTable->anterior=NULL;
    VIEW_addTable(newTable);
 }

 if (auxEdit != NULL) {
    newEdit = (tXmlEditPtr) malloc(sizeof(tXmlEdit));
    memcpy(newEdit,auxEdit,sizeof(tXmlEdit));
    strcpy(newEdit->name,to);
    if (!cMove) memset(&newEdit->move,'\0',sizeof(tXmlMove));
    if (!caMove) memset(&newEdit->personalAction,'\0',sizeof(tXmlMove));
    if (!caCall) memset(&newEdit->personalFEdit,'\0',sizeof(tXmlFApplication));
    newEdit->siguiente=newEdit->anterior=NULL;
    VIEW_addEdit(newEdit);
 }

 return &action;
}

static void VIEW_deleteComponents(tXmlPanelPtr panel)
{
  tXmlCompPanel * aux,*aux2;
  aux = aux2 = panel->elements;
  panel->elements = NULL;
  while (aux != NULL)
  {
    aux2=aux;
    aux=aux->siguiente;
    COMP_delComp(aux2->componente);
    free(aux2);
  }
}

static void VIEW_copyComponents(tXmlPanelPtr newPanel,tXmlPanelPtr oldPanel,
          unsigned short cMove,unsigned short caMove,unsigned short caCall)
{
 tXmlCompPanel * aux;
 tXmlCompPanel * newCP, * enlaceCP;
 tXmlComponent * auxC;

  
 aux=oldPanel->elements;
 enlaceCP = NULL;

 while (aux!=NULL) {
   newCP = (tXmlCompPanel *) malloc(sizeof(tXmlCompPanel));
   auxC = (tXmlComponent *) malloc(sizeof(tXmlComponent));
   memcpy(auxC,aux->componente,sizeof(tXmlComponent));
   if (!cMove) memset(&auxC->move,'\0',sizeof(tXmlMove));
   if (!caMove) memset(&auxC->personalAction,'\0',sizeof(tXmlMove));
   if (!caCall) memset(&auxC->personalFComponent,'\0',sizeof(tXmlFApplication));
   strcpy(auxC->panelName,oldPanel->name);
   newCP->componente=auxC;
   newCP->siguiente=NULL;
   if (enlaceCP== NULL){ newPanel->elements=newCP; enlaceCP=newCP;}
   else {enlaceCP->siguiente = newCP; enlaceCP=newCP;}
   COMP_addComp(auxC);
   aux = aux->siguiente;
 }
}

tXmlPanelPtr VIEW_searchPanel(char * name)
{
 int npanel=0;
 char * end;
 tXmlPanelPtr aux;
 aux = cabPanels;

 npanel = (int)strtol(name,&end,10);
 if (end-name != strlen(name)) npanel=0;

 while (aux != NULL) {
   if (npanel==0&&strcmp(aux->name,name)==0) return aux;
   if (npanel!=0&&npanel==aux->id) return aux;
   aux = aux->siguiente;
 }
 return NULL;
}

tXmlTablePtr VIEW_searchTable(char * name)
{
 int ntable=0;
 tXmlTablePtr aux;
 char * end;

 aux = cabTables;
 ntable = (int)strtol(name,&end,10);
 if (end-name != strlen(name)) ntable=0;

 while (aux != NULL) {
   if (ntable==0&&strcmp(aux->name,name)==0) return aux;
   if (ntable!=0&&ntable==aux->id) return aux;
   aux = aux->siguiente;
 }
 return NULL;
}

tXmlEditPtr VIEW_searchEdit(char * name)
{
 int nedit=0;
 tXmlEditPtr aux;
 char * end;

 aux = cabEdits;
 nedit = (int)strtol(name,&end,10);
 if (end-name != strlen(name)) nedit=0;

 while (aux != NULL) {
   if (nedit==0&&strcmp(aux->name,name)==0) return aux;
   if (nedit!=0&&nedit==aux->id) return aux;
   aux = aux->siguiente;
 }
 return NULL;
}

trAction* VIEW_panelChange (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send("fnpanel:pid",1);
 TEXT_send("PANEL",0);
 TEXT_send("mnPrincipal:mnPviews",0);

 return &action;
}

trAction* VIEW_panelComps (tComponent * component,int key){
static trAction action;
char * value;
tComponent * auxC;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"fnpnombre");
 value = COMPONENT_getValue(auxC);
 if(VIEW_searchPanel(value) == NULL){
   action.error=1;
   MSG_create(M_ERROR,CENTER_VIEW,"Save panel View before ");
 }

 TEXT_send(value,1);
 TEXT_send("PANEL_COMPS",0);
 TEXT_send("-:",0);

 return &action;
}

trAction* VIEW_tableChange (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send("fntable:tpid",1);
 TEXT_send("TABLE",0);
 TEXT_send("mnPrincipal:mnPviews",0);

 return &action;
}

trAction* VIEW_editChange (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send("fnedit:epid",1);
 TEXT_send("EDIT",0);
 TEXT_send("mnPrincipal:mnPviews",0);

 return &action;
}

trAction* VIEW_copyChange (tComponent * component,int key){
static trAction action;
 initAction(action);

 TEXT_send("frmVCopy:toView",1);
 TEXT_send("ALL_VIEW",0);
 TEXT_send("mnPrincipal:mnPviews",0);

 return &action;
}

trAction* VIEW_panelDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);

 tTablePtr auxT;
 tXmlPanelPtr auxPanel;

 char * value;
 tComponent * auxC;
 auxC = (tComponent *)LVIEW_getElement(NULL,"pid");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditPanel.id=atoi(value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"fnpnombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Panel must have a name");
    action.error=1;
    return &action;
 }
 strcpy(auxEditPanel.name,value);   

 auxC = (tComponent *)LVIEW_getElement(NULL,"plevel");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) auxEditPanel.level=0;
 else auxEditPanel.level = atoi(value);
  

 auxC = (tComponent *)LVIEW_getElement(NULL,"ptitle");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditPanel.title,value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"pcolor");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditPanel.visual.color,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"pop");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditPanel.opToMade=PARSER_decodeOp(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"fnpborder");
 value = COMPONENT_getValue(auxC);
 auxEditPanel.visual.dimension.border = (value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"pX");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditPanel.visual.dimension.x = atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"pY");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditPanel.visual.dimension.y = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"pWidth");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
    action.error=1;
    return &action;
 }
 auxEditPanel.visual.dimension.ancho = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"pHigh");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
    action.error=1;
    return &action;
 }
 auxEditPanel.visual.dimension.alto = atoi(value);

 auxPanel = VIEW_searchPanel(auxEditPanel.name);

 if (auxPanel == NULL) {
   VIEW_addPanel(&auxEditPanel);
   auxT = (tTable *)LVIEW_getElement("telement",NULL);
   TEXT_addData(auxT->text, auxEditPanel.name);
   LVIEW_refresh("telement");
   TEXT_send(auxEditPanel.name,1);
 }
 else {
  auxEditPanel.siguiente = auxPanel->siguiente;
  auxEditPanel.anterior = auxPanel->anterior;
  memcpy(auxPanel,&auxEditPanel,sizeof(auxEditPanel));
 }

 MSG_create(M_INFO,CENTER_VIEW,"Operation Done!!");
 return &action;
}

trAction* VIEW_tableDoIt (tComponent * component,int key){
static trAction action;

 tTablePtr auxT;
 tXmlTablePtr auxTable;
 char * value;
 tComponent * auxC;
 tXmlElemsTable * auxElems;

 initAction(action);
 auxC = (tComponent *)LVIEW_getElement(NULL,"tpid");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditTable.id=atoi(value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"fntnombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Table must have a name");
    action.error=1;
    return &action;
 }
 strcpy(auxEditTable.name,value);   

 auxC = (tComponent *)LVIEW_getElement(NULL,"tlevel");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) auxEditTable.level=0;
 else auxEditTable.level = atoi(value);
  

 auxC = (tComponent *)LVIEW_getElement(NULL,"ttitle");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditTable.title,value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"thcolor");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditTable.visual.color,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tdcolor");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditTable.visual.colorData,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"top");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditTable.opToMade=PARSER_decodeOp(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLKeymap");
 value = COMPONENT_getValue(auxC);
 if (value != NULL && strcmp(value,"") && strcmp(value,"Default"))
 strcpy(auxEditTable.mapkey,value);
 else
 strcpy(auxEditTable.mapkey,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"head");
 value = COMPONENT_getValue(auxC);
 auxEditTable.visual.thead = (value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"vline");
 value = COMPONENT_getValue(auxC);
 auxEditTable.visual.vline = (value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"hline");
 value = COMPONENT_getValue(auxC);
 auxEditTable.visual.hline = (value==NULL)?0:1;


 auxC = (tComponent *)LVIEW_getElement(NULL,"tborder");
 value = COMPONENT_getValue(auxC);
 auxEditTable.visual.dimension.border = (value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"tX");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditTable.visual.dimension.x = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tY");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditTable.visual.dimension.y = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tWidth");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
    action.error=1;
    return &action;
 }
 auxEditTable.visual.dimension.ancho = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"tHigh");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
    action.error=1;
    return &action;
 }
 auxEditTable.visual.dimension.alto = atoi(value);

 auxTable = VIEW_searchTable(auxEditTable.name);


 if (auxTable == NULL) {
   VIEW_addTableElemens(&auxEditTable);
   VIEW_addTable(&auxEditTable);
   auxEditTable.elements=NULL;
   auxT = (tTable *)LVIEW_getElement("telement",NULL);
   TEXT_addData(auxT->text, auxEditTable.name);
   TABLE_refresh(auxT);
   TEXT_send(auxEditTable.name,1);
 }
 else {
   VIEW_addTableElemens(auxTable);
   auxElems=auxTable->elements;
   auxEditTable.siguiente = auxTable->siguiente;
   auxEditTable.anterior = auxTable->anterior;
   memcpy(auxTable,&auxEditTable,sizeof(auxEditTable));
   auxTable->elements=auxElems;
 }

 MSG_create(M_INFO,CENTER_VIEW,"Operation Done!!");

 return &action;
}

static void VIEW_addTableElemens(tXmlTablePtr auxTable)
{
 tXmlElemsTable * auxElems,*aux2Elems;
 tComponent * auxC;
 int i,nLines=0;
 char len[5];
 char elem[MAX_VIEW_TITLE];
 int nElems=0;

 auxC = (tComponent *)LVIEW_getElement(NULL,"tElemens");

 nLines = (auxC->text!=NULL)?auxC->text->nroLines:0;
 auxElems=auxTable->elements;
 
 aux2Elems = auxElems = auxTable->elements;
 nElems = nLines;

 if (nLines == 0){
  while(aux2Elems !=NULL){
    auxElems=aux2Elems->siguiente;
    free(aux2Elems);
    aux2Elems=auxElems;
  } 
  auxTable->elements=NULL;
 }
 else {
  for (nElems =0;aux2Elems != NULL && nElems!=nLines;nElems++) {
    auxElems = aux2Elems;
    aux2Elems = aux2Elems->siguiente;
  }
  if (aux2Elems==NULL){
    for (;nElems!=nLines;nElems++){
      aux2Elems = (tXmlElemsTable *) malloc(sizeof(tXmlElemsTable));
      aux2Elems->siguiente=NULL;
      if (auxElems==NULL) 
         { auxTable->elements=aux2Elems; }
      else auxElems->siguiente=aux2Elems;
      auxElems=aux2Elems;
    }
  }
  else {
     auxElems->siguiente =NULL;
     auxElems = aux2Elems;
     while(aux2Elems !=NULL) {
        aux2Elems=aux2Elems->siguiente;
        free(auxElems);
        auxElems=aux2Elems;
     }
   }
 }

 auxElems = auxTable->elements;
 for (i=0;i!=nLines;i++){
   strncpy(len,auxC->text->text[i][0],3);
   strcpy(elem,auxC->text->text[i][0]+4);
   strcpy(auxElems->title,elem);
   auxElems->len=atoi(len);
   auxElems=auxElems->siguiente;
 }
}

trAction* VIEW_editDoIt (tComponent * component,int key){
 static trAction action;
 tComponent * auxC;
 tTablePtr auxT;
 char * value;
 tXmlEditPtr auxEdit;

 initAction(action);

 auxC = (tComponent *)LVIEW_getElement(NULL,"epid");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditEdit.id=atoi(value);
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"fnenombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Edit must have a name");
    action.error=1;
    return &action;
 }
 strcpy(auxEditEdit.name,value);   

 auxC = (tComponent *)LVIEW_getElement(NULL,"elevel");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) auxEditEdit.level=0;
 else auxEditEdit.level = atoi(value);
  

 auxC = (tComponent *)LVIEW_getElement(NULL,"etitle");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditEdit.title,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"efile");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditEdit.fileName,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"eread");
 value = COMPONENT_getValue(auxC);
 if (value==NULL) auxEditEdit.visual.eMode=RW; 
		else auxEditEdit.visual.eMode=R_ONLY;
 
 auxC = (tComponent *)LVIEW_getElement(NULL,"ecolor");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) strcpy(auxEditEdit.visual.color,value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"eop");
 value = COMPONENT_getValue(auxC);
 if (value != NULL) auxEditEdit.opToMade=PARSER_decodeOp(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"CoLKeymap");
 value = COMPONENT_getValue(auxC);
 if (value != NULL && strcmp(value,"") && strcmp(value,"Default"))
 strcpy(auxEditEdit.mapkey,value);
 else
 strcpy(auxEditEdit.mapkey,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"fneborder");
 value = COMPONENT_getValue(auxC);
 auxEditEdit.visual.dimension.border = (value==NULL)?0:1;
 auxC = (tComponent *)LVIEW_getElement(NULL,"eX");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"X point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditEdit.visual.dimension.x = atoi(value);
 auxC = (tComponent *)LVIEW_getElement(NULL,"eY");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Y point not fixed ");
    action.error=1;
    return &action;
 }
 auxEditEdit.visual.dimension.y = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"eWidth");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"Width not fixed ");
    action.error=1;
    return &action;
 }
 auxEditEdit.visual.dimension.ancho = atoi(value);

 auxC = (tComponent *)LVIEW_getElement(NULL,"eHigh");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    MSG_create(M_ERROR,CENTER_VIEW,"High not fixed ");
    action.error=1;
    return &action;
 }
 auxEditEdit.visual.dimension.alto = atoi(value);

 auxEdit= VIEW_searchEdit(auxEditEdit.name);

 if (auxEdit == NULL) {
   VIEW_addEdit(&auxEditEdit);
   auxT = (tTable *)LVIEW_getElement("telement",NULL);
   TEXT_addData(auxT->text, auxEditEdit.name);
   TABLE_refresh(auxT);
   TEXT_send(auxEditEdit.name,1);
 }
 else {
  auxEditEdit.siguiente = auxEdit->siguiente;
  auxEditEdit.anterior = auxEdit->anterior;
  memcpy(auxEdit,&auxEditEdit,sizeof(auxEditEdit));
 }

 MSG_create(M_INFO,CENTER_VIEW,"Operation Done!!");

 return &action;
}

trAction* VIEW_panelDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
 tComponent * auxC;
 tTable * auxT;
 char * value;


 auxC = (tComponent *)LVIEW_getElement(NULL,"fnpnombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Panel must have a name");
    return &action;
 }

 if (VIEW_delPanel(value) != 0) 
 {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Panel not found ");
    return &action;
 }
  
 auxT = (tTable *)LVIEW_getElement("telement",NULL);
 TEXT_delLineText(auxT->text, value);
 TABLE_refresh(auxT);
 TEXT_send(value,1);

 return &action;
}

trAction* VIEW_tableDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
 tComponent * auxC;
 tTable * auxT;
 char * value;


 auxC = (tComponent *)LVIEW_getElement(NULL,"fntnombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Table must have a name");
    return &action;
 }

 if (VIEW_delTable(value) != 0) 
 {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Table not found ");
    return &action;
 }
  
 auxT = (tTable *)LVIEW_getElement("telement",NULL);
 TEXT_delLineText(auxT->text, value);
 TABLE_refresh(auxT);
 TEXT_send(value,1);

 return &action;
}

trAction* VIEW_editDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
 tComponent * auxC;
 tTable * auxT;
 char * value;


 auxC = (tComponent *)LVIEW_getElement(NULL,"fnenombre");
 value = COMPONENT_getValue(auxC);
 if (value == NULL || strcmp(value,"")==0) {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Edit must have a name");
    return &action;
 }

 if (VIEW_delEdit(value) != 0) 
 {
    action.error=1;
    MSG_create(M_ERROR,CENTER_VIEW,"Edit not found ");
    return &action;
 }
  
 auxT = (tTable *)LVIEW_getElement("telement",NULL);
 TEXT_delLineText(auxT->text, value);
 TABLE_refresh(auxT);
 TEXT_send(value,1);

 return &action;
}

static void VIEW_addPanel(tXmlPanelPtr newP)
{
 tXmlPanelPtr auxPanel;
  
 auxPanel=(tXmlPanelPtr )malloc(sizeof(tXmlPanel));
 memcpy(auxPanel,newP,sizeof(tXmlPanel));
 auxPanel->siguiente = auxPanel->anterior = NULL;
 
 if (cabPanels == NULL){
   cabPanels=ultPanels=auxPanel;
 } else {
   ultPanels->siguiente = auxPanel;
   auxPanel->anterior = ultPanels;
   ultPanels = auxPanel;
 }
}

static void VIEW_addTable(tXmlTablePtr newT)
{
 tXmlTablePtr auxTable;
  
 auxTable =(tXmlTablePtr )malloc(sizeof(tXmlTable));
 memcpy(auxTable,newT,sizeof(tXmlTable));
 auxTable->siguiente = auxTable->anterior = NULL;
 
 if (cabTables == NULL){
   cabTables=ultTables=auxTable;
 } else {
   ultTables->siguiente = auxTable;
   auxTable->anterior = ultTables;
   ultTables = auxTable;
 }
}

static void VIEW_addEdit(tXmlEditPtr newE)
{
 tXmlEditPtr auxEdit;
  
 auxEdit=(tXmlEditPtr )malloc(sizeof(tXmlEdit));
 memcpy(auxEdit,newE,sizeof(tXmlEdit));
 auxEdit->siguiente = auxEdit->anterior = NULL;
 
 if (cabEdits == NULL){
   cabEdits=ultEdits=auxEdit;
 } else {
   ultEdits->siguiente = auxEdit;
   auxEdit->anterior = ultEdits;
   ultEdits = auxEdit;
 }
}

static int VIEW_delPanel(char * name)
{
 tXmlPanelPtr auxPanel;
  
 auxPanel=cabPanels;
  
 while(auxPanel != NULL){
   if (strcmp(auxPanel->name,name)==0){
     if (auxPanel==cabPanels) cabPanels=cabPanels->siguiente;
     if (auxPanel==ultPanels) ultPanels=ultPanels->anterior;
     if (auxPanel->siguiente != NULL) 
	 auxPanel->siguiente->anterior = auxPanel->anterior;
     if (auxPanel->anterior != NULL)
         auxPanel->anterior->siguiente = auxPanel->siguiente;

     VIEW_deleteComponents(auxPanel);
     free(auxPanel);
     return 0;
   }
   auxPanel = auxPanel->siguiente;
 }
 return -1; 
}

static int VIEW_delTable(char * name)
{
 tXmlTablePtr auxTable;
  
 auxTable=cabTables;
  
 while(auxTable != NULL){
   if (strcmp(auxTable->name,name)==0){
     if (auxTable==cabTables) cabTables=cabTables->siguiente;
     if (auxTable==ultTables) ultTables=ultTables->anterior;
     if (auxTable->siguiente != NULL) 
	 auxTable->siguiente->anterior = auxTable->anterior;
     if (auxTable->anterior != NULL)
         auxTable->anterior->siguiente = auxTable->siguiente;
     free(auxTable);
     return 0;
   }
   auxTable = auxTable->siguiente;
 }
 return -1; 
}

static int VIEW_delEdit(char * name)
{
 tXmlEditPtr auxEdit;
  
 auxEdit=cabEdits;
  
 while(auxEdit != NULL){
   if (strcmp(auxEdit->name,name)==0){
     if (auxEdit==cabEdits) cabEdits=cabEdits->siguiente;
     if (auxEdit==ultEdits) ultEdits=ultEdits->anterior;
     if (auxEdit->siguiente != NULL) 
	 auxEdit->siguiente->anterior = auxEdit->anterior;
     if (auxEdit->anterior != NULL)
         auxEdit->anterior->siguiente = auxEdit->siguiente;
     free(auxEdit);
     return 0;
   }
   auxEdit = auxEdit->siguiente;
 }
 return -1; 
}

trAction* VIEW_panelCalls (tComponent * component,int key){
static trAction action;
 initAction(action);

 if (actPanel != NULL)
  TEXT_send(actPanel->name,1);
 else
  TEXT_send("",1);

 TEXT_send("CALL_PANEL",0);

 return &action;
}

trAction* VIEW_panelMove (tComponent * component,int key){
static trAction action;
 initAction(action);

 if (actPanel != NULL)
  TEXT_send(actPanel->name,1);
 else
  TEXT_send("",1);

 TEXT_send("VIEW_MOVE",0);

 return &action;
}

tXmlCompPanelPtr VIEW_getPanelComps(char * panel)
{
tXmlPanelPtr aux;

  if (panel == NULL) return auxEditPanel.elements;

  aux = VIEW_searchPanel(panel);
  if (aux == NULL) return NULL;  
  return aux->elements;
}

void VIEW_updateViewMove(int tipo, tXmlMove * move)
{
 switch(actEditView){
   case V_Panel:
      if (tipo==0) memcpy(&auxEditPanel.move,move,sizeof(tXmlMove));
      else memcpy(&auxEditPanel.personalAction,move,sizeof(tXmlMove));
   case V_Table:
      if (tipo==0) memcpy(&auxEditTable.move,move,sizeof(tXmlMove));
      else memcpy(&auxEditTable.personalAction,move,sizeof(tXmlMove));
   case V_Edit:
      if (tipo==0) memcpy(&auxEditEdit.move,move,sizeof(tXmlMove));
      else memcpy(&auxEditEdit.personalAction,move,sizeof(tXmlMove));
  }
}

tXmlFApplication * VIEW_getViewCalls(){
 switch(actEditView){
   case V_Panel:
      return &auxEditPanel.personalFPanel;
   case V_Table:
      return &auxEditTable.personalFTable;
   case V_Edit:
      return &auxEditEdit.personalFEdit;
   default:
     return NULL;
  }
}

tXmlMove * VIEW_getViewMove(int tipo)
{
 switch(actEditView){
   case V_Panel:
     if (tipo==0) return &auxEditPanel.move;
     else return &auxEditPanel.personalAction;
   case V_Table:
     if (tipo==0) return &auxEditTable.move;
     else return &auxEditTable.personalAction;
   case V_Edit:
     if (tipo==0) return &auxEditEdit.move;
     else return &auxEditEdit.personalAction;
   default: return NULL;
 }
}

void VIEW_reset()
{
  tXmlPanelPtr paux,paux2;
  tXmlTablePtr taux,taux2;
  tXmlEditPtr  eaux,eaux2;

  paux = cabPanels;
  while (paux!=NULL){
    paux2=paux->siguiente;
    free(paux);
    paux=paux2;
  }
  taux = cabTables;
  while (taux!=NULL){
    taux2=taux->siguiente;
    free(taux);
    taux=taux2;
  }
  eaux = cabEdits;
  while (eaux!=NULL){
    eaux2=eaux->siguiente;
    free(eaux);
    eaux=eaux2;
  }
  
  cabPanels=ultPanels=NULL;
  cabTables=ultTables=NULL;
  cabEdits=ultEdits=NULL;
}

int VIEW_duplicate(int id, char * name){
tXmlPanelPtr paux;
tXmlTablePtr taux;
tXmlEditPtr  eaux;
int nro=0;
   
  if (id<1&& (name ==NULL || strcmp(name,"")==0))
    return -1;

  if (id > 0){
     paux = cabPanels;
     while (paux != NULL) {
          if (paux->id == id) nro++;
          paux = paux->siguiente;
     }
     taux = cabTables;
     while (taux != NULL) {
          if (taux->id == id) nro++;
          taux = taux->siguiente;
     }
     eaux = cabEdits;
     while (eaux != NULL) {
          if (eaux->id == id) nro++;
          eaux = eaux->siguiente;
     }
     return nro;
  }
  paux = cabPanels;
  while (paux != NULL) {
    if (strcmp(paux->name,name)==0)  nro++;
    paux = paux->siguiente;
  }
  taux = cabTables;
  while (taux != NULL) {
    if (strcmp(taux->name,name)==0)  nro++;
    taux = taux->siguiente;
  }
  eaux = cabEdits;
  while (eaux != NULL) {
    if (strcmp(eaux->name,name)==0)  nro++;
    eaux = eaux->siguiente;
  }
  return nro;
}

int VIEW_useColor(char * color){
tXmlPanelPtr paux;
tXmlTablePtr taux;
tXmlEditPtr  eaux;
int nro=0;

  paux = cabPanels;
  while (paux != NULL) {
    if (strcmp(paux->visual.color,color)==0)  nro++;
    paux = paux->siguiente;
  }
  taux = cabTables;
  while (taux != NULL) {
    if (strcmp(taux->visual.color,color)==0)  nro++;
    if (strcmp(taux->visual.colorData,color)==0)  nro++;
    taux = taux->siguiente;
  }
  eaux = cabEdits;
  while (eaux != NULL) {
    if (strcmp(eaux->visual.color,color)==0)  nro++;
    eaux = eaux->siguiente;
  }
  return nro;
}


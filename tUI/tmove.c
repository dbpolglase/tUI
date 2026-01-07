#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <text.h>
#include <table.h>
#include <lview.h>
#include <component.h>

#include <tparser.h>
#include <tproyect.h>
#include <tview.h>
#include <tcomp.h>
#include <tmove.h>

tXmlFApplication * datosCallback;
tXmlMove * datosMove;
tXmlMove  editDatosMove;

typedef struct {
  char ret[2][MAX_COMPONENT_NAME];
}tsplit;

static tsplit* MOVE_split(char * dato);
static void MOVE_newDatos(char * datos,char * panel, char * component);

void MOVE_load(tPanel * panel){
char * npanel;
char * comp;
char * op;
tComponent * auxC;
tsplit * splitMove;
char buf[30];
int i=0,j=0;

 op = TEXT_recv();
 npanel = TEXT_recv();
 comp = TEXT_recv();

 if (op==NULL) return;
 datosMove = NULL;

 if (comp != NULL)
 {
   auxC = (tComponent *)LVIEW_getElement("aMove","panel");
   if (auxC!=NULL) COMPONENT_setValue(auxC,npanel);
   
   if (strcmp(op,"COMP_MOVE")==0)
     datosMove = COMP_getCompMove(comp);
 }
 else {
   if (strcmp(op,"VIEW_MOVE")==0)
     datosMove = VIEW_getViewMove(0);
 }

 if (datosMove == NULL) {
   memset(&editDatosMove,'\0',sizeof(editDatosMove));
   return;
 }


 memcpy(&editDatosMove,datosMove,sizeof(editDatosMove));

 if (strcmp(datosMove->enter,"")!=0){
     splitMove=MOVE_split(datosMove->enter);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelenter");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompenter");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->out,"")!=0){
     splitMove=MOVE_split(datosMove->out);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelout");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompout");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->next,"")!=0){
     splitMove=MOVE_split(datosMove->next);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelnext");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompnext");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->previous,"")!=0){
     splitMove=MOVE_split(datosMove->previous);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelprev");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompprev");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->up,"")!=0){
     splitMove=MOVE_split(datosMove->up);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelup");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompup");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->down,"")!=0){
     splitMove=MOVE_split(datosMove->down);
     auxC = (tComponent *)LVIEW_getElement("aMove","empaneldown");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompdown");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->left,"")!=0){
     splitMove=MOVE_split(datosMove->left);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelleft");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompleft");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->right,"")!=0){
     splitMove=MOVE_split(datosMove->right);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelright");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompright");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }

 for (i=0;i!=9&&j<4;i++) {
    if (strcmp(datosMove->Fn[i],"")!=0){
     splitMove=MOVE_split(datosMove->Fn[i]);
     sprintf(buf,"empanelFn%d",j);
     auxC = (tComponent *)LVIEW_getElement("aMove",buf);
     sprintf(buf,"%d",i+1);
     if (auxC!=NULL) COMPONENT_setValue(auxC,buf);
     sprintf(buf,"empanelF%d",j);
     auxC = (tComponent *)LVIEW_getElement("aMove",buf);
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     sprintf(buf,"emcompF%d",j);
     auxC = (tComponent *)LVIEW_getElement("aMove",buf);
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
     j++;
    }
 }

 if (strcmp(datosMove->back,"")!=0){
     splitMove=MOVE_split(datosMove->back);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelback");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompback");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
 if (strcmp(datosMove->other,"")!=0){
     splitMove=MOVE_split(datosMove->other);
     auxC = (tComponent *)LVIEW_getElement("aMove","empanelother");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[0]);
     auxC = (tComponent *)LVIEW_getElement("aMove","emcompother");
     if (auxC!=NULL) COMPONENT_setValue(auxC,splitMove->ret[1]);
 }
}

void MOVE_loadFunction(tPanel * panel){
char * npanel;
char * comp;
char * op;
tComponent * auxC;

 op = TEXT_recv();
 npanel = TEXT_recv();
 comp = TEXT_recv();

 if (op==NULL) return;
 datosMove = NULL;

 if (comp != NULL)
 {
   if (strcmp(op,"COMP_MOVE")==0)
     datosMove = COMP_getCompAppMove(comp);
 }
 else {
   if (strcmp(op,"VIEW_MOVE")==0)
     datosMove = VIEW_getViewMove(1);
 }

 if (datosMove == NULL) {
     memset(&editDatosMove,'\0',sizeof(editDatosMove));
     return;
 }

 memcpy(&editDatosMove,datosMove,sizeof(editDatosMove));

 if (strcmp(datosMove->enter,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amenterfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->enter);
 }
 if (strcmp(datosMove->out,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amoutfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->out);
 }
 if (strcmp(datosMove->next,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amnextfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->next);
 }
 if (strcmp(datosMove->previous,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amprevfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->previous);
 }
 if (strcmp(datosMove->up,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amupfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->up);
 }
 if (strcmp(datosMove->down,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amdownfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->down);
 }
 if (strcmp(datosMove->left,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amleftfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->left);
 }
 if (strcmp(datosMove->right,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amrightfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->right);
 }

 if (strcmp(datosMove->Fn[0],"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fMove","amFnfunction");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosMove->Fn[0]);
 }
}

void FUNC_load(tPanel * panel){
char * dato;
char * op;
tComponent * auxC;


 op = TEXT_recv();
 dato = TEXT_recv();

 if (op==NULL) return;

 if (dato != NULL)
 {
   if (strcmp(op,"CALL_PANEL")==0)
     datosCallback = VIEW_getViewCalls();

   if (strcmp(op,"CALL_COMPONENT")==0)
     datosCallback = COMP_getCalls();

   if (datosCallback == NULL) return;

   if (strcmp(datosCallback->pre_create,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreCr");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_create);
   }
   if (strcmp(datosCallback->post_create,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostCr");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_create);
   }
   if (strcmp(datosCallback->pre_show,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreSh");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_show);
   }
   if (strcmp(datosCallback->post_show,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostSh");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_show);
   }
   if (strcmp(datosCallback->pre_activate,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreAct");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_activate);
   }
   if (strcmp(datosCallback->post_activate,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostAct");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_activate);
   }
   if (strcmp(datosCallback->pre_deactivate,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreDAct");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_deactivate);
   }
   if (strcmp(datosCallback->post_deactivate,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostDAct");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_deactivate);
   }
   if (strcmp(datosCallback->pre_hide,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreHide");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_hide);
   }
   if (strcmp(datosCallback->post_hide,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostHide");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_hide);
   }
   if (strcmp(datosCallback->pre_destroy,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreDest");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->pre_destroy);
   }
   if (strcmp(datosCallback->post_destroy,"")!=0){
     auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostDest");
     if (auxC!=NULL) COMPONENT_setValue(auxC,datosCallback->post_destroy);
   }
 }
}

trAction* MOVE_save (tComponent *,int )
{
static trAction action;
tComponent * auxC,*auxC2;
char * value;
int i;

 initAction(action)

 if (datosMove == NULL) return &action;

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelenter");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompenter");
 sprintf(datosMove->enter,"%s:%s",COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->enter,":")==0) strcpy(datosMove->enter,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelout");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompout");
 MOVE_newDatos(datosMove->out,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->out,":")==0) strcpy(datosMove->out,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelnext");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompnext");
 MOVE_newDatos(datosMove->next,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->next,":")==0) strcpy(datosMove->next,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelprev");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompprev");
 MOVE_newDatos(datosMove->previous,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->previous,":")==0) strcpy(datosMove->previous,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelup");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompup");
 MOVE_newDatos(datosMove->up,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->up,":")==0) strcpy(datosMove->up,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empaneldown");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompdown");
 MOVE_newDatos(datosMove->down,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->down,":")==0) strcpy(datosMove->down,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelleft");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompleft");
 MOVE_newDatos(datosMove->left,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->left,":")==0) strcpy(datosMove->left,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelright");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompright");
 MOVE_newDatos(datosMove->right,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->right,":")==0) strcpy(datosMove->right,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn0");
 value= COMPONENT_getValue(auxC);
 if (value != NULL && !strcmp(value,"")==0) {
   i = atoi(value) -1;
   auxC = (tComponent *)LVIEW_getElement(NULL,"empanelF0");
   auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompF0");
   MOVE_newDatos(datosMove->Fn[i],COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
   if (strcmp(datosMove->Fn[i],":")==0) strcpy(datosMove->Fn[i],"");
 }

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn1");
 value= COMPONENT_getValue(auxC);
 if (value != NULL && !strcmp(value,"")==0) {
   i = atoi(value) -1;
   auxC = (tComponent *)LVIEW_getElement(NULL,"empanelF1");
   auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompF1");
   MOVE_newDatos(datosMove->Fn[i],COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
   if (strcmp(datosMove->Fn[i],":")==0) strcpy(datosMove->Fn[i],"");
 }

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn2");
 value= COMPONENT_getValue(auxC);
 if (value != NULL && !strcmp(value,"")==0) {
   i = atoi(value) -1;
   auxC = (tComponent *)LVIEW_getElement(NULL,"empanelF2");
   auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompF2");
   MOVE_newDatos(datosMove->Fn[i],COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
   if (strcmp(datosMove->Fn[i],":")==0) strcpy(datosMove->Fn[i],"");
 }

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn3");
 value= COMPONENT_getValue(auxC);
 if (value != NULL && !strcmp(value,"")==0) {
   i = atoi(value) -1;
   auxC = (tComponent *)LVIEW_getElement(NULL,"empanelF3");
   auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompF3");
   MOVE_newDatos(datosMove->Fn[i],COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
   if (strcmp(datosMove->Fn[i],":")==0) strcpy(datosMove->Fn[i],"");
 }

/* 
 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelback");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompback");
 MOVE_newDatos(datosMove->back,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->back,":")==0) strcpy(datosMove->back,"");

 auxC = (tComponent *)LVIEW_getElement(NULL,"empanelother");
 auxC2 = (tComponent *)LVIEW_getElement(NULL,"emcompother");
 MOVE_newDatos(datosMove->other,COMPONENT_getValue(auxC),COMPONENT_getValue(auxC2));
 if (strcmp(datosMove->other,":")==0) strcpy(datosMove->other,"");
*/

 return &action;
}

trAction* MOVE_saveFunction (tComponent *,int )
{
static trAction action;
tComponent * auxC;

 initAction(action)

 if (datosMove == NULL) return &action;

 auxC = (tComponent *)LVIEW_getElement(NULL,"amenterfunction");
 strcpy(datosMove->enter,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amoutfunction");
 strcpy(datosMove->out,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amnextfunction");
 strcpy(datosMove->next,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amprevfunction");
 strcpy(datosMove->previous,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amupfunction");
 strcpy(datosMove->up,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amdownfunction");
 strcpy(datosMove->down,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amleftfunction");
 strcpy(datosMove->left,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amrightfunction");
 strcpy(datosMove->right,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement(NULL,"amFnfunction");
 strcpy(datosMove->Fn[0],COMPONENT_getValue(auxC));

 return &action;
}

static void MOVE_newDatos(char * datos,char * panel, char * component)
{
  strcpy(datos,"");

  if (panel!=NULL && !strcmp(panel,"")==0){
   strcat(datos,panel);
   strcat(datos,":");
  }
  if (component!=NULL && !strcmp(component,"")==0)
  {
   if (strcmp(datos,"")==0) strcat(datos,":");
   strcat(datos,component);
  }
}


trAction* FUNC_save (tComponent *,int )
{
static trAction action;
tComponent * auxC;

 initAction(action)

 if (datosCallback == NULL) return &action;

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreCr");
 if (auxC!=NULL ) strcpy(datosCallback->pre_create,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostCr");
 if (auxC!=NULL ) strcpy(datosCallback->post_create,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreSh");
 if (auxC!=NULL ) strcpy(datosCallback->pre_show,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostSh");
 if (auxC!=NULL ) strcpy(datosCallback->post_show,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreAct");
 if (auxC!=NULL ) strcpy(datosCallback->pre_activate,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostAct");
 if (auxC!=NULL ) strcpy(datosCallback->post_activate,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreDAct");
 if (auxC!=NULL ) strcpy(datosCallback->pre_deactivate,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostDAct");
 if (auxC!=NULL ) strcpy(datosCallback->post_deactivate,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreHide");
 if (auxC!=NULL ) strcpy(datosCallback->pre_hide,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostHide");
 if (auxC!=NULL ) strcpy(datosCallback->post_hide,COMPONENT_getValue(auxC));

 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPreDest");
 if (auxC!=NULL ) strcpy(datosCallback->pre_destroy,COMPONENT_getValue(auxC));
 auxC = (tComponent *)LVIEW_getElement("fAppCalls","fACPostDest");
 if (auxC!=NULL ) strcpy(datosCallback->post_destroy,COMPONENT_getValue(auxC));

 return &action;
}

static tsplit * MOVE_split(char * dato)
{
 static tsplit splitMove;
 char * aux;

  memset(&splitMove,'\0',sizeof(splitMove));

  aux =dato;
  while (*aux != '\0' && *aux!=':') aux++;
  if (*aux == ':') {
    strncpy(splitMove.ret[0],dato,(aux-dato));
    strcpy(splitMove.ret[1],aux+1);
  }
  return &splitMove;
}

trAction* MOVE_selectHelp (tComponent * component,int key,int Fn){
static trAction action;
tComponent * auxC;
char buf[50];
char * value;

 initAction(action);

  if (strstr(component->name,"panel") != NULL)
  {
    TEXT_send("-:",1);
    TEXT_send("ALL_VIEW",0);
    TEXT_send(component->name,0);
  }

  if (strstr(component->name,"comp") != NULL)
  {
    TEXT_send("-:",1);
    TEXT_send("PANEL_HELP_COMPs",0);
   
    strcpy(buf,"empanel");
    strcat(buf,component->name+6);
    auxC = (tComponent *)LVIEW_getElement(NULL,buf);
    value = COMPONENT_getValue(auxC);
    if (value==NULL || strcmp(value,"")==0){
      auxC = (tComponent *)LVIEW_getElement(NULL,"panel");
      TEXT_send(COMPONENT_getValue(auxC),0);
    }
    else
      TEXT_send(value,0);
  }
  return &action;
}

trAction* MOVE_enterPanel (tComponent * component,int key){
static trAction action;
tComponent * auxC;
char value[50];
char buf[50];
char *auxValue;
char *auxFnValue;
unsigned short change;
int i;

 change=0;
 initAction(action)


 if (datosMove != NULL) {
   auxValue = COMPONENT_getValue(component); 
   strcpy(value,auxValue); strcat(value,":");
   strcpy(buf,"emcomp");
   strcat(buf,component->name+7);
   if (strstr(component->name,"enter") != NULL ){
       if (strcmp(editDatosMove.enter,"")!=0 &&
           strstr(editDatosMove.enter,value)==NULL) change=1;
       strcpy(editDatosMove.enter,value);
   }

   if (strstr(component->name,"out") != NULL ){
       if (strcmp(editDatosMove.out,"")!=0 &&
           strstr(editDatosMove.out,value)==NULL) change=1;
       strcpy(editDatosMove.out,value);
   }

   if (strstr(component->name,"next") != NULL ){
       if (strcmp(editDatosMove.next,"")!=0 &&
           strstr(editDatosMove.next,value)==NULL) change=1;
       strcpy(editDatosMove.next,value);
   }

   if (strstr(component->name,"prev") != NULL ){
       if (strcmp(editDatosMove.previous,"")!=0 &&
           strstr(editDatosMove.previous,value)==NULL) change=1;
       strcpy(editDatosMove.previous,value);
   }
   if (strstr(component->name,"up") != NULL ){
       if (strcmp(editDatosMove.up,"")!=0 &&
           strstr(editDatosMove.up,value)==NULL) change=1;
       strcpy(editDatosMove.up,value);
   }

   if (strstr(component->name,"down") != NULL ){
       if (strcmp(editDatosMove.down,"")!=0 &&
           strstr(editDatosMove.down,value)==NULL) change=1;
       strcpy(editDatosMove.down,value);
   }

   if (strstr(component->name,"left") != NULL ){
       if (strcmp(editDatosMove.left,"")!=0 &&
           strstr(editDatosMove.left,value)==NULL) change=1;
       strcpy(editDatosMove.left,value);
   }

   if (strstr(component->name,"right") != NULL ){
       if (strcmp(editDatosMove.right,"")!=0 &&
           strstr(editDatosMove.right,value)==NULL) change=1;
       strcpy(editDatosMove.right,value);
   }

   if (strstr(component->name,"F0") != NULL ){
     auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn0");
     auxFnValue = COMPONENT_getValue(auxC); 
     i = atoi(auxFnValue)-1;

     if (strcmp(editDatosMove.Fn[i],"")!=0 &&
         strstr(editDatosMove.Fn[i],value)==NULL) change=1;
       strcpy(editDatosMove.Fn[i],value);
   }
   if (strstr(component->name,"F1") != NULL ){
     auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn1");
     auxFnValue = COMPONENT_getValue(auxC); 
     i = atoi(auxFnValue)-1;

     if (strcmp(editDatosMove.Fn[i],"")!=1 &&
         strstr(editDatosMove.Fn[i],value)==NULL) change=1;
       strcpy(editDatosMove.Fn[i],value);
   }

   if (strstr(component->name,"F2") != NULL ){
     auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn2");
     auxFnValue = COMPONENT_getValue(auxC); 
     i = atoi(auxFnValue)-1;

     if (strcmp(editDatosMove.Fn[i],"")!=0 &&
         strstr(editDatosMove.Fn[i],value)==NULL) change=1;
       strcpy(editDatosMove.Fn[i],value);
   }
   if (strstr(component->name,"F3") != NULL ){
     auxC = (tComponent *)LVIEW_getElement(NULL,"empanelFn3");
     auxFnValue = COMPONENT_getValue(auxC); 
     i = atoi(auxFnValue)-1;

     if (strcmp(editDatosMove.Fn[i],"")!=0 &&
         strstr(editDatosMove.Fn[i],value)==NULL) change=1;
       strcpy(editDatosMove.Fn[i],value);
   }

   
   if (change) {
       auxC = (tComponent *)LVIEW_getElement(NULL,buf);
       COMPONENT_setValue(auxC,"");
       COMPONENT_refresh(auxC);
   }
 }
 return &action;
}



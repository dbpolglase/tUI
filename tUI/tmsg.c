
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
#include <view.h>
#include <component.h>
#include <back.h>

#include <tparser.h>
#include <tcolor.h>
#include <tmsg.h>

static tXmlMsgs Msgs = {{NULL,NULL,NULL}};

static tXmlMsg defaultInfo={M_INFO,"Info",0,"OK","CANCEL","noColor"};
static tXmlMsg defaultWarning={M_WARNING,"Warning",2,"OK","CANCEL","noColor"};
static tXmlMsg defaultError={M_ERROR,"Error",1,"OK","CANCEL","noColor"};
static int msgTipe=0;

trAction* MSG_select (tComponent * component,int key){
static trAction action;
 initAction(action);
 TEXT_send(component->name,1);
return &action;
}

void MSG_load(){
  char * auxMsg;
  tComponent * aux;
  tPanel * tpanel;
  tXmlcolorPtr auxColor;

  auxMsg=TEXT_recv();
  aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMcolor");
  auxColor = COLOR_getXml();
  COMPONENT_clean(aux);
  while (auxColor !=NULL){
     COMPONENT_addText(aux,auxColor->name);
    auxColor = auxColor->siguiente;
  }
  if (auxMsg != NULL){
    if (strcmp(auxMsg,"information") == 0){
     if (Msgs.msg[0] == NULL) {
		Msgs.msg[0] = (tXmlMsg *)malloc(sizeof(tXmlMsg));
		memcpy(Msgs.msg[0],&defaultInfo,sizeof(tXmlMsg));
     }
     msgTipe=0;
     tpanel=LVIEW_searchView("frmMsgs")->view.panel;
     strcpy(tpanel->title,"MSG Information");
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMtitle");
     COMPONENT_setValue(aux,Msgs.msg[0]->title);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMnbuttons");
     COMPONENT_setSelectValue(aux,Msgs.msg[0]->nroButtons,NULL);
     MSG_buttons (aux,0);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_setValue(aux,Msgs.msg[0]->ButtonText1);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_setValue(aux,Msgs.msg[0]->ButtonText2);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMcolor");
     COMPONENT_setSelectValue(aux,-1,Msgs.msg[0]->color);
    }
    if (strcmp(auxMsg,"warning") == 0){
      if (Msgs.msg[1] == NULL){
		Msgs.msg[1] = (tXmlMsg *)malloc(sizeof(tXmlMsg));
		memcpy(Msgs.msg[1],&defaultWarning,sizeof(tXmlMsg));
      }
     msgTipe=1;
     tpanel=LVIEW_searchView("frmMsgs")->view.panel;
     strcpy(tpanel->title,"MSG Warning");
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMtitle");
     COMPONENT_setValue(aux,Msgs.msg[1]->title);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMnbuttons");
     COMPONENT_setSelectValue(aux,Msgs.msg[1]->nroButtons,NULL);
     MSG_buttons (aux,0);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_setValue(aux,Msgs.msg[1]->ButtonText1);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_setValue(aux,Msgs.msg[1]->ButtonText2);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMcolor");
     COMPONENT_setSelectValue(aux,-1,Msgs.msg[1]->color);
    }
    if (strcmp(auxMsg,"error") == 0){
     if (Msgs.msg[2] == NULL) {
		Msgs.msg[2] = (tXmlMsg *)malloc(sizeof(tXmlMsg));
		memcpy(Msgs.msg[2],&defaultError,sizeof(tXmlMsg));
              }
     msgTipe=2;
     tpanel=LVIEW_searchView("frmMsgs")->view.panel;
     strcpy(tpanel->title,"MSG Error");
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMtitle");
     COMPONENT_setValue(aux,Msgs.msg[2]->title);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMnbuttons");
     COMPONENT_setSelectValue(aux,Msgs.msg[2]->nroButtons,NULL);
     MSG_buttons (aux,0);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_setValue(aux,Msgs.msg[2]->ButtonText1);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_setValue(aux,Msgs.msg[2]->ButtonText2);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMcolor");
     COMPONENT_setSelectValue(aux,-1,Msgs.msg[2]->color);
    }
  }
}

void MSG_reset(){
int i;

  for (i=0;i!=3;i++)
   if (Msgs.msg[i]!=NULL) { free(Msgs.msg[i]);Msgs.msg[i]=NULL; }
}


void MSG_set(tXmlMsgs msgs){
  MSG_reset();
  memcpy(&Msgs,&msgs,sizeof(tXmlMsgs));
}

tXmlMsgs * MSG_get(){
  return &Msgs;
}

tXmlMsg * MSG_getEditActual(){
  return Msgs.msg[msgTipe];
}

trAction* MSG_change (tComponent * component,int key){
static trAction action;
 tComponent * aux; 

 initAction(action);

 aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMtitle");
 strcpy(Msgs.msg[msgTipe]->title,COMPONENT_getValue(aux));
 aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMnbuttons");
 Msgs.msg[msgTipe]->nroButtons=atoi(COMPONENT_getValue(aux));
 aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
 strcpy(Msgs.msg[msgTipe]->ButtonText1,COMPONENT_getValue(aux));
 aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
 strcpy(Msgs.msg[msgTipe]->ButtonText2,COMPONENT_getValue(aux));
 aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMcolor");
 strcpy(Msgs.msg[msgTipe]->color,COMPONENT_getValue(aux));

 return &action;
}

trAction* MSG_buttons (tComponent * component,int key){
static trAction action;
 tComponent * aux; 
 char * data; 
 int i;
  
 initAction(action);

 data = COMPONENT_getValue(component);

 i = atoi(data);
  
 switch(i)
 {
   case 0:
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_display(aux,DIS_HIDDEN);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_display(aux,DIS_HIDDEN);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet04");
     COMPONENT_display(aux,DIS_HIDDEN);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet05");
     COMPONENT_display(aux,DIS_HIDDEN);
     break;
   case 2:
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_display(aux,DIS_NORMAL);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet05");
     COMPONENT_display(aux,DIS_NORMAL);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_display(aux,DIS_NORMAL);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet04");
     COMPONENT_display(aux,DIS_NORMAL);
     break;
   case 1:
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton2");
     COMPONENT_display(aux,DIS_HIDDEN);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet05");
     COMPONENT_display(aux,DIS_HIDDEN);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMbutton1");
     COMPONENT_display(aux,DIS_NORMAL);
     aux = (tComponent *)LVIEW_getElement("frmMsgs","frmMet04");
     COMPONENT_display(aux,DIS_NORMAL);
     break;
   default: break;
 }

 return &action;
}



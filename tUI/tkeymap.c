
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <text.h>
#include <lview.h>
#include <component.h>

#include <tparser.h>
#include <tkeymap.h>

tXmlMapKey workMap;

static tXmlMapKeyPtr cabKeymap;
static tXmlMapKeyPtr ultKeymap;

static void setTecla(char * opcion,int tnum,int tecla);
static void KEYM_add();
static int KEYM_del();

tXmlMapKeyPtr KEYM_get(){
  return cabKeymap;
}

void KEYM_load()
{
char * data;
tXmlMapKeyPtr aux;
tComponent * auxC;
char name[50];
char buf[10];
int i;

  memset(&workMap,'\0',sizeof(tXmlMapKey));
  data = TEXT_recv();
  if (data != NULL){
   aux = KEYM_search(data);
   if (aux == NULL) {
	MSG_create(M_INFO,CENTER_VIEW,"KEYMAP <%s> not found",data);
   }
   else
   { 
     auxC = (tComponent *)LVIEW_getElement("frmkeymap","nkeymap"); 
     COMPONENT_setValue(auxC,aux->name);
     memcpy(&workMap,aux,sizeof(workMap));
     auxC = (tComponent *)LVIEW_getElement("frmkeymap","bkmFunction"); 
     if (workMap.mapa.Fn[0][0] != 0)
      COMPONENT_setValue(auxC,"");
     else
      COMPONENT_setValue(auxC,NULL);

     for (i=0;i!=3;i++){
         sprintf(name,"etkenter%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.enter[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"enter%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.enter[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkout%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.out[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"out%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.out[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etknext%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.next[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"next%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.next[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkprevious%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.previous[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"previous%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.previous[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkup%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.up[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"up%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.up[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkdown%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.down[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"down%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.down[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkleft%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.left[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"left%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.left[i]);
         COMPONENT_setValue(auxC,buf);

         sprintf(name,"etkright%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%c",workMap.mapa.right[i]);
         COMPONENT_setValue(auxC,buf);
         sprintf(name,"right%d",i);
         auxC = (tComponent *)LVIEW_getElement("frmkeymap",name);
         sprintf(buf,"%-4d",workMap.mapa.right[i]);
         COMPONENT_setValue(auxC,buf);

     }
   }
   auxC = (tComponent *)LVIEW_getElement("frmkeymap","frmKdelete"); 
   COMPONENT_display(auxC,DIS_NORMAL);
 }
 else {
     auxC = (tComponent *)LVIEW_getElement("frmkeymap","frmKdelete"); 
     COMPONENT_display(auxC,DIS_HIDDEN);
 }
}

void KEYMAP_set(tXmlMapKeyPtr cab, tXmlMapKeyPtr ult)
{
  cabKeymap = cab;
  ultKeymap = ult;
}

tXmlMapKeyPtr KEYMAP_get(){
   return cabKeymap;
}

void KEYMAP_reset()
{
tXmlMapKeyPtr aux;
memset(&workMap,'\0',sizeof(tXmlMapKey));
  aux = cabKeymap;
  while (aux!=NULL){
   cabKeymap = cabKeymap->siguiente;
   free(aux);
   aux = cabKeymap;
  }
  cabKeymap=ultKeymap=NULL;
}

trAction* KEYM_create (tComponent * component,int key){
static trAction action;
tComponent * aux;
char * value;
int i;

 initAction(action);
 aux = (tComponent *)LVIEW_getElement(NULL,"nkeymap"); 
 strncpy(workMap.name,COMPONENT_getValue(aux),MAX_FUNC_NAME); 
 if (strcmp(workMap.name,"")==0){
  action.error=1;
  MSG_create(M_ERROR,CENTER_VIEW,"No name from Keymap");
 }
 else {
  aux = (tComponent *)LVIEW_getElement(NULL,"bkmFunction"); 
  value=COMPONENT_getValue(aux); 
  for (i=0;i!=MAX_Fn_KEYS;i++)
     workMap.mapa.Fn[i][0] = (value==NULL)?0:KEY_F(i);
  KEYM_add();
  MSG_setSegInfo(2);
  MSG_create(M_INFO,CENTER_VIEW," Done !! ");
  MSG_setSegInfo(MSG_TIME_INFO);
 }

 return &action;
}

trAction* KEYM_delete (tComponent * component,int key){
static trAction action;
tComponent * aux;

 initAction(action);
 aux = (tComponent *)LVIEW_getElement(NULL,"nkeymap"); 
 strncpy(workMap.name,COMPONENT_getValue(aux),MAX_FUNC_NAME); 
 if (strcmp(workMap.name,"")==0){
  action.error=1;
  MSG_create(M_ERROR,CENTER_VIEW,"No name from Keymap");
 }
 else {
  if (KEYM_del() != 0){
    MSG_create(M_ERROR,CENTER_VIEW,"Can't delete %s Keymap",workMap.name);
    action.error=1;
  }
 }

 return &action;
}

tXmlMapKey * KEYM_search(char * name) {
 tXmlMapKey * aux;
 aux = cabKeymap;

 while (aux!=NULL){
   if (strcmp(aux->name,name)==0)
    return aux;
   aux=aux->siguiente;
 }
 return NULL;
}

static void KEYM_add() {
tXmlMapKey * aux;

 if ((aux=KEYM_search(workMap.name)) != NULL){
  memcpy(&aux->mapa,&workMap.mapa,sizeof(tmapKeys));
  return;
 }

 aux = (tXmlMapKeyPtr) malloc(sizeof(tXmlMapKey));
 if (aux == NULL) {
   ERR_fatalError(ERR_MEM,"Out of memory %d",sizeof(tXmlMapKey));
 }
 memcpy(aux,&workMap,sizeof(tXmlMapKey));
 memset(&workMap,'\0',sizeof(tXmlMapKey));
 aux->siguiente=NULL;
 aux->anterior=NULL;

 if (cabKeymap == NULL) {
    cabKeymap = ultKeymap = aux; 
 }
 else {
  aux->anterior=ultKeymap;
  ultKeymap->siguiente=aux;
  ultKeymap=aux;
 }
}

static int KEYM_del() {
tXmlMapKey * aux;

 if ((aux=KEYM_search(workMap.name)) == NULL){
  return -1;
 }

 if (aux == cabKeymap) cabKeymap = aux->siguiente;
 if (aux == ultKeymap) ultKeymap = aux->anterior;
  
 if (aux->siguiente != NULL) aux->siguiente->anterior=aux->anterior;
 if (aux->anterior != NULL) aux->anterior->siguiente=aux->siguiente;
 free(aux);
 return 0;
}

trAction* KEYM_new (tComponent * component,int key){
static trAction action;
int tecla;
char buf[200];
int i;

 initAction(action);
 MSG_create(M_INFO,CENTER_VIEW,"Press 3 keys, Space to clear or not to set");

 for (i=0;i<3;i++){
   tecla = getch();
   sprintf(buf,"%c",tecla);
   setTecla(component->name,i,tecla); 
 }
 return &action;
}

trAction* KEYM_change (tComponent * component,int key){
static trAction action;
 initAction(action);
 
 if (cabKeymap == NULL) {
   MSG_create(M_ERROR,CENTER_VIEW,"The aren't keymaps defined");
   action.error=1;
 }
 else {
  TEXT_send("frmkeymap:nkeymap",1);
  TEXT_send("KEYMAP",0);
  TEXT_send("-:",0);
 }

 return &action;
}

static void setTecla(char * opcion,int tnum,int tecla)
{
tComponent * aux;
char buf[20];
char name[20];
int t2;

  t2 = tecla;

  if (tecla==32){ t2=0; tecla='0';}

  if (strcmp(opcion,"bkmEnter") == 0){
         workMap.mapa.enter[tnum]=t2;
         sprintf(name,"etkenter%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"enter%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmOut") == 0){
         workMap.mapa.out[tnum]=t2;
         sprintf(name,"etkout%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"out%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmNext") == 0){
         workMap.mapa.next[tnum]=t2;
         sprintf(name,"etknext%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"next%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmPrevious") == 0){
         workMap.mapa.previous[tnum]=t2;
         sprintf(name,"etkprevious%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"previous%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmUp") == 0){
         workMap.mapa.up[tnum]=t2;
         sprintf(name,"etkup%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"up%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmDown") == 0){
         workMap.mapa.down[tnum]=t2;
         sprintf(name,"etkdown%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"down%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmLeft") == 0){
         workMap.mapa.left[tnum]=t2;
         sprintf(name,"etkleft%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"left%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
  if (strcmp(opcion,"bkmRight") == 0){
         workMap.mapa.right[tnum]=t2;
         sprintf(name,"etkright%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%c",tecla);
         COMPONENT_changeText(aux,buf);
         sprintf(name,"right%d",tnum);
         aux = (tComponent *)LVIEW_getElement(NULL,name);
         sprintf(buf,"%-4d",t2);
         COMPONENT_changeText(aux,buf);
  }
}



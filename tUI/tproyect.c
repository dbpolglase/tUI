
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
#include <edit.h>
#include <component.h>
#include <tparser.h>
#include <tfunc.h>
#include <tcomp.h>
#include <tcolor.h>
#include <tkeymap.h>
#include <tview.h>
#include <tmsg.h>
#include <tedf.h>
#include <tprintXml.h>
#include <tmake_func.h>

#include <tparser.h>

#define MAX_TTY        200
#define MAX_TYPE_TERM  50

typedef struct {
  SCREEN * screen;
  char tty[MAX_TTY];
  FILE * fd;
  char term[MAX_TYPE_TERM];
}tTest,*tTestPtr;

extern SCREEN * scrSTD;

static int manualEdit=0;

tXmlProyect theProyect={"","","",NULL,0};

tXmlProp proyectInitXmlProperties={1,1,1,"errors.err",
		'?','X','_',
		{'-','-','|','|','+','+','+','+'},
		{'-','-','|','#','+','+','^','v'},
                "","","view:component"};

tXmlProp proyectXmlProperties={1,1,1,"errors.err",
		'?','X','_',
		{'-','-','|','|','+','+','+','+'},
		{'-','-','|','#','+','+','^','v'},
                "","","view:component"};

tTest testTerminal={NULL,"/dev/pts",NULL,"xterm-256color"};

static void PROY_resetXmlProyect();
static void PROY_resetXmlProperties();

trAction* PROY_propertiesDoIt (tComponent * component,int key){
static trAction action;
tComponent * aux;

 initAction(action);

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPmouse");
 if (aux!=NULL&&COMPONENT_getValue(aux) == NULL)
   proyectXmlProperties.useMouse=0;
 else
   proyectXmlProperties.useMouse=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPcolor");
 if (aux!=NULL&&COMPONENT_getValue(aux) == NULL)
   proyectXmlProperties.useColor=0;
 else
   proyectXmlProperties.useColor=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPerror");
 if (aux!=NULL&&COMPONENT_getValue(aux) == NULL)
   proyectXmlProperties.printErrors=0;
 else
   proyectXmlProperties.printErrors=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPferror");
 if (aux!=NULL)
   strcpy(proyectXmlProperties.ferrors,COMPONENT_getValue(aux));
 else
   action.error=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"chCheck");
 if (aux!=NULL)
   proyectXmlProperties.chCheck=(int)COMPONENT_getValue(aux)[0];
 aux = (tComponent *)LVIEW_getElement(NULL,"chisCheck");
   proyectXmlProperties.chIsCheck=(int)COMPONENT_getValue(aux)[0];
 aux = (tComponent *)LVIEW_getElement(NULL,"chnoCheck");
   proyectXmlProperties.chNoCheck=(int)COMPONENT_getValue(aux)[0];

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPup");
 if (aux!=NULL)
   proyectXmlProperties.borders[0]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPdw");
 if (aux!=NULL)
   proyectXmlProperties.borders[1]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPlf");
 if (aux!=NULL)
   proyectXmlProperties.borders[2]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPrg");
 if (aux!=NULL)
   proyectXmlProperties.borders[3]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPcul");
 if (aux!=NULL)
   proyectXmlProperties.borders[4]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPcur");
 if (aux!=NULL)
   proyectXmlProperties.borders[5]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPcdl");
 if (aux!=NULL)
   proyectXmlProperties.borders[6]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPcdr");
 if (aux!=NULL)
   proyectXmlProperties.borders[7]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPup");
 if (aux!=NULL)
   proyectXmlProperties.sborders[0]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPdw");
 if (aux!=NULL)
   proyectXmlProperties.sborders[1]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPlf");
 if (aux!=NULL)
   proyectXmlProperties.sborders[2]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPrg");
 if (aux!=NULL)
   proyectXmlProperties.sborders[3]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPcul");
 if (aux!=NULL)
   proyectXmlProperties.sborders[4]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPcur");
 if (aux!=NULL)
   proyectXmlProperties.sborders[5]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPcdl");
 if (aux!=NULL)
   proyectXmlProperties.sborders[6]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmSPcdr");
 if (aux!=NULL)
   proyectXmlProperties.sborders[7]=COMPONENT_getValue(aux)[0];
 else
   action.error=1;

 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPmainf");
 if (aux!=NULL)
   strcpy(proyectXmlProperties.mainFunction,COMPONENT_getValue(aux));
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPendf");
 if (aux!=NULL)
   strcpy(proyectXmlProperties.endFunction,COMPONENT_getValue(aux));
 else
   action.error=1;
 aux = (tComponent *)LVIEW_getElement(NULL,"frmPPinit");
 if (aux!=NULL)
   strcpy(proyectXmlProperties.initView,COMPONENT_getValue(aux));
 else
   action.error=1;

 return &action;
}

void PROY_loadProperties(tPanel * panel)
{
tComponent * aux;
char buffer[4];

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPmouse");
 if (aux!=NULL){
  if (proyectXmlProperties.useMouse)
   COMPONENT_setValue(aux,"1");
 else
   COMPONENT_setValue(aux,NULL);
 }

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPcolor");
 if (aux!=NULL){
  if (proyectXmlProperties.useColor) COMPONENT_setValue(aux,"1");
    else COMPONENT_setValue(aux,NULL);
 }

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPerror");
 if (aux!=NULL){
  if (proyectXmlProperties.printErrors) COMPONENT_setValue(aux,"1");
    else COMPONENT_setValue(aux,NULL);
 }

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPferror");
 if (aux!=NULL)
   COMPONENT_setValue(aux,proyectXmlProperties.ferrors);

 aux = (tComponent *)LVIEW_getElement("frmPProyect","chCheck");
 if (aux!=NULL){
   sprintf(buffer,"%c",proyectXmlProperties.chCheck);
   COMPONENT_setValue(aux,buffer);
 }  

 aux = (tComponent *)LVIEW_getElement("frmPProyect","chisCheck");
 if (aux!=NULL){
   sprintf(buffer,"%c",proyectXmlProperties.chIsCheck);
   COMPONENT_setValue(aux,buffer);
 }  

 aux = (tComponent *)LVIEW_getElement("frmPProyect","chnoCheck");
 if (aux!=NULL){
   sprintf(buffer,"%c",proyectXmlProperties.chNoCheck);
   COMPONENT_setValue(aux,buffer);
 }  

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPup");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[0]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPdw");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[1]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPlf");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[2]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPrg");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[3]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPcul");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[4]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPcur");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[5]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPcdl");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[6]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPcdr");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.borders[7]);
   COMPONENT_setValue(aux,buffer);
 }

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPup");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[0]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPdw");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[1]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPlf");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[2]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPrg");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[3]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPcul");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[4]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPcur");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[5]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPcdl");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[6]);
   COMPONENT_setValue(aux,buffer);
 }
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmSPcdr");
 if (aux!=NULL){
   sprintf(buffer,"%c",(char)proyectXmlProperties.sborders[7]);
   COMPONENT_setValue(aux,buffer);
 }

 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPmainf");
 if (aux!=NULL)
   COMPONENT_setValue(aux,proyectXmlProperties.mainFunction);
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPendf");
   COMPONENT_setValue(aux,proyectXmlProperties.endFunction);
 aux = (tComponent *)LVIEW_getElement("frmPProyect","frmPPinit");
   COMPONENT_setValue(aux,proyectXmlProperties.initView);
}

void PROY_loadSave(tPanel * panel)
{
tComponent * aux;

 aux = (tComponent *)LVIEW_getElement("frmSave","frmSPname");
 if (aux!=NULL)
  COMPONENT_setValue(aux,theProyect.fileName);
}

trAction* PROY_new (tComponent * component,int key){
static trAction action;
char * auxNombre;
tComponent * aux;
 
  initAction(action);
  if (strcmp(theProyect.name,"")!=0){
    MSG_create(M_ERROR,CENTER_VIEW," Close the proyect \n before open a new one ");
    action.error=1;
    return &action;
  }
  aux = (tComponent *)LVIEW_getElement(NULL,"frmNPname");
  if (aux == NULL){
     MSG_create(M_ERROR,CENTER_VIEW," Can't get NewProyect name ");
     action.error=1;
     return &action;
  }
  auxNombre = COMPONENT_getValue(aux);
  if (auxNombre ==NULL || strcmp(auxNombre,"")==0){
     MSG_create(M_ERROR,CENTER_VIEW," Can't get NewProyect name ");
     action.error=1;
     return &action;
  }

  PROY_resetXmlProperties();
  PROY_resetXmlProyect();
  FUNC_reset();
  COLOR_reset();
  EDF_reset();
  KEYMAP_reset();
  MSG_reset();
  COMP_reset();
  PANEL_reset();
  TABLE_reset();
  EDIT_reset();
  VIEW_reset();

  strncpy(theProyect.name,auxNombre,sizeof(theProyect.name)-1);

  aux = (tComponent *)LVIEW_getElement(NULL,"frmNPdescripcion");
  if (aux == NULL)
     MSG_create(M_ERROR,CENTER_VIEW," Can't get NewProyect description ");
    else 
     strncpy(theProyect.description,COMPONENT_getValue(aux),sizeof(theProyect.description)-1);
  strcpy(theProyect.fileName,theProyect.name);
  strcat(theProyect.fileName,".xml");
  if (access(theProyect.fileName, F_OK) == 0) {
       MSG_create(M_ERROR,CENTER_VIEW," File <%s> exists use Open",theProyect.fileName);
       action.error=1;
       strcpy(theProyect.name,"");
       strcpy(theProyect.description,"");
       strcpy(theProyect.fileName,"");
     return &action;
  } 
  theProyect.exist=0;

  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPnew");
  COMPONENT_display(aux,DIS_HIDDEN);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPopen");
  COMPONENT_display(aux,DIS_HIDDEN);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPclose");
  COMPONENT_display(aux,DIS_NORMAL);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPsave");
  COMPONENT_display(aux,DIS_NORMAL);


  return &action;
}

trAction* PROY_editMenu (tComponent * component,int key,int Fn){
static trAction action;
  
  initAction(action);
  switch (Fn)
  {
    case 2:
      return PROY_editOpen (component,key);
		break;
    case 3:
      return PROY_editSave (component,key);
		break;
    case 4:
      return PROY_editClose (component,key);
		break;
    default:
      return &action;
  }
}

trAction* PROY_editPanel (tEdit * edit,int key,int Fn){
static trAction  action;
tComponent * auxC;
  initAction(action);
  switch (Fn)
  {
    case 3:
       if (manualEdit != 1) {
        MSG_create(M_ERROR,CENTER_VIEW,"Nothing to save");
        action.error=1;
       }
       if (EDIT_saveFile(edit) != 0) {
         MSG_create(M_ERROR,CENTER_VIEW,"Error saving the file");
         action.error=1;
       }
       MSG_create(M_INFO,CENTER_VIEW,"File save");
       action.made=1;
       break;
    case 4:
       manualEdit=0;
       auxC = (tComponent *)LVIEW_getElement("mnEdit","open");
       COMPONENT_display(auxC,DIS_NORMAL);
       auxC = (tComponent *)LVIEW_getElement("mnEdit","save");
       COMPONENT_display(auxC,DIS_HIDDEN);
      break;
    default:
      break;
  }
  return &action;
}

trAction* PROY_editOpen (tComponent * component,int key){
static trAction action;
char buffer[100];
tEdit * auxE;
tComponent * auxC;

  initAction(action);

  if (strcmp(theProyect.name,"")==0){
   MSG_create(M_ERROR,CENTER_VIEW,"Open or create a proyect try to edit");
   action.error=1;
   return &action;
  }
  sprintf(buffer,"%s.xml",theProyect.name);
  if (MSG_create(M_WARNING,CENTER_VIEW,"OK to Save Current Work before open Proyect File") == 1) {
   if (WXML_print(buffer) != 0) {
     MSG_create(M_ERROR,CENTER_VIEW,"Error saving current proyect");
     action.error=1;
     return &action;
   }
  }

  auxE = (tEdit *)LVIEW_getElement("XmlFile",NULL);
  if (EDIT_loadFile(auxE,buffer,300,50) != 0) {
     MSG_create(M_ERROR,CENTER_VIEW,"Error loading <%s> file",buffer);
     action.error=1;
     return &action;
  }
  
  COMPONENT_display(component,DIS_HIDDEN);
  auxC = (tComponent *)LVIEW_getElement(NULL,"save");
  COMPONENT_display(auxC,DIS_NORMAL);

  manualEdit=1;
  return &action;
}

trAction* PROY_editSave (tComponent * component,int key){
static trAction action;
tEdit * auxE;

  initAction(action);
  if (manualEdit != 1) {
   MSG_create(M_ERROR,CENTER_VIEW,"Nothing to save");
   action.error=1;
  }
  auxE = (tEdit *)LVIEW_getElement("XmlFile",NULL);
  if (EDIT_saveFile(auxE) != 0) {
   MSG_create(M_ERROR,CENTER_VIEW,"Error saving the file");
   action.error=1;
  }
  MSG_create(M_INFO,CENTER_VIEW,"File save");
  return &action;
}

trAction* PROY_editClose (tComponent * component,int key){
static trAction action;
tComponent * auxC;

  initAction(action);
  manualEdit=0;
  auxC = (tComponent *)LVIEW_getElement(NULL,"open");
  COMPONENT_display(auxC,DIS_NORMAL);
  auxC = (tComponent *)LVIEW_getElement(NULL,"save");
  COMPONENT_display(auxC,DIS_HIDDEN);

  return &action;
}


trAction* PROY_open (tComponent * component,int key){
static trAction action;
tComponent * aux;
char fileName[MAX_NAME_FILE];

  initAction(action);

  if (strcmp(theProyect.name,"")!=0){
   MSG_create(M_ERROR,CENTER_VIEW,"Close proyect before open a new one");
   action.error=1;
   return &action;
  }

  aux = (tComponent *)LVIEW_getElement(NULL,"frmOPname");
  if (aux == NULL){
    MSG_create(M_ERROR,CENTER_VIEW," Can't get Proyect name ");
    action.error=1;
    return &action;
  }

  sprintf(fileName,"%s.xml",COMPONENT_getValue(aux));
  if (access(fileName, W_OK) != 0) {
    MSG_create(M_ERROR,CENTER_VIEW," Can't get write acess to file <%s>",fileName);
    strcpy(theProyect.fileName,"");
    action.error=1;
    return &action;
  }

  if (PARSER_loadXmlFile(fileName,1) == 0)
  {
    memcpy(&theProyect,PARSER_getProyect(),sizeof(theProyect));
    strncpy(theProyect.fileName,fileName,sizeof(theProyect.fileName)-2);
    memcpy(&proyectXmlProperties,PARSER_getProperties(),sizeof(proyectXmlProperties));
    FUNC_set(PARSER_getCabFunciones(), PARSER_getUltFunciones());
    COLOR_set(PARSER_getCabColors(),PARSER_getUltColors());
    EDF_set(PARSER_getCabCEdFunctions(),PARSER_getUltCEdFunctions());
    KEYMAP_set(PARSER_getCabKeymaps(),PARSER_getUltKeymaps());
    MSG_set(PARSER_getMsgs());
    PANEL_set(PARSER_getCabPanels(),PARSER_getUltPanels());
    COMP_set(PARSER_getCabComponents(),PARSER_getUltComponents());
    TABLE_set(PARSER_getCabTables(),PARSER_getUltTables());
    EDIT_set(PARSER_getCabEdits(),PARSER_getUltEdits());
  }
  else{
    MSG_create(M_ERROR,CENTER_VIEW," Error parsing the file ");
    strcpy(theProyect.fileName,"");
    action.error=1;
    return &action;
  }

  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPnew");
  COMPONENT_display(aux,DIS_HIDDEN);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPopen");
  COMPONENT_display(aux,DIS_HIDDEN);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPclose");
  COMPONENT_display(aux,DIS_NORMAL);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPsave");
  COMPONENT_display(aux,DIS_NORMAL);

  return &action;
}

trAction* PROY_close (tComponent * component,int key){
static trAction action;
tComponent * aux;

  initAction(action);

  if (MSG_create(M_WARNING,CENTER_TERMINAL,"Save before close ?")==0){
    WXML_print(theProyect.fileName);
  }

  PROY_resetXmlProperties();
  PROY_resetXmlProyect();
  FUNC_reset();
  COLOR_reset();
  EDF_reset();
  KEYMAP_reset();
  MSG_reset();
  PANEL_reset();
  COMP_reset();
  TABLE_reset();
  EDIT_reset();
  VIEW_reset();

  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPnew");
  COMPONENT_display(aux,DIS_NORMAL);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPopen");
  COMPONENT_display(aux,DIS_NORMAL);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPclose");
  COMPONENT_display(aux,DIS_HIDDEN);
  aux = (tComponent *)LVIEW_getElement("mnProyect","mnPsave");
  COMPONENT_display(aux,DIS_HIDDEN);
  return &action;
}

trAction* PROY_save (tComponent * component,int key){
static trAction action;
tComponent * aux;

  initAction(action);
  aux = (tComponent *)LVIEW_getElement(NULL,"frmSPname");
  if (aux != NULL)
   WXML_print(COMPONENT_getValue(aux));

  return &action;
}

static void PROY_resetXmlProyect()
{
  strcpy(theProyect.name,"");
  strcpy(theProyect.description,"");
  strcpy(theProyect.fileName,"");
  theProyect.exist=0;
}

static void PROY_resetXmlProperties(){
  memcpy(&proyectXmlProperties,&proyectInitXmlProperties,sizeof(tXmlProp));
}

trAction* PROY_test (tComponent * component,int key){
tComponent * aux;
static trAction action; 

 initAction(action);

  if (testTerminal.screen != NULL){
   set_term(testTerminal.screen);
   endwin();
   set_term(scrSTD);
  }

  aux = (tComponent *)LVIEW_getElement("fttest","ttytest");
  if (aux!=NULL)
   strcpy(testTerminal.tty,COMPONENT_getValue(aux));
  else {
    MSG_create(M_ERROR,CENTER_VIEW,"Can't find fttest/ttytest ");
    action.error =1;
  }
    

  aux = (tComponent *)LVIEW_getElement("fttest","term");
  if (aux!=NULL)
   strcpy(testTerminal.term,COMPONENT_getValue(aux));
  else {
    MSG_create(M_ERROR,CENTER_VIEW,"Can't find fttest/term ");
    action.error =1;
  }

  testTerminal.fd= fopen(testTerminal.tty,"r+");
  if (testTerminal.fd != NULL)
   testTerminal.screen = newterm(testTerminal.term,
			testTerminal.fd,testTerminal.fd);

  if (testTerminal.screen == NULL)
  {
    MSG_create(M_ERROR,CENTER_VIEW,"Can't open TTY\n Connect to the host as the same user\n use the result of tty command here");
    action.error =1;
  }

 set_term(scrSTD);

 return &action;
}


void PROY_replace(tComponent *  component){
  COMPONENT_editMode(component,Replace);
return;
}

SCREEN * PROY_testScreen()
{
  return testTerminal.screen;
}

char * PROY_getTestTerm()
{
  if (testTerminal.fd == NULL) return NULL;
  return testTerminal.term;
}

char * PROY_getTestTty()
{
  if (testTerminal.fd == NULL) return NULL;
  return testTerminal.tty;
}


tXmlProyectPtr PROY_getProyect(){
  return &theProyect;
}

tXmlPropPtr PROY_getProperties(){
  return &proyectXmlProperties;
}

int PROY_isColor(){
  return  proyectXmlProperties.useColor;
}

trAction* PROY_checkOpen (tComponent * component,int key){
static trAction action;

 initAction(action);
 if (strcmp(theProyect.name,"")==0){
   MSG_create(M_INFO,CENTER_TERMINAL,"Open or create a proyect ");
   action.error=1;
   return &action;
 }

 return &action;
}

trAction* PROY_exit (tComponent * component,int key){
static trAction action;

 initAction(action);
 if (strcmp(theProyect.name,"")!=0){
  if (MSG_create(M_WARNING,CENTER_TERMINAL,"Save before close ?")==0){
    WXML_print(theProyect.fileName);
  }
 }
 if (testTerminal.screen != NULL){
   set_term(testTerminal.screen);
   endwin();
   set_term(scrSTD);
 }

 return &action;
}


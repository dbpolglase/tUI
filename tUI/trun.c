#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

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
#include <tedf.h>
#include <tproyect.h>
#include <tcolor.h>
#include <tview.h>
#include <tcomp.h>
#include <tmsg.h>
#include <tprintXml.h>

extern SCREEN * scrSTD;
extern tChAttr miColor1Inv;
extern tChAttr miColor3;
extern tChAttr miColor7;

static void RUN_checkMsgs(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult);
static void RUN_checkComp(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult);
static void RUN_checkPanel(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult);
static void RUN_checkTable(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult);
static void RUN_checkEdit(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult);
static int RUN_checkText(tDim * dimension, tXmlText * text);
static int RUN_checkMoves(char * name, tXmlMove * moves,
			  tXmlCompPanel * panelComp, tEdit * auxResult);
static int RUN_checkMove(char * name, char  * move,tXmlCompPanel * panelComp,
		              tEdit * auxResult,char *errorText);

static int RUN_edfNull(char * edf);

void RUN_check () {
tComponent * auxC;
char auxdata[200];
tXmlPropPtr auxProperties;
tXmlMapKeyPtr auxKeymap;
tEdit * auxResult;
tXmlcolorPtr auxColor;
tXmlCEdFunction * auxEdf;
int error,aviso;
tXmlProyectPtr auxProy;

 auxProy=PROY_getProyect();

 if (strcmp(auxProy->name,"")==0){
   MSG_create(M_WARNING,CENTER_VIEW,"Open or create a proyect ");
   return; 
 }


 auxResult = (tEdit *)LVIEW_searchView("CheckFile")->view.edit;
 TEXT_free(auxResult->text);
 if (auxResult->text == NULL)
  auxResult->text = TEXT_newEdit(100,50,1);

 auxColor =  COLOR_getXml();

 error = aviso = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","prop");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 auxProperties =PROY_getProperties();
 if (strcmp(auxProperties->initView,"")==0 
  || strcmp(auxProperties->initView,"view:component") == 0) {
   error=1;
   TEXT_addEditData(auxResult->text,"Not initView defined");
 }
 if (auxProperties->useColor && auxColor==NULL){
   error=1;
   TEXT_addEditData(auxResult->text,"Use color set and not colors defined");
 }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}

 COMPONENT_refresh(auxC);
 
 error = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","keymap");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 auxKeymap = KEYM_get();
 while (auxKeymap != NULL){
    if (!COMP_searchUseKeymap(auxKeymap->name)) {
     sprintf(auxdata," Keymap <%s> not use ",auxKeymap->name);
     TEXT_addEditData(auxResult->text,auxdata);
     aviso=1;
    }
   auxKeymap = auxKeymap->siguiente;
 }
 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
 COMPONENT_refresh(auxC);

 error = aviso = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","edf");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 auxEdf = EDF_get();
 while (auxEdf != NULL){
    if (!COMP_searchUseEdf(auxEdf->name)) {
     sprintf(auxdata," Edit Function <%s> not use ",auxEdf->name);
     TEXT_addEditData(auxResult->text,auxdata);
     aviso=1;
    }
   auxEdf = auxEdf->siguiente;
 }
 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
 COMPONENT_refresh(auxC);

 error = aviso = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","color");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 while (auxColor != NULL){
    if (!COMP_searchUseColor(auxColor->name) &&
	!VIEW_useColor(auxColor->name)) {
     sprintf(auxdata,"Color <%s> not use ",auxColor->name);
     TEXT_addEditData(auxResult->text,auxdata);
     aviso=1;
    }
   auxColor = auxColor->siguiente;
 }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
 COMPONENT_refresh(auxC);

 auxColor =  COLOR_getXml();

 RUN_checkMsgs(auxColor,auxProperties, auxResult);
 RUN_checkComp(auxColor,auxProperties,auxResult);
 RUN_checkPanel(auxColor,auxProperties,auxResult);
 RUN_checkTable(auxColor,auxProperties,auxResult);
 RUN_checkEdit(auxColor,auxProperties,auxResult);

}

static void RUN_checkMsgs(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult)
{
tComponent * auxC;
int error,aviso;
tXmlMsgs * msgs;

 error = aviso = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","msgs");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 msgs=MSG_get();

 if (msgs != NULL){
   if (msgs->msg[M_INFO] != NULL){
     if (msgs->msg[M_INFO]->nroButtons > 2) {
      error =1;
      TEXT_addEditData(auxResult->text,"Nro. Buttons of INFO MSG wrong");
     }
     if (strcmp(msgs->msg[M_INFO]->title,"")==0){
      error =1;
      TEXT_addEditData(auxResult->text,"INFO MSG has no title ");
     }
     if (msgs->msg[M_INFO]->nroButtons ==1 &&
            strcmp(msgs->msg[M_INFO]->ButtonText1,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"INFO MSG button 1 has no text ");
     }
     if (msgs->msg[M_INFO]->nroButtons ==2 &&
            strcmp(msgs->msg[M_INFO]->ButtonText2,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"INFO MSG button 2 has no text ");
     }
     if (!strcmp(msgs->msg[M_INFO]->color,"")==0) {
      if (COLOR_searchColor(msgs->msg[M_INFO]->color) == NULL) {
       error =1;
       TEXT_addEditData(auxResult->text,"INFO MSG color not found ");
      }
     }
   }
   if (msgs->msg[M_WARNING] != NULL){
     if (msgs->msg[M_WARNING]->nroButtons > 2) {
      error =1;
      TEXT_addEditData(auxResult->text,"Nro. Buttons of WARNING MSG wrong");
     }
     if (strcmp(msgs->msg[M_WARNING]->title,"")==0){
      error =1;
      TEXT_addEditData(auxResult->text,"WARNING MSG has no title ");
     }
     if (msgs->msg[M_WARNING]->nroButtons ==1 &&
            strcmp(msgs->msg[M_WARNING]->ButtonText1,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"WARNING MSG button 1 has no text ");
     }
     if (msgs->msg[M_WARNING]->nroButtons ==2 &&
            strcmp(msgs->msg[M_WARNING]->ButtonText2,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"WARNING MSG button 2 has no text ");
     }
     if (!strcmp(msgs->msg[M_WARNING]->color,"")==0) {
      if (COLOR_searchColor(msgs->msg[M_WARNING]->color) == NULL) {
       error =1;
       TEXT_addEditData(auxResult->text,"WARNING MSG color not found ");
      }
     }
   }
   if (msgs->msg[M_ERROR] != NULL){
     if (msgs->msg[M_ERROR]->nroButtons > 2) {
      error =1;
      TEXT_addEditData(auxResult->text,"Nro. Buttons of ERROR MSG wrong");
     }
     if (strcmp(msgs->msg[M_ERROR]->title,"")==0){
      error =1;
      TEXT_addEditData(auxResult->text,"ERROR MSG has no title ");
     }
     if (msgs->msg[M_ERROR]->nroButtons ==1 &&
            strcmp(msgs->msg[M_ERROR]->ButtonText1,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"ERROR MSG button 1 has no text ");
     }
     if (msgs->msg[M_ERROR]->nroButtons ==2 &&
            strcmp(msgs->msg[M_ERROR]->ButtonText2,"")==0) {
      error =1;
      TEXT_addEditData(auxResult->text,"ERROR MSG button 2 has no text ");
     }
     if (!strcmp(msgs->msg[M_ERROR]->color,"")==0) {
      if (COLOR_searchColor(msgs->msg[M_ERROR]->color) == NULL) {
       error =1;
       TEXT_addEditData(auxResult->text,"ERROR MSG color not found ");
      }
     }
   }
  }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
 COMPONENT_refresh(auxC);

}

static void RUN_checkComp(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult)
{
tComponent * auxC;
char auxdata[200];
int error,aviso,err_dim;
tXmlPanelPtr auxPanel;
tXmlComponentPtr auxComp;
tXmlCompPanel * auxElements;

 error = aviso = 0;
 auxC = (tComponent *)LVIEW_getElement("frmCheck","comps");
 COMPONENT_setValue(auxC,"checking");
 COMPONENT_refresh(auxC);
 auxComp =  COMP_get();
 while (auxComp != NULL){
   if (strcmp(auxComp->name,"")==0) {
       error =1;
       TEXT_addEditData(auxResult->text,"Component without name ");
   }
   if (strcmp(auxComp->panelName,"")==0) {
       error =1;
       sprintf(auxdata,"Orphan component <%s> ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
   }
   if (strcmp(auxComp->visual.color,"")==0 &&
       auxProperties->useColor) {
       aviso =1;
       sprintf(auxdata,"no color for component <%s> ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
   } else {
      if (strcmp(auxComp->visual.color,"noColor") != 0 && 
          COLOR_searchColor(auxComp->visual.color) == NULL) {
       error =1;
       sprintf(auxdata,"color for component <%s> not found ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
      }
   }
   if (strcmp(auxComp->mapkey,"")!=0) {
     if (KEYM_search(auxComp->mapkey) == NULL) {
       error =1;
       sprintf(auxdata,"mapkey for component <%s> not found ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
   }
   if (auxComp->type == C_LSBUTTON){
     if (strcmp(auxComp->move.up,"") != 0 || strcmp(auxComp->move.down,"") != 0)
     {
       aviso =1;
       sprintf(auxdata,"component <%s> type List Button with up/down moves ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
   }
   if (auxComp->type == C_CKBUTTON){
     if (strcmp(auxComp->move.enter,"") != 0)
     {
       aviso =1;
       sprintf(auxdata,"component <%s> type check Button with enter moves ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
   }
   if (auxComp->type == C_EDIT){
     if (strcmp(auxComp->move.left,"") != 0 || strcmp(auxComp->move.right,"") != 0)
     {
       aviso =1;
       sprintf(auxdata,"component <%s> type field with left/right moves ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
   }

   if (RUN_edfNull(auxComp->editMode.editFunction)) {
     if (EDF_search(auxComp->editMode.editFunction) == NULL) {
       error =1;
       sprintf(auxdata,"editFunction for component <%s> not found ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
   }

   auxPanel = (tXmlPanelPtr) auxComp->panel;
   if (auxPanel != NULL){
     if (auxPanel->visual.dimension.border &&
         (auxComp->visual.dimension.y == 0 ||
          auxComp->visual.dimension.x == 0 ))
     {
       sprintf(auxdata,"component <%s> dimension  x/y over panel border",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
       error=1;
     }
     if ((auxComp->visual.dimension.ancho + auxComp->visual.dimension.x) 
         > (auxPanel->visual.dimension.ancho - auxPanel->visual.dimension.border))
     {
       sprintf(auxdata,"Witdh dimension of component <%s> exceed panel dimension ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if ((auxComp->visual.dimension.alto + auxComp->visual.dimension.y) 
         > (auxPanel->visual.dimension.alto - auxPanel->visual.dimension.border))
     {
       sprintf(auxdata,"High dimension of component <%s> exceed panel dimension ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
       error=1;
     }

    if (RUN_checkText(&auxComp->visual.dimension,auxComp->text)){
       sprintf(auxdata,"Text exceed component <%s> dimension ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
       error=1;
    }

    if ( auxComp->visual.visible != DIS_HIDDEN &&
           auxComp->visual.visible != DIS_OPEN ){
       err_dim=0;
       auxElements=auxPanel->elements;
       while (auxElements != NULL){
         if (auxElements->componente != auxComp &&
           auxElements->componente->visual.visible != DIS_HIDDEN &&
           auxElements->componente->visual.visible != DIS_OPEN ){
         if (auxElements->componente->visual.dimension.x > auxComp->visual.dimension.x && auxElements->componente->visual.dimension.x < (auxComp->visual.dimension.x + auxComp->visual.dimension.ancho) &&
           (auxElements->componente->visual.dimension.y > auxComp->visual.dimension.y && auxElements->componente->visual.dimension.y < (auxComp->visual.dimension.y + auxComp->visual.dimension.alto)))
        {
          err_dim=1; aviso=1;
          sprintf(auxdata,"component <%s> overlapping component <%s>",auxComp->name,auxElements->componente->name);
          TEXT_addEditData(auxResult->text,auxdata);
        }
        if (auxElements->componente->visual.dimension.x > auxComp->visual.dimension.x && auxElements->componente->visual.dimension.x < (auxComp->visual.dimension.x + auxComp->visual.dimension.ancho) &&
           ((auxElements->componente->visual.dimension.y+auxElements->componente->visual.dimension.alto) > auxComp->visual.dimension.y && (auxElements->componente->visual.dimension.y + auxElements->componente->visual.dimension.alto) < (auxComp->visual.dimension.y + auxComp->visual.dimension.alto)))
        {
          if (!err_dim){
            sprintf(auxdata,"component <%s> overlapping component <%s>",auxComp->name,auxElements->componente->name);
            TEXT_addEditData(auxResult->text,auxdata);
            aviso=1; err_dim=1;
          }
        }
        if (auxElements->componente->visual.dimension.x > auxComp->visual.dimension.x && auxElements->componente->visual.dimension.x < (auxComp->visual.dimension.x + auxComp->visual.dimension.ancho) &&
           ((auxElements->componente->visual.dimension.y+auxElements->componente->visual.dimension.alto) > auxComp->visual.dimension.y && (auxElements->componente->visual.dimension.y + auxElements->componente->visual.dimension.alto) < (auxComp->visual.dimension.y + auxComp->visual.dimension.alto)))
        {
          if (!err_dim){
            sprintf(auxdata,"component <%s> overlapping component <%s>",auxComp->name,auxElements->componente->name);
            TEXT_addEditData(auxResult->text,auxdata);
            aviso=1; err_dim=1;
          }
        }
        if ((auxElements->componente->visual.dimension.x+auxElements->componente->visual.dimension.ancho) > auxComp->visual.dimension.x && (auxElements->componente->visual.dimension.x+auxElements->componente->visual.dimension.ancho) < (auxComp->visual.dimension.x + auxComp->visual.dimension.ancho) &&
           ((auxElements->componente->visual.dimension.y+auxElements->componente->visual.dimension.alto) > auxComp->visual.dimension.y && (auxElements->componente->visual.dimension.y + auxElements->componente->visual.dimension.alto) < (auxComp->visual.dimension.y + auxComp->visual.dimension.alto)))
        {
          if (!err_dim){
            sprintf(auxdata,"component <%s> overlapping component <%s>",auxComp->name,auxElements->componente->name);
            TEXT_addEditData(auxResult->text,auxdata);
            aviso=1; err_dim=1;
          }
        }
       }
       auxElements = auxElements->siguiente;
      }
     }
     auxElements=auxPanel->elements;
     RUN_checkMoves(auxComp->name, &auxComp->move,auxElements,auxResult);
   }
   else {
       sprintf(auxdata,"component <%s> orphand panel ",auxComp->name);
       TEXT_addEditData(auxResult->text,auxdata);
       error=1;
   }

   auxComp = auxComp->siguiente;
  }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
  COMPONENT_refresh(auxC);

}

static void RUN_checkPanel(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult)
{
tComponent * auxC;
char auxdata[200];
int error,aviso;
tXmlPanelPtr auxPanel;

  error = aviso = 0;
  auxC = (tComponent *)LVIEW_getElement("frmCheck","panels");
  COMPONENT_setValue(auxC,"checking");
  COMPONENT_refresh(auxC);
  auxPanel = PANEL_get();
  while (auxPanel != NULL)
  {
    if (VIEW_duplicate(auxPanel->id,NULL) > 1){
      error =1;
      sprintf(auxdata,"Panel id <%d> duplicate ",auxPanel->id);
      TEXT_addEditData(auxResult->text,auxdata);
    }

    if (strcmp(auxPanel->name,"")==0) {
       error =1;
       TEXT_addEditData(auxResult->text,"Panel without name ");
    }

    if (VIEW_duplicate(-1,auxPanel->name) > 1){
      error =1;
      sprintf(auxdata,"Panel name <%s> duplicate ",auxPanel->name);
      TEXT_addEditData(auxResult->text,auxdata);
    }

    if (strcmp(auxPanel->visual.color,"")==0 &&
       auxProperties->useColor) {
       aviso =1;
       sprintf(auxdata,"no color for panel <%s> ",auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
    } else {
      if (strcmp(auxPanel->visual.color,"noColor") != 0 && COLOR_searchColor(auxPanel->visual.color) == NULL) {
       error =1;
       sprintf(auxdata,"color for panel <%s> not found ",auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
      }
    }
    if (auxPanel->visual.dimension.x > 80 || auxPanel->visual.dimension.y > 24) 
    {
       aviso =1;
       sprintf(auxdata,"x-y position (%d,%d) for panel <%s> must be wrong ",
		auxPanel->visual.dimension.x,auxPanel->visual.dimension.y,auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if (auxPanel->visual.dimension.ancho > 80 || auxPanel->visual.dimension.alto > 24) 
     {
       aviso =1;
       sprintf(auxdata,"Width-High (%d,%d) for panel <%s> must be wrong ",
		auxPanel->visual.dimension.ancho,auxPanel->visual.dimension.alto,auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if ((auxPanel->visual.dimension.x + auxPanel->visual.dimension.ancho) > 80 || (auxPanel->visual.dimension.y + auxPanel->visual.dimension.alto) > 24) 
     {
       aviso =1;
       sprintf(auxdata,"End position (%d,%d) for panel <%s> must be wrong ",
		(auxPanel->visual.dimension.x + auxPanel->visual.dimension.ancho),
		(auxPanel->visual.dimension.y + auxPanel->visual.dimension.alto),auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if (auxPanel->elements == NULL){
       aviso =1;
       sprintf(auxdata,"Panel <%s> has not components ", auxPanel->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     RUN_checkMoves(auxPanel->name, &auxPanel->move,NULL,auxResult);

    auxPanel = auxPanel->siguiente;
  }
 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
  COMPONENT_refresh(auxC);
}


static void RUN_checkTable(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult)
{
tComponent * auxC;
char auxdata[200];
int error,aviso;
tXmlTablePtr auxTable;

  error = aviso = 0;
  auxC = (tComponent *)LVIEW_getElement("frmCheck","tables");
  COMPONENT_setValue(auxC,"checking");
  COMPONENT_refresh(auxC);
  auxTable = TABLE_get();
  while (auxTable != NULL)
  {
    if (VIEW_duplicate(auxTable->id,NULL) > 1){
      error =1;
      sprintf(auxdata,"Table id <%d> duplicate ",auxTable->id);
      TEXT_addEditData(auxResult->text,auxdata);
    }
    if (strcmp(auxTable->name,"")==0) {
       error =1;
       TEXT_addEditData(auxResult->text,"Table without name ");
    }
    if (VIEW_duplicate(-1,auxTable->name) > 1){
       error =1;
       sprintf(auxdata,"Table name <%s> duplicate ",auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
    }
    if (strcmp(auxTable->visual.color,"")==0 &&
       auxProperties->useColor) {
       aviso =1;
       sprintf(auxdata,"no color for table <%s> ",auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
    } else {
      if (strcmp(auxTable->visual.color,"noColor") != 0 && COLOR_searchColor(auxTable->visual.color) == NULL) {
       error =1;
       sprintf(auxdata,"color for table <%s> not found ",auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
      }
    }
    if (auxTable->visual.dimension.x > 80 || auxTable->visual.dimension.y > 24) 
    {
       aviso =1;
       sprintf(auxdata,"x-y position (%d,%d) for table <%s> must be wrong ",
		auxTable->visual.dimension.x,auxTable->visual.dimension.y,auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if (auxTable->visual.dimension.ancho > 80 || auxTable->visual.dimension.alto > 24) 
     {
       aviso =1;
       sprintf(auxdata,"Width-High (%d,%d) for table <%s> must be wrong ",
		auxTable->visual.dimension.ancho,auxTable->visual.dimension.alto,auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if ((auxTable->visual.dimension.x + auxTable->visual.dimension.ancho) > 80 || (auxTable->visual.dimension.y + auxTable->visual.dimension.alto) > 24) 
     {
       aviso =1;
       sprintf(auxdata,"End position (%d,%d) for table <%s> must be wrong ",
		(auxTable->visual.dimension.x + auxTable->visual.dimension.ancho),
		(auxTable->visual.dimension.y + auxTable->visual.dimension.alto),auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if (auxTable->elements == NULL){
       aviso =1;
       sprintf(auxdata,"Table <%s> has not columns ", auxTable->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     RUN_checkMoves(auxTable->name, &auxTable->move,NULL,auxResult);

    auxTable = auxTable->siguiente;
  }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
  COMPONENT_refresh(auxC);
}


static void RUN_checkEdit(tXmlcolorPtr auxColor,tXmlPropPtr auxProperties,
                           tEdit * auxResult)
{
tComponent * auxC;
char auxdata[200];
int error,aviso;
tXmlEditPtr  auxEdit;

  error = aviso = 0;
  auxC = (tComponent *)LVIEW_getElement("frmCheck","edit");
  COMPONENT_setValue(auxC,"checking");
  COMPONENT_refresh(auxC);
  auxEdit = EDIT_get();
  while (auxEdit != NULL)
  {
    if (VIEW_duplicate(auxEdit->id,NULL) > 1){
      error =1;
      sprintf(auxdata,"EditView id <%d> duplicate ",auxEdit->id);
      TEXT_addEditData(auxResult->text,auxdata);
    }
    if (strcmp(auxEdit->name,"")==0) {
       error =1;
       TEXT_addEditData(auxResult->text,"Edit View without name ");
    }
    if (VIEW_duplicate(-1,auxEdit->name) > 1){
       error =1;
       sprintf(auxdata,"EditView name <%s> duplicate ",auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
    }
    if (strcmp(auxEdit->visual.color,"")==0 &&
       auxProperties->useColor) {
       aviso =1;
       sprintf(auxdata,"no color for edit view <%s> ",auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
    } else {
      if (strcmp(auxEdit->visual.color,"noColor")!=0 
			&& COLOR_searchColor(auxEdit->visual.color) == NULL) {
       error =1;
       sprintf(auxdata,"color for edit view <%s> not found ",auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
      }
    }
    if (auxEdit->visual.dimension.x > 80 || auxEdit->visual.dimension.y > 24) 
    {
       aviso =1;
       sprintf(auxdata,"x-y position (%d,%d) for edit view <%s> must be wrong ",
		auxEdit->visual.dimension.x,auxEdit->visual.dimension.y,auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if (auxEdit->visual.dimension.ancho > 80 || auxEdit->visual.dimension.alto > 24) 
     {
       aviso =1;
       sprintf(auxdata,"Width-High (%d,%d) for edit view <%s> must be wrong ",
		auxEdit->visual.dimension.ancho,auxEdit->visual.dimension.alto,auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     if ((auxEdit->visual.dimension.x + auxEdit->visual.dimension.ancho) > 80 || (auxEdit->visual.dimension.y + auxEdit->visual.dimension.alto) > 24) 
     {
       aviso =1;
       sprintf(auxdata,"End position (%d,%d) for edit view <%s> must be wrong ",
		(auxEdit->visual.dimension.x + auxEdit->visual.dimension.ancho),
		(auxEdit->visual.dimension.y + auxEdit->visual.dimension.alto),auxEdit->name);
       TEXT_addEditData(auxResult->text,auxdata);
     }
     RUN_checkMoves(auxEdit->name, &auxEdit->move,NULL,auxResult);

    auxEdit = auxEdit->siguiente;
  }

 if (error) {
  COMPONENT_changeColor(auxC, &miColor3); COMPONENT_setValue(auxC,"error");}
 else {if (aviso) { COMPONENT_changeColor(auxC, &miColor7); COMPONENT_setValue(auxC,"warning"); }
       else  {COMPONENT_changeColor(auxC, &miColor1Inv); COMPONENT_setValue(auxC,"done");}}
  COMPONENT_refresh(auxC);
}

static int RUN_edfNull(char * edf)
{
  if (strcmp(edf,"") == 0 )  return 0;
  if (strcmp(edf,"none") == 0 )  return 0;
  if (strcmp(edf,"numeric") == 0 )  return 0;
  if (strcmp(edf,"alfnumeric") == 0 )  return 0;
  if (strcmp(edf,"7ascii") == 0 )  return 0;
  if (strcmp(edf,"upper") == 0 )  return 0;
  if (strcmp(edf,"lower") == 0 )  return 0;
  return 1;
}

static int RUN_checkMoves(char * name, tXmlMove * moves,
			  tXmlCompPanel * panelComp, tEdit * auxResult)
{
 int i,error=0;

  if (strcmp(moves->enter,"") != 0)
    if (RUN_checkMove(name,moves->enter,panelComp,auxResult,"ENTER")) error=1;
  if (strcmp(moves->out,"") != 0)
    if (RUN_checkMove(name,moves->out,panelComp,auxResult,"OUT")) error=1;
  if (strcmp(moves->next,"") != 0)
    if (RUN_checkMove(name,moves->next,panelComp,auxResult,"NEXT")) error=1;
  if (strcmp(moves->previous,"") != 0)
    if (RUN_checkMove(name,moves->previous,panelComp,auxResult,"PREVIOUS")) error=1;
  if (strcmp(moves->up,"") != 0)
    if (RUN_checkMove(name,moves->up,panelComp,auxResult,"UP")) error=1;
  if (strcmp(moves->down,"") != 0)
    if (RUN_checkMove(name,moves->down,panelComp,auxResult,"DOWN")) error=1;
  if (strcmp(moves->left,"") != 0)
    if (RUN_checkMove(name,moves->left,panelComp,auxResult,"LEFT")) error=1;
  if (strcmp(moves->right,"") != 0)
    if (RUN_checkMove(name,moves->right,panelComp,auxResult,"RIGHT")) error=1;
  if (strcmp(moves->back,"") != 0)
    if (RUN_checkMove(name,moves->back,panelComp,auxResult,"BACK")) error=1;
  if (strcmp(moves->other,"") != 0)
    if (RUN_checkMove(name,moves->other,panelComp,auxResult,"OTHER")) error=1;
  for (i=0;i!=MAX_Fn_KEYS;i++)
    if (RUN_checkMove(name,moves->Fn[i],panelComp,auxResult,"Fn")) error=1;

  return error;
}

static int RUN_checkMove(char * name, char  * move,tXmlCompPanel * panelComp,
		              tEdit * auxResult,char *errorText)
{
  char * aux;
  char view[MAX_NAME_VIEW+1];
  char component[MAX_COMPONENT_NAME+1];
  char auxdata[150];
  int ncomp=0;
  tXmlPanelPtr auxPanel=NULL;
  tXmlTablePtr auxTable=NULL;
  tXmlEditPtr  auxEdit=NULL;
  memset(view,'\0',sizeof(view));
  memset(component,'\0',sizeof(view));

  if (strcmp(move,"")==0) return 0;
  if (strcmp(move,"exit:")==0) return 0;
  if (strcmp(move,"-:")==0) return 0;

  aux = move;
  while (*aux != '\0' && *aux!=':') aux++;
  strncpy(view,move,(aux-move));
  if (*aux == ':') {
    strcpy(component,aux+1);
  }
  else{
    strcpy(component,"");
  }

  if (strcmp(view,"")!=0){
     auxPanel = VIEW_searchPanel(view);
     if (auxPanel == NULL){
       auxTable = VIEW_searchTable(view);
       if (auxTable ==NULL) auxEdit = VIEW_searchEdit(view);
     }
     else
      panelComp = auxPanel->elements;
     if (auxPanel == NULL && auxTable == NULL && auxEdit == NULL) {
       sprintf(auxdata,"Move %s of %s not found view %s ",errorText,name,view);
       TEXT_addEditData(auxResult->text,auxdata);
       return 1;
     }
  }

  if (strcmp(component,"")!=0) {
    while (panelComp!=NULL){
      ncomp=atoi(component);
      if (ncomp==0 && strcmp(panelComp->componente->name,component)==0) return 0;
      if (ncomp!=0 && panelComp->componente->id==ncomp) return 0;
      panelComp = panelComp->siguiente;
    }
    sprintf(auxdata,"Move %s of %s not found component %s ",errorText,name,component);
    TEXT_addEditData(auxResult->text,auxdata);
    return 2;
  }
 return 0;
}

static int RUN_checkText(tDim * dimension, tXmlText * text){
char * token;
int y=dimension->border;
char textAux[500];

  while(text!=NULL){
    strcpy(textAux,text->texto);
    token = strtok(textAux,"\n");
    while (token != NULL){
      if (strlen(token) > (dimension->ancho-dimension->border) ||
	y > (dimension->alto-dimension->border)) 
       return 1;
      token = strtok(NULL, "\n");
    }
    text = text->siguiente;
  }
  return 0;
}

void RUN_compile () {
tComponent * auxC;
struct stat st;
tXmlProyectPtr auxProy;
pid_t pid;
int status;
char * argv[]={"/bin/sh","-c","make -f makefile_tui 2>/tmp/tcomp 1>/tmp/tcomp",0};

char sproy[100];
extern char ** environ;


 auxProy=PROY_getProyect();

 if (strcmp(auxProy->name,"")==0){
   MSG_create(M_WARNING,CENTER_VIEW,"Open or create a proyect ");
   return; 
 }

 sprintf(sproy,"./%s",auxProy->name);

 if (stat(sproy, &st) == -1) {
    mkdir(sproy, 0700);
 }
 auxC = (tComponent *)LVIEW_getElement("frCompile","directory");
 COMPONENT_setValue(auxC,"done");
 COMPONENT_refresh(auxC);

 sprintf(sproy,"./%s/%s.xml",auxProy->name,auxProy->name);
 if (WXML_print(sproy) != 0) {
     MSG_create(M_ERROR,CENTER_VIEW,"Error saving current proyect");
     return; 
 }
 auxC = (tComponent *)LVIEW_getElement("frCompile","saving");
 COMPONENT_setValue(auxC,"done");
 COMPONENT_refresh(auxC);

 auxC = (tComponent *)LVIEW_getElement("frCompile","compile");
 
 sprintf(sproy,"TUI_PROYECT=%s",auxProy->name);

 pid = vfork();  

 if (pid == 0) { 
        setenv("TUI_PROYECT",auxProy->name , 1);
        execve(argv[0],argv,environ);
 } else if (pid > 0) {  
	waitpid(pid,&status,0);
        if (status != 0)
         COMPONENT_setValue(auxC,"error");
        else
         COMPONENT_setValue(auxC,"done");
 } else {
      MSG_create(M_ERROR,CENTER_VIEW,"Error making vfork");
      COMPONENT_setValue(auxC,"error");
 }
 COMPONENT_refresh(auxC);
}

trAction* RUN_compileFile (tComponent * component,int key){
 static trAction action;
 tEdit * auxE;

 initAction(action);

  auxE = (tEdit *)LVIEW_searchView("CheckFile")->view.edit;
  if (EDIT_loadFile(auxE,"/tmp/tcomp",300,50) != 0) {
     MSG_create(M_ERROR,CENTER_VIEW,"Error loading <%s> file","/tmp/tcomp");
     action.error=1;
     return &action;
  }

  return &action;
}


trAction* RUN_execute (tComponent * component,int key){
 char * term = NULL;
 char * tty = NULL;
 extern char ** environ;
 pid_t pid;
 static trAction action;
 tXmlProyectPtr auxProy;
 int status;
 char * argv[]={"/bin/sh","-c","make -f makefile_tui run 2>/tmp/tcomp 1>/tmp/tcomp",0};


 initAction(action);

 auxProy=PROY_getProyect();

 if (strcmp(auxProy->name,"")==0){
   MSG_create(M_ERROR,CENTER_TERMINAL,"Open or create a proyect ");
   action.error=1;
   return &action;
 }

 term=PROY_getTestTerm();
 tty=PROY_getTestTty();
 if (term == NULL || tty == NULL) {
    MSG_create(M_ERROR,CENTER_TERMINAL,"TTy test terminal not set ");
    action.error=1;
    return &action;
 }

 pid = vfork();  

 if (pid == 0) { 
        setenv("TUI_PROYECT",auxProy->name , 1);
        setenv("TERM",term , 1);
        setenv("TTY",tty , 1);
        execve(argv[0],argv,environ);
 } else if (pid > 0) {  
	waitpid(pid,&status,0);
 } else {
      MSG_create(M_ERROR,CENTER_TERMINAL,"Error making vfork");
      action.error=1;
 }

 return &action;
}



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
#include <tparser.h>
#include <component.h>
#include <tkeymap.h>
#include <tcolor.h>
#include <tedf.h>
#include <tview.h>
#include <tcomp.h>
#include <tproyect.h>
#include <tfunc.h>


char * selectDestino;
char * selectOut;
char * selectOptionOut;
char * panelSelect;

trAction* SELECT_enter (tTable * table,int key){
static trAction action;
 char * value;

 initAction(action);

 value = TABLE_getColumnValue(table,0);
 if (value==NULL || strcmp(value,"")==0)
  return &action;

 TEXT_send(value,1);
 action.made=1;
 action.componentNext=selectDestino;
 return &action;
}

trAction* SELECT_optionEnter (tTable * table,int key){
static trAction action;
 char * value;
 tXmlComponentPtr aux;

 initAction(action);

 value = TABLE_getColumnValue(table,0);
 if (value==NULL || strcmp(value,"")==0)
  return &action;

 if (strcmp(value,"NEW LABEL")==0){
  TEXT_send(panelSelect,1);
  TEXT_send("NEW",0);
  action.made=1;
  action.componentNext="CoL:CoLid";
  return &action;
 }
 if (strcmp(value,"NEW BUTTON")==0){
  TEXT_send(panelSelect,1);
  TEXT_send("NEW",0);
  action.made=1;
  action.componentNext="CoB:CoBid";
  return &action;
 }
 if (strcmp(value,"NEW CHECK BUTTON")==0){
  TEXT_send(panelSelect,1);
  TEXT_send("NEW",0);
  action.made=1;
  action.componentNext="CoCB:CoCBid";
  return &action;
 }
 if (strcmp(value,"NEW LIST BUTTON")==0){
  TEXT_send(panelSelect,1);
  TEXT_send("NEW",0);
  action.made=1;
  action.componentNext="CoLB:CoLBid";
  return &action;
 }
 if (strcmp(value,"NEW FIELD")==0){
  TEXT_send(panelSelect,1);
  TEXT_send("NEW",0);
  action.made=1;
  action.componentNext="CoED:CoEDid";
  return &action;
 }
 TEXT_send(panelSelect,1);
 TEXT_send(value,0);
 aux=COMP_searchComp(panelSelect,value);
 if (aux == NULL) return &action;
 switch(aux->type){
  case C_LABEL:
    action.componentNext="CoL:CoLid";
    break;
  case C_BUTTON:
    action.componentNext="CoB:CoBid";
    break;
  case C_CKBUTTON:
    action.componentNext="CoCB:CoCBid";
    break;
  case C_LSBUTTON:
    action.componentNext="CoLB:CoLBid";
    break;
  case C_EDIT:
    action.componentNext="CoED:CoEDid";
    break;
   default: return &action;
 }
 action.made=1;
 return &action;
}

trAction* SELECT_compEnter (tTable * table,int key){
static trAction action;
char * panel;
char * comp;
tXmlComponentPtr aux;

 initAction(action);
 panel = TABLE_getColumnValue(table,0);
 comp = TABLE_getColumnValue(table,1);
 TEXT_send("update",1);
 TEXT_send(panel,0);
 TEXT_send(comp,0);
 if (strcmp(comp,"NEW")==0){
   action.made=1;
   action.componentNext="PLcomponents:Colabel";
   return &action;
 }
 aux=COMP_searchComp(panel,comp);
 if (aux == NULL) return &action;
 switch(aux->type){
  case C_LABEL:
    action.componentNext="CoL:CoLid";
    break;
  case C_BUTTON:
    action.componentNext="CoB:CoBid";
    break;
  case C_CKBUTTON:
    action.componentNext="CoCB:CoCBid";
    break;
  case C_LSBUTTON:
    action.componentNext="CoLB:CoLBid";
    break;
  case C_EDIT:
    action.componentNext="CoED:CoEDid";
    break;
   default: return &action;
 }

 action.made=1;
 return &action;
}

trAction* SELECT_out (tTable * table,int key){
static trAction action;

 initAction(action);

 action.made=1;
 action.componentNext=selectOut;
 return &action;
}


void SELECT_load(tTable * table){
char * orden;
tXmlMapKeyPtr auxKeymap;
tXmlcolorPtr auxColor;
tXmlPanelPtr auxPanel;
tXmlTablePtr auxTable;
tXmlEditPtr auxEdit;
tXmlComponentPtr auxComp;
tXmlCompPanelPtr auxCompPanel;


  selectOut = TEXT_recv();
  orden = TEXT_recv();
  selectDestino = TEXT_recv();
 
  if (selectOut == NULL || orden == NULL) return;
  TEXT_clear(table->text);

  if (strcmp(orden,"KEYMAP") == 0){
   auxKeymap = KEYMAP_get();
   while (auxKeymap != NULL) {
     TEXT_addData(table->text,auxKeymap->name);
     auxKeymap = auxKeymap->siguiente;
   }
  }
  if (strcmp(orden,"COLOR") == 0){
   auxColor = COLOR_getXml();
   while (auxColor != NULL) {
     TEXT_addData(table->text,auxColor->name);
     auxColor = auxColor->siguiente;
   }
  }

  if (strcmp(orden,"PANEL") == 0){
   auxPanel = PANEL_get();
   TABLE_setColumnHead(table,0,"PANELS");
   TEXT_addData(table->text,"NEW");
   while (auxPanel != NULL) {
     TEXT_addData(table->text,auxPanel->name);
     auxPanel = auxPanel->siguiente;
   }
  }
  if (strcmp(orden,"TABLE") == 0){
   auxTable = TABLE_get();
   TABLE_setColumnHead(table,0,"TABLES");
   TEXT_addData(table->text,"NEW");
   while (auxTable != NULL) {
     TEXT_addData(table->text,auxTable->name);
     auxTable = auxTable->siguiente;
   }
  }
  if (strcmp(orden,"EDIT") == 0){
   auxEdit = EDIT_get();
   TABLE_setColumnHead(table,0,"EDITs");
   TEXT_addData(table->text,"NEW");
   while (auxEdit != NULL) {
     TEXT_addData(table->text,auxEdit->name);
     auxEdit = auxEdit->siguiente;
   }
  }
  if (strcmp(orden,"ALL_VIEW") == 0){
   TABLE_setColumnHead(table,0," VIEWs");
   auxPanel = PANEL_get();
   while (auxPanel != NULL) {
     TEXT_addData(table->text,auxPanel->name);
     auxPanel = auxPanel->siguiente;
   }
   auxTable = TABLE_get();
   while (auxTable != NULL) {
     TEXT_addData(table->text,auxTable->name);
     auxTable = auxTable->siguiente;
   }
   auxEdit = EDIT_get();
   while (auxEdit != NULL) {
     TEXT_addData(table->text,auxEdit->name);
     auxEdit = auxEdit->siguiente;
   }
  }
  if (strcmp(orden,"COMP_LABEL") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"LABELs");
   TEXT_addData(table->text,"NEW");
   while (auxComp != NULL) {
     if (auxComp->type == C_LABEL)
      TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }
  if (strcmp(orden,"COMP_BUTTON") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"BUTTONs");
   TEXT_addData(table->text,"NEW");
   while (auxComp != NULL) {
     if (auxComp->type == C_BUTTON)
      TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }
  if (strcmp(orden,"COMP_CKBUTTON") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"CHECK BUTTONs");
   TEXT_addData(table->text,"NEW");
   while (auxComp != NULL) {
     if (auxComp->type == C_CKBUTTON)
      TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }
  if (strcmp(orden,"COMP_LSBUTTON") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"LIST BUTTONs");
   TEXT_addData(table->text,"NEW");
   while (auxComp != NULL) {
     if (auxComp->type == C_LSBUTTON)
      TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }
  if (strcmp(orden,"COMP_FIELD") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"FIELDs");
   TEXT_addData(table->text,"NEW");
   while (auxComp != NULL) {
     if (auxComp->type == C_EDIT)
      TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }
  if (strcmp(orden,"COMP_ALL") == 0){
   auxComp = COMP_get();
   TABLE_setColumnHead(table,0,"FIELDs");
   while (auxComp != NULL) {
     TEXT_addData(table->text,auxComp->name);
     auxComp = auxComp->siguiente;
   }
  }

  if (strcmp(orden,"PANEL_COMPS") == 0){
   auxCompPanel = VIEW_getPanelComps(selectOut);
   TABLE_setColumnHead(table,0,"COMPONENTS");
   while (auxCompPanel != NULL) {
      TEXT_addData(table->text,auxCompPanel->componente->name);
     auxCompPanel = auxCompPanel->siguiente;
   }
  }

  if (strcmp(orden,"PANEL_HELP_COMPs") == 0){
   auxCompPanel = VIEW_getPanelComps(selectOut);
   TABLE_setColumnHead(table,0,"COMPONENTS");
   while (auxCompPanel != NULL) {
      if (auxCompPanel->componente->type != C_LABEL)
        TEXT_addData(table->text,auxCompPanel->componente->name);
     auxCompPanel = auxCompPanel->siguiente;
   }
  }
}

void SELECT_compLoad(tTable * table){
tXmlPanelPtr auxPanel;
tXmlCompPanelPtr auxComp;

  auxPanel = PANEL_get();
  while (auxPanel != NULL) {
    auxComp = auxPanel->elements;
    TEXT_addData(table->text,auxPanel->name);
    TEXT_addData(table->text,"NEW");
    while (auxComp != NULL) {
      TEXT_addData(table->text,auxPanel->name);
      TEXT_addData(table->text,auxComp->componente->name);
      auxComp = auxComp->siguiente;
    }
    auxPanel = auxPanel->siguiente;
  }
}

void SELECT_optionLoad(tTable * table){
char * orden;
tXmlCompPanelPtr auxCompPanel;

  selectOptionOut = TEXT_recv();
  orden = TEXT_recv();
  panelSelect = TEXT_recv();
 
  if (selectOptionOut == NULL || orden == NULL) return;

  TEXT_clear(table->text);

  if (strcmp(orden,"PANEL_COMPS") == 0){
   auxCompPanel = VIEW_getPanelComps(panelSelect);
   TABLE_setColumnHead(table,0,"COMPONENTS");
   TEXT_addData(table->text,"NEW LABEL");
   TEXT_addData(table->text,"NEW BUTTON");
   TEXT_addData(table->text,"NEW CHECK BUTTON");
   TEXT_addData(table->text,"NEW LIST BUTTON");
   TEXT_addData(table->text,"NEW FIELD");
   while (auxCompPanel != NULL) {
      TEXT_addData(table->text,auxCompPanel->componente->name);
     auxCompPanel = auxCompPanel->siguiente;
   }
  }
}

void SELECT_listViews(tTable * table){
tXmlPanelPtr auxPanel;
tXmlTablePtr auxTable;
tXmlEditPtr  auxEdit;
tXmlCompPanel * auxComp;

    if (table->text == NULL)
      TABLE_text(table,TEXT_new(RESIZE, 1,50,60,4));

    auxPanel = PANEL_get();

    while (auxPanel != NULL) {
     auxComp = auxPanel->elements;
     TEXT_addData(table->text,"panel");
     TEXT_addData(table->text,auxPanel->name);
     if (auxComp == NULL){
       TEXT_addData(table->text,"");
       TEXT_addData(table->text,"");
     }
     else {
       while (auxComp != NULL){
        TEXT_addData(table->text,auxComp->componente->name);
        switch(auxComp->componente->type){
         case C_LABEL: 
			TEXT_addData(table->text,"label");
			break;
         case C_BUTTON:
			TEXT_addData(table->text,"button");
			break;
         case C_CKBUTTON:
			TEXT_addData(table->text,"ckButton");
			break;
         case C_LSBUTTON:
			TEXT_addData(table->text,"lsbutton");
			break;
         case C_EDIT:
			TEXT_addData(table->text,"field");
			break;
         default:	
			TEXT_addData(table->text,"");
       }
       if (auxComp->siguiente != NULL) {
	TEXT_addData(table->text,"");
	TEXT_addData(table->text,"");
       }
       auxComp=auxComp->siguiente;
      }
    }
   auxPanel = auxPanel->siguiente;
 }

 auxTable = TABLE_get();
 while (auxTable != NULL) {
    TEXT_addData(table->text,"table");
    TEXT_addData(table->text,auxTable->name);
    TEXT_addData(table->text,"");
    TEXT_addData(table->text,"");
   auxTable=auxTable->siguiente;
 }
 auxEdit = EDIT_get();
 while (auxEdit != NULL) {
    TEXT_addData(table->text,"edit");
    TEXT_addData(table->text,auxEdit->name);
    TEXT_addData(table->text,"");
    TEXT_addData(table->text,"");
   auxEdit=auxEdit->siguiente;
 }

}

void SELECT_listColors(tTable * table){
tXmlcolorPtr auxColor;

   if (table->text == NULL)
      TABLE_text(table,TEXT_new(RESIZE, 1,50,60,4));

   auxColor = COLOR_getXml();
   while (auxColor != NULL) {
     TEXT_addData(table->text,auxColor->name);
     switch (auxColor->fcolor){
	case 0:
     		TEXT_addData(table->text,"BLACK");
		break;
	case 1:
     		TEXT_addData(table->text,"BLUE");
		break;
	case 2:
     		TEXT_addData(table->text,"GREEN");
		break;
	case 3:
     		TEXT_addData(table->text,"CYAN");
		break;
	case 4:
     		TEXT_addData(table->text,"RED");
		break;
	case 5:
     		TEXT_addData(table->text,"MAGENTA");
		break;
	case 6:
     		TEXT_addData(table->text,"YELLOW");
		break;
	case 7:
     		TEXT_addData(table->text,"WHITE");
		break;

     }
     switch (auxColor->bcolor){
	case 0:
     		TEXT_addData(table->text,"BLACK");
		break;
	case 1:
     		TEXT_addData(table->text,"BLUE");
		break;
	case 2:
     		TEXT_addData(table->text,"GREEN");
		break;
	case 3:
     		TEXT_addData(table->text,"CYAN");
		break;
	case 4:
     		TEXT_addData(table->text,"RED");
		break;
	case 5:
     		TEXT_addData(table->text,"MAGENTA");
		break;
	case 6:
     		TEXT_addData(table->text,"YELLOW");
		break;
	case 7:
     		TEXT_addData(table->text,"WHITE");
		break;

     }
     TEXT_addData(table->text,COLOR_textoChTipo(auxColor->attr));
     auxColor = auxColor->siguiente;
   }
}

void SELECT_listCalls(tTable * table){
int init,init2;
tXmlPropPtr proyProp;
tXmlPanelPtr panels;
tXmlTablePtr tables;
tXmlEditPtr  edits;
tXmlCompPanel * auxElements;

   if (table->text == NULL)
      TABLE_text(table,TEXT_new(RESIZE, 1,50,60,4));

   proyProp=PROY_getProperties();
   if (strcmp(proyProp->mainFunction,""))
   {
       TEXT_addEditData(table->text,"");
       TEXT_addEditData(table->text,"");
       TEXT_addEditData(table->text,"Main App");
       TEXT_addEditData(table->text,"RUN");
       TEXT_addEditData(table->text,proyProp->mainFunction);
   }
   if (strcmp(proyProp->endFunction,""))
   {
       TEXT_addEditData(table->text,"");
       TEXT_addEditData(table->text,"");
       TEXT_addEditData(table->text,"End App");
       TEXT_addEditData(table->text,"EXIT");
       TEXT_addEditData(table->text,proyProp->endFunction);
   }

   panels = PANEL_get();
   while (panels != NULL){
      init=1;  
      if (strcmp(panels->personalFPanel.pre_create,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_CRE_PANEL");
        TEXT_addEditData(table->text,"PREV. CRE.");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_create);
      }
      if (strcmp(panels->personalFPanel.post_create,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST CRE.");
        TEXT_addEditData(table->text,panels->personalFPanel.post_create);
      }
      if (strcmp(panels->personalFPanel.pre_show,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"PREV. SHOW");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_show);
      }
      if (strcmp(panels->personalFPanel.post_show,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST SHOW");
        TEXT_addEditData(table->text,panels->personalFPanel.post_show);
      }
      if (strcmp(panels->personalFPanel.pre_hide,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"PREV. HIDE");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_hide);
      }
      if (strcmp(panels->personalFPanel.post_hide,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST HIDE");
        TEXT_addEditData(table->text,panels->personalFPanel.post_hide);
      }
      if (strcmp(panels->personalFPanel.pre_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"PREV. DEST.");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_destroy);
      }
      if (strcmp(panels->personalFPanel.post_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST DEST.");
        TEXT_addEditData(table->text,panels->personalFPanel.post_destroy);
      }
      if (strcmp(panels->personalFPanel.pre_activate,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"PREV. ACT.");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_activate);
      }
      if (strcmp(panels->personalFPanel.post_activate,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST ACT.");
        TEXT_addEditData(table->text,panels->personalFPanel.post_activate);
      }
      if (strcmp(panels->personalFPanel.pre_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"PREV. DEACT.");
        TEXT_addEditData(table->text,panels->personalFPanel.pre_deactivate);
      }
      if (strcmp(panels->personalFPanel.post_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_PANEL");
        TEXT_addEditData(table->text,"POST DEACT.");
        TEXT_addEditData(table->text,panels->personalFPanel.post_deactivate);
      }

      if (strcmp(panels->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,panels->personalAction.enter);
      }
      if (strcmp(panels->personalAction.out,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OUT");
        TEXT_addEditData(table->text,panels->personalAction.out);
      }
      if (strcmp(panels->personalAction.next,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"NEXT");
        TEXT_addEditData(table->text,panels->personalAction.next);
      }
      if (strcmp(panels->personalAction.previous,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"PREVIOUS");
        TEXT_addEditData(table->text,panels->personalAction.previous);
      }

      if (strcmp(panels->personalAction.up,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"UP");
        TEXT_addEditData(table->text,panels->personalAction.up);
      }
      if (strcmp(panels->personalAction.down,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"DOWN");
        TEXT_addEditData(table->text,panels->personalAction.down);
      }
      if (strcmp(panels->personalAction.left,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"LEFT");
        TEXT_addEditData(table->text,panels->personalAction.left);
      }
      if (strcmp(panels->personalAction.right,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"RIGHT");
        TEXT_addEditData(table->text,panels->personalAction.right);
      }
      if (strcmp(panels->personalAction.back,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"BACK");
        TEXT_addEditData(table->text,panels->personalAction.back);
      }
      if (strcmp(panels->personalAction.other,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OTHER");
        TEXT_addEditData(table->text,panels->personalAction.other);
      }
      if (strcmp(panels->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,panels->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,panels->personalAction.enter);
      }
      if (strcmp(panels->personalAction.Fn[0],"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");

          TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F. MOVE");
          TEXT_addEditData(table->text,"Fn");
          TEXT_addEditData(table->text,panels->personalAction.Fn[0]);
      }
      auxElements = panels->elements;
      while (auxElements != NULL){
        init2=1;
        if (strcmp(auxElements->componente->personalFComponent.pre_create,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_CRE_COMP");
          TEXT_addEditData(table->text,"PREV. CRE.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_create);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_create,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST CRE.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_create);
        }
        if (strcmp(auxElements->componente->personalFComponent.pre_show,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"PREV. SHOW");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_show);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_show,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST SHOW");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_show);
        }
        if (strcmp(auxElements->componente->personalFComponent.pre_hide,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"PREV. HIDE");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_hide);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_hide,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST HIDE");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_hide);
        }
        if (strcmp(auxElements->componente->personalFComponent.pre_destroy,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"PREV. DEST.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_destroy);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_destroy,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST DEST.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_destroy);
        }
        if (strcmp(auxElements->componente->personalFComponent.pre_activate,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"PREV. ACT.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_activate);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_activate,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST ACT.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_activate);
        }
        if (strcmp(auxElements->componente->personalFComponent.pre_deactivate,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"PREV. DEACT.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.pre_deactivate);
        }
        if (strcmp(auxElements->componente->personalFComponent.post_deactivate,"")){
          if (init){
            TEXT_addEditData(table->text,panels->name);
            init =0;
          } else TEXT_addEditData(table->text,"");
          if (init2){
            TEXT_addEditData(table->text,auxElements->componente->name);
            init2 =0;
          } else TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F_APP_COMP");
          TEXT_addEditData(table->text,"POST DEACT.");
          TEXT_addEditData(table->text,auxElements->componente->personalFComponent.post_deactivate);
        }

        if (strcmp(auxElements->componente->personalAction.enter,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"ENTER");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.enter);
        }
        if (strcmp(auxElements->componente->personalAction.out,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"OUT");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.out);
        }
        if (strcmp(auxElements->componente->personalAction.next,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"NEXT");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.next);
        }
        if (strcmp(auxElements->componente->personalAction.previous,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"PREVIOUS");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.previous);
        }
        if (strcmp(auxElements->componente->personalAction.up,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"UP");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.up);
        }
        if (strcmp(auxElements->componente->personalAction.down,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"DOWN");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.down);
        }
        if (strcmp(auxElements->componente->personalAction.left,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"LEFT");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.left);
        }
        if (strcmp(auxElements->componente->personalAction.right,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"RIGHT");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.right);
        }
        if (strcmp(auxElements->componente->personalAction.back,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"BACK");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.back);
        }
        if (strcmp(auxElements->componente->personalAction.other,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"OTHER");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.other);
        }
        if (strcmp(auxElements->componente->personalAction.Fn[0],"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"Fn");
         TEXT_addEditData(table->text,auxElements->componente->personalAction.Fn[0]);
        }
        if (strcmp(auxElements->componente->editMode.editFunction,"")){
          if (init){
           TEXT_addEditData(table->text,panels->name);
            init =0;
         } else TEXT_addEditData(table->text,"");
         if (init2){
           TEXT_addEditData(table->text,auxElements->componente->name);
           init2 =0;
         } else TEXT_addEditData(table->text,"");
         TEXT_addEditData(table->text,"F. MOVE");
         TEXT_addEditData(table->text,"EDIT FUNC.");
         TEXT_addEditData(table->text,auxElements->componente->editMode.editFunction);
        }

        auxElements=auxElements->siguiente;
      } 
      
     panels = panels->siguiente;
   }

   tables = TABLE_get();
   while (tables != NULL){
      init=1;  
      if (strcmp(tables->personalFTable.pre_create,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_CRE_TABLE");
        TEXT_addEditData(table->text,"PREV. CRE.");
        TEXT_addEditData(table->text,tables->personalFTable.pre_create);
      }
      if (strcmp(tables->personalFTable.post_create,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST CRE.");
        TEXT_addEditData(table->text,tables->personalFTable.post_create);
      }
      if (strcmp(tables->personalFTable.pre_show,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"PREV. SHOW");
        TEXT_addEditData(table->text,tables->personalFTable.pre_show);
      }
      if (strcmp(tables->personalFTable.post_show,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST SHOW");
        TEXT_addEditData(table->text,tables->personalFTable.post_show);
      }
      if (strcmp(tables->personalFTable.pre_hide,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"PREV. HIDE");
        TEXT_addEditData(table->text,tables->personalFTable.pre_hide);
      }
      if (strcmp(tables->personalFTable.post_hide,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST HIDE");
        TEXT_addEditData(table->text,tables->personalFTable.post_hide);
      }
      if (strcmp(tables->personalFTable.pre_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"PREV. DEST.");
        TEXT_addEditData(table->text,tables->personalFTable.pre_destroy);
      }
      if (strcmp(tables->personalFTable.post_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST DEST.");
        TEXT_addEditData(table->text,tables->personalFTable.post_destroy);
      }
      if (strcmp(tables->personalFTable.pre_activate,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"PREV. ACT.");
        TEXT_addEditData(table->text,tables->personalFTable.pre_activate);
      }
      if (strcmp(tables->personalFTable.post_activate,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST ACT.");
        TEXT_addEditData(table->text,tables->personalFTable.post_activate);
      }
      if (strcmp(tables->personalFTable.pre_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"PREV. DEACT.");
        TEXT_addEditData(table->text,tables->personalFTable.pre_deactivate);
      }
      if (strcmp(tables->personalFTable.post_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_TABLE");
        TEXT_addEditData(table->text,"POST DEACT.");
        TEXT_addEditData(table->text,tables->personalFTable.post_deactivate);
      }

      if (strcmp(tables->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,tables->personalAction.enter);
      }
      if (strcmp(tables->personalAction.out,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OUT");
        TEXT_addEditData(table->text,tables->personalAction.out);
      }
      if (strcmp(tables->personalAction.next,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"NEXT");
        TEXT_addEditData(table->text,tables->personalAction.next);
      }
      if (strcmp(tables->personalAction.previous,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"PREVIOUS");
        TEXT_addEditData(table->text,tables->personalAction.previous);
      }

      if (strcmp(tables->personalAction.up,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"UP");
        TEXT_addEditData(table->text,tables->personalAction.up);
      }
      if (strcmp(tables->personalAction.down,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"DOWN");
        TEXT_addEditData(table->text,tables->personalAction.down);
      }
      if (strcmp(tables->personalAction.left,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"LEFT");
        TEXT_addEditData(table->text,tables->personalAction.left);
      }
      if (strcmp(tables->personalAction.right,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"RIGHT");
        TEXT_addEditData(table->text,tables->personalAction.right);
      }
      if (strcmp(tables->personalAction.back,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"BACK");
        TEXT_addEditData(table->text,tables->personalAction.back);
      }
      if (strcmp(tables->personalAction.other,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OTHER");
        TEXT_addEditData(table->text,tables->personalAction.other);
      }
      if (strcmp(tables->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,tables->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,tables->personalAction.enter);
      }
      if (strcmp(tables->personalAction.Fn[0],"")){
          if (init){
            TEXT_addEditData(table->text,tables->name);
            init =0;
          } else TEXT_addEditData(table->text,"");

          TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F. MOVE");
          TEXT_addEditData(table->text,"Fn");
          TEXT_addEditData(table->text,tables->personalAction.Fn[0]);
      }
     tables = tables->siguiente;
   }
   edits = EDIT_get();
   while (edits != NULL){
      init=1;  
      if (strcmp(edits->personalFEdit.pre_create,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_CRE_EDIT");
        TEXT_addEditData(table->text,"PREV. CRE.");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_create);
      }
      if (strcmp(edits->personalFEdit.post_create,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST CRE.");
        TEXT_addEditData(table->text,edits->personalFEdit.post_create);
      }
      if (strcmp(edits->personalFEdit.pre_show,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"PREV. SHOW");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_show);
      }
      if (strcmp(edits->personalFEdit.post_show,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST SHOW");
        TEXT_addEditData(table->text,edits->personalFEdit.post_show);
      }
      if (strcmp(edits->personalFEdit.pre_hide,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"PREV. HIDE");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_hide);
      }
      if (strcmp(edits->personalFEdit.post_hide,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST HIDE");
        TEXT_addEditData(table->text,edits->personalFEdit.post_hide);
      }
      if (strcmp(edits->personalFEdit.pre_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"PREV. DEST.");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_destroy);
      }
      if (strcmp(edits->personalFEdit.post_destroy,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST DEST.");
        TEXT_addEditData(table->text,edits->personalFEdit.post_destroy);
      }
      if (strcmp(edits->personalFEdit.pre_activate,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"PREV. ACT.");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_activate);
      }
      if (strcmp(edits->personalFEdit.post_activate,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST ACT.");
        TEXT_addEditData(table->text,edits->personalFEdit.post_activate);
      }
      if (strcmp(edits->personalFEdit.pre_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"PREV. DEACT.");
        TEXT_addEditData(table->text,edits->personalFEdit.pre_deactivate);
      }
      if (strcmp(edits->personalFEdit.post_deactivate,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F_APP_EDIT");
        TEXT_addEditData(table->text,"POST DEACT.");
        TEXT_addEditData(table->text,edits->personalFEdit.post_deactivate);
      }

      if (strcmp(edits->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,edits->personalAction.enter);
      }
      if (strcmp(edits->personalAction.out,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OUT");
        TEXT_addEditData(table->text,edits->personalAction.out);
      }
      if (strcmp(edits->personalAction.next,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"NEXT");
        TEXT_addEditData(table->text,edits->personalAction.next);
      }
      if (strcmp(edits->personalAction.previous,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"PREVIOUS");
        TEXT_addEditData(table->text,edits->personalAction.previous);
      }

      if (strcmp(edits->personalAction.up,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"UP");
        TEXT_addEditData(table->text,edits->personalAction.up);
      }
      if (strcmp(edits->personalAction.down,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"DOWN");
        TEXT_addEditData(table->text,edits->personalAction.down);
      }
      if (strcmp(edits->personalAction.left,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"LEFT");
        TEXT_addEditData(table->text,edits->personalAction.left);
      }
      if (strcmp(edits->personalAction.right,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"RIGHT");
        TEXT_addEditData(table->text,edits->personalAction.right);
      }
      if (strcmp(edits->personalAction.back,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"BACK");
        TEXT_addEditData(table->text,edits->personalAction.back);
      }
      if (strcmp(edits->personalAction.other,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"OTHER");
        TEXT_addEditData(table->text,edits->personalAction.other);
      }
      if (strcmp(edits->personalAction.enter,"")){
        if (init){
          TEXT_addEditData(table->text,edits->name);
          init =0;
        } else TEXT_addEditData(table->text,"");

        TEXT_addEditData(table->text,"");
        TEXT_addEditData(table->text,"F. MOVE");
        TEXT_addEditData(table->text,"ENTER");
        TEXT_addEditData(table->text,edits->personalAction.enter);
      }
      if (strcmp(edits->personalAction.Fn[0],"")){
          if (init){
            TEXT_addEditData(table->text,edits->name);
            init =0;
          } else TEXT_addEditData(table->text,"");

          TEXT_addEditData(table->text,"");
          TEXT_addEditData(table->text,"F. MOVE");
          TEXT_addEditData(table->text,"Fn");
          TEXT_addEditData(table->text,edits->personalAction.Fn[0]);
      }
     edits = edits->siguiente;
    }
}

void SELECT_optionUpdate(){
char * msg;
tTable * auxT;

  msg = TEXT_recv();
  if (msg != NULL){
   auxT = (tTable *)LVIEW_getElement("tselect",NULL);
   TABLE_refresh(auxT);
  }
}

void SELECT_filePreShow(tEdit * edit){
  EDIT_loadFile(edit,"tmake.xml",200,100);
return;
}


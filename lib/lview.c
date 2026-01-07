#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>
#include <error.h>
#include <tBasic.h>
#include <panel.h>
#include <table.h>
#include <edit.h>
#include <view.h>
#include <lview.h>
#include <back.h>

static int testView = 0;
static tlView * listaViews = NULL;

tCaller * LVIEW_getCaller() {
tView * auxView;

 auxView = VIEW_getActive();
 if (auxView == NULL) return NULL;
 return &auxView->caller;
}

void * LVIEW_getElement(char * nView, char * nComponent)
{
  tView * auxView;
  tComponent * auxComponent;

  if (nView != NULL)
   auxView = LVIEW_searchView(nView);
  else
   auxView = VIEW_getActive();

  if (auxView == NULL) return  NULL;

  switch(auxView->type)
  {
     case V_Panel:
       if (nComponent != NULL){
         auxComponent = PANEL_searchComponent(auxView->view.panel,nComponent);
         return auxComponent;
       }
       return auxView->view.panel;
       break;
     case V_Table:
       if (nComponent != NULL) return NULL;
       return auxView->view.table;
       break;
     case V_Edit:
       if (nComponent != NULL) return NULL;
       return auxView->view.edit;
       break;
     default:
       return NULL;
  }
  return NULL;
}

tView * LVIEW_searchView(char * name)
{
 tlView * pView;
 char * end;
 int id=0;
 
 if (name == NULL) return NULL;
 id = (int)strtol(name,&end,10);
 if (end-name != strlen(name)) id=0;


 if (id == 0 && (name==NULL||strcmp(name,"")==0)) return NULL;
 pView = listaViews;

 while (pView != NULL)
 {
   switch(pView->view->type)
   {
     case V_Panel:
       if (id > 0)
       {
	if (pView->view->view.panel->id == id)
            return pView->view;
       }
       else
       {
         if (strcmp(pView->view->view.panel->name,name) == 0)
           return pView->view;
       }
       break;
     case V_Table:
       if (id > 0)
       {
	if (pView->view->view.table->id == id)
            return pView->view;
       }
       else
       {
         if (strcmp(pView->view->view.table->name,name) == 0)
           return pView->view;
       }
       break;
     case V_Edit:
       if (id > 0)
       {
	if (pView->view->view.edit->id == id)
            return pView->view;
       }
       else
       {
         if (strcmp(pView->view->view.edit->name,name) == 0)
           return pView->view;
       }
       break;
     default:
       break;
    }
   pView = pView->siguiente;
 }
 return NULL;
}

void LVIEW_testView(){
  testView=1;
}

void LVIEW_addView(tView * vista)
{
  tlView * pLView = NULL;
  tlView * pLAux = NULL;
  char * name;  
  
  if (testView) { testView=0; return; }

  switch(vista->type) 
  {
    case V_Panel:
		name=vista->view.panel->name;
		break;
    case V_Table:
		name=vista->view.table->name;
		break;
    case V_Edit:
		name=vista->view.edit->name;
		break;
    default: break;
  }
 
  if (LVIEW_searchView(name) == NULL)
  {
    pLView = malloc(sizeof(tlView));
    if (pLView == NULL) 
     ERR_fatalError(ERR_MEM,"Fail malloc of view <%d>\n",sizeof(tlView));

    pLView->view = vista; 
    pLView->siguiente = NULL; 
    if (listaViews == NULL) listaViews = pLView;
    else
    {
      pLAux = listaViews;
      while (pLAux->siguiente != NULL)
       pLAux = pLAux->siguiente;
      pLAux->siguiente = pLView;
    }
  }
}

void LVIEW_delView(void * view)
{
  tlView * pLAux = NULL;

  if (view == listaViews->view)
  {
      listaViews = listaViews->siguiente;
      return;
  }
  pLAux = listaViews;
  while (pLAux != NULL)
  {
    if (pLAux->siguiente->view == view)
     pLAux->siguiente = pLAux->siguiente->siguiente;

    pLAux= pLAux->siguiente;
  }
  return;
}

char * LVIEW_searchXYView(int sx, int sy)
{
 tlView * pView;
 tView * actView;
 static char viewName[MAX_NAME_VIEW+MAX_COMPONENT_NAME+5];
 char * auxVName;
 int level = -1;
 int x,y;

 pView = listaViews;
 strcpy(viewName,"");
 
 actView= VIEW_getActive();
 /*  
  *  Buscar primero en la activa.
  */
 x=sx; y=sy;
 switch(actView->type)
 {
     case V_Panel:
       if (wmouse_trafo(actView->view.panel->visual->win, &y, &x, FALSE) == TRUE)
       {
         auxVName = PANEL_searchXYComponent(actView->view.panel,x,y);
         if (auxVName != NULL) {strcpy(viewName,auxVName); return viewName;}
       }
       break;
     case V_Table:
       if (wmouse_trafo(actView->view.table->vTable->win, &y, &x, FALSE) == TRUE)
       {
         sprintf(viewName,"%s:",actView->view.table->name); 
	 return viewName;
       }
       break;
     case V_Edit:
       if (wmouse_trafo(actView->view.edit->vData->win, &y, &x, FALSE) == TRUE)
       {
          sprintf(viewName,"%s:",actView->view.edit->name);
          return viewName; 
       }
       break;
     default:
       break;
 }

 while (pView != NULL)
 {
   x=sx; y=sy;
   switch(pView->view->type)
   {
     case V_Panel:
       if (pView->view->view.panel->visual->status.visible==DIS_NORMAL &&
           pView->view->level > level){
           if (wmouse_trafo(pView->view->view.panel->visual->win, &y, &x, FALSE) == TRUE)
           {
             auxVName = PANEL_searchXYComponent(pView->view->view.panel,x,y);
             if (auxVName != NULL)
              strcpy(viewName,auxVName);
             else return NULL;
             level = pView->view->level;
           }
       }
       break;
     case V_Table:
       if (pView->view->view.table->vTable->status.visible==DIS_NORMAL &&
           pView->view->level > level){
           if (wmouse_trafo(pView->view->view.table->vTable->win, &y, &x, FALSE) == TRUE)
           {
             sprintf(viewName,"%s:",pView->view->view.table->name);
             level = pView->view->level;
           }
       }
       break;
     case V_Edit:
       if (pView->view->view.edit->vData->status.visible==DIS_NORMAL &&
           pView->view->level > level){
           if (wmouse_trafo(pView->view->view.edit->vData->win, &y, &x, FALSE) == TRUE)
           {
             sprintf(viewName,"%s:",pView->view->view.edit->name);
             level = pView->view->level;
           }
       }
       break;
     default:
       break;
    }
   pView = pView->siguiente;
 }
 return viewName;
}

int LVIEW_refresh(char * name)
{
 tlView * pView;
 tView * actView;
 int levelAct = -1;

 actView= LVIEW_searchView(name);
 if (actView == NULL) return ERR_VIEW;
 levelAct = actView->level; 
 switch(actView->type)
 {
    case V_Panel:
       if (actView->view.panel->visual->status.visible==DIS_NORMAL){
         PANEL_refresh(actView->view.panel);
         BACK_refresh(actView->view.panel->visual->win);
       }
       else
         return ERR_VIEW;
       break;
     case V_Table:
       if (actView->view.table->vTable->status.visible==DIS_NORMAL){
         TABLE_refresh(actView->view.table);
         BACK_refresh(actView->view.table->vData->win);
       }
       else
         return ERR_VIEW;
       break;
     case V_Edit:
       if (actView->view.edit->vData->status.visible==DIS_NORMAL){
         EDIT_refresh(actView->view.edit);
         BACK_refresh(actView->view.edit->vData->win);
       }
       else
         return ERR_VIEW;
       break;
     default:
       break;
 }

 pView = listaViews;
 while (pView != NULL){
   switch(pView->view->type)
   {
     case V_Panel:
       if (pView->view->view.panel->visual->status.visible==DIS_NORMAL &&
           pView->view->level > levelAct)
          BACK_refreshView(pView->view->wBack);
       break;
     case V_Table:
       if (pView->view->view.table->vTable->status.visible==DIS_NORMAL &&
           pView->view->level > levelAct)
          BACK_refreshView(pView->view->wBack);
       break;
     case V_Edit:
       if (pView->view->view.edit->vData->status.visible==DIS_NORMAL &&
           pView->view->level > levelAct)
          BACK_refreshView(pView->view->wBack);
       break;
     default:
       break;
   }
   pView = pView->siguiente;
 }
 return 0;
}

void LVIEW_clean(char * antCaller,tViewPtr antView,tViewPtr newView)
{
  int nlevel;
  tlView * aux = NULL;

  aux = listaViews;
  
  nlevel=newView->level;
  while (aux != NULL)
  {
    if ( aux->view->caller.View != NULL &&
	 strcmp(aux->view->caller.View,antCaller)==0 &&
         aux->view->level > nlevel && aux->view != newView &&
         antView != aux->view) {
      switch(aux->view->type)
      {
        case V_Panel:
         if (aux->view->view.panel->visual->status.visible==DIS_NORMAL)
           PANEL_opToMade(aux->view->view.panel);
         break;
        case V_Table:
         if (aux->view->view.table->vTable->status.visible==DIS_NORMAL)
           TABLE_opToMade(aux->view->view.table);
         break;
        case V_Edit:
         if (aux->view->view.edit->vData->status.visible==DIS_NORMAL)
            EDIT_hide(aux->view->view.edit);
         break;
        default:
         break;
      }
    }
   aux = aux->siguiente;
  }
}


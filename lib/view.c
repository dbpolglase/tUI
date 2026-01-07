#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tBasic.h>
#include <error.h>
#include <panel.h>
#include <table.h>
#include <edit.h>
#include <back.h>
#include <lview.h>

static void VIEW_hide(tViewPtr antView,tViewPtr newView);
static tViewPtr actView = NULL;

tViewPtr VIEW_getActive()
{
   return actView;
}

void VIEW_Loop(tView * view, char * element)
{
  tNext next;
  tViewPtr nextView = view;
  
  next.opToMade=OP_NONE;
  strcpy(next.element,element);
  while (true)
  {
    /* ---------------
     * Eliminar lo anterior si necesario.
     * -------------------------------------- */
    switch (next.opToMade)
    {
        case OP_NONE:
        case OP_CREATE:
        case OP_SHOW:
        case OP_ACT:
         break;
        case OP_DESTROY:
         VIEW_hide(actView,nextView);
         break;
        case OP_HIDE:
         VIEW_hide(actView,nextView);
         break;
        case OP_DEACT:
         VIEW_hide(actView,nextView);
         break;
    }

    /* ----------------
     * Ponemos la nueva vista.
     * ------------------------------ */
    switch(nextView->type)
    {
      case V_Panel:
                if (nextView->view.panel->visual->status.visible==DIS_HIDDEN){
	          nextView->caller.View=next.caller.View;
	          nextView->caller.Element=next.caller.Element;
                  BACK_push(nextView);
                  PANEL_show(nextView->view.panel);
                }
                actView=nextView;
                PANEL_activate(nextView->view.panel,next.element);
                PANEL_Action(nextView->view.panel,&next);
                break;
      case V_Table:
               if (nextView->view.table->vTable->status.visible ==DIS_HIDDEN){
	          nextView->caller.View=next.caller.View;
	          nextView->caller.Element=next.caller.Element;
                  BACK_push(nextView);
                  TABLE_show(nextView->view.table);
               }
               actView=nextView;
               TABLE_activate(nextView->view.table);
               TABLE_Action(nextView->view.table,&next);
               break;
      case V_Edit:
                if (nextView->view.edit->vData->status.visible == DIS_HIDDEN){
	          nextView->caller.View=next.caller.View;
	          nextView->caller.Element=next.caller.Element;
                  BACK_push(nextView);
                  EDIT_show(nextView->view.edit);
                }
                actView=nextView;
                EDIT_activate(nextView->view.edit);
                EDIT_Action(nextView->view.edit,&next);
                break;
      default:
		return;
    }
    if (strcmp(next.view,"")==0 || strcmp(next.view,":")==0 
					|| strcmp(next.view,"exit:")==0) 
      return;
    nextView=LVIEW_searchView(next.view);
    if (nextView == NULL) {
        ERR_Error(ERR_VIEW," view %s not found\n ",next.view);
        return;
    }

    if (nextView->level>=actView->level ||
                    (next.opToMade != OP_HIDE && next.opToMade != OP_DESTROY ))
    {
      switch(actView->type)
      {
        case V_Panel:
          BACK_update(actView->view.panel->visual->win);
          break;
        case V_Table:
          wrefresh(actView->view.table->vData->win);
          BACK_update(actView->view.table->vTable->win);
/*
          BACK_update(actView->view.table->vData->win);
          BACK_update(actView->view.table->vHead->win);
*/
          break;
        case V_Edit:
          BACK_update(actView->view.edit->vData->win);
          break;
        default:
	  break;
      }
    }
  }
}


static void VIEW_hide(tViewPtr antView,tViewPtr newView)
{
 int level,nlevel;
 tCaller caller;

   nlevel=newView->level;
   while(antView != NULL )
   {
     level=antView->level;
     if (level > nlevel && antView != newView) {
       switch(antView->type)
       {
         case V_Panel:
                memcpy(&caller,&antView->caller,sizeof(caller));
                LVIEW_clean(antView->view.panel->name,antView,newView);
	        PANEL_opToMade(antView->view.panel);
                BACK_pop(antView);
                break;
        case V_Table:
                memcpy(&caller,&antView->caller,sizeof(caller));
                LVIEW_clean(antView->view.table->name,antView,newView);
	        TABLE_opToMade(antView->view.table);
                BACK_pop(antView);
                break;
        case V_Edit:
                memcpy(&caller,&antView->caller,sizeof(caller));
                LVIEW_clean(antView->view.edit->name,antView,newView);
                BACK_pop(antView);
		EDIT_hide(antView->view.edit);
                break;
        default: break;
       }
       antView->caller.View=NULL;
       antView->caller.Element=NULL;
     }
     else return; 
     antView=LVIEW_searchView(caller.View);
   }
}

int VIEW_cargaMove(tMove * cmove,tMove *move)
{
 int i=0;

   memset(cmove,'\0',sizeof(tMove));
   if (move == NULL) return 0;

   if (move->enter != NULL && !strcmp(move->enter,"")==0)
   {
      cmove->enter = malloc(strlen(move->enter)+2);
      if (cmove->enter == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->enter+2));
      strcpy(cmove->enter,move->enter);
   }
   if (move->out != NULL && !strcmp(move->out,"")==0)
   {
      cmove->out = malloc(strlen(move->out)+2);
      if (cmove->out == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->out+2));
      strcpy(cmove->out,move->out);
   }
   if (move->next != NULL && !strcmp(move->next,"")==0)
   {
      cmove->next = malloc(strlen(move->next)+2);
      if (cmove->next == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->next+2));
      strcpy(cmove->next,move->next);
   }
   if (move->previous != NULL && !strcmp(move->previous,"")==0)
   {
      cmove->previous = malloc(strlen(move->previous)+2);
      if (cmove->previous == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->previous+2));
      strcpy(cmove->previous,move->previous);
   }
   if (move->up != NULL && !strcmp(move->up,"")==0)
   {
      cmove->up = malloc(strlen(move->up)+2);
      if (cmove->up == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->up+2));
      strcpy(cmove->up,move->up);
   }
   if (move->down != NULL && !strcmp(move->down,"")==0)
   {
      cmove->down = malloc(strlen(move->down)+2);
      if (cmove->down == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->down+2));
      strcpy(cmove->down,move->down);
   }
   if (move->left != NULL && !strcmp(move->left,"")==0)
   {
      cmove->left = malloc(strlen(move->left)+2);
      if (cmove->left == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->left+2));
      strcpy(cmove->left,move->left);
   }
   if (move->right != NULL && !strcmp(move->right,"")==0)
   {
      cmove->right = malloc(strlen(move->right)+2);
      if (cmove->right == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->right+2));
      strcpy(cmove->right,move->right);
   }
   if (move->back != NULL && !strcmp(move->back,"")==0)
   {
      cmove->back = malloc(strlen(move->back)+2);
      if (cmove->back == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->back+2));
      strcpy(cmove->back,move->back);
   }


   for (i=0;i!=MAX_Fn_KEYS;i++)
   {
       if (move->Fn[i] != NULL && !strcmp(move->Fn[i],"")==0)
       {
         cmove->Fn[i] = malloc(strlen(move->Fn[i])+2);
         if (cmove->Fn[i] == NULL)
          ERR_fatalError(ERR_MEM,"Error malloc component move (%d)\n",
                                        sizeof(move->Fn[i]+2));
         strcpy(cmove->Fn[i],move->Fn[i]);
       }
   }
   return 0;
}

tCaller * VIEW_getAtras(int atras)
{
tCaller * atrasView=NULL;
static tViewPtr auxView= NULL;
int i;

auxView = actView;

   for (i=0;i!=atras;i++){
	atrasView = &auxView->caller;
   }
   if (atrasView != NULL) {
     auxView=LVIEW_searchView(atrasView->View);
     if (auxView == NULL) return NULL;
   }
   return atrasView;
}


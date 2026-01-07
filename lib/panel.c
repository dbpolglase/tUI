#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>
#include <error.h>
#include <tBasic.h>
#include <component.h>
#include <error.h>
#include <lview.h>
#include <msg.h>
#include <keys.h>
#include <visual.h>
#include <view.h>
#include <panel.h>
#include <text.h>


tPanel * activePanel = NULL;

tView * PANEL_create(int id,
                      char * name,
		      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * color,
		      unsigned short opToMade,
                      tMove * move,
                      _tFActionPanel * personalAction,
                      _tFPanel * personalFPanel)
{
  tPanel * panel;
  int maxTitle;
  tView * view;

  if (personalFPanel != NULL &&
        personalFPanel->pre_create != NULL)
    (*personalFPanel->pre_create)(name);

  view = malloc(sizeof(tView));
  if (view == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Panel malloc %d\n",sizeof(tView));
    return NULL;
  }
  view->caller.View=NULL;
  view->caller.Element=NULL;

  panel = malloc(sizeof(tPanel));
  if (panel == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Panel malloc %d\n",sizeof(tPanel));
    free(view);
    return NULL;
  }
  panel->visual = malloc(sizeof(tVisual));
  if (panel->visual == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Panel malloc %d\n",sizeof(tVisual));
    free(panel);
    free(view);
    return NULL;
  }
  panel->id=id;
  strncpy(panel->name,name,sizeof(panel->name));
  if (title == NULL) panel->title[0] = '\0';
  else
  {
    maxTitle=(strlen(title)>dimension->ancho)?dimension->ancho-1:strlen(title)+1;
    if (maxTitle > MAX_VIEW_TITLE) maxTitle = MAX_VIEW_TITLE -1;
    strncpy(panel->title,title,maxTitle);
  } 
  
  memcpy(&panel->visual->dimension ,dimension,sizeof(tDim));
  memcpy(&panel->visual->color ,color,sizeof(tChAttr));

  panel->visual->status.visible=DIS_HIDDEN;
  panel->visual->status.activa=0;

  panel->elements = NULL;
  panel->opToMade=opToMade;
  panel->visual->win = newwin(panel->visual->dimension.alto,
                      panel->visual->dimension.ancho,
                      panel->visual->dimension.y,
                      panel->visual->dimension.x);

  view->level=level;
  view->type=V_Panel;
  view->view.panel=panel;
  panel->activeElement = NULL;
  panel->personalFPanel=(tFPanel *)personalFPanel;
  panel->personalAction=(tFActionPanel *)personalAction;

  panel->move = malloc(sizeof(tMove));
  if (panel->move == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error visual malloc (%d)\n",sizeof(tMove));
  }

  VIEW_cargaMove(panel->move,move);


  LVIEW_addView(view);

  if (personalFPanel != NULL &&
        personalFPanel->post_create != NULL)
    (*personalFPanel->post_create)(panel);

  return view;
}

tPanel * PANEL_getActivePanel()
{
  return activePanel;
}

int PANEL_addComponent(tPanel * panel,
                       tComponent * componente)
{
  tlComponent * elemento;
  tlComponent * pComponent;

 elemento = malloc (sizeof(tlComponent));
 
 if (elemento == NULL) 
     ERR_fatalError(ERR_MEM,"Fail malloc of panel <%d>\n",sizeof(tlComponent));

 elemento->componente = componente;
 elemento->siguiente = NULL;

 pComponent = panel->elements;
 if (pComponent == NULL)
 {
   panel->elements = elemento;
   return 0;
 }
 while (pComponent->siguiente != NULL)
  pComponent = pComponent->siguiente;

 pComponent->siguiente = elemento;
 
 return 0;
}

int PANEL_delComponent(tPanel * panel,
		       short id,
		       char * name)
{
 tlComponent * elemento ;
 tlComponent * pAnt;

  elemento = panel->elements;
  pAnt = elemento;

  while (elemento != NULL)
  {
      if (id > 0)
      {
	if (elemento->componente->id == id)
        {
          if (elemento == pAnt)
          {
             panel->elements = elemento->siguiente;
          }
          else
          {
             pAnt->siguiente = elemento->siguiente;
          }
          free(elemento);
          return 0;
         }
      }
      else
      {
	if (strcmp(elemento->componente->name,name) == 0)
        {
          if (elemento == pAnt)
          {
            panel->elements = elemento->siguiente;
          }
          else
          {
            pAnt->siguiente = elemento->siguiente;
          }
          free(elemento);
          return 0;
        }
      }
      pAnt = elemento;
      elemento = elemento->siguiente;
  }
  return -1;
}

tComponent * PANEL_searchComponent(tPanel * panel,
		       char * name)
{
 tlComponent * pComponents;
 int id=0;
 char * end;

 if (panel == NULL) return NULL;
 pComponents = panel->elements;
 
 if (name == NULL)  return NULL;

 id = (int)strtol(name,&end,10);
 if (end-name != strlen(name)) id=0;

 while (pComponents != NULL)
 {
    if (id > 0)
    {
	if (pComponents->componente->id == id)
            return pComponents->componente;
    }
    else
    {
      if (strcmp(pComponents->componente->name,name) == 0)
        return pComponents->componente;
    }
   pComponents = pComponents->siguiente;
 }
 return NULL;
}

int  PANEL_changeDim(tPanel * panel,
                  tDim * dimension)
{
  memcpy(&panel->visual->dimension ,dimension,sizeof(tDim));
  return 0;
}

int  PANEL_changeColor(tPanel * panel,
                  tChAttr * color)
{
  memcpy(&panel->visual->color ,color,sizeof(tChAttr));
  return 0;
}

int PANEL_show(tPanel * panel)
{
  tlComponent * elementos=NULL;

  if (panel->visual->status.visible != DIS_NORMAL)
  {
   if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->pre_show != NULL)
     (*((_tFPanel*)panel->personalFPanel)->pre_show)(panel);

   /* ----------------------------------
    *   Show the window.
    * ---------------------------------- */
   wclear(panel->visual->win);
   wattron(panel->visual->win,COLOR_PAIR(panel->visual->color.colorpair)|panel->visual->color.attr);
   wbkgd(panel->visual->win,COLOR_PAIR(panel->visual->color.colorpair));

   if (panel->visual->dimension.border)
    VISUAL_border(panel->visual->win,0);


  if (strcmp(panel->title,"") != 0)
    VISUAL_pintaTitle(panel->visual,panel->title);

  wrefresh(panel->visual->win);

  /* ---------------------
   *  Show the components.
   * ------------------------ */
  elementos=panel->elements;
  while (elementos != NULL)
  {
    COMPONENT_show(elementos->componente);
    elementos = elementos->siguiente;
  }

   if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->post_show != NULL)
      (*((_tFPanel*)panel->personalFPanel)->post_show)(panel);

    panel->visual->status.visible = DIS_NORMAL;
  }
  return 0;
}

int PANEL_refresh(tPanel * panel)
{
  tlComponent * elementos=NULL;

  /* ----------------------------------
   *   Show the window.
   * ---------------------------------- */
   wclear(panel->visual->win);
   wattron(panel->visual->win,COLOR_PAIR(panel->visual->color.colorpair)|panel->visual->color.attr);
   wbkgd(panel->visual->win,COLOR_PAIR(panel->visual->color.colorpair));

   if (panel->visual->dimension.border)
    VISUAL_border(panel->visual->win,0);


  if (strcmp(panel->title,"") != 0)
    VISUAL_pintaTitle(panel->visual,panel->title);

  wrefresh(panel->visual->win);

  /* ---------------------
   *  Show the components.
   * ------------------------ */
  elementos=panel->elements;
  while (elementos != NULL)
  {
    COMPONENT_show(elementos->componente);
    elementos = elementos->siguiente;
  }
  return 0;
}

int PANEL_activate(tPanel * panel,char * ncomponent)
{
  tComponent * component=NULL;

  if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->pre_activate != NULL)
    (*((_tFPanel*)panel->personalFPanel)->pre_activate)(panel);

   if (ncomponent != NULL && !strcmp(ncomponent,"")==0) {
     component = PANEL_searchComponent(panel,ncomponent);
     while (component!=NULL && 
	(component->visual->status.visible == DIS_HIDDEN ||
	 component->visual->status.visible == DIS_NO_SELECT) )
     {
      if (component->move->next != NULL && component->move->next[0]==':') 
       component = PANEL_searchComponent(panel,component->move->next+1);
      else
       component = NULL;
     }
   }
   else
   {
     if (panel->elements != NULL)
       component = panel->elements->componente;
   }

  if (component != NULL && component != panel->activeElement)
  {
    if (panel->activeElement != NULL)
      COMPONENT_deactivate(panel->activeElement);
  }

  if (component != NULL)
  {
     panel->activeElement=component;
/*     wrefresh(panel->visual->win); */
     COMPONENT_activate(component);
  }

  activePanel = panel;

  if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->post_activate != NULL)
      (*((_tFPanel*)panel->personalFPanel)->post_activate)(panel);

  return 0;
}

void PANEL_Action(tPanel * panel,tNextPtr next)
{
 int tecla;
 int atras = 0;
 trAction * accion;
 tCaller * auxCaller;
 char npanel[MAX_NAME_VIEW]="";
 char * ncomponent;
 char * paux;
 MEVENT ev_mouse;
 int wx,wy;
 char nActComponent[MAX_NAME_VIEW+MAX_COMPONENT_NAME+5];
 static trAction mouseAction = {0,1,OP_NONE,NULL};
 mmask_t mmask, oldmmask;
 int hasMouse;

  strcpy(next->view,"");
  hasMouse = KEYS_getMouse();
  next->opToMade=OP_NONE;
  mmask=BUTTON1_CLICKED|BUTTON3_CLICKED;

  if (panel->activeElement != NULL)
  {
     keypad(panel->visual->win,TRUE);
     while (1)
     {
       accion = NULL;
       sprintf(nActComponent,"%s:%s",panel->name,panel->activeElement->name);
       
       if (hasMouse) mousemask(mmask, &oldmmask);
       tecla = wgetch(panel->visual->win);
       if(hasMouse && tecla == KEY_MOUSE)
       {
 	 if(getmouse(&ev_mouse) == OK)
         {
           wx = ev_mouse.x; wy = ev_mouse.y;
           mouseAction.componentNext = LVIEW_searchXYView(wx,wy);
           if (mouseAction.componentNext != NULL &&
		strcmp(mouseAction.componentNext,"")!=0) {
             if (strcmp(mouseAction.componentNext, nActComponent)== 0){
               if(ev_mouse.bstate & BUTTON1_CLICKED){
                tecla=panel->activeElement->mapkey->enter[0];
                accion = COMPONENT_Action(panel->activeElement,tecla);
               }
               if(ev_mouse.bstate & BUTTON3_CLICKED){
                 tecla=panel->activeElement->mapkey->out[0];
                 accion = COMPONENT_Action(panel->activeElement,tecla);
               }
             }
             else {
               accion=&mouseAction;
             }
           }
         }
       }
       else
       {
        accion = COMPONENT_Action(panel->activeElement,tecla);
       }

       if (accion != NULL && accion->error == 0 && accion->made == 1)
       {
         if (accion->componentNext != NULL)
         {
           if (strcmp(accion->componentNext,":")==0 ||	
	       strcmp(accion->componentNext,"exit:")==0) return;
           paux = accion->componentNext;
           memset(npanel,'\0',sizeof(npanel));
           while (*paux!=':'&& *paux!='\0') paux ++;
           if (*paux==':')
           {
            strncpy(npanel,accion->componentNext,(paux - accion->componentNext));
            ncomponent = ++paux;
            if (strcmp(npanel,"") == 0)
             PANEL_activate(panel,ncomponent);
            else
            {
              if (strcmp(npanel,panel->name)!=0)
              {
                 if (npanel[0]!='-'){
                   strcpy(next->view,npanel);
                   strcpy(next->element,ncomponent);
                   next->caller.View=panel->name;
                   next->caller.Element=panel->activeElement->name;

                   next->opToMade = accion->opToMade==OP_NONE?panel->opToMade:accion->opToMade;
                 }
                 else {
		   atras = strlen(npanel)>=2?npanel[1]-'0':1;
                   auxCaller = VIEW_getAtras(atras);
                   if (auxCaller != NULL) {
                     strcpy(next->view,auxCaller->View);
                     if (auxCaller->Element == NULL)
		       strcpy(next->element,"");
                     else
		       strcpy(next->element,auxCaller->Element);
		   }
                   else{
                     strcpy(next->view,"");
	             strcpy(next->element,"");
                   }
                   next->opToMade = accion->opToMade==OP_NONE?panel->opToMade:accion->opToMade;
                 }
                 return;
              }
              else
              {
                PANEL_activate(panel,ncomponent);
              }
            }
           }
           else
             ERR_Error(ERR_VIEW," move %s wrong must be panel:component \n ",accion->componentNext);
         }
       }
     }
  }
}

int PANEL_opToMade(tPanel * panel)
{
  switch(panel->opToMade){
    case OP_HIDE: return PANEL_hide(panel);
    case OP_DESTROY: return PANEL_destroy(panel);
    default: return 0;
  }
}

int PANEL_hide(tPanel * panel)
{

 if (panel->visual->status.visible != DIS_NORMAL) return 0; 

 if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->pre_hide != NULL)
     (*((_tFPanel*)panel->personalFPanel)->pre_hide)(panel);

 if (panel->activeElement != NULL)
      COMPONENT_deactivate(panel->activeElement);

  /* ---------------------
   *  BACK_POP 
   * ------------------------ */
 panel->visual->status.visible=DIS_HIDDEN;

 if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->post_hide != NULL)
     (*((_tFPanel*)panel->personalFPanel)->post_hide)(panel);

 activePanel = NULL;
 return 0;
}

int PANEL_destroy(tPanel * panel)
{
  int retorno;
  int i,j;
  tlComponent * aux;

  if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->pre_destroy != NULL)
     (*((_tFPanel*)panel->personalFPanel)->pre_destroy)(panel);

  aux = panel->elements;
  while (aux != NULL)
  {
    if (aux->componente->type == C_EDIT) {
      for (i=0;i!=aux->componente->text->maxLines;i++)
       for (j=0;j!=aux->componente->text->maxFields;j++)
         aux->componente->text->text[i][j][0]='\0';
    }
    if (aux->componente->type==C_CKBUTTON && 
			aux->componente->visual->status.defCheck)
      aux->componente->text->check=1; else aux->componente->text->check=0;

    TEXT_clear(aux->componente->text);

    aux->componente->visual->status.actLine=0;
    aux->componente->visual->status.actColumn=0;
    aux->componente->visual->status.actField=0;
    aux->componente->visual->cursor.y = aux->componente->visual->dimension.border;

    aux = aux->siguiente;
  }
 
  retorno=PANEL_hide(panel);

  if (panel->personalFPanel != NULL &&
        ((_tFPanel *)panel->personalFPanel)->post_destroy != NULL)
     (*((_tFPanel*)panel->personalFPanel)->post_destroy)(panel);

  return retorno;
}

char * PANEL_searchXYComponent(tPanelPtr panel,int x,int y)
{
  tlComponent * aux;
  static char nNext[MAX_NAME_VIEW+MAX_COMPONENT_NAME+5];

  aux = panel->elements;

  while (aux != NULL)
  {
     if ( aux->componente->type != C_LABEL &&
          x >= aux->componente->visual->dimension.x &&
          x <= aux->componente->visual->dimension.x+
		aux->componente->visual->dimension.ancho-1 &&
          y >= aux->componente->visual->dimension.y &&
          y <= aux->componente->visual->dimension.y+
               aux->componente->visual->dimension.alto-1)
     {
       if (aux->componente->visual != NULL 
		&& aux->componente->visual->status.visible == DIS_NORMAL){
        sprintf(nNext,"%s:%s",panel->name,aux->componente->name);
        return nNext;
       }
     }
     aux = aux->siguiente;
  }
  return NULL;
}




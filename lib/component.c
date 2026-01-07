#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <tBasic.h>
#include <color.h>
#include <text.h>
#include <msg.h>
#include <error.h>
#include <visual.h>
#include <keys.h>
#include <fedit.h>
#include <panel.h>
#include <view.h>
#include <back.h>
#include <component.h>

static int idComponent = 0;
static trAction rAction;

static void COMPONENT_TypeAction(tComponent * component,int action);
static int COMPONENT_ediccion(tComponent * component, int tecla);
static char * COMPONENT_searchMove(tComponent * component,int move,int Fn);
static trAction * COMPONENT_searchAction(tComponent * component,
			int move,int caracter,int Fn);


tComponent * COMPONENT_create(tPanel * panel,
			char * name, 
			char type, 
			tDim * dimension, 
			tChAttr * color, 
			tmapKeys * mapkey,
			tMove * move,
			_tFActionPanel * personalAction,
                        _tFComponent * personalFComponent)
{
  tComponent * component;

  if (personalFComponent != NULL &&
        personalFComponent->pre_create != NULL)
    (*personalFComponent->pre_create)(name);

  component = malloc(sizeof(tComponent));
  if (component == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error malloc component (%d)\n",sizeof(tComponent));
    return NULL;
  }

  component->parent=panel;

  strncpy(component->name,name,sizeof(component->name));
  component->id=++idComponent;
  component->type = type;
  component->editMode = NULL;

  component->personalAction = (tFActionPanel *) personalAction;
  component->personalFComponent = (tFComponent *)personalFComponent;

  component->visual = 
	VISUAL_createComponent(component->type,
			panel->visual->win,dimension, color);
  
  component->visual->wBack=NULL;
  component->visual->status.actLine=0;
  component->visual->status.actColumn=0;

  if (mapkey == NULL)
  {
    switch (component->type)
    {
      case C_LABEL:
            component->mapkey= (tmapKeys *)&KEY_STD_LABEL;
            break;
      case C_BUTTON:
            component->mapkey= (tmapKeys *)&KEY_STD_BUTTON;
            break;
      case C_CKBUTTON:
            component->mapkey= (tmapKeys *)&KEY_STD_BUTTON;
            break;
      case C_LSBUTTON:
            component->mapkey= (tmapKeys *)&KEY_STD_BUTTON;
            break;
      case C_EDIT:
            component->mapkey= (tmapKeys *)&KEY_STD_EDIT;
            break;
      default:
       component->mapkey=NULL;
    }
  }
  else
   component->mapkey= mapkey;

  component->visual->status.insert = Insert;   
  component->move = malloc(sizeof(tMove));
  if (component->move == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error visual malloc (%d)\n",sizeof(tMove));
  }

  VIEW_cargaMove(component->move,move);

  if (personalFComponent != NULL &&
        personalFComponent->post_create != NULL)
    (*personalFComponent->post_create)(component);

  return component;
}

void COMPONENT_display(tComponent * component, int visible) {
 tPanel * aux;

  if (component == NULL || component->visual == NULL) return;
  if (component->visual->status.visible == visible) return;

  aux = PANEL_getActivePanel();
  if (aux != NULL && aux == component->parent) {
   if (component->visual->status.visible == DIS_HIDDEN &&
       visible != DIS_OPEN) {
      component->visual->status.visible = visible;
      COMPONENT_show(component);
   }
   if (component->visual->status.visible==DIS_NORMAL && visible ==DIS_HIDDEN){
        COMPONENT_hide(component,&PANEL_getActivePanel()->visual->color);
        component->visual->status.visible = visible;
   }
   wrefresh(PANEL_getActivePanel()->visual->win);
  }
  component->visual->status.visible = visible;
}

void COMPONENT_createEdit(tComponent * component, tEDIT * editMode)
{
 component->editMode = malloc(sizeof(tEDIT));
 if (component->editMode == NULL)
        ERR_fatalError(ERR_MEM,"Error malloc component edit (%d)\n",
					sizeof(tEDIT));
 memcpy(component->editMode,editMode,sizeof(tEDIT));
 component->visual->status.align=FEDIT_getAlign(component->editMode->editType);
 component->visual->status.insert=FEDIT_getInsert(component->editMode->editType);
}

int COMPONENT_simpleText(tComponent * component, char * text,
						unsigned short delete)
{
  component->text = TEXT_newSimpleText(&component->visual->dimension,text,delete);
  return 0;
}

int COMPONENT_changeColor(tComponent * component, tChAttr * color)
{
 return VISUAL_changeColor(component->visual,color,component->text,component->editMode);
}

int COMPONENT_show(tComponent * component)
{
 int i;

  if (component->visual->status.visible == DIS_HIDDEN ||
      component->visual->status.visible == DIS_OPEN)
     return 0;

  if (component->personalFComponent != NULL &&
        ((_tFComponent *)component->personalFComponent)->pre_show != NULL)
     (*((_tFComponent*)component->personalFComponent)->pre_show)(component);


  i = VISUAL_showComponent(component->visual, component->text,component->editMode);

  if (i==0 && component->personalFComponent != NULL &&
       ((_tFComponent *)component->personalFComponent)->post_show != NULL)
     (*((_tFComponent*)component->personalFComponent)->post_show)(component);


  if (component->text != NULL) component->text->actLine=0;
  if (component->type == C_EDIT) 
		component->text->nroLines=component->text->maxLines;
  return i;
}

int COMPONENT_hide(tComponent * component,tChAttr *parentColor)
{
 int i;

  if (component->visual->status.visible == DIS_HIDDEN ||
      component->visual->status.visible == DIS_OPEN ) return 0;

  if (component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->pre_hide != NULL)
    (*((_tFComponent*)component->personalFComponent)->pre_hide)(component);

  i = VISUAL_hideComponent( component->visual,parentColor);

  component->visual->status.actLine=0;
  component->visual->status.actColumn=0;

  if (component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->post_hide != NULL)
    (*((_tFComponent*)component->personalFComponent)->post_hide)(component);

  return i;
}
   
int COMPONENT_refresh(tComponent * component)
{
  if (component == NULL) return ERR_COMPONENT;
/*
  return VISUAL_activateComponent(component->visual,component->text,
						component->editMode);
*/
  return VISUAL_showComponent(component->visual, component->text,component->editMode);
}

int COMPONENT_activate(tComponent * component)
{
 int i,cursor;
 tPanel * aux;

  if (component == NULL) return ERR_COMPONENT;

  if (component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->pre_activate != NULL)
    (*((_tFComponent*)component->personalFComponent)->pre_activate)(component);

  if (component->visual->status.visible == DIS_OPEN){
     aux = PANEL_getActivePanel();
     if (aux != NULL && aux == component->parent) 
       component->visual->wBack = 
		BACK_pushWindow(PANEL_getActivePanel()->visual->win);
  }

  i = VISUAL_activateComponent(component->visual,component->text,
						component->editMode);

  if (component->type != C_EDIT){
      cursor=0;
  }
  else {
   component->visual->status.actLine=0;
   component->visual->status.actColumn=0;

   VISUAL_setXY(component->visual,
			component->visual->status.actLine,
			component->visual->status.actColumn);

   cursor=1;
  }

  if (i==0) i=VISUAL_cursor(cursor); 

  if( component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->post_activate != NULL)
      (*((_tFComponent*)component->personalFComponent)->post_activate)(component);
  return i;
} 

int COMPONENT_deactivate(tComponent * component)
{
 int i=0;
 tPanel * aux;

  if (component == NULL) return ERR_COMPONENT;
  if (component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->pre_deactivate != NULL)
    (*((_tFComponent*)component->personalFComponent)->pre_deactivate)(component);
  if (component->visual->status.visible == DIS_OPEN){
    component->visual->status.activa = 0; 
    aux = PANEL_getActivePanel();
    if (aux != NULL && aux == component->parent) 
      BACK_restoreWindow(aux->visual->win, component->visual->wBack);
  }
  else {
   i = VISUAL_deactivateComponent(component->visual,component->text,component->editMode);
  }
  VISUAL_cursor(0); 

  
  if (i==0&&component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->post_deactivate != NULL)
    (*((_tFComponent*)component->personalFComponent)->post_deactivate)(component);

  return i;
} 

int COMPONENT_changeText(tComponent * component ,char * text)
{
 if (component == NULL) return ERR_COMPONENT;
  if (component->text != NULL)
  {
     TEXT_free(component->text);
  }
  if (text == NULL) return ERR_DATA;
  component->text = TEXT_newSimpleText(&component->visual->dimension,text,
                                       component->text->delete);
  return VISUAL_changeTextComponent(component->visual,
			component->text,component->editMode);

  return 0;
}

char * COMPONENT_getText(tComponent * component)
{
  if (component == NULL) return NULL;
  if (component->text == NULL || component->text->text[0][0] == NULL)
   return NULL;
  return component->text->text[0][0];
}

int COMPONENT_setText(tComponent * component,char * text)
{
  if (component == NULL) return ERR_COMPONENT;
  if (component->text != NULL)
  {
     TEXT_free(component->text);
  }
  component->text = TEXT_newSimpleText(&component->visual->dimension,text,
		component->text->delete);
  return 0;
}

char * COMPONENT_getValue(tComponent * component)
{
 int fila,i,len=0,len2=0;
 static int lenMaxTexto=0;
 static char * aux = NULL;

  if (component == NULL) return NULL;
  if (component->text == NULL) return NULL;

  switch (component->type)
  {
    case C_CKBUTTON:
        if (!component->text->check) return NULL;
        return (char*)&component->text->check;
        break;
    case C_EDIT:
        if (component->text->maxLines == 1)
            return component->text->text[0][0];
        for (i=0;i!=component->text->maxLines;i++)
           len+=strlen(component->text->text[i][0]);
        if ((len+component->text->maxLines) > lenMaxTexto) {
	   if (aux == NULL) {
              aux=(char *) malloc((len+component->text->maxLines)+2); 
              if (aux == NULL) {
                ERR_fatalError(ERR_MEM,"Error malloc getValue (%d)\n",len);
                return NULL;
              }
              lenMaxTexto=(len+component->text->maxLines);
           }
           else { 
              aux=(char *) realloc(aux,(len+component->text->maxLines+2)); 
              if (aux == NULL) {
                 ERR_fatalError(ERR_MEM,"Error realloc getValue (%d)\n",len);
                 return NULL;
              }
              lenMaxTexto=(len+component->text->maxLines);
           }
        }
        strcpy(aux,"");
        for (i=0,len2=0;i!=component->text->maxLines&&len2<len;i++) {
          if (i!=0) {strcat(aux,"\n");len2++;}
          if (component->text->text[i][0]!=NULL) {
	       strcat(aux,component->text->text[i][0]);
               len2+=strlen(component->text->text[i][0]);
          }
        }
        return aux;
        break;
    case C_LSBUTTON:    
       fila = component->visual->status.actLine+
		component->text->actLine + 
		component->visual->cursor.y - 
		component->visual->dimension.border;
       return component->text->text[fila][0];
       break;
    default:
       break;
  }
 return NULL;
}

int COMPONENT_isValue(tComponent * component,char * text)
{
 int i;

  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;

  switch (component->type)
  {
    case C_CKBUTTON:
        if (component->text->check && text == NULL) return 1;
        return 0;
        break;
    case C_LABEL:
    case C_EDIT:
    case C_LSBUTTON:
        for (i=0;i!=component->text->nroLines;i++){
           if (strcmp(component->text->text[i][0],text)==0)
             return 1;
        }
        return 0;
        break;
    default:
       break;
  }
 return 0;
}

int COMPONENT_setSelectValue(tComponent * component,int line,char * texto)
{
int i,fila=ERR_DATA;

  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;
  if (component->type != C_LSBUTTON) return ERR_DATA;
  
  if (texto!=NULL){
   for (i=0;i!=component->text->nroLines;i++){
     if (strcmp(component->text->text[i][0],texto)==0) {
       fila=i;
       break;
    }
   }
  } else fila = line;
  if (fila < 0) return ERR_DATA;
  
  if (fila >= component->text->nroLines) return ERR_DATA;
  component->visual->status.actLine=fila;
  component->visual->cursor.y=component->visual->dimension.border;
  return 0;
}

char *  COMPONENT_getSelectValue(tComponent * component,int * line)
{
 int fila;

  fila = component->visual->status.actLine+
		component->text->actLine + 
		component->visual->cursor.y - 
		component->visual->dimension.border;
  *line = fila;
  return component->text->text[fila][0];
}

int COMPONENT_clean(tComponent * component) {
unsigned short prevDelete;

  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;

  prevDelete = component->text->delete;
  component->text->delete=1;
  switch (component->type)
  {
    case C_CKBUTTON:
        component->text->check=0;
        TEXT_clear(component->text);
        break;
    case C_EDIT:
        TEXT_clear(component->text);
        break;
    case C_LSBUTTON:
        TEXT_clear(component->text);
        break;
    case C_LABEL:
        TEXT_clear(component->text);
    default:
       break;
  }
  component->text->delete=prevDelete;
  return 0;
}

int COMPONENT_addText(tComponent * component,char * texto) {
  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;

  switch (component->type)
  {
    case C_CKBUTTON:
    case C_LABEL:
        TEXT_addSimpleData(component->text,texto);
        break;
    case C_EDIT:
        TEXT_addSimpleData(component->text,texto);
        break;
    case C_LSBUTTON:
        TEXT_addSimpleData(component->text,texto);
        break;
    default:
        break;
  }
  return 0;
}

int COMPONENT_delText(tComponent * component,char * texto) {
  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;

  TEXT_delSimpleData(component->text,texto);
  return 0;
}

int COMPONENT_setValue(tComponent * component,char * texto)
{
  if (component == NULL) return ERR_COMPONENT;
  if (component->text == NULL) return ERR_DATA;

  switch (component->type)
  {
    case C_CKBUTTON:
        if (texto == NULL) component->text->check=0;
         else component->text->check=1;
        break;
    case C_EDIT:
    case C_LABEL:
        component->text->delete=1;
        TEXT_clear(component->text);
        TEXT_addSimpleData(component->text,texto);
        break;
    case C_LSBUTTON:
        return COMPONENT_setSelectValue(component,-1,texto);
        break;
    default:
        break;
  }
 return 0;
}


int COMPONENT_destroy(tComponent * component)
{
 int i;

  if (component == NULL) return ERR_COMPONENT;
  if (component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->pre_destroy != NULL)
    (*((_tFComponent*)component->personalFComponent)->pre_destroy)(component);

  if (component->type==C_CKBUTTON && component->visual->status.defCheck)
    component->text->check=1; else component->text->check=0;

  TEXT_free(component->text);
  i=VISUAL_destroy(component->visual);

  if (i==0&&component->personalFComponent != NULL &&
	((_tFComponent *)component->personalFComponent)->post_destroy != NULL)
    (*((_tFComponent*)component->personalFComponent)->post_destroy)(component);

  free(component);
  return i; 
}

trAction * COMPONENT_Action(tComponent * component,int caracter)
{
  int i,j;
  trAction * resultado;

  rAction.error =0;
  rAction.made =0;
  rAction.componentNext=NULL;
  rAction.opToMade=OP_NONE;

  if (component == NULL) return NULL;

  for (i=0;i!= MAX_KEYS_FUNC;i++)
  {
    if (component->mapkey->enter[i]!=0&&
         component->mapkey->enter[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_enter,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made )
        {
             rAction.opToMade=resultado->opToMade;
             rAction.componentNext = resultado->componentNext;
        }
      }
      if (!rAction.error && !rAction.made)
      {
         rAction.componentNext=COMPONENT_searchMove(component,A_enter,0);
         rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
         if (!rAction.made || component->type == C_CKBUTTON) 
	    COMPONENT_TypeAction(component,A_enter);
      }
      return &rAction;
    }
    if (component->mapkey->out[i]!=0&&
         component->mapkey->out[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_out,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_out,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
      }
      return &rAction;
    }
    if (component->mapkey->next[i]!=0&&
         component->mapkey->next[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_next,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
             rAction.componentNext = resultado->componentNext;
             rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_next,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
      }
      return &rAction;
    }
    if (component->mapkey->previous[i]!=0&&
         component->mapkey->previous[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_previous,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
            rAction.componentNext = resultado->componentNext;
            rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_previous,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
      }
      return &rAction;
    }
    if (component->mapkey->up[i]!=0&&
         component->mapkey->up[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_up,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
           rAction.componentNext = resultado->componentNext;
           rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_up,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_up);
      }
      return &rAction;
    }
    if (component->mapkey->down[i]!=0&&
         component->mapkey->down[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_down,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
           rAction.componentNext = resultado->componentNext;
           rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made) 
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_down,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_down);
      }
      return &rAction;
    }
    if (component->mapkey->left[i]!=0&&
         component->mapkey->left[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_left,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
            rAction.componentNext = resultado->componentNext;
            rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made) 
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_left,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_left);
      }
      return &rAction;
    }

    if (component->mapkey->right[i]!=0&&
         component->mapkey->right[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_right,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_right,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_right);
      }
      return &rAction;
    }

    if (component->mapkey->back[i]!=0&&
         component->mapkey->back[i] == caracter)
    { 
      if ((resultado =  COMPONENT_searchAction(component,A_back,caracter,0)) != NULL)
      {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made)
      {
          rAction.componentNext=COMPONENT_searchMove(component,A_back,0);
          rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_back);
      }
      return &rAction;
    }


    for (j=0;j!=MAX_Fn_KEYS;j++)
    {
       if (component->mapkey->Fn[j][i]!=0&&
            component->mapkey->Fn[j][i] == caracter)
       { 
         if ((resultado =  COMPONENT_searchAction(component,A_Fn,caracter,j+1)) != NULL)
         {
           rAction.error = resultado->error;
           rAction.made = resultado->made;
           if (!resultado->error && resultado->made)
           {
               rAction.componentNext = resultado->componentNext;
               rAction.opToMade=resultado->opToMade;
           }
         }
         if (!rAction.error && !rAction.made && component->move != NULL)
         {
           rAction.componentNext=COMPONENT_searchMove(component,A_Fn,j);
           rAction.made = 
	   rAction.componentNext==NULL||strcmp(rAction.componentNext,"")==0?0:1;
         }
         return &rAction;
       }
    }   
  } 

  if (COMPONENT_ediccion(component, caracter) &&
	component->editMode != NULL && component->editMode->autoComplet) {
     if ((resultado =  COMPONENT_searchAction(component,A_enter,caracter,0)) != NULL)
     {
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made )
        {
             rAction.opToMade=resultado->opToMade;
             rAction.componentNext = resultado->componentNext;
        }
     }
     if (!rAction.error && !rAction.made && component->move != NULL)
     {
          rAction.made = component->move->enter==NULL?0:1;
          rAction.componentNext = component->move->enter;
          if (!rAction.made) 
	    COMPONENT_TypeAction(component,A_enter);
     }
  }

  return &rAction;
}

int COMPONENT_editMode(tComponent * component, int mode)
{
   component->visual->status.insert = mode;   
   return 0;
}

static int COMPONENT_ediccion(tComponent * component, int tecla)
{
 int len;

  if (component->type == C_EDIT)
  {
    if (KEYS_isInsert(tecla)){
     if (component->visual->status.insert == Insert)   
      component->visual->status.insert = Replace;
     else {
      if (component->visual->status.insert == Replace)   
       component->visual->status.insert = Insert;
     }
     return 0;
    }

    if (KEYS_isDelete(tecla)) {
       len=strlen(component->text->text[component->visual->status.actLine][0]);
       if (component->visual->status.actColumn < len) {
           strcpy(component->text->text[component->visual->status.actLine][0]+
		  component->visual->status.actColumn,
		  component->text->text[component->visual->status.actLine][0]+
			  component->visual->status.actColumn+1);
           component->text->actLine = component->visual->status.actLine;
           VISUAL_pintaLinea(component->visual,
				component->text,component->editMode);
           VISUAL_setXY(component->visual,
			component->visual->status.actLine,
			component->visual->status.actColumn);
        
       }
       return 0;
    }

    if (component->editMode != NULL)
    {
      if (FEDIT_checkEdit(component->editMode->editType, &tecla))
       beep();
      else
      {
        if (component->visual->status.insert == Insert){
           if (component->visual->status.actColumn >=
	       component->visual->status.nactColumns &&
	      component->visual->status.actLine >=
               component->visual->status.nactLines){
            beep();
            return 0;
           }	
           if (component->visual->status.actColumn >=
	       component->visual->status.nactColumns)
           {
             component->visual->status.actLine++;
             component->visual->status.actColumn=0;
           }
           TEXT_addChar(component->text,
		component->visual->status.actLine,0,
		component->visual->status.actColumn,tecla,
		component->visual->status.insert);
            VISUAL_pintaLinea(component->visual,
				component->text,component->editMode);

            component->visual->status.actColumn++;

            if (component->visual->status.actColumn >=
		 component->visual->status.nactColumns){
               component->visual->status.actColumn=0;
               component->visual->status.actLine++;
            }

            if (component->visual->status.actLine >=
		 component->visual->status.nactLines)
            {
               component->visual->status.actLine=0;
              return 1;
            }

            component->visual->cursor.x=
			component->visual->status.actColumn +
                        component->visual->dimension.border;
            component->visual->cursor.y=
			component->visual->status.actLine +
                        component->visual->dimension.border;
            
            VISUAL_setXY(component->visual,
			component->visual->status.actLine,
			component->visual->status.actColumn);
        }
        else {
         switch(VISUAL_addChar(component->visual,tecla))
         {
          case 0:
            TEXT_addChar(component->text,
		component->visual->status.actLine,0,
		component->visual->status.actColumn,tecla,
		component->visual->status.insert);
            component->text->actColumn++;
            component->visual->status.actColumn++;
            break;
          case 1:
            TEXT_addChar(component->text,
		component->visual->status.actLine,0,
		component->visual->status.actColumn,tecla,
		component->visual->status.insert);
            component->visual->status.actColumn=0;
            component->visual->status.actLine++;
            break;
          case 2:
            TEXT_addChar(component->text,
		component->visual->status.actLine,0,
		component->visual->status.actColumn,tecla,
		component->visual->status.insert);
            component->visual->status.actColumn=0;
            component->visual->status.actLine=0;
            return 1;
            break;
          default:
	    break;
         }
        }
       }
    }
  }
  else
    beep();

  return 0;
}


static void COMPONENT_TypeAction(tComponent * component,int action)
{
 int len;

   switch(component->type)
   {
     case C_LABEL:
		break;
     case C_BUTTON:
		break;
     case C_CKBUTTON:
	   switch(action)
           {
            case  A_enter:
		   TEXT_check(component->text);
                   VISUAL_activateComponent(component->visual,
				component->text,component->editMode);
                  break;
            case  A_out:
            case  A_previous:
            case  A_up:
            case  A_left:
                  if (component->visual->status.actLine > 0)
                   component->visual->status.actLine--;
                  VISUAL_activateComponent(component->visual,
				component->text,component->editMode);
                  break;
            case  A_next:
            case  A_down:
            case  A_right:
                 if (component->visual->status.actLine < component->text->nroLines-1)
                  component->visual->status.actLine++;
                 VISUAL_activateComponent(component->visual,
				component->text,component->editMode);
                 break;
            case  A_Fn:
            case  A_back:
		break;
            default: break;
           }
	   break;
     case C_LSBUTTON:
	   switch(action)
           {
            case  A_enter:
            case  A_out:
		break;
            case  A_previous:
            case  A_left:
		break;
            case  A_up:
                if (component->visual->cursor.y > 
			component->visual->dimension.border)
                  component->visual->cursor.y--;
                else
                {
                  if (component->visual->status.actLine > 0)
                   component->visual->status.actLine--;
                  else 
                    break;
                }
                VISUAL_activateComponent(component->visual,
				component->text,component->editMode);
                break;
            case  A_next:
            case  A_right:
		break;
            case  A_down:
                if ((component->visual->cursor.y -
		     component->visual->dimension.border) <
			component->visual->status.nactLines-1) {
                   component->visual->cursor.y++;
                   if (component->text->nroLines <=
                       (component->visual->status.actLine +
                        component->visual->cursor.y -
			component->visual->dimension.border)){
                     component->visual->cursor.y--;
                     break;
                   }
                }
                else {
                 if (component->visual->status.actLine < 
			 component->text->nroLines - 
				component->visual->status.nactLines)
                    component->visual->status.actLine++;
                  else
                    break;
                }
                VISUAL_pintaTexto(component->visual,
				component->text,component->editMode);
                break;
            case  A_Fn:
            case  A_back:
		break;
            default: break;
           }
           break;
     case C_EDIT:
	   switch(action)
           {
             case A_left: 
                 if (component->visual->status.actColumn !=0)
                 {
                     component->visual->status.actColumn--;
                     VISUAL_setXY(component->visual,
			component->visual->status.actLine +
			component->visual->dimension.border,
			component->visual->status.actColumn);
                 }
		 break;
             case A_right: 
                 len=strlen(component->text->text[component->visual->status.actLine][0]);
                 if (component->visual->status.actColumn < len)
                 {
                     component->visual->status.actColumn++;
                     if (component->visual->status.actColumn >=
			 component->visual->status.nactColumns){
                       component->visual->status.actColumn=0;
                     }
                     VISUAL_setXY(component->visual,
			component->visual->status.actLine+
			component->visual->dimension.border,
			component->visual->status.actColumn);
                 }
                 break;
             case A_back: 
                 if (component->visual->status.actColumn !=0) {
                  strcpy(component->text->text[component->visual->status.actLine][0]+
		          component->visual->status.actColumn-1,
			  component->text->text[component->visual->status.actLine][0]+
			  component->visual->status.actColumn);
                     component->visual->status.actColumn--;
                  component->text->actLine = component->visual->status.actLine;
                  VISUAL_pintaLinea(component->visual,
				component->text,component->editMode);
                  VISUAL_setXY(component->visual,
			component->visual->status.actLine+
			component->visual->dimension.border,
			component->visual->status.actColumn);
                 }
                 break;
             case A_up: 
                 if (component->visual->status.actLine !=0) {
                    component->visual->status.actLine--; 
                    len=strlen(component->text->text[component->visual->status.actLine][0]);
                    if (len < component->visual->status.actColumn)
                       component->visual->status.actColumn = len;
                    component->visual->cursor.x=
			component->visual->status.actColumn +
                        component->visual->dimension.border;
                    component->visual->cursor.y=
			component->visual->status.actLine +
                        component->visual->dimension.border;
                    VISUAL_setXY(component->visual,
			component->visual->cursor.y,
			component->visual->cursor.x);
                 }
                 break;
             case A_enter: 
             case A_down: 
                 if (component->visual->status.actLine < 
				component->visual->status.nactLines-1) {
                    component->visual->status.actLine++; 
                    len=strlen(component->text->text[component->visual->status.actLine][0]);
                    if (len < component->visual->status.actColumn)
                     component->visual->status.actColumn = len;

                    VISUAL_setXY(component->visual,
			component->visual->status.actLine+
			component->visual->dimension.border,
			component->visual->status.actColumn);
                  }
                 break;
             default: break;
           }
           break;
     default: break;
   }
}

static char * COMPONENT_searchMove(tComponent * component,int move,int Fn)
{
  tComponent * aux,* auxNext;
  char * value=NULL;

  aux = component;

   while (aux != NULL && aux->move!=NULL)
   {
     switch(move){
        case A_enter:
          if (aux->move !=NULL && aux->move->enter != NULL) 
            value = aux->move->enter;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->enter != NULL) 
            value=((tPanel *)aux->parent)->move->enter;
          }
          break;
        case A_out:
          if (aux->move !=NULL && aux->move->out != NULL) 
            value = aux->move->out;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->out != NULL) 
            value=((tPanel *)aux->parent)->move->out;
          }
          break;
        case A_next:
          if (aux->move !=NULL && aux->move->next != NULL) 
            value = aux->move->next;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->next != NULL) 
            value=((tPanel *)aux->parent)->move->next;
          }
          break;
        case A_previous:
          if (aux->move !=NULL && aux->move->previous != NULL) 
            value = aux->move->previous;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->previous != NULL) 
            value=((tPanel *)aux->parent)->move->previous;
          }
          break;
        case A_up:
          if (aux->move !=NULL && aux->move->up != NULL) 
            value = aux->move->up;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->up != NULL) 
            value=((tPanel *)aux->parent)->move->up;
          }
          break;
        case A_down:
          if (aux->move !=NULL && aux->move->down != NULL) 
            value = aux->move->down;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->down != NULL) 
            value=((tPanel *)aux->parent)->move->down;
          }
          break;
        case A_right:
          if (aux->move !=NULL && aux->move->right != NULL) 
            value = aux->move->right;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->right != NULL) 
            value=((tPanel *)aux->parent)->move->right;
          }
          break;
        case A_left:
          if (aux->move !=NULL && aux->move->left != NULL) 
            value = aux->move->left;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->left != NULL) 
            value=((tPanel *)aux->parent)->move->left;
          }
          break;
        case A_back:
          if (aux->move !=NULL && aux->move->back != NULL) 
            value = aux->move->back;
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->back != NULL) 
            value=((tPanel *)aux->parent)->move->back;
          }
          break;
        case A_Fn:
          if (aux->move !=NULL && aux->move->Fn[Fn] != NULL) 
            value = aux->move->Fn[Fn];
          else {
           if (((tPanel*)aux->parent)->move != NULL &&
                ((tPanel *)aux->parent)->move->Fn[Fn] != NULL) 
            value=((tPanel *)aux->parent)->move->Fn[Fn];
          }
          break;
       default:
	  return NULL;
     }
     if (value == NULL || value[0]!= ':')  return value;
     auxNext = PANEL_searchComponent(component->parent, value+1);
     if (auxNext == NULL) return value;
     if (auxNext->visual->status.visible == DIS_NORMAL ||
         auxNext->visual->status.visible == DIS_OPEN)
       return value;
     else
       aux = auxNext;
   }
   return NULL;
}

static trAction * COMPONENT_searchAction(tComponent * component,
			int move,int caracter,int Fn)
{
 tPanel * parent = (tPanel *) component->parent;

   switch(move){
     case A_enter:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->enter != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->enter)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->enter != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->enter)(component,caracter));
        }
        break;
     case A_out:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->out != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->out)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->out != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->out)(component,caracter));
        }
        break;
     case A_next:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->next != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->next)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->next != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->next)(component,caracter));
        }
        break;
     case A_previous:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->previous != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->previous)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->previous != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->previous)(component,caracter));
        }
        break;
     case A_up:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->up != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->up)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->up != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->up)(component,caracter));
        }
        break;
     case A_down:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->down != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->down)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->down != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->down)(component,caracter));
        }
        break;
     case A_right:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->right != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->right)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->right != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->right)(component,caracter));
        }
        break;
     case A_left:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->left != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->left)(component,caracter));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->left != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->left)(component,caracter));
        }
        break;
     case A_Fn:
        if (component->personalAction != NULL &&
	   ((_tFActionPanel*)component->personalAction)->Fn != NULL){
           return ((*((_tFActionPanel*)component->personalAction)->Fn)(component,caracter,Fn));
      }
      else {
           if (parent->personalAction != NULL &&
	      ((_tFActionPanel*)parent->personalAction)->Fn != NULL)
             return ((*((_tFActionPanel*)parent->personalAction)->Fn)(component,caracter,Fn));
        }
        break;
    default:
	break;
 }
 return NULL;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <libgen.h>
#include <tBasic.h>
#include <color.h>
#include <text.h>
#include <msg.h>
#include <error.h>
#include <visual.h>
#include <keys.h>
#include <component.h>
#include <view.h>
#include <lview.h>
#include <edit.h>



static trAction rAction;
static void EDIT_nuevaEntrada(tEdit * edit, int caracter);
static trAction * EDIT_Move(tEdit * edit,int caracter);
static void EDIT_TypeAction(tEdit * edit,int action);
static tCursorPtr EDIT_buscaPosicion(tVisual * visual, tText * text,
							int wx, int wy);
static int EDIT_activatePosition(tEdit * edit,tCursor * nPos);

tView * EDIT_create(int id,
                      char * name,
		      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * color,
		      unsigned short opToMade,
		      enum EMode mode,
		      tmapKeys * mapkey,
                      tMove * move,
                      _tFActionEdit * personalAction,
                      _tFEdit * personalFEdit)
{
  tEdit * edit;
  int maxTitle;
  tView * view;

  if (personalFEdit != NULL &&
        personalFEdit->pre_create != NULL)
    (*personalFEdit->pre_create)(name);

  view = (tView *)malloc(sizeof(tView));
  if (view == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Edit malloc %d\n",sizeof(tView));
    return NULL;
  }
  view->caller.View=NULL;
  view->caller.Element=NULL;

  view->level=level;
  view->type=V_Edit;

  edit = (tEdit *)malloc(sizeof(tEdit));
  if (edit == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Edit malloc %d\n",sizeof(tEdit));
    free(view);
    return NULL;
  }

  view->view.edit=edit;
  edit->opToMade=opToMade;
  strcpy(edit->file,"");

  edit->mode=mode;

  if (mapkey == NULL)
   edit->mapkey= (tmapKeys *)&KEY_STD_EDIT;
  else
   edit->mapkey= mapkey;

  edit->move = malloc(sizeof(tMove));
  if (edit->move == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error edit move malloc (%d)\n",sizeof(tMove));
  }

  edit->personalAction = (tFActionEdit *) personalAction;
  edit->personalFEdit = (tFEdit *)personalFEdit;

  VIEW_cargaMove(edit->move,move);

  edit->id=id;

  strncpy(edit->name,name,sizeof(edit->name));

  if (title == NULL) edit->title[0] = '\0';
  else
  {
    maxTitle=(strlen(title)>dimension->ancho)?dimension->ancho-1:strlen(title)+1;
    if (maxTitle > MAX_VIEW_TITLE) maxTitle = MAX_VIEW_TITLE -1;
    strncpy(edit->title,title,maxTitle);
  } 
  
  edit->vData = malloc(sizeof(tVisual));

  if (edit->vData == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error creating Edit visual malloc %d\n",sizeof(tVisual));
    free(edit); free(view);
    return NULL;
  }

  memcpy(&edit->vData->dimension ,dimension,sizeof(tDim));
  if (dimension->border) {
    edit->vHead = malloc(sizeof(tVisual));

    if (edit->vHead == NULL)
    {
      ERR_fatalError(ERR_MEM,"Error creating Edit visual malloc %d\n",sizeof(tVisual));
      free(edit); free(view);
      return NULL;
    }
    memcpy(&edit->vHead->dimension ,dimension,sizeof(tDim));
    memcpy(&edit->vHead->color,color,sizeof(tChAttr));
    edit->vData->dimension.alto-=2;
    edit->vData->dimension.ancho-=2;
    edit->vHead->status.visible=DIS_HIDDEN;
    edit->vHead->status.activa=0;
  }
  else
    edit->vHead = NULL;

  edit->vData->dimension.border=0;
  memcpy(&edit->vData->color,color,sizeof(tChAttr));

  edit->vData->status.visible=DIS_HIDDEN;
  edit->vData->status.activa=0;
  edit->text = NULL;

  if (edit->vHead != NULL)
  {
    edit->vHead->win = newwin(edit->vHead->dimension.alto,
                              edit->vHead->dimension.ancho,
                              edit->vHead->dimension.y,
                              edit->vHead->dimension.x);
    edit->vData->win = derwin(edit->vHead->win,
			      edit->vData->dimension.alto,
                              edit->vData->dimension.ancho,
                              1,1);
  }
  else
    edit->vData->win = newwin(edit->vData->dimension.alto,
                              edit->vData->dimension.ancho,
                              edit->vData->dimension.y,
                              edit->vData->dimension.x);

  edit->vData->cursor.y=0;
  edit->vData->cursor.x=0;
  if (mode == R_ONLY){
   edit->vData->status.insert=ReadOnly;
   if (edit->vHead != NULL) edit->vHead->status.insert=ReadOnly;
  }
  else{
   edit->vData->status.insert=Insert;
   if (edit->vHead != NULL) edit->vHead->status.insert=Insert;
  }

  LVIEW_addView(view);

  if (personalFEdit != NULL &&
        personalFEdit->post_create != NULL)
    (*personalFEdit->post_create)(edit);


  return view;
}

int  EDIT_changeColor(tEdit * edit, tChAttr * color)
{
  if (color != NULL)
    memcpy(&edit->vData->color ,color,sizeof(tChAttr));

  return 0;
}

int EDIT_show(tEdit * edit)
{
  edit->vData->cursor.x=0;
  edit->vData->cursor.y=0;
  edit->vData->status.actColumn=0;
  edit->vData->status.actLine = 0;
  edit->vData->status.actField = 0;

  if (edit->mode == R_ONLY){
   edit->vData->status.insert=ReadOnly;
   if (edit->vHead != NULL) edit->vHead->status.insert=ReadOnly;
  }
  else{
   edit->vData->status.insert=Insert;
   if (edit->vHead != NULL) edit->vHead->status.insert=Insert;
  }
 
  if (edit->text != NULL) {
    edit->text->actField=0;
    edit->text->actLine=0;
    edit->text->actColumn=0;
  }

  if (edit->vData->status.visible == DIS_NORMAL) return 0;

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->pre_show != NULL)
   (*((_tFEdit*)edit->personalFEdit)->pre_show)(edit);

   /* ----------------------------------
    *   Show the window.
    * ---------------------------------- */
  if (edit->vHead != NULL){
      edit->vHead->color.attr=A_REVERSE;
      VISUAL_color(edit->vHead->win,&edit->vHead->color);
      VISUAL_border(edit->vHead->win,1);
      if (strcmp(edit->title,"") != 0) 
        VISUAL_pintaTitle(edit->vHead,edit->title);
      VISUAL_pintaInsert(edit->vHead); 
      if (strcmp(edit->file,"") != 0)
       VISUAL_pintaFileName(edit->vHead,basename(edit->file)); 
      edit->vData->status.visible =1;
      wrefresh(edit->vHead->win);
  }
  edit->vData->status.actLine=0;
  edit->vData->status.actField=0;
  VISUAL_win(edit->vData->win,&edit->vData->color);
   
  edit->vData->status.visible = DIS_NORMAL;

  if (edit->text != NULL) {
     edit->text->actField=0;
     edit->text->actLine=0;
     edit->text->actColumn=0;

     if (edit->text->nroLines >0) VISUAL_pintaEditData(edit->text, edit->vData);
  }
  wrefresh(edit->vData->win);

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->post_show != NULL)
   (*((_tFEdit*)edit->personalFEdit)->post_show)(edit);

  return 0;
}

int EDIT_refresh(tEdit * edit)
{
  if (edit->text->actLine > edit->text->nroLines)
    edit->text->actLine = edit->text->nroLines-1;

  if (edit->text->actLine < 0) edit->text->actLine=0;
 
  VISUAL_pintaEditData(edit->text, edit->vData);
  wrefresh(edit->vData->win);

  return 0;
}

int EDIT_activate(tEdit * edit)
{
  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->pre_activate != NULL)
   (*((_tFEdit*)edit->personalFEdit)->pre_activate)(edit);

  VISUAL_cursor(1);

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->post_activate != NULL)
   (*((_tFEdit*)edit->personalFEdit)->post_activate)(edit);
  return 0;
}

int EDIT_deactivate(tEdit * edit)
{
  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->pre_deactivate != NULL)
   (*((_tFEdit*)edit->personalFEdit)->pre_deactivate)(edit);

  VISUAL_cursor(0);

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->post_deactivate != NULL)
   (*((_tFEdit*)edit->personalFEdit)->post_deactivate)(edit);

  return 0;
}

void EDIT_Action(tEdit * edit,tNextPtr next)
{
 int tecla;
 int atras;
 trAction * accion;
 tCaller * auxCaller;
 char npanel[MAX_NAME_VIEW]="";
 char * ncomponent;
 char * paux;
 tCursorPtr nCurPosicion;
 MEVENT ev_mouse;
 int wx,wy;
 char nActComponent[MAX_NAME_VIEW+MAX_COMPONENT_NAME+5];
 static trAction mouseAction = {0,1,OP_NONE,NULL};
 mmask_t mmask, oldmmask;
 int hasMouse;

  strcpy(next->view,"");
  
  hasMouse = KEYS_getMouse();
  next->opToMade=OP_NONE;
  mmask=BUTTON1_CLICKED|BUTTON3_CLICKED|BUTTON4_PRESSED|BUTTON5_PRESSED|BUTTON2_PRESSED|BUTTON1_DOUBLE_CLICKED;

  keypad(edit->vData->win,TRUE);
  while (1)
  {
    accion = NULL;
    sprintf(nActComponent,"%s:%s",edit->name,"");
       
    if (hasMouse) mousemask(mmask, &oldmmask);
    tecla = wgetch(edit->vData->win);
    if(hasMouse && tecla == KEY_MOUSE) {
 	 if(getmouse(&ev_mouse) == OK) {
           wx = ev_mouse.x; wy = ev_mouse.y;
           mouseAction.componentNext = LVIEW_searchXYView(wx,wy);
           if (mouseAction.componentNext != NULL &&
                   strcmp(mouseAction.componentNext,"")!=0) {
             if (strcmp(mouseAction.componentNext, nActComponent)== 0){
               if(ev_mouse.bstate & BUTTON1_CLICKED){
                 nCurPosicion = EDIT_buscaPosicion(edit->vData,edit->text,wx,wy);
                 if (nCurPosicion != NULL) EDIT_activatePosition(edit,nCurPosicion);
               }
               if(ev_mouse.bstate & BUTTON1_DOUBLE_CLICKED){
                tecla=edit->mapkey->enter[0];
                accion = EDIT_Move(edit,tecla);
               }
               if(ev_mouse.bstate & BUTTON3_CLICKED){
                 tecla=edit->mapkey->out[0];
                 accion = EDIT_Move(edit,tecla);
               }
               if(ev_mouse.bstate & BUTTON2_PRESSED){
                 tecla=edit->mapkey->down[0];
                 accion = EDIT_Move(edit,tecla);
               }
               if(ev_mouse.bstate & BUTTON4_PRESSED){
                 tecla=edit->mapkey->up[0];
                 accion = EDIT_Move(edit,tecla);
               }
               if(ev_mouse.bstate & BUTTON5_PRESSED){
                 tecla=edit->mapkey->down[0];
                 accion = EDIT_Move(edit,tecla);
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
        accion = EDIT_Move(edit,tecla);
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
            if (strcmp(npanel,"") != 0)
            {
              if (strcmp(npanel,edit->name)!=0)
              {
                 if (npanel[0]!='-'){
                   strcpy(next->view,npanel);
                   strcpy(next->element,ncomponent);
                   next->caller.View=edit->name;
                   next->caller.Element=NULL;
                   next->opToMade = accion->opToMade==OP_NONE?edit->opToMade:accion->opToMade;
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
                   next->opToMade = accion->opToMade==OP_NONE?edit->opToMade:accion->opToMade;
                 }
                 return;
              }
            }
           }
           else
             ERR_Error(ERR_VIEW," move %s wrong must be view:component \n ",accion->componentNext);

         }
      }
   }
}

int EDIT_hide(tEdit * edit)
{
  if (edit->vData->status.visible != DIS_NORMAL)return 0;
  
  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->pre_hide != NULL)
   (*((_tFEdit*)edit->personalFEdit)->pre_hide)(edit);

  /* ---------------------
   *  BACK_POP 
   * ------------------------ */
  edit->vData->status.visible=DIS_HIDDEN;
  if (edit->vHead != NULL)
      edit->vHead->status.visible=DIS_HIDDEN;

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->post_hide != NULL)
   (*((_tFEdit*)edit->personalFEdit)->post_hide)(edit);

  return 0;
}

int EDIT_destroy(tEdit * edit)
{
 int retorno;

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->pre_destroy != NULL)
   (*((_tFEdit*)edit->personalFEdit)->pre_destroy)(edit);


  if (edit->text != NULL) 
  {
    TEXT_free(edit->text);
  } 
  edit->text = NULL;
  retorno = EDIT_hide(edit);

  if (edit->personalFEdit != NULL &&
     ((_tFEdit *)edit->personalFEdit)->post_destroy != NULL)
   (*((_tFEdit*)edit->personalFEdit)->post_destroy)(edit);

  return retorno;
}


static trAction * EDIT_Move(tEdit * edit,int caracter)
{
  int i,j;
  trAction * resultado;
  unsigned short chTratado=0;

  rAction.error =0;
  rAction.made =0;
  rAction.componentNext=NULL;
  rAction.opToMade=OP_NONE;
  

  for (i=0;i!= MAX_KEYS_FUNC && !chTratado;i++)
  {
    if (edit->vData->status.insert==ReadOnly &&
         edit->mapkey->enter[i]!=0&&
         edit->mapkey->enter[i] == caracter)
    { 
        if( edit->personalAction != NULL &&
	   ((_tFActionEdit*)edit->personalAction)->enter != NULL)
      {
        resultado = ((*((_tFActionEdit*)edit->personalAction)->enter)(edit,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made )
        {
             rAction.opToMade=resultado->opToMade;
             rAction.componentNext = resultado->componentNext;
        }
      }
      if (!rAction.error && !rAction.made && edit->move != NULL)
      {
          rAction.made = edit->move->enter==NULL?0:1;
          rAction.componentNext = edit->move->enter;
          if (!rAction.made) 
	    EDIT_TypeAction(edit,A_enter);
      }
      return &rAction;
    }
    if (edit->mapkey->out[i]!=0&&
         edit->mapkey->out[i] == caracter)
    { 
      if (edit->personalAction != NULL &&
	   ((_tFActionEdit*)edit->personalAction)->out != NULL)
      {
        resultado = ((*((_tFActionEdit*)edit->personalAction)->out)(edit,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error  && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made && edit->move != NULL)
      {
          rAction.made = edit->move->out==NULL?0:1;
          rAction.componentNext = edit->move->out;
      }
      return &rAction;
    }

    if (edit->mapkey->next[i]!=0&&
         edit->mapkey->next[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_next);
      chTratado=1;
    }

    if (edit->mapkey->previous[i]!=0&&
         edit->mapkey->previous[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_previous);
      chTratado=1;
    }

    if (edit->mapkey->up[i]!=0&&
         edit->mapkey->up[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_up);
      chTratado=1;
    }

    if (edit->mapkey->down[i]!=0&&
         edit->mapkey->down[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_down);
      chTratado=1;
    }

    if (edit->mapkey->left[i]!=0&&
         edit->mapkey->left[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_left);
      chTratado=1;
    }

    if (edit->mapkey->right[i]!=0&&
         edit->mapkey->right[i] == caracter)
    { 
      EDIT_TypeAction(edit,A_right);
      chTratado=1;
    }

    if (edit->vData->status.insert==ReadOnly &&
	edit->mapkey->back[i]!=0&&
         edit->mapkey->back[i] == caracter)
    { 
      if (edit->personalAction != NULL &&
	   ((_tFActionEdit*)edit->personalAction)->back != NULL)
      {
        resultado = ((*((_tFActionEdit*)edit->personalAction)->back)(edit,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made && edit->move != NULL)
      {
          rAction.made = edit->move->back==NULL?0:1;
          rAction.componentNext = edit->move->back;
          if (!rAction.made) 
	    EDIT_TypeAction(edit,A_back);
      }
      return &rAction;
    }


    for (j=0;j!=MAX_Fn_KEYS;j++)
    {
       if (edit->mapkey->Fn[j][i]!=0&&
            edit->mapkey->Fn[j][i] == caracter)
       { 
         if (edit->personalAction != NULL &&
	   ((_tFActionEdit*)edit->personalAction)->Fn != NULL)
          {
             resultado = ((*((_tFActionEdit*)edit->personalAction)->Fn)(edit,caracter,j+1));
             rAction.error = resultado->error;
             rAction.made = resultado->made;
             if (!resultado->error && resultado->made)
             {
                     rAction.componentNext = resultado->componentNext;
                     rAction.opToMade=resultado->opToMade;
             }
         }
         if (!rAction.error && !rAction.made && edit->move != NULL)
         {
             rAction.made = edit->move->Fn[j]==NULL?0:1;
             rAction.componentNext = edit->move->Fn[j];
         }
        return &rAction;
       }
    }   
  }   

  if (!chTratado && KEYS_isInsert(caracter)){
    chTratado=1;
    EDIT_TypeAction(edit,A_ic);
  }

  if (!chTratado && KEYS_isHome(caracter)){
    chTratado=1;
    EDIT_TypeAction(edit,A_home);
  }
  if (!chTratado && KEYS_isEnd(caracter)) {
    chTratado=1;
    EDIT_TypeAction(edit,A_end);
  }

  if (!chTratado && edit->mode != R_ONLY){
     EDIT_nuevaEntrada(edit,caracter);
  }

  return &rAction;
}

static void EDIT_nuevaEntrada(tEdit * edit, int caracter)
{
 int len,pos,linea,lenAnt;
 int i;
 char * p;

  if (caracter < 32 && !KEYS_isEnter(caracter)) return; /* car. de control */
  if (caracter == 127 || caracter >= 255) {
   if (!KEYS_isBackspace(caracter) &&
       !KEYS_isEnter(caracter) &&
       !KEYS_isDelete(caracter))
    return;
  }
  
  linea=edit->text->actLine + edit->vData->cursor.y;
  len=strlen(edit->text->text[edit->text->actLine
                        + edit->vData->cursor.y][0]);
  pos=edit->vData->status.actColumn + edit->vData->cursor.x;
  if (pos > len) pos = len;

  if (KEYS_isBackspace(caracter)) {
    if (pos <=0 ) 
    {
      /* Fusionar con la linea anterior. */
      if (edit->vData->cursor.y == 0) {
        if (edit->vData->status.actLine == 0) return;
        edit->text->actLine --;
        lenAnt=strlen(edit->text->text[edit->text->actLine-1][0]);
        TEXT_joinEditLine(edit->text,
			edit->text->actLine-1,edit->text->actLine);
        edit->vData->status.nactLines=0;
      }
      else
      {
        lenAnt=strlen(edit->text->text[edit->text->actLine +
				edit->vData->cursor.y -1][0]);
        TEXT_joinEditLine(edit->text,
			edit->text->actLine+
			edit->vData->cursor.y -1,
			edit->text->actLine+edit->vData->cursor.y);
        edit->vData->cursor.y--;
      }
      if ( lenAnt - edit->vData->status.actColumn > 
				edit->vData->dimension.ancho){
          edit->vData->status.actColumn = 
			lenAnt - edit->vData->dimension.ancho -1;
          edit->vData->cursor.x = edit->vData->dimension.ancho-1;
      }
      else
          edit->vData->cursor.x = lenAnt - edit->vData->status.actColumn;
       
      VISUAL_cleanWin(edit->vData);
      VISUAL_pintaEditData(edit->text, edit->vData);
    }
    else
    {
      for (i=pos-1,p=edit->text->text[linea][0]+pos-1;i!=len;i++,p++) 
         *p=*(p+1); 
      if (edit->vData->cursor.x > 0) {
        edit->vData->cursor.x --;
        VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
        if (len - edit->vData->status.actColumn >= 
	  edit->vData->dimension.ancho) 
        {
         VISUAL_cleanWin(edit->vData);
         VISUAL_pintaEditData(edit->text, edit->vData);
        }
        else
         wdelch(edit->vData->win);
      }
      else {
       edit->vData->status.actColumn--;
       VISUAL_cleanWin(edit->vData);
       VISUAL_pintaEditData(edit->text, edit->vData);
     }
    }
    return;
  }

  if (KEYS_isEnter(caracter)) {
    if( TEXT_insEditLine(edit->text,linea,pos) == 0)
    {
       VISUAL_cleanWin(edit->vData);
       edit->vData->cursor.x=0;

       if (edit->vData->cursor.y < edit->vData->status.nactLines-1) 
         edit->vData->cursor.y++;
       else
       {
        edit->text->actLine ++;
        edit->vData->status.actLine++;
        edit->vData->status.nactLines=0;
       }

       VISUAL_cleanWin(edit->vData);
       VISUAL_pintaEditData(edit->text, edit->vData);
       
       VISUAL_pintaEditData(edit->text, edit->vData);
    }
    return;
  }

  if (KEYS_isDelete(caracter)) {
    if (pos >=len ) 
    {
      if (edit->vData->cursor.y + edit->vData->status.actLine
               >= edit->text->nroLines-1) return;
       TEXT_joinEditLine(edit->text,
			edit->text->actLine+
			edit->vData->cursor.y ,
			edit->text->actLine+edit->vData->cursor.y+1);
       VISUAL_cleanWin(edit->vData);
       VISUAL_pintaEditData(edit->text, edit->vData);
    }
    else
    {
       for (i=pos,p=edit->text->text[linea][0]+pos;i!=len;i++,p++) 
         *p=*(p+1); 
       if (len - edit->vData->status.actColumn >= 
	  edit->vData->dimension.ancho) 
       {
          VISUAL_cleanWin(edit->vData);
          VISUAL_pintaEditData(edit->text, edit->vData);
       }
       else
        wdelch(edit->vData->win);
    }
    return;
  }

  if (pos >= len && (len%ADD_COLUMNS==0))
  {
      edit->text->text[linea][0] = 
           realloc(edit->text->text[linea][0],sizeof(char)*len + ADD_COLUMNS+2);
      edit->text->text[linea][0][len]=caracter;
      edit->text->text[linea][0][len+1]='\0';
      waddch(edit->vData->win,caracter);
  }
  else
  {
    if (edit->vData->status.insert==Replace)
    {
      waddch(edit->vData->win,caracter);
      edit->text->text[linea][0][pos]=caracter;
      edit->vData->cursor.x++;
    }
    else
    {
      if (len%ADD_COLUMNS == 0) {
       edit->text->text[linea][0] = 
           realloc(edit->text->text[linea][0],sizeof(char)*len + ADD_COLUMNS + 2);
      }

      for (i=len+1,p=edit->text->text[linea][0]+len+1;i!=pos;i--,p--) 
          *p=*(p-1); 
      *p=caracter; 
       winsch(edit->vData->win,caracter);
    }
  }

  if (edit->vData->cursor.x > edit->vData->dimension.ancho-2)
  {
       edit->vData->status.actColumn++;
       VISUAL_cleanWin(edit->vData);
       VISUAL_pintaEditData(edit->text, edit->vData);
  }
  else
  {
     if (edit->vData->status.insert == Insert){
      edit->vData->cursor.x ++;
      VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
     }
  }
}

static void EDIT_TypeAction(tEdit * edit,int action)
{
 int lData=0;

 if (edit->text == NULL) return;

 switch(action)
 {
    case  A_ic:
            if (edit->vData->status.insert==ReadOnly) return;
            if (edit->vData->status.insert == Insert){
              edit->vData->status.insert=Replace;
              edit->vHead->status.insert=Replace;
            } else {
              edit->vData->status.insert=Insert;
              edit->vHead->status.insert=Insert;
	    }
            if (edit->vHead != NULL)
            {
             VISUAL_pintaInsert(edit->vHead); 
             wrefresh(edit->vHead->win);
             VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
            }
            break;
    case  A_home:
            if (edit->vData->status.actColumn != 0)
            {
              edit->vData->status.actColumn = 0;
              edit->vData->cursor.x = 0;
              VISUAL_cleanWin(edit->vData);
              VISUAL_pintaEditData(edit->text, edit->vData);
            }
            else 
            {
              if (edit->vData->cursor.x > 0){
               edit->vData->cursor.x = 0;
               VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
              }
            }
	    break;
    case  A_end:
            lData=TEXT_strVisLen(edit->text->text[edit->text->actLine 
			+ edit->vData->cursor.y][0],0);
            if ((lData - edit->vData->status.actColumn) > 
				edit->vData->dimension.ancho-2)
            {
              edit->vData->status.actColumn = lData - edit->vData->dimension.ancho+1;
              edit->vData->cursor.x =  edit->vData->dimension.ancho-1;
              VISUAL_cleanWin(edit->vData);
              VISUAL_pintaEditData(edit->text, edit->vData);
            }
            else
            {
                if (edit->vData->cursor.x != lData){
                  edit->vData->cursor.x = lData-edit->vData->status.actColumn;
                  VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
                } 
            } 
               
            
	    break;
    case  A_up:
            if (edit->vData->cursor.y > 0)
            {
               edit->vData->cursor.y--;
               lData=TEXT_strVisLen(edit->text->text[edit->text->actLine 
			+ edit->vData->cursor.y][0],
			edit->vData->status.actColumn);
               if (edit->vData->status.actColumn != 0 && lData == 0) {
                 lData=TEXT_strVisLen(edit->text->text[edit->text->actLine
                        + edit->vData->cursor.y][0],0);
                 edit->vData->status.actColumn=lData;
                 VISUAL_cleanWin(edit->vData);
                 VISUAL_pintaEditData(edit->text, edit->vData);
               }
               else {
                if (lData < edit->vData->cursor.x) {
                  edit->vData->cursor.x =lData>0?lData:0;
                 }
               }
               VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
            }
            else
            {
    	      if (edit->text->actLine > 0)
              {
                 edit->text->actLine --;
                 edit->vData->status.nactLines=0;
                 VISUAL_cleanWin(edit->vData);
                 VISUAL_pintaEditData(edit->text, edit->vData);
              }
            }
            break;
    case  A_down:
            if (edit->vData->cursor.y < edit->vData->status.nactLines-1) 
            {
               edit->vData->cursor.y++;
                lData=TEXT_strVisLen(edit->text->text[edit->text->actLine
                        + edit->vData->cursor.y][0],
			edit->vData->status.actColumn);
               if (edit->vData->status.actColumn != 0 && lData == 0) {
                 lData=TEXT_strVisLen(edit->text->text[edit->text->actLine
                        + edit->vData->cursor.y][0],0);
                 edit->vData->status.actColumn= lData;
                 VISUAL_cleanWin(edit->vData);
                 VISUAL_pintaEditData(edit->text, edit->vData);
               }
               else
               {
                 if (lData < edit->vData->cursor.x) {
                   edit->vData->cursor.x =lData>0?lData:0;
                 }
                 VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			   edit->vData->cursor.x);
               }
            }
            else
            {
    	      if ((edit->text->actLine + edit->vData->status.nactLines) 
                                        < edit->text->nroLines)
              {
                 edit->text->actLine ++;
                 edit->vData->status.actLine++;
                 edit->vData->status.nactLines=0;
                 VISUAL_cleanWin(edit->vData);
                 VISUAL_pintaEditData(edit->text, edit->vData);
                 edit->vData->cursor.y=edit->vData->status.nactLines-1;
                 if (edit->vData->cursor.y < 0) edit->vData->cursor.y=0;
              }
              else return;
            }
            break;
    case  A_right:
           lData=TEXT_strVisLen(edit->text->text[edit->text->actLine
                        + edit->vData->cursor.y][0],
			edit->vData->status.actColumn+edit->vData->cursor.x);
           if (lData > 0)
           {
             if (edit->vData->cursor.x < 
		        edit->vData->dimension.ancho-2){
               edit->vData->cursor.x ++;
               VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			edit->vData->cursor.x);
             }
             else {
                edit->vData->status.actColumn++;
                VISUAL_cleanWin(edit->vData);
                VISUAL_pintaEditData(edit->text, edit->vData);
             }
           }
           break;
    case  A_left:
          if (edit->vData->cursor.x > 0)
          {
             edit->vData->cursor.x --;
             VISUAL_setXY(edit->vData,edit->vData->cursor.y,
			edit->vData->cursor.x);
          }
          else
          {
             if (edit->vData->status.actColumn > 0)
             {
               edit->vData->cursor.x=0;
               edit->vData->status.actColumn --;
               VISUAL_cleanWin(edit->vData);
               VISUAL_pintaEditData(edit->text, edit->vData);
             }
          }
	  break;
    case  A_previous:
          if (edit->text->actLine > 0)
          {
              if (edit->text->actLine > edit->vData->dimension.alto){
                edit->text->actLine -= edit->vData->dimension.alto;
               }else{
                edit->text->actLine=0;
              }
              edit->vData->status.actLine = 0;
              lData = TEXT_strVisLen(edit->text->text[edit->text->actLine+
			edit->vData->cursor.y][0], 
			edit->vData->status.actColumn);
              if (lData == 0) edit->vData->status.actColumn = lData;
              VISUAL_cleanWin(edit->vData);
              VISUAL_pintaEditData(edit->text, edit->vData);
          }
          break;
    case  A_next:
          if ((edit->text->actLine + edit->vData->status.nactLines)
              < edit->text->nroLines)
          {
              edit->vData->status.actLine = 0;
              edit->text->actLine += edit->vData->status.nactLines;

              if (edit->text->actLine+edit->vData->cursor.y >=
			                      edit->text->nroLines-1) 
                  edit->vData->cursor.y=edit->text->nroLines - edit->text->actLine -1;
                  
              lData = TEXT_strVisLen(edit->text->text[edit->text->actLine+
			edit->vData->cursor.y][0], 
			edit->vData->status.actColumn);
              if (lData == 0) edit->vData->status.actColumn = lData;
              VISUAL_cleanWin(edit->vData);
              VISUAL_pintaEditData(edit->text, edit->vData);
          }
          break;
    default: break;
  }
}

char * EDIT_getValue(tEdit * edit)
{
   return edit->text->text[edit->text->actLine][0];
}

static tCursorPtr EDIT_buscaPosicion(tVisual * visual,
			tText * text,int wx, int wy)
{
  static tCursor posicion;
  int y,x;
  int dx;
  y=wy;x=wx;

   posicion.x=wx; posicion.y=wy;

   if (wmouse_trafo(visual->win,&y,&x,FALSE) == TRUE) {
    posicion.x = x;
    if (y > visual->status.nactLines) y = visual->status.nactLines-1;

    posicion.y = y;
    dx=TEXT_strVisLen(text->text[text->actLine+y][0],
			      visual->status.actColumn);
    if (dx == 0) posicion.x=65000;
    else {
      if (x > dx) posicion.x = dx;
    }
    return &posicion; 
   }
   return NULL;

}

static int EDIT_activatePosition(tEdit * edit,tCursor * nPos)
{

  if (nPos->x == 65000)
  {
     edit->vData->status.actColumn=0;
     nPos->x=0;
     VISUAL_cleanWin(edit->vData);
     VISUAL_pintaEditData(edit->text, edit->vData);
  }

  if (VISUAL_setXY(edit->vData,nPos->y,nPos->x) == 0)
  {
    edit->vData->cursor.y=nPos->y;
    edit->vData->cursor.x=nPos->x;
    return 0;
  }

  return ERR_NCURSES;
}

void EDIT_Text(tEdit * edit,tText * text)
{
   edit->text = text;
}

int EDIT_saveFile(tEdit * edit)
{
   if (strcmp(edit->file,"")==0 || edit->text == NULL) 
    return -1;

   return TEXT_saveFile(edit->text,edit->file);
}

int EDIT_loadFile(tEdit * edit,char * fileName,int maxData, int iniLines)
{
  if (edit->text != NULL) TEXT_free(edit->text);
 
  edit->text = TEXT_newEdit(maxData,iniLines,1);
  if (edit->text == NULL) return -1;
  TEXT_loadFile(edit->text,fileName);
  edit->text->actLine=0;
  edit->text->actColumn=0;
  strcpy(edit->file,fileName);

  return 0;
}


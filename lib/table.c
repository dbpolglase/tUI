#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
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
#include <table.h>



static trAction rAction;
static trAction * TABLE_Move(tTable * table,int caracter);
static void TABLE_TypeAction(tTable * table,int action);
static void TABLE_calculaColumnsShow(tTablePtr table);
static int TABLE_buscaLinea(WINDOW * win, int vline,int wx, int wy);
static void TABLE_activateLine(tTable * table,int linea);

tView * TABLE_create(int id,
                      char * name,
		      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * colorHead,
                      tChAttr * colorData,
		      unsigned short opToMade,
                      unsigned short head,
                      unsigned short vline,
                      unsigned short hline,
		      tmapKeys * mapkey,
                      tMove * move,
                      _tFActionTable * personalAction,
                      _tFTable * personalFTable)
{
  tTable * table;
  int maxTitle;
  tView * view;

  if (personalFTable != NULL &&
        personalFTable->pre_create != NULL)
    (*personalFTable->pre_create)(name);

  view = (tView *)malloc(sizeof(tView));
  if (view == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Table malloc %d\n",sizeof(tView));
    return NULL;
  }
  view->caller.View=NULL;
  view->caller.Element=NULL;

  view->level=level;
  view->type=V_Table;

  table = (tTable *)malloc(sizeof(tTable));
  if (table == NULL)
  {
    ERR_Error(ERR_MEM,"Error creating Table malloc %d\n",sizeof(tPanel));
    free(view);
    return NULL;
  }

  view->view.table=table;
  table->vline=vline;
  table->hline=hline;
  table->nColumns=0;
  table->opToMade=opToMade;

  if (mapkey == NULL)
   table->mapkey= (tmapKeys *)&KEY_STD_TABLE;
  else
   table->mapkey= mapkey;

  table->move = malloc(sizeof(tMove));
  if (table->move == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error table move malloc (%d)\n",sizeof(tMove));
  }

  table->personalAction = (tFActionTable *) personalAction;
  table->personalFTable = (tFTable *)personalFTable;

  VIEW_cargaMove(table->move,move);

  table->id=id;

  strncpy(table->name,name,sizeof(table->name));

  if (title == NULL) table->title[0] = '\0';
  else
  {
    maxTitle=(strlen(title)>dimension->ancho)?dimension->ancho-1:strlen(title)+1;
    if (maxTitle > MAX_VIEW_TITLE) maxTitle = MAX_VIEW_TITLE -1;
    strncpy(table->title,title,maxTitle);
  } 
  

  table->vTable = malloc(sizeof(tVisual));
  table->vData = malloc(sizeof(tVisual));

  if (table->vTable == NULL || table->vData == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error creating Table visual malloc %d\n",sizeof(tVisual));
    free(table->vTable); free(table->vData);
    free(table); free(view);
    return NULL;
  }

  if (head){
     table->vHead = malloc(sizeof(tVisual));
     if (table->vHead == NULL)
     {
       ERR_fatalError(ERR_MEM,"Error creating Table visual malloc %d\n",sizeof(tVisual));
       free(table->vTable); free(table->vData); 
       free(table); free(view);
       return NULL;
     }
  }
  else table->vHead = NULL;

  memcpy(&table->vTable->dimension ,dimension,sizeof(tDim));
  memcpy(&table->vTable->color,colorData,sizeof(tChAttr));
  memcpy(&table->vData->color,colorData,sizeof(tChAttr));

  if (head) {
    memcpy(&table->vHead->color,colorHead,sizeof(tChAttr));
    table->vHead->status.visible=DIS_HIDDEN;
    table->vHead->status.activa=0;
  }

  table->vTable->status.visible=DIS_HIDDEN;
  table->vData->status.visible=DIS_HIDDEN;
  table->vTable->status.activa=0;
  table->vData->status.activa=0;


  table->nLines=table->vTable->dimension.y;

  if (dimension->border) table->nLines-=2;
  if (head) table->nLines --;
  if (hline) table->nLines=table->nLines/2;

  table->columns = NULL;
  table->text = NULL;
  table->vTable->win = newwin(table->vTable->dimension.alto,
                      table->vTable->dimension.ancho,
                      table->vTable->dimension.y,
                      table->vTable->dimension.x);

  if (head) {
    table->vHead->dimension.alto=1+vline;
    table->vHead->dimension.ancho=
		dimension->border?dimension->ancho-2:dimension->ancho;
    table->vHead->dimension.x=dimension->border?1:0;
    table->vHead->dimension.y=dimension->border?1:0;

    table->vHead->win = derwin(table->vTable->win,
                      table->vHead->dimension.alto,
                      table->vHead->dimension.ancho,
                      table->vHead->dimension.y,
                      table->vHead->dimension.x);
  }

  table->vData->dimension.alto=dimension->border?dimension->alto-2-head-hline:dimension->alto-head-vline;

  table->vData->dimension.ancho=
		dimension->border?dimension->ancho-2:dimension->ancho;
  table->vData->dimension.x=dimension->border?1:0;
  table->vData->dimension.y=dimension->border+head;
  if (head && vline) table->vData->dimension.y++;


  table->vData->win = derwin(table->vTable->win,
                      table->vData->dimension.alto,
                      table->vData->dimension.ancho,
                      table->vData->dimension.y,
                      table->vData->dimension.x);


  LVIEW_addView(view);

  if (personalFTable != NULL &&
        personalFTable->post_create != NULL)
    (*personalFTable->post_create)(table);

  return view;
}

int TABLE_addColumn(tTable * table,
                    char * title, unsigned int len)
{
  tTableColumnPtr elemento;
  tTableColumnPtr comienzo;
  unsigned int maxLen;

  maxLen=table->vData->dimension.ancho;
  if (table->hline) maxLen--;

  if (len > maxLen) return ERR_SIZE;

  elemento = malloc (sizeof(tTableColumn));
  elemento->next=NULL;
 
  if (elemento == NULL) 
     ERR_fatalError(ERR_MEM,"Fail malloc of table <%d>\n",sizeof(tTableColumn));

  if (title == NULL)
    elemento->title = NULL;
  else
  {
    elemento->title = (char *)malloc(len+3);
    strcpy(elemento->title,title);
  }

  elemento->len = len;
  table->nColumns++;

  
  if (table->columns == NULL) 
  {
   table->columns=elemento;
   return 0;
  }
  comienzo = table->columns;
  while (comienzo->next != NULL) comienzo=comienzo->next;

  comienzo->next = elemento;
  table->vData->status.nactFields=table->nColumns++;
  return 0;
}


int  TABLE_changeColor(tTable * table,
                  tChAttr * colorHead,
                  tChAttr * colorData)
{
  if (colorHead != NULL && table->vHead != NULL)
    memcpy(&table->vHead->color ,colorHead,sizeof(tChAttr));

  if (colorData != NULL && table->vData != NULL)
   memcpy(&table->vData->color ,colorData,sizeof(tChAttr));
  return 0;
}

int TABLE_refresh(tTable * table)
{
  if (table->text != NULL) {
    VISUAL_cleanWin(table->vData);
    table->text->actLine = table->vData->status.nactLines=0;
    table->vData->status.actLine=0;
    table->text->actColumn=0;
    VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
    wrefresh(table->vData->win);
  }
 return 0;

/*
  if (table->text != NULL) {
    table->text->actLine=0; 
    table->text->actColumn=0;

    VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,1);

    wrefresh(table->vData->win);
  }
 return 0;
*/
}

int TABLE_show(tTable * table)
{
  if (table->vTable->status.visible == DIS_HIDDEN)
  {
    if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->pre_show != NULL)
     (*((_tFTable*)table->personalFTable)->pre_show)(table);

    table->vData->status.actLine=0;
    table->vData->status.actField=0;
   /* ----------------------------------
    *   Show the window.
    * ---------------------------------- */
    VISUAL_win(table->vTable->win,&table->vTable->color);
    if (table->vTable->dimension.border){
      VISUAL_border(table->vTable->win,1);
      if (strcmp(table->title,"") != 0) 
        VISUAL_pintaTitle(table->vTable,table->title);
    }
    wrefresh(table->vTable->win);

    TABLE_calculaColumnsShow(table);
   /* ----------------------------------
    *   Show the Head.
    * ---------------------------------- */
    if (table->vHead != NULL)
    {
      table->vHead->status.actLine=0;
      table->vHead->status.actField=0;
      VISUAL_win(table->vHead->win,&table->vHead->color);
      VISUAL_pintaTableHead(table->columns,table->vline,
                        table->hline,table->vHead);
      wrefresh(table->vHead->win);
    } 
    /*
     *  Show the data.
     */
    VISUAL_win(table->vData->win,&table->vData->color);
  }
   
  table->vTable->status.visible =DIS_NORMAL;

  if (table->text != NULL) {
    table->text->actField=0;
    table->text->actLine=0;
    table->text->actColumn=0;

    VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,1);

    wrefresh(table->vData->win);
  }

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->post_show != NULL)
     (*((_tFTable*)table->personalFTable)->post_show)(table);

  
  return 0;
}

int TABLE_activate(tTable * table)
{
  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->pre_activate != NULL)
     (*((_tFTable*)table->personalFTable)->pre_activate)(table);

  if (table->text != NULL)
    VISUAL_activateTableLine(WA_REVERSE,table->columns,
                     table->vline, table->hline,
                     table->vData,
		     table->text->text[table->text->actLine]);

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->post_activate != NULL)
     (*((_tFTable*)table->personalFTable)->post_activate)(table);

  return 0;
}

int TABLE_deactivate(tTable * table)
{
  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->pre_deactivate != NULL)
     (*((_tFTable*)table->personalFTable)->pre_deactivate)(table);

  VISUAL_activateTableLine(WA_NORMAL,table->columns,
                     table->vline, table->hline,
                     table->vData,
		     table->text->text[table->text->actLine]);

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->post_deactivate != NULL)
     (*((_tFTable*)table->personalFTable)->post_activate)(table);

  return 0;
}

void TABLE_Action(tTable * table,tNextPtr next)
{
 int tecla;
 int atras;
 trAction * accion;
 tCaller * auxCaller;
 char npanel[MAX_NAME_VIEW]="";
 char * ncomponent;
 char * paux;
 MEVENT ev_mouse;
 int wx,wy;
 int linea;
 char nActComponent[MAX_NAME_VIEW+MAX_COMPONENT_NAME+5];
 static trAction mouseAction = {0,1,OP_NONE,NULL};
 mmask_t mmask, oldmmask;
 int hasMouse;

  hasMouse=KEYS_getMouse();
  strcpy(next->view,"");
  next->opToMade=OP_NONE;
  mmask=BUTTON1_CLICKED|BUTTON3_CLICKED|BUTTON4_PRESSED|BUTTON5_PRESSED|BUTTON2_PRESSED|BUTTON1_DOUBLE_CLICKED;

  keypad(table->vTable->win,TRUE);
  while (1)
  {
    accion = NULL;
    sprintf(nActComponent,"%s:%s",table->name,"");
       
    if (hasMouse) mousemask(mmask, &oldmmask);
    tecla = wgetch(table->vTable->win);
    if(hasMouse && tecla == KEY_MOUSE) {
 	 if(getmouse(&ev_mouse) == OK) {
           wx = ev_mouse.x; wy = ev_mouse.y;
           mouseAction.componentNext = LVIEW_searchXYView(wx,wy);
           if (mouseAction.componentNext != NULL) {
             if (strcmp(mouseAction.componentNext, nActComponent)== 0){
               if(ev_mouse.bstate & BUTTON1_CLICKED){
                 linea = TABLE_buscaLinea(table->vData->win,table->vline,wx,wy);
                 if (linea>=0) TABLE_activateLine(table,linea);
               }
               if(ev_mouse.bstate & BUTTON1_DOUBLE_CLICKED){
                tecla=table->mapkey->enter[0];
                accion = TABLE_Move(table,tecla);
               }
               if(ev_mouse.bstate & BUTTON3_CLICKED){
                 tecla=table->mapkey->out[0];
                 accion = TABLE_Move(table,tecla);
               }
               if(ev_mouse.bstate & BUTTON2_PRESSED){
                 tecla=table->mapkey->down[0];
                 accion = TABLE_Move(table,tecla);
               }
               if(ev_mouse.bstate & BUTTON4_PRESSED){
                 tecla=table->mapkey->up[0];
                 accion = TABLE_Move(table,tecla);
               }
               if(ev_mouse.bstate & BUTTON5_PRESSED){
                 tecla=table->mapkey->down[0];
                 accion = TABLE_Move(table,tecla);
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
        accion = TABLE_Move(table,tecla);
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
              if (strcmp(npanel,table->name)!=0)
              {
                 if (npanel[0]!='-'){
                   strcpy(next->view,npanel);
                   strcpy(next->element,ncomponent);
                   next->caller.View=table->name;
                   next->caller.Element=NULL;
                   next->opToMade = accion->opToMade==OP_NONE?table->opToMade:accion->opToMade;
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
                   next->opToMade = accion->opToMade==OP_NONE?table->opToMade:accion->opToMade;
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

int TABLE_hide(tTable * table)
{
  if (table->vTable->status.visible != DIS_NORMAL) return 0;

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->pre_hide != NULL)
     (*((_tFTable*)table->personalFTable)->pre_hide)(table);

  /* ---------------------
   *  BACK_POP 
   * ------------------------ */
  table->vTable->status.visible=DIS_HIDDEN;

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->post_hide != NULL)
     (*((_tFTable*)table->personalFTable)->post_hide)(table);

  return 0;
}

int TABLE_destroy(tTable * table)
{
 int retorno;

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->pre_destroy != NULL)
     (*((_tFTable*)table->personalFTable)->pre_destroy)(table);

  TEXT_clear(table->text);
/*
  if (table->text != NULL) 
  {
    TEXT_free(table->text);
    table->text = NULL;
  }
*/
  retorno = TABLE_hide(table);

  if (table->personalFTable != NULL &&
        ((_tFTable *)table->personalFTable)->post_destroy != NULL)
     (*((_tFTable*)table->personalFTable)->post_destroy)(table);

  return retorno;
}

int TABLE_opToMade(tTable * table)
{
  switch(table->opToMade){
    case OP_HIDE: return TABLE_hide(table);
    case OP_DESTROY: return TABLE_destroy(table);
    default: return 0;
  }
}


static trAction * TABLE_Move(tTable * table,int caracter)
{
  int i,j;
  trAction * resultado;

  rAction.error =0;
  rAction.made =0;
  rAction.componentNext=NULL;
  rAction.opToMade=OP_NONE;

  for (i=0;i!= MAX_KEYS_FUNC;i++)
  {
    if (table->mapkey->enter[i]!=0&&
         table->mapkey->enter[i] == caracter)
    { 
      if (table->personalAction != NULL &&
	   ((_tFActionTable*)table->personalAction)->enter != NULL)
      {
        resultado = ((*((_tFActionTable*)table->personalAction)->enter)(table,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made )
        {
             rAction.opToMade=resultado->opToMade;
             rAction.componentNext = resultado->componentNext;
        }
      }
      if (!rAction.error && !rAction.made && table->move != NULL)
      {
          rAction.made = table->move->enter==NULL?0:1;
          rAction.componentNext = table->move->enter;
          if (!rAction.made) 
	    TABLE_TypeAction(table,A_enter);
      }
      return &rAction;
    }
    if (table->mapkey->out[i]!=0&&
         table->mapkey->out[i] == caracter)
    { 
      if (table->personalAction != NULL &&
	   ((_tFActionTable*)table->personalAction)->out != NULL)
      {
        resultado = ((*((_tFActionTable*)table->personalAction)->out)(table,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error  && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made && table->move != NULL)
      {
          rAction.made = table->move->out==NULL?0:1;
          rAction.componentNext = table->move->out;
      }
      return &rAction;
    }

    if (table->mapkey->next[i]!=0&&
         table->mapkey->next[i] == caracter)
    { 
      TABLE_TypeAction(table,A_next);
    }

    if (table->mapkey->previous[i]!=0&&
         table->mapkey->previous[i] == caracter)
    { 
      TABLE_TypeAction(table,A_previous);
    }
    if (table->mapkey->up[i]!=0&&
         table->mapkey->up[i] == caracter)
    { 
      TABLE_TypeAction(table,A_up);
    }

    if (table->mapkey->down[i]!=0&&
         table->mapkey->down[i] == caracter)
    { 
      TABLE_TypeAction(table,A_down);
    }

    if (table->mapkey->left[i]!=0&&
         table->mapkey->left[i] == caracter)
    { 
      TABLE_TypeAction(table,A_left);
    }

    if (table->mapkey->right[i]!=0&&
         table->mapkey->right[i] == caracter)
    { 
      TABLE_TypeAction(table,A_right);
    }

    if (table->mapkey->back[i]!=0&&
         table->mapkey->back[i] == caracter)
    { 
      if (table->personalAction != NULL &&
	   ((_tFActionTable*)table->personalAction)->back != NULL)
      {
        resultado = ((*((_tFActionTable*)table->personalAction)->back)(table,caracter));
        rAction.error = resultado->error;
        rAction.made = resultado->made;
        if (!resultado->error && resultado->made)
        {
          rAction.componentNext = resultado->componentNext;
          rAction.opToMade=resultado->opToMade;
        }
      }
      if (!rAction.error && !rAction.made && table->move != NULL)
      {
          rAction.made = table->move->back==NULL?0:1;
          rAction.componentNext = table->move->back;
          if (!rAction.made) 
	    TABLE_TypeAction(table,A_back);
      }
      return &rAction;
    }


    for (j=0;j!=MAX_Fn_KEYS;j++)
    {
       if (table->mapkey->Fn[j][i]!=0&&
            table->mapkey->Fn[j][i] == caracter)
       { 
         if (table->personalAction != NULL &&
	   ((_tFActionTable*)table->personalAction)->Fn != NULL)
          {
             resultado = ((*((_tFActionTable*)table->personalAction)->Fn)(table,caracter,j+1));
             rAction.error = resultado->error;
             rAction.made = resultado->made;
             if (!resultado->error && resultado->made)
             {
                     rAction.componentNext = resultado->componentNext;
                     rAction.opToMade=resultado->opToMade;
             }
         }
         if (!rAction.error && !rAction.made && table->move != NULL)
         {
             rAction.made = table->move->Fn[j]==NULL?0:1;
             rAction.componentNext = table->move->Fn[j];
         }
         return &rAction;
       }
    }   
  }   

  return &rAction;
}

static void TABLE_TypeAction(tTable * table,int action)
{
 int ajusteMuestra=0;

 if (table->text == NULL) return;

 switch(action)
 {
    case  A_up:
            if (table->text->actLine > 0) { 
    	     if (table->vData->status.actLine > 0)
             {
              TABLE_deactivate(table);
              table->text->actLine --;
              table->vData->status.actLine--;
              TABLE_activate(table);
             }
             else
             {
               table->vData->status.nactLines=0;
               VISUAL_cleanWin(table->vData);
               table->text->actLine--; 
               table->vData->status.actLine=0;
               VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline,
			table->vData,1);
               TABLE_activate(table);
             }
            }
            break;
    case  A_down:
            if (table->text->actLine < table->text->nroLines-1) { 
             if (table->vData->status.actLine < table->vData->status.nactLines-1) 
             {
               TABLE_deactivate(table);
               table->vData->status.actLine++;
               table->text->actLine ++;
               TABLE_activate(table);
             }
             else {
                VISUAL_cleanWin(table->vData);
                table->text->actLine ++;
                table->vData->status.actLine=0;
                VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,1);
                TABLE_activate(table);
              }
            }
            break;
    case  A_right:
           if (table->vData->status.actField < table->text->maxFields-1)
           {
             table->vData->status.actField++;
             TABLE_calculaColumnsShow(table);
             if (table->vHead != NULL)
             {
                VISUAL_cleanWin(table->vHead);
                table->vHead->status.actField++;
                VISUAL_pintaTableHead(table->columns,table->vline,
                                         table->hline,table->vHead);
             }
             VISUAL_cleanWin(table->vData);
             table->text->actField++;
             ajusteMuestra = table->vData->status.actLine;
             if (ajusteMuestra > 0) {
	       table->text->actLine -=ajusteMuestra;
	       table->vData->status.actLine=0;
             }
             VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
             if (ajusteMuestra > 0) {
	       table->text->actLine +=ajusteMuestra;
	       table->vData->status.actLine=ajusteMuestra;
             }
             TABLE_activate(table);
           }
           break;
    case  A_left:
          if (table->vData->status.actField > 0)
          {
             table->vData->status.actField--;
             TABLE_calculaColumnsShow(table);
             if (table->vHead != NULL) {
               VISUAL_cleanWin(table->vHead);
               table->vHead->status.actField--;
               VISUAL_pintaTableHead(table->columns,table->vline,
                          table->hline,table->vHead);
             }
             VISUAL_cleanWin(table->vData);
             table->text->actField--;
             ajusteMuestra = table->vData->status.actLine;
             if (ajusteMuestra > 0) {
	       table->text->actLine -=ajusteMuestra;
	       table->vData->status.actLine=0;
             }
             VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
             if (ajusteMuestra > 0) {
	       table->text->actLine +=ajusteMuestra;
	       table->vData->status.actLine=ajusteMuestra;
             }
             TABLE_activate(table);
          }
	  break;
    case  A_previous:
          if (table->text->actLine >= table->vData->status.nactLines)
          {
            VISUAL_cleanWin(table->vData);
            table->text->actLine -= table->vData->status.nactLines;
            table->vData->status.actLine=0;
            VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
            TABLE_activate(table);
          }
          else
          {
             if (table->vData->status.actLine < table->text->actLine) {
               VISUAL_cleanWin(table->vData);
               table->vData->status.actLine=0;
               table->text->actLine=0;
               VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
               TABLE_activate(table);
             }
          }
          break;
    case  A_next:
          if ((table->text->nroLines - table->text->actLine ) 
              > table->vData->status.nactLines-1)
          {
            VISUAL_cleanWin(table->vData);
            table->text->actLine += table->vData->status.nactLines;
            table->vData->status.actLine=0;
            if (table->text->actLine >= table->text->nroLines)
		table->text->actLine = table->text->nroLines -1;
            VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
            TABLE_activate(table);
           }
           else
           {
            if ((table->text->nroLines - table->text->actLine ) >=
                (table->vData->status.nactLines - table->vData->status.actLine))
            {
              VISUAL_cleanWin(table->vData);
              table->text->actLine = table->text->nroLines-1;
              table->vData->status.actLine=0;
              VISUAL_pintaTableData(table->columns,table->text,table->vline,
                        table->hline, table->vData,0);
              TABLE_activate(table);
            }
           }
           break;
    default: break;
  }
}

void TABLE_text(tTable * table,tText * text)
{
   table->text = text;
}

int TABLE_setColumnHead(tTable * table, int column,char * data)
{
tTableColumnPtr  aux;
int i;

   if (column > table->nColumns)
    return -1;

   aux = table->columns;
   
   for (i=0;i!=column;i++) aux = aux->next;

   strncpy(aux->title,data,aux->len);
 
 return 0;
}

char * TABLE_getColumnValue(tTable * table,int column)
{
   if (column > table->text->maxColumns-1)
    return NULL;
   return table->text->text[table->text->actLine][column];
}

char ** TABLE_getValue(tTable * table)
{
   return table->text->text[table->text->actLine];
}

char * TABLE_getTextValue(tTable * table,int column)
{
  tTableColumnPtr aux;
  int i;

   if (column > table->text->maxColumns-1)
    return NULL;
   
   aux = table->columns;
   for (i=0;aux != NULL && i < table->text->maxColumns;i++)
     aux = aux->next;

   if (aux != NULL) return table->title;

   return NULL;
}

char ** TABLE_getText(tTable * table)
{
  tTableColumnPtr auxColumn;
  char ** aux;
  int i;
 
   aux = (char **)malloc(sizeof(char *) * table->text->maxColumns);
   if (aux == NULL)
   {
    ERR_Error(ERR_MEM,"Error malloc getText %d\n",sizeof(table->text->maxColumns*sizeof(char*)));
    return NULL;
   }
   
   for (i=0,auxColumn=table->columns;
		i!= table->text->maxColumns && auxColumn != NULL;
		i++,auxColumn=auxColumn->next)
   {
      if (auxColumn != NULL)
        aux[i] = auxColumn->title; 
   }
 
   return aux;
}

static void TABLE_calculaColumnsShow(tTablePtr table)
{
  int show,i;
  tTableColumnPtr aux;
  int nactFields=0;

  aux = table->columns;

  show = table->vData->dimension.ancho-1;

  for (i=0;i!=table->vData->status.actField && aux != NULL;i++)
   aux=aux->next;

  for (;aux != NULL && show >= aux->len;nactFields++){
   show -= (aux->len + table->hline);
   aux=aux->next;
  } 

  if (table->vHead != NULL){
   /* mirar si tiene sentido y cabe el ".." de cabecera */
   if ((table->vHead->dimension.ancho-1 - show) < 2 ) {
	if (nactFields > 1) nactFields --;
   }
   table->vHead->status.nactFields=nactFields;
  }
  table->vData->status.nactFields=nactFields;
  table->vTable->status.nactFields=nactFields;
}

static int TABLE_buscaLinea(WINDOW * win, int vline,int wx, int wy)
{
  int x,y;

   x=wx; y=wy;

   if (wmouse_trafo(win,&y,&x,FALSE) == TRUE) {
    if (vline && y!=0 && y%2) y--;
      return y;
   }
   return -1;
}

static void TABLE_activateLine(tTable * table,int linea)
{
  if (linea != table->vData->status.actLine){
   if (linea < table->vData->status.actLine)
   {
     TABLE_deactivate(table);
     table->text->actLine-=(table->vData->status.actLine - linea); 
     table->vData->status.actLine = linea;
     TABLE_activate(table);
   }
   else {
     if (linea < table->vData->status.nactLines){
      if ((table->text->actLine+(linea - table->vData->status.actLine)) >= 
		 table->text->maxLines) return ; 
      TABLE_deactivate(table);
      table->text->actLine+=(linea - table->vData->status.actLine); 
      table->vData->status.actLine = linea;
      TABLE_activate(table);
     }
   }
  }
}

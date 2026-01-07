#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <tBasic.h>
#include <color.h>
#include <text.h>
#include <error.h>
#include <msg.h>
#include <visual.h>

#define   RESET_CURSOR(visual)  (visual->dimension.border?1:0);
#define   MULTILINEA_HIGH(border,ancho)  (border?(ancho<=3?0:1):(ancho>1?1:0));
#define   MULTILINEA(tipo)  (tipo==C_LSBUTTON || tipo==C_EDIT?1:0);
#define   SCROLL(tipo)  (tipo==C_LSBUTTON?1:0);
#define   VIS_LINEAS(border,alto)  (border?alto-2:alto);
#define   VIS_COLUMN(border,ancho) (border?ancho-2:ancho);
#define   VIS_ANCHO(border,ancho) (border?ancho-2:ancho);


#define   CH_SCR(scroll,chsr,ch) (scroll?chsr:ch)

chtype ch_check=CH_CHECK;
chtype ch_is_check=CH_IS_CHECK;
chtype ch_no_check=CH_NO_CHECK;

chtype ch_lup=DEF_LUP;chtype ch_lup_scr=DEF_LUP_SCR;
chtype ch_ldw=DEF_LDW;chtype ch_ldw_scr=DEF_LDW_SCR;
chtype ch_rup=DEF_RUP;chtype ch_rup_scr=DEF_RUP_SCR;
chtype ch_rdw=DEF_RDW;chtype ch_rdw_scr=DEF_RDW_SCR;
chtype ch_ll=DEF_LL;chtype ch_ll_scr=DEF_LL_SCR;
chtype ch_lu=DEF_LU;chtype ch_lu_scr=DEF_LU_SCR;
chtype ch_lr=DEF_LR;chtype ch_lr_scr=DEF_LR_SCR;
chtype ch_ld=DEF_LD;chtype ch_ld_scr=DEF_LD_SCR;




tVisual * VISUAL_createComponent(int tipo,
		        WINDOW * wParent,
			tDim * dimension,
                        tChAttr * color)
{
  tVisual * visual;
  visual = malloc(sizeof(tVisual));
  if (visual == NULL)
  {
    ERR_fatalError(ERR_MEM,"Error visual malloc (%d)\n",sizeof(tVisual));
  }
  memcpy(&visual->dimension ,dimension,sizeof(tDim));
  memcpy(&visual->color ,color,sizeof(tChAttr));
  if (visual->dimension.border) 
  {
   visual->cursor.x = 1;
   visual->cursor.y = 1;
  }
  else
  {
   visual->cursor.x = 0;
   visual->cursor.y = 0;
  }
  visual->status.insert = 1;
  visual->status.visible = DIS_NORMAL;
  visual->status.activa = 0;

  visual->status.actField = 0;
  visual->status.actLine = 0;
  visual->status.actColumn = 0;

  visual->status.nactFields = 0;
  visual->status.nactLines = VIS_LINEAS(visual->dimension.border,visual->dimension.alto);
  visual->status.nactColumns = VIS_COLUMN(visual->dimension.border,visual->dimension.ancho);

  visual->status.multiLine = MULTILINEA(tipo);
  visual->scroll = SCROLL(tipo);
  visual->status.ckCheck=(tipo==C_CKBUTTON)?ch_check:0;
  visual->status.ckIsCheck=(tipo==C_CKBUTTON)?ch_is_check:0;
  visual->status.ckNoCheck=(tipo==C_CKBUTTON)?ch_no_check:0;

  if (wParent != NULL)
   visual->win = derwin(wParent,
		      visual->dimension.alto, 
		      visual->dimension.ancho, 
                      visual->dimension.y, 
	   	      visual->dimension.x);
  else
   visual->win = newwin(visual->dimension.alto, 
		      visual->dimension.ancho, 
                      visual->dimension.y, 
	   	      visual->dimension.x);

  if (visual->win == NULL)
  {
    ERR_fatalError(ERR_NCURSES,"Error in newwin \n");
  }

  return visual;
}


int VISUAL_changeColor(tVisual * visual,tChAttr * color,tText * texto,tEDIT * edit)
{
 int i=0;

  if (wattroff(visual->win,visual->color.attr) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wattroff\n");
     i=-1;
  }
  memcpy(&visual->color,color,sizeof(tChAttr));
  if (werase(visual->win) != OK)
    ERR_Error(ERR_NCURSES,"Error in werase\n");
  else 
   i=VISUAL_showComponent(visual,texto,edit);

  return i;
}


int VISUAL_showComponent(tVisual * visual,tText * texto,tEDIT * edit)
{
int i=0;
char addCh=0;
int reverse=0;

  if (visual->status.visible == DIS_HIDDEN) return 0;

/* To put . just add | '.'*/
  if (edit != NULL) addCh=edit->chToEDIT;
  if (visual->status.activa) reverse=WA_REVERSE;

  if (wbkgd(visual->win,
            COLOR_PAIR(visual->color.colorpair)|addCh) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wbkgd\n");
    i = -1;
  }

  if (wattron(visual->win,
      COLOR_PAIR(visual->color.colorpair)|visual->color.attr|reverse) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wattron\n");
    i = -1;
  }

  if (visual->dimension.border)
    i = VISUAL_border(visual->win,visual->scroll);

  if (texto != NULL)
    if (VISUAL_pintaTexto(visual,texto,edit) != 0) i = -1;

/*
  if (touchwin(visual->win) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in touchwin\n");
    i = -1;
  }
*/
  if (wrefresh(visual->win) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
    i = -1;
  }

/*  visual->status.visible = 1;*/
  return i;
}

int VISUAL_pintaLinea(tVisual * visual, tText * texto,tEDIT * edit)
{
 char * text;
 int i=0,j=0;
 int nanchoShow = 0;
 int begin = 0;
 char auxText[MAX_TEXT_AUX];

   nanchoShow = VIS_ANCHO(visual->dimension.border,visual->dimension.ancho);
   begin=visual->status.actLine;

   visual->cursor.x = visual->dimension.border;
   visual->cursor.y = begin+visual->dimension.border;

   text = TEXT_getData(texto,begin,0);
   if (text == NULL) return -1;
   if (wattron(visual->win,WA_REVERSE) != OK)
   {
         ERR_Error(ERR_NCURSES,"Error in wattroff\n");
         i=-1;
   }
   if (wmove(visual->win,visual->cursor.y,visual->cursor.x) != OK)
   {
       ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",
					visual->cursor.y,visual->cursor.x);
       i=-1;
   }
       
   strncpy(auxText,text,MAX_TEXT_AUX-1);
   if (visual->status.ckCheck  || (edit != NULL && edit->secret))
   {
      for (j=0;auxText[j]!='\0';j++) {
	if (edit!=NULL && edit->secret) auxText[j]='*';
        else {
          if (text[j] == visual->status.ckCheck)
	    auxText[j]=(texto->check==0)?visual->status.ckNoCheck:visual->status.ckIsCheck;
        }
      }
   }
   wprintw(visual->win,"%-*s",nanchoShow,auxText);

   if (wattroff(visual->win,WA_REVERSE) != OK) {
         ERR_Error(ERR_NCURSES,"Error in wattroff\n");
         i=-1;
   }

   wrefresh(visual->win);
  return i;
}

int VISUAL_pintaTexto(tVisual * visual, tText * texto,tEDIT * edit)
{
 char * text;
 int i=0,j=0;
 int flinea;
 int nlineasShow = 0;
 int nanchoShow = 0;
 int begin = 0;
 int marca = 0;
 char auxText[MAX_TEXT_AUX];


   nlineasShow = visual->status.nactLines;
   nanchoShow = VIS_ANCHO(visual->dimension.border,visual->dimension.ancho);
   if (visual->status.multiLine && edit==NULL)
     begin=visual->status.actLine;
   else
     begin=0;
   flinea=visual->dimension.border;
   marca = visual->cursor.y; 

   if (edit!=NULL){
       visual->cursor.x = RESET_CURSOR(visual);
       visual->cursor.y = RESET_CURSOR(visual);
   }

   if (visual->status.activa && visual->status.multiLine && edit==NULL)
         wattroff(visual->win,WA_REVERSE);

      do 
      {
        text = TEXT_getData(texto,begin,0);
        if (text == NULL) break;
        if (visual->status.multiLine && edit==NULL)
        {
          if (flinea != marca && visual->status.activa){
            if (wattron(visual->win,WA_REVERSE) != OK)
            {
               ERR_Error(ERR_NCURSES,"Error in wattron\n");
               i=-1;
            }
          }
          if (flinea == marca && !visual->status.activa){
            if (wattron(visual->win,WA_REVERSE) != OK)
            {
               ERR_Error(ERR_NCURSES,"Error in wattron\n");
               i=-1;
            }
          }
        }

        if (wmove(visual->win,flinea,visual->cursor.x) != OK)
        {
           ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",
					visual->cursor.y,visual->cursor.x);
           i=-1;
        }
       
        memset(&auxText,'\0',sizeof(auxText));
        strncpy(auxText,text,MAX_TEXT_AUX-1);
        if (visual->status.ckCheck || edit != NULL)
        {
          for (j=0;auxText[j]!='\0';j++) {
		if (edit!=NULL && edit->secret) auxText[j]='*';
                else {
		 if (edit==NULL && text[j] == visual->status.ckCheck)
		    auxText[j]=(texto->check)?visual->status.ckIsCheck:visual->status.ckNoCheck;
                }
          }
          if (strlen(auxText) > nanchoShow) auxText[nanchoShow]='\0';
          if (visual->status.activa) 
            wprintw(visual->win,"%-*s",nanchoShow,auxText);
          else {
            if (visual->status.align == A_Left)
             wprintw(visual->win,"%-*s",nanchoShow,auxText);
            else
             wprintw(visual->win,"%*s",nanchoShow,auxText);
          }
        }
        else
        {
          if (strlen(auxText) > nanchoShow) auxText[nanchoShow]='\0';
          wprintw(visual->win,"%-*s",nanchoShow,auxText);
        }
        if (visual->status.multiLine && edit==NULL)
          wattroff(visual->win,WA_REVERSE);
        nlineasShow--;begin++;flinea++;
      } while (text != NULL && nlineasShow != 0);

      if (wattroff(visual->win,WA_REVERSE) != OK)
      {
         ERR_Error(ERR_NCURSES,"Error in wattroff\n");
         i=-1;
      }

      if (edit!=NULL){
       visual->cursor.x = visual->dimension.border+visual->status.actColumn;
       visual->cursor.y = visual->dimension.border+visual->status.actLine;
       if (wmove(visual->win,visual->cursor.y,visual->cursor.x) != OK)
       {
           ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",
					visual->cursor.y,visual->cursor.x);
         i=-1;
       }
      }

      wrefresh(visual->win);
  return i;
}

int VISUAL_hideComponent(tVisual * visual,tChAttr *parentColor)
{
 int i;

  if (werase(visual->win) != OK)
  {
      ERR_Error(ERR_NCURSES,"Error in werase\n");
      i = -1;
  }
  if (wbkgd(visual->win,COLOR_PAIR(parentColor->colorpair)) != OK)
  {
      ERR_Error(ERR_NCURSES,"Error in bkgd\n");
      i = -1;
  }
  if (wrefresh(visual->win) != OK)
  {
      ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
      i = -1;
  }
  return i;
}
   
int VISUAL_activateComponent(tVisual * visual,tText * texto,tEDIT * edit)
{
 int i=0;

  {
    visual->status.activa = 1;
    visual->cursor.x = RESET_CURSOR(visual);
/*
    visual->cursor.y = RESET_CURSOR(visual);
*/
    if ((i=werase(visual->win))!=OK)
      ERR_Error(ERR_NCURSES,"Error in werase\n");
    else
      i=VISUAL_showComponent(visual,texto,edit);
  }
  return i;
} 

int VISUAL_deactivateComponent(tVisual * visual,tText * text,tEDIT * edit)
{
 int i=0;

  if (visual->status.activa == 0) return 0;

  if (visual->status.visible != DIS_HIDDEN &&
      visual->status.visible != DIS_NO_SELECT )
  {
    visual->status.activa = 0;
    visual->cursor.x = RESET_CURSOR(visual);
    if (wclear(visual->win) != OK)
      ERR_Error(ERR_NCURSES,"Error in wclear\n");
    else
      i = VISUAL_showComponent(visual,text,edit);
  }
  return i;
} 

int VISUAL_changeTextComponent(tVisual * visual ,tText * text,tEDIT * edit)
{
 int i=0;

  if (visual->status.visible != DIS_HIDDEN)
  {
    if (werase(visual->win) != OK)
       ERR_Error(ERR_NCURSES,"Error in werase\n");
    else
       i=VISUAL_showComponent(visual,text,edit);
  }
  return i;
}

int VISUAL_destroy(tVisual * visual)
{
 int i=0;

   if ((i=delwin(visual->win)) != OK)
     ERR_Error(ERR_NCURSES,"Error in delwin\n");

   free(visual);
   return i; 
}

void VISUAL_changeCheck(int check,int is_check, int no_check)
{
  if (check != 0)ch_check = check;
  if (is_check!=0)ch_is_check = is_check;
  if (no_check!=0)ch_no_check = no_check;
}

void VISUAL_changeChCheck(tComponent * component,int caracter)
{
  if (component->visual)
   component->visual->status.ckCheck = caracter;
}

void VISUAL_changeIsCheck(tComponent * component,int caracter)
{
  if (component->visual)
   component->visual->status.ckIsCheck = caracter;
}

void VISUAL_changeNoCheck(tComponent * component, int caracter)
{
  if (component->visual)
   component->visual->status.ckNoCheck = caracter;
}

void VISUAL_clear(tVisual *visual)
{
  if (wclear(visual->win) != OK)
    ERR_Error(ERR_NCURSES,"Error in werase\n");
  wbkgd(visual->win,0);
  if (wrefresh(visual->win) != OK)
    ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
}

int VISUAL_pintaTitle(tVisual * visual, char * texto)
{
    if (wmove(visual->win,0,1) != OK)
    {
         ERR_Error(ERR_NCURSES,"Error in wmove 0-1\n");
         return -1;
    }
    if (wprintw(visual->win,"%s",texto) != OK)
    {
       ERR_Error(ERR_NCURSES,"Error in wprintw\n");
       return -1;
    }

  return 0;
}

int VISUAL_cursor(int cursor)
{
    if (curs_set(cursor)== ERR)
    {
         ERR_Error(ERR_NCURSES,"Error in curs_set\n");
         return -1;
    }
   return 0;
}

int VISUAL_addChar(tVisual * visual,int tecla)
{
 int topex,topey;
 int ret=0;

  topex= VIS_COLUMN(visual->dimension.border,visual->dimension.ancho);

  if (wattron(visual->win,WA_REVERSE) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wattron\n");
    ret=-1;
  }
  if (mvwaddch(visual->win,visual->cursor.y,visual->cursor.x,tecla)== ERR &&
      visual->cursor.x != topex-1)
  {
       ERR_Error(ERR_NCURSES,"Error in waddch\n");
       return -1;
  }
  if (wattroff(visual->win,WA_REVERSE) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wattroff\n");
    ret=-1;
  }

  if(visual->cursor.x != topex-1)
    getyx(visual->win,visual->cursor.y,visual->cursor.x);
  else
    visual->cursor.x++;

  if (visual->cursor.x >= topex)
  {
    topey= VIS_COLUMN(visual->dimension.border,visual->dimension.alto);
    visual->cursor.x=RESET_CURSOR(visual);
    visual->cursor.y++;
    ret=1;
    if (visual->cursor.y >= topey)
    {
      visual->cursor.y = RESET_CURSOR(visual);
      ret=2;
    }
    if (wmove(visual->win,visual->cursor.y,visual->cursor.x) != OK)
    {
      ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",
					visual->cursor.y,visual->cursor.x);
      return -1;
    }
  }
  if (wrefresh(visual->win) != OK)
  {
      ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
      return  -1;
  }
  return ret;
}

int VISUAL_setXY(tVisual * visual,int linea,int column)
{
   visual->cursor.x = RESET_CURSOR(visual);
   visual->cursor.y = RESET_CURSOR(visual);
   visual->cursor.y += linea;
   visual->cursor.x += column;
   if (wmove(visual->win,visual->cursor.y,visual->cursor.x) != OK)
   {
      ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",
					visual->cursor.y,visual->cursor.x);
      return -1;
   }
  if (wrefresh(visual->win) != OK)
  {
      ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
      return  -1;
  }
  return 0;
}


void VISUAL_changeBorder(chtype scroll, chtype chll, chtype chlr, chtype chlu,
		 	 chtype chld, chtype chlup, chtype chrup,
                         chtype chldw, chtype chrdw)
{
  if (!scroll){
    ch_lup=chlup;
    ch_ldw=chldw;
    ch_rup=chrup;
    ch_rdw=chrdw;
    ch_ll=chll;
    ch_lr=chlr;
    ch_lu=chlu;
    ch_ld=chld;
  }
  else {
    ch_lup_scr=chlup;
    ch_ldw_scr=chldw;
    ch_rup_scr=chrup;
    ch_rdw_scr=chrdw;
    ch_ll_scr=chll;
    ch_lr_scr=chlr;
    ch_lu_scr=chlu;
    ch_ld_scr=chld;
  }
}

int VISUAL_msgShow(WINDOW * win, tMsgPtr msg, char texto[24][128])
{
int i=0,error=0;
int x=0,y=0;
tDim   dimButton;


  if (wbkgd(win,COLOR_PAIR(msg->color.colorpair)) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wbkgd\n");
    error = -1;
  }
  if (msg->dimension.border)
  {
    y++; x++;
    if (VISUAL_border(win,0) != 0) error=-1;
  }

  if (wattron(win,COLOR_PAIR(msg->color.colorpair)|msg->color.attr) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wattron\n");
    error = -1;
  }

  if (strcmp(msg->title,"")!=0)
  {
    if (wmove(win,0,1) != OK)
    {
         ERR_Error(ERR_NCURSES,"Error in wmove 0-1\n");
         return -1;
    }
    if (wprintw(win,"%s",msg->title) != OK)
    {
       ERR_Error(ERR_NCURSES,"Error in wprintw\n");
       return -1;
    }
  }

  for (i=0;i!= LINES;i++,y++)
  {
    if (strcmp(texto[i],"")==0) break;
    if (wmove(win,y,x) != OK)
    {
         ERR_Error(ERR_NCURSES,"Error in wmove\n");
         return -1;
    }
    if (wprintw(win,"%s",texto[i]) != OK)
    {
       ERR_Error(ERR_NCURSES,"Error in wprintw\n");
       return -1;
    }
  }

  switch(msg->nroButtons)
  {
    case 1:
           dimButton.border = 1;
           dimButton.ancho = msg->dimButton1.ancho;
           dimButton.alto = msg->dimButton1.alto-1;
           dimButton.y = msg->dimension.alto - msg->dimButton1.alto;
           dimButton.x = (msg->dimension.ancho / 2) -
			 (msg->dimButton1.ancho / 2);
           msg->wButton1 = derwin(win,
		         dimButton.alto,
		         dimButton.ancho,
                         dimButton.y, dimButton.x);
           if (VISUAL_border(msg->wButton1,0) != 0) error=-1;
           if (wattron(msg->wButton1,COLOR_PAIR(msg->color.colorpair)|A_REVERSE) != OK)
           {
             ERR_Error(ERR_NCURSES,"Error in wattron\n");
             error = -1;
           }
           if (wmove(msg->wButton1,1,1) != OK)
           {
               ERR_Error(ERR_NCURSES,"Error in wmove 1-1\n");
               return -1;
           }
           if (wprintw(msg->wButton1,"%-*s",dimButton.ancho-2,msg->ButtonText1) != OK)
           {
              ERR_Error(ERR_NCURSES,"Error in wprintw\n");
              return -1;
           }
           break;
    case 2:
           dimButton.border =1;
           dimButton.ancho = msg->dimButton1.ancho;
           dimButton.alto = msg->dimButton1.alto-1;
           dimButton.y = msg->dimension.alto - msg->dimButton1.alto;
           dimButton.x = (msg->dimension.ancho / 2) -
			 msg->dimButton1.ancho;
           msg->wButton1 = derwin(win,
		         dimButton.alto,
		         dimButton.ancho,
                         dimButton.y, dimButton.x);
           if (VISUAL_border(msg->wButton1,0) != 0) error=-1;
           if (wattron(msg->wButton1,COLOR_PAIR(msg->color.colorpair)|A_REVERSE) != OK)
           {
             ERR_Error(ERR_NCURSES,"Error in wattron\n");
             error = -1;
           }
           if (wmove(msg->wButton1,1,1) != OK)
           {
               ERR_Error(ERR_NCURSES,"Error in wmove 1-1\n");
               return -1;
           }
           if (wprintw(msg->wButton1,"%-*s",dimButton.ancho-2,msg->ButtonText1) != OK)
           {
              ERR_Error(ERR_NCURSES,"Error in wprintw\n");
              return -1;
           }
           dimButton.border =1;
           dimButton.ancho = msg->dimButton2.ancho;
           dimButton.alto = msg->dimButton2.alto-1;
           dimButton.y = msg->dimension.alto - msg->dimButton2.alto;
           dimButton.x = (msg->dimension.ancho / 2) + 1;
           msg->wButton2 = derwin(win,
		         dimButton.alto,
		         dimButton.ancho,
                         dimButton.y, dimButton.x);
           if (VISUAL_border(msg->wButton2,0) != 0) error=-1;
           if (wattron(msg->wButton2,COLOR_PAIR(msg->color.colorpair)) != OK)
           {
             ERR_Error(ERR_NCURSES,"Error in wattron\n");
             error = -1;
           }
           if (wmove(msg->wButton2,1,1) != OK)
           {
               ERR_Error(ERR_NCURSES,"Error in wmove 1-1\n");
               return -1;
           }
           if (wprintw(msg->wButton2,"%-*s",dimButton.ancho-2,msg->ButtonText2) != OK)
           {
              ERR_Error(ERR_NCURSES,"Error in wprintw\n");
              return -1;
           }
           break;
    default:
  }

  if (wnoutrefresh(win) != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wnoutrefresh\n");
    error = -1;
  }
  if (doupdate() != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in doupdate\n");
    error = -1;
  }
  return error;
}

int VISUAL_color(WINDOW * win, tChAttr * color)
{
   if (wattron(win,COLOR_PAIR(color->colorpair)|color->attr) != OK)
   {
       ERR_Error(ERR_NCURSES,"Error in wattron\n");
       return -1;
   }

 return 0;
}

int VISUAL_border(WINDOW * win,int scroll)
{
    if (wborder(win, 
		(CH_SCR(scroll,ch_ll_scr,ch_ll)),
		(CH_SCR(scroll,ch_lr_scr,ch_lr)),
		(CH_SCR(scroll,ch_lu_scr,ch_lu)),
		(CH_SCR(scroll,ch_ld_scr,ch_ld)),
		(CH_SCR(scroll,ch_lup_scr,ch_lup)),
		(CH_SCR(scroll,ch_rup_scr,ch_rup)),
		(CH_SCR(scroll,ch_ldw_scr,ch_ldw)),
		(CH_SCR(scroll,ch_rdw_scr,ch_rdw))
                ) != OK)
    {
      ERR_Error(ERR_NCURSES,"Error in wborder\n");
      return -1;
    }
   return 0;
}

int VISUAL_win(WINDOW * win,tChAttrPtr color)
{
   wclear(win);
   wbkgd(win,COLOR_PAIR(color->colorpair));
   if (wattron(win,COLOR_PAIR(color->colorpair)|color->attr) != OK)
   {
    ERR_Error(ERR_NCURSES,"Error in wattron\n");
    return -1;
   }
   return 0;
}

int VISUAL_pintaTableHead(tTableColumnPtr element,unsigned short vline,
				unsigned short hline, tVisual * visual)
{
  int error,i;

  visual->status.nactLines =1;

  for (i=0;i!=visual->status.actField && element != NULL;i++)
    element=element->next;

  for (i=0;element != NULL && i!=visual->status.nactFields;i++)
  {
     if (hline)
     {
          error = wprintw(visual->win,"%-*.*s|",element->len-1,element->len-1,element->title);
     }
     else
          error = wprintw(visual->win,"%-*.*s",element->len,element->len,element->title);
     if (error != OK)
     {
          ERR_Error(ERR_NCURSES,"Error in wprintw\n");
          return -1;
     }
     element=element->next;
  }
  if (element != NULL) {
      if (wprintw(visual->win,"%s","..") != OK)
      {
          ERR_Error(ERR_NCURSES,"Error in wprintw\n");
          return -1;
      }
  }
  if (vline) {
    if (wmove(visual->win,1,0) == OK) {
      if (whline(visual->win,'-',visual->dimension.ancho) != OK){
          ERR_Error(ERR_NCURSES,"Error in whline %d\n",visual->dimension.ancho);
          return -1;
      } 
    }else {
      ERR_Error(ERR_NCURSES,"Error in whline\n");
      return -1;
    }
  }
  wrefresh(visual->win);
  return 0;
}

int VISUAL_pintaTableData(tTableColumnPtr element,tTextPtr data,
			unsigned short vline, unsigned short hline, 
			tVisual * visual,int update)
{
  int showC,showL,error;
  int lineS,fieldS,vlinea=0;
  tTableColumnPtr cabElems,auxElems;
  int nactLines=0;
  int i;

  showL=visual->dimension.alto;

  lineS=data->actLine;
  fieldS=data->actField;
  
  cabElems = element;
  for (i=0;i!=visual->status.actField && cabElems != NULL;i++)
    cabElems=cabElems->next;


  for (;vlinea < showL && lineS < data->nroLines;lineS++)
  {
    auxElems = cabElems;
    showC=visual->status.nactFields;
    if (wmove(visual->win,vlinea,0) != OK) {
          ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",vline,0);
          return -1;
    }
    nactLines++;
    for (;auxElems!=NULL && showC > 0 && fieldS < data->maxFields;fieldS++,showC--)
    {
     if (hline)
         error = wprintw(visual->win,"%-*.*s|",auxElems->len-1,
				auxElems->len-1,data->text[lineS][fieldS]);
     else
         error = wprintw(visual->win,"%-*.*s",auxElems->len,
				auxElems->len,data->text[lineS][fieldS]);
     if (error != OK)
     {
          ERR_Error(ERR_NCURSES,"Error in wprintw\n");
          return -1;
     }

     auxElems=auxElems->next;
    }
    fieldS=data->actField;
    vlinea++;

    if (vline && vlinea < showL) {
       if (wmove(visual->win,vlinea,0) == OK) {
        if (whline(visual->win,'-',visual->dimension.ancho) != OK) {
           ERR_Error(ERR_NCURSES,"Error in whline %d\n",visual->dimension.ancho);
          return -1;
        } 
       }else{
          ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",vline,0);
          return -1;
       }
       vlinea++;
     }
  }
  if (visual->status.nactLines == 0 || update)
   visual->status.nactLines = nactLines;
  wrefresh(visual->win);
  return 0;
}

int  VISUAL_activateTableLine(int modo,tTableColumnPtr element,
		     unsigned short vline, unsigned short hline, 
		     tVisual * visual,
                     char ** textLine)
{
  unsigned short vnline=0;
  int error = 0,i;
  char ** aux;
  tTableColumnPtr auxElement;

  aux = textLine;
  vnline =(vline)?visual->status.actLine*2:visual->status.actLine;
  aux+=visual->status.actField;
  for (i=0;i!=visual->status.actField && element != NULL;i++)
    element=element->next;
  auxElement = element;

  if (wmove(visual->win,vnline,0) != OK) {
      ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",vnline,0);
      return -1;
  }

  if (modo==WA_REVERSE){
   if (wattron(visual->win,WA_REVERSE) != OK){
      ERR_Error(ERR_NCURSES,"Error in wattron reverse");
      return -1;
   }
  }

  for (i=0;i!=visual->status.nactFields;i++,aux++)
  {
     if (hline)
        error = wprintw(visual->win,"%-*.*s|",auxElement->len-1,auxElement->len-1,*aux);
     else
        error = wprintw(visual->win,"%-*.*s",auxElement->len,auxElement->len,*aux);
    auxElement=auxElement->next;
  }

  if (modo == WA_REVERSE){
   if (wattroff(visual->win,WA_REVERSE) != OK)
   {
      ERR_Error(ERR_NCURSES,"Error in wattroff reverse");
      return -1;
   }
  }
  
  wrefresh(visual->win);
  return error;
}

int VISUAL_cleanWin(tVisualPtr visual)
{
   if (wclear(visual->win) != OK){
      ERR_Error(ERR_NCURSES,"Error in wclear\n");
      return -1;
    }
  wrefresh(visual->win);
  return 0;
}

int VISUAL_msgSwitchButtons(WINDOW * win, tMsgPtr msg, int button)
{
 int error,x1,x2,y;

  switch(button)
  {
    case 0:
      error=wattroff(msg->wButton2,WA_REVERSE);
      error=wattron(msg->wButton1,WA_REVERSE);
      break;
    case 1:
      error=wattroff(msg->wButton1,WA_REVERSE);
      error=wattron(msg->wButton2,WA_REVERSE);
      break;
    default:
      break;
  }
  if( error != OK)
  {
    ERR_Error(ERR_NCURSES,"Error in wattroff\n");
    error = -1;
  }
  getmaxyx(msg->wButton1,y,x1);
  getmaxyx(msg->wButton2,y,x2);

  if (wmove(msg->wButton1,1,1) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wmove 1-1\n");
     return -1;
  }
  if (wprintw(msg->wButton1,"%-*s",(x1-2),msg->ButtonText1) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wprintw\n");
     return -1;
  }
  if (wmove(msg->wButton2,1,1) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wmove 1-1\n");
     return -1;
  }
  if (wprintw(msg->wButton2,"%-*s",(x2-2),msg->ButtonText2) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wprintw\n");
     return -1;
  }

  if (wrefresh(msg->wButton1) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
     error = -1;
  }
  if (wrefresh(msg->wButton2) != OK)
  {
     ERR_Error(ERR_NCURSES,"Error in wrefresh\n");
     error = -1;
  }
  return error;
}

int VISUAL_pintaEditData(tTextPtr data, tVisual * visual)
{
  int showC,showL;
  int lineS,vlinea=0;
  int lData;
  int error;

  showL=visual->dimension.border?visual->dimension.alto-2:
				visual->dimension.alto;
  showC=visual->dimension.border?visual->dimension.ancho-2:
				visual->dimension.ancho;

  showC--;
  lineS=data->actLine;
  
  for (;vlinea < showL && lineS < data->nroLines;lineS++,vlinea++)
  {
    if (wmove(visual->win,vlinea+
		visual->dimension.border,visual->dimension.border) != OK) {
       ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",vline,0);
       error=ERR_NCURSES;
    }
    lData = TEXT_strVisLen(data->text[lineS][0],visual->status.actColumn);
    if (lData>0)
    {
     if (wprintw(visual->win,"%.*s",showC,data->text[lineS][0]+visual->status.actColumn) != OK)
     {
       ERR_Error(ERR_NCURSES,"Error in wprintw\n");
       error=ERR_NCURSES;
     }
    }
  }

  visual->status.nactLines = vlinea;

  if (visual->cursor.y > vlinea-1) visual->cursor.y=vlinea-1;
/*
  lData=strlen(&data->text[data->actLine+visual->cursor.y][0][visual->status.actColumn])-1;
  if (lData < visual->cursor.x) {
       visual->cursor.x =lData>0?lData:0;
  }
*/
  lData = TEXT_strVisLen(data->text[data->actLine+visual->cursor.y][0],
                visual->status.actColumn);
  if (visual->cursor.x > lData) visual->cursor.x = lData;

  if (wmove(visual->win,visual->cursor.y,visual->cursor.x) != OK) {
       ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",visual->cursor.y,visual->cursor.x);
       error=ERR_NCURSES;
    }
  wrefresh(visual->win);
  return error;
}

int VISUAL_pintaInsert(tVisual * visual)
{
 int len;

  if (visual->dimension.ancho < 10) return 0;
  len = visual->dimension.ancho - 10;
  switch(visual->status.insert) {
    case Insert:
        if (wmove(visual->win,(visual->dimension.alto-1),len) != OK){
         ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",visual->dimension.alto,len);
         return ERR_NCURSES;
        }
        if (wprintw(visual->win,"%s","Insert  ") != OK){
         ERR_Error(ERR_NCURSES,"Error in wprintw \n");
         return ERR_NCURSES;
        }
        break;
    case Replace:
        if (wmove(visual->win,visual->dimension.alto-1 ,len) != OK){
         ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",visual->dimension.alto,len);
         return ERR_NCURSES;
        }
        if (wprintw(visual->win,"%s","Replace ") != OK){
         ERR_Error(ERR_NCURSES,"Error in wprintw \n");
         return ERR_NCURSES;
        }
        break;
    case ReadOnly:
        if (wmove(visual->win,visual->dimension.alto-1 ,len) != OK){
         ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",visual->dimension.alto,len);
         return ERR_NCURSES;
        }
        if (wprintw(visual->win,"%s","ReadOnly") != OK){
         ERR_Error(ERR_NCURSES,"Error in wprintw \n");
         return ERR_NCURSES;
        }
        break;
    default:
        return -1;
   }

  
  return 0;
}

int VISUAL_pintaFileName(tVisual * visual,char * nFile)
{
  int l;

  l=strlen(nFile);

  if (visual->dimension.ancho < (10+l+1)) return 0;
  if (wmove(visual->win,visual->dimension.alto-1,1) != OK){
     ERR_Error(ERR_NCURSES,"Error in wmove %d-%d\n",visual->dimension.alto,l);
     return ERR_NCURSES;
  }
  if (wprintw(visual->win,"%s",nFile) != OK){
         ERR_Error(ERR_NCURSES,"Error in wprintw \n");
         return ERR_NCURSES;
  }

  return 0;
}



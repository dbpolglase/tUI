#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>
#include <error.h>
#include <tBasic.h>
#include <error.h>
#include <color.h>
#include <keys.h>
#include <msg.h>
#include <view.h>
#include <lview.h>
#include <back.h>
#include <visual.h>

typedef struct {
  int cursor;
  int y;
  int x;
  WINDOW * win;
} tsaveCursor;

static tsaveCursor saveCursor;

static tMsg vistaMsg[3]; 
static tMsg oldVistaMsg[3]; 
static char msgText[24][128];
static int minAncho[3]={0,0,0};
static int minAlto[3]={0,0,0};
static struct sigaction new_action,old_action;

static void MSG_minDimension(enum CMsg type);
static void MSG_calculaDim(enum CMsg type, char * Text);
static void MSG_calculaXY(enum CMsg type,unsigned int center,tDim actVisual);
static int MSG_show(enum CMsg type);
static unsigned int nroSeg = MSG_TIME_INFO;
static unsigned int isAlarm = 0;
static void MSG_setAlarm();
static void MSG_getAlarm();
static void MSG_saveCursor(WINDOW * win);
static void MSG_restoreCursor();

void MSG_Init()
{
  vistaMsg[M_INFO].color.colorpair = COLOR_get(COLOR_BACK_INFO,COLOR_FORE_INFO);
  vistaMsg[M_INFO].color.attr= ATTR_INFO;
  vistaMsg[M_INFO].nroButtons=DEF_INFO_NBUTTONS;
  vistaMsg[M_INFO].dimension.border=DEF_INFO_BORDER;
  strcpy(vistaMsg[M_INFO].title,DEF_INFO_TITLE);
  strcpy(vistaMsg[M_INFO].ButtonText1,DEF_INFO_BUTTON1);
  strcpy(vistaMsg[M_INFO].ButtonText2,DEF_INFO_BUTTON2);
  vistaMsg[M_WARNING].color.colorpair = COLOR_get(COLOR_BACK_WARNING,COLOR_FORE_WARNING);
  vistaMsg[M_WARNING].color.attr= ATTR_WARNING;
  vistaMsg[M_WARNING].nroButtons=DEF_WARNING_NBUTTONS;
  vistaMsg[M_WARNING].dimension.border=DEF_WARNING_BORDER;
  strcpy(vistaMsg[M_WARNING].title,DEF_WARNING_TITLE);
  strcpy(vistaMsg[M_WARNING].ButtonText1,DEF_WARNING_BUTTON1);
  strcpy(vistaMsg[M_WARNING].ButtonText2,DEF_WARNING_BUTTON2);
  vistaMsg[M_ERROR].color.colorpair = COLOR_get(COLOR_BACK_ERROR,COLOR_FORE_ERROR);
  vistaMsg[M_ERROR].color.attr= ATTR_ERROR;
  vistaMsg[M_ERROR].nroButtons=DEF_ERROR_NBUTTONS;
  vistaMsg[M_ERROR].dimension.border=DEF_ERROR_BORDER;
  strcpy(vistaMsg[M_ERROR].title,DEF_ERROR_TITLE);
  strcpy(vistaMsg[M_ERROR].ButtonText1,DEF_ERROR_BUTTON1);
  strcpy(vistaMsg[M_ERROR].ButtonText2,DEF_ERROR_BUTTON2);
  memset(msgText,'\0',sizeof(msgText));
  memset(&vistaMsg[M_INFO].dimButton1,0,sizeof(vistaMsg[M_INFO].dimButton1));
  memset(&vistaMsg[M_INFO].dimButton2,0,sizeof(vistaMsg[M_INFO].dimButton2));
  memset(&vistaMsg[M_WARNING].dimButton1,0,sizeof(vistaMsg[M_WARNING].dimButton1));
  memset(&vistaMsg[M_WARNING].dimButton2,0,sizeof(vistaMsg[M_WARNING].dimButton2));
  memset(&vistaMsg[M_ERROR].dimButton1,0,sizeof(vistaMsg[M_ERROR].dimButton1));
  memset(&vistaMsg[M_ERROR].dimButton2,0,sizeof(vistaMsg[M_ERROR].dimButton2));
  MSG_minDimension(M_INFO);
  MSG_minDimension(M_WARNING);
  MSG_minDimension(M_ERROR);
  vistaMsg[M_INFO].wButton1=vistaMsg[M_INFO].wButton2 = NULL;
  vistaMsg[M_WARNING].wButton1=vistaMsg[M_WARNING].wButton2 = NULL;
  vistaMsg[M_ERROR].wButton1=vistaMsg[M_ERROR].wButton2 = NULL;
}


void MSG_borderColor(enum CMsg type, unsigned short border,tChAttr * color)
{
   vistaMsg[type].dimension.border = (border==1)?1:0;
   memcpy(&vistaMsg[type].color,color,sizeof(tChAttr));
   MSG_minDimension(type);
}

void MSG_txtButton(enum CMsg type, 
                   char * title,
		   unsigned short nButtons,
		   char * text1, char * text2)
{
    vistaMsg[type].nroButtons = nButtons;
    if (title == NULL) strcpy(vistaMsg[type].title,"");
    else strcpy(vistaMsg[type].title,title);
    if (text1 == NULL) strcpy(vistaMsg[type].ButtonText1,"");
    else strcpy(vistaMsg[type].ButtonText1,text1);
    if (text2 == NULL) strcpy(vistaMsg[type].ButtonText2,"");
    else strcpy(vistaMsg[type].ButtonText2,text2);
    MSG_minDimension(type);
}


int MSG_create(enum CMsg type, unsigned int center, char * formato,...)
{
 va_list       params;
 char text[MAX_MSG_DATA+5];

  if (formato == NULL){ ERR_Error(ERR_DATA,"msg empty");return -1;}
  va_start(params, formato);
  if (vsprintf(text,formato,params) < 0) {
   ERR_Error(ERR_DATA,"msg to big");
   va_end(params);
   return -1;
  }
  va_end(params);

  MSG_calculaDim(type,text);
  if (VIEW_getActive() != NULL)
  {
   switch (VIEW_getActive()->type)
   {
     case V_Panel:
       MSG_saveCursor(VIEW_getActive()->view.panel->visual->win);
       vistaMsg[type].wBack = BACK_pushWindow(
          VIEW_getActive()->view.panel->visual->win);
          MSG_calculaXY(type,center,VIEW_getActive()->view.panel->visual->dimension);
	break;
     case V_Table:
       MSG_saveCursor(VIEW_getActive()->view.table->vData->win);
       vistaMsg[type].wBack = BACK_pushWindow(
          VIEW_getActive()->view.table->vTable->win);
          MSG_calculaXY(type,center,VIEW_getActive()->view.table->vTable->dimension);
	break;
     case V_Edit:
       MSG_saveCursor(VIEW_getActive()->view.edit->vData->win);
       vistaMsg[type].wBack = BACK_pushWindow(
          VIEW_getActive()->view.edit->vHead->win);
          MSG_calculaXY(type,center,VIEW_getActive()->view.edit->vData->dimension);
	break;
     default:
   }
  }
  else
   vistaMsg[type].wBack = NULL;
  return MSG_show(type);
}

void MSG_setSegInfo(unsigned int nseg){
  nroSeg = nseg;
}

static void MSG_setAlarm(){
   memset(&new_action, 0, sizeof(new_action)); 
   new_action.sa_handler = MSG_getAlarm;
   sigemptyset(&new_action.sa_mask);
   new_action.sa_flags = 0;

   sigaction(SIGALRM, &new_action, &old_action);
   alarm(nroSeg);
}

static void MSG_getAlarm(){
  sigaction(SIGALRM, &old_action, NULL);
  isAlarm=1;
}

static void MSG_calculaDim(enum CMsg type, char * Text)
{
  int ancho=0,alto=0;
  char * textAux;
  char * token;

  if (Text != NULL) /* Just to save strtok core in case constant Text */
  {
    textAux = malloc(strlen(Text)+2);
    strcpy(textAux,Text);
    if (textAux == NULL)
    {
      ERR_Error(ERR_MEM,
		"Error creating msg text malloc %d\n",strlen(Text));
      return;
    }

    token = strtok(textAux, "\n");
    while (token != NULL)
    {
      if ((strlen(token)) > ancho) ancho = strlen(token);
      if (ancho > COLS - 4) ancho = COLS-4;
      strncpy(msgText[alto],token,COLS-4);
      alto ++;
      token=strtok(NULL,"\n");
    }
  }
  alto += minAlto[type]+1;
  ancho = ancho>minAncho[type]?ancho:minAncho[type];
  ancho +=  vistaMsg[type].dimension.border?2:0;
  if (alto > LINES - 2) alto = LINES -2;
  if (ancho > COLS - 4) ancho = COLS-4;
  vistaMsg[type].dimension.alto = alto;
  vistaMsg[type].dimension.ancho = ancho;
}

static void MSG_calculaXY(enum CMsg type,unsigned int center, tDim actVisual)
{
   vistaMsg[type].dimension.x = (COLS/2 - vistaMsg[type].dimension.ancho/2);
   vistaMsg[type].dimension.y = (LINES/2 - vistaMsg[type].dimension.alto/2);
   if (center == CENTER_TERMINAL) return;
   if (vistaMsg[type].dimension.x < actVisual.x ||
       vistaMsg[type].dimension.x > actVisual.x+actVisual.ancho)
     vistaMsg[type].dimension.x=actVisual.x;
   if (vistaMsg[type].dimension.y < actVisual.y ||
       vistaMsg[type].dimension.y > actVisual.y+actVisual.alto)
     vistaMsg[type].dimension.y=actVisual.y;
}

static int MSG_show(enum CMsg type)
{
  WINDOW * win;
  int tecla;
  MEVENT ev_mouse;
  mmask_t mmask, oldmmask;
  mmask=BUTTON1_CLICKED;
  int noClick = 1;
  int x,y;
  int teclaActiva;
  int hasMouse;

  int retorno = 0;

  hasMouse = KEYS_getMouse();
  win = newwin( vistaMsg[type].dimension.alto,
		vistaMsg[type].dimension.ancho,
		vistaMsg[type].dimension.y,
		vistaMsg[type].dimension.x);
  
  retorno = vistaMsg[type].nroButtons;
  teclaActiva = 0;

  VISUAL_msgShow(win, &vistaMsg[type], msgText);
  keypad(win,TRUE);

  if (hasMouse) mousemask(mmask, &oldmmask);

  isAlarm=0;
  while (noClick && !isAlarm)
  {
   if (vistaMsg[type].nroButtons ==  0) MSG_setAlarm();
   tecla = wgetch(win);
   if (vistaMsg[type].nroButtons !=  0) 
   {
    if(hasMouse && tecla == KEY_MOUSE)
    {
      if (getmouse(&ev_mouse) == OK) 
      {
        y = ev_mouse.y;
        x = ev_mouse.x;
      }
      if (wmouse_trafo(win, &y, &x, FALSE) == TRUE)
      {
         if(ev_mouse.bstate & BUTTON1_CLICKED){
           if (y >= vistaMsg[type].dimension.alto - 4)
           {
             if ( x < vistaMsg[type].dimension.ancho / 2){
                retorno=0; 
                noClick=0;
             }
             else
             {
               retorno = (x >= vistaMsg[type].dimension.ancho/2&&
			       vistaMsg[type].nroButtons==1?0:1);
               noClick=0;
             }
           }
         }
      }
     }
     if (tecla == KEY_ENTER || tecla == 10 || tecla == 13){
       retorno = teclaActiva;
       noClick =0;
     }
     if (tecla == KEY_LEFT || tecla == KEY_RIGHT) {
         if (vistaMsg[type].nroButtons ==  2) {
          if (teclaActiva==0) teclaActiva=1; else teclaActiva=0;
            VISUAL_msgSwitchButtons(win, &vistaMsg[type], teclaActiva);
        }
     }
   }
   else noClick=0;
  }
    

  if (vistaMsg[type].wButton1 != NULL)
  {
    delwin(vistaMsg[type].wButton1);
    vistaMsg[type].wButton1 = NULL;
  }
  if (vistaMsg[type].wButton2 != NULL)
  {
    delwin(vistaMsg[type].wButton2);
    vistaMsg[type].wButton2 = NULL;
  }
  delwin(win);
  
  BACK_popWindow(vistaMsg[type].wBack);
  memset(msgText,'\0',sizeof(msgText));
  
  MSG_restoreCursor();

  return retorno;
}


static void MSG_minDimension(enum CMsg type)
{
   minAncho[type] =  vistaMsg[type].dimension.border?2:0;
   minAncho[type] +=  2;
   switch(vistaMsg[type].nroButtons)
   {
     case 0: 
       memset(&vistaMsg[type].dimButton1,0,sizeof(vistaMsg[type].dimButton1));
       memset(&vistaMsg[type].dimButton2,0,sizeof(vistaMsg[type].dimButton2));
           break;
     case 1: 
           minAncho[type] +=  2+strlen(vistaMsg[type].ButtonText1);
           vistaMsg[type].dimButton1.alto = 3;
           vistaMsg[type].dimButton1.ancho = 4+strlen(vistaMsg[type].ButtonText1);
           break;
     case 2: 
           if (strlen(vistaMsg[type].ButtonText1) > 
               strlen(vistaMsg[type].ButtonText2)){
            minAncho[type] +=  4+(2*strlen(vistaMsg[type].ButtonText1));
            vistaMsg[type].dimButton1.ancho = 2+strlen(vistaMsg[type].ButtonText1);
            vistaMsg[type].dimButton2.ancho = 2+strlen(vistaMsg[type].ButtonText1);
           }
           else {
            minAncho[type] +=  4+(2*strlen(vistaMsg[type].ButtonText2));
            vistaMsg[type].dimButton1.ancho = 2+strlen(vistaMsg[type].ButtonText2);
            vistaMsg[type].dimButton2.ancho = 2+strlen(vistaMsg[type].ButtonText2);
           }
           vistaMsg[type].dimButton2.alto = 3;
           break;
     default:
           break;
   }

   vistaMsg[type].dimButton1.alto = vistaMsg[type].dimButton2.alto = 4;
   minAlto[type] =  2+vistaMsg[type].dimension.border?2:0;
   if (vistaMsg[type].nroButtons != 0)
   minAlto[type] =  3+1;
}

void MSG_saveView(enum CMsg type){
 memcpy(&oldVistaMsg[type],&vistaMsg[type],sizeof(tMsg)); 
}

void MSG_restoreView(enum CMsg type){
 memcpy(&vistaMsg[type],&oldVistaMsg[type],sizeof(tMsg)); 
}

static void MSG_saveCursor(WINDOW * win)
{
  saveCursor.win = win;
  getyx(win, saveCursor.y, saveCursor.x);
  saveCursor.cursor = curs_set(0);
}

static void MSG_restoreCursor()
{
  if (saveCursor.cursor != 0){
   curs_set(saveCursor.cursor);
   wmove(saveCursor.win, saveCursor.y, saveCursor.x);
  }
}


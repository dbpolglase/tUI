#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <tBasic.h>
#include <error.h>
#include <back.h>

static WINDOW * Wmaster = NULL;

int BACK_init()
{
  Wmaster = newwin(LINES,COLS,0,0); 
  return 0;
}

int BACK_update(WINDOW * new)
{
  if (overwrite(new,Wmaster) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    return -1;
  }
 return 0;
}

int BACK_push(tView * vista)
{
  WINDOW * Waux=NULL;

  vista->wBack = NULL;

  Waux=newwin(LINES,COLS,0,0);
  wrefresh(Wmaster);
  if (overwrite(Wmaster,Waux) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    delwin(Waux);
    vista->wBack = NULL;
    return -1;
  }
  vista->wBack = Waux;
  return 0;
}

int BACK_refresh(WINDOW * new)
{
  if (overwrite(new,Wmaster) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    return -1;
  }
  return 0;
}

int BACK_refreshView(WINDOW * old)
{
  if (overwrite(Wmaster,old) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    return -1;
  }
  return 0;
}

int BACK_pop(tView * view)
{
 int ret=0;
 wrefresh(view->wBack);
 if (view->wBack != NULL)
 {
  if ((ret=overwrite(view->wBack,Wmaster)) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
  }
  delwin(view->wBack);
  view->wBack = NULL;
  wrefresh(Wmaster);
 }
 return ret;
}

WINDOW * BACK_pushWindow(WINDOW * actual)
{
 WINDOW * win;

  win=newwin(LINES,COLS,0,0);

  if (overwrite(Wmaster,win) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    delwin(win);
    return NULL; 
 }
 if (overwrite(actual,win) == ERR)
 {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
    delwin(win);
    return NULL;
 }

 return win;
}

int BACK_restoreWindow(WINDOW *origin,WINDOW * copy)
{
int ret;
  if ((ret=overwrite(copy,origin)) == ERR)
  {
    ERR_Error(ERR_OVERLAY,"Error in photo back (overlay)\n");
  }
  delwin(copy);
  copy = NULL;
  wrefresh(origin);
 return ret;
}

int BACK_popWindow(WINDOW *win)
{
 int ret=0;

 if (win == NULL) return 0;

 wrefresh(win);

 delwin(win);
 win = NULL;

 return ret;
}

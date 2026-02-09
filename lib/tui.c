#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <stdlib.h>
#include <tui.h> 

/* ==========================
 * Init the TUI library.
 * ================================== */
SCREEN * TUI_init(unsigned int useColor,unsigned int useMouse)
{
 SCREEN * auxScr;
 char * pterm;
 char * ptty;
 FILE * fd;

   setlocale(LC_ALL, "");
   pterm = getenv("TERM");
   ptty = getenv("TTY");
   if (ptty == NULL){
    if (pterm == NULL)
     auxScr=newterm("xterm",stdin,stdout);
    else
     auxScr=newterm(pterm,stdin,stdout);
   } else {
      fd= fopen(ptty,"r+");
      if (fd != NULL){
        if (pterm == NULL)
           auxScr=newterm("xterm",fd,fd);
        else
           auxScr = newterm(pterm,fd,fd);
      }
   }
   raw();
   keypad(stdscr, TRUE);
   cbreak();
   noecho();
   refresh();
   MSG_init();
   COLOR_inicializar(useColor);
   KEYS_setMouse(useMouse);
   BACK_init();
  
 return auxScr;
}

void TUI_end()
{
 endwin();
}


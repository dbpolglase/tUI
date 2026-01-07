#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <text.h>
#include <color.h>
#include <panel.h>
#include <component.h>
#include <Back.h>

int main(int argc, char * argv[])
{
int pair;
tComponent * componente;
tComponent * componente2;
tComponent * componente12;
tComponent * componente13;
tPanel *panel;
tPanel *panel2;

setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, TRUE); 
    cbreak();
    noecho();
 /*   crmode();*/
    refresh();

if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
}
  COLOR_inicializar();
  BACK_init();
  pair = COLOR_get(7,5);
/*
  printf("color %d \n", COLOR_get(1,5));
  printf("fg %d \n", COLOR_getForeground(pair));
  printf("bg %d \n", COLOR_getBackground(pair));
*/
 tDim dimension = {1,1,1,3,30};
 tChAttr color = { COLOR_get(1,4),WA_NORMAL};
 tDim dim_panel = {0,1,1,17,45};
 tChAttr color_panel = { COLOR_get(1,4),WA_NORMAL};
 tDim dim_panel2 = {0,1,1,5,79};
 tChAttr color_panel2 = { COLOR_get(2,5),WA_NORMAL};
 tDim dimension2 = {1,1,4,3,30};
 tDim dimension12 = {1,1,1,3,10};
 tDim dimension13 = {1,14,1,3,10};
 tMove moveB1 = {
   "enter",
   "out",
   "next",
   "previous",
   ":Boton3",
   ":Boton3",
   ":Boton13",
   ":Boton13",
   {"1","2","3","4","5","6","7","8","9","10","11","12"},
   " back"
   };

 tMove moveB2 = {
   "enter",
   "out",
   "next",
   "previous",
   ":Boton12",
   ":Boton13",
   ":Boton12",
   ":Boton12",
   {"1","2","3","4","5","6","7","8","9","10","11","12"},
   " back"
   };

 panel2 =PANEL_create(-1,"p2",
                      &dim_panel2,
                      &color_panel2);
 componente12 = COMPONENT_create(panel2,"Boton12",C_BUTTON,&dimension12,&color,NULL,&moveB1,&DEF_OPMOVE,NULL,NULL,NULL);

 componente13 = COMPONENT_create(panel2,"Boton13",C_BUTTON,&dimension13,&color,NULL,&moveB2,&DEF_OPMOVE,NULL,NULL,NULL);


 PANEL_addComponent(panel2, componente12);
 PANEL_addComponent(panel2, componente13);


 COMPONENT_addSimpleText(componente12,"Ab");
 COMPONENT_addSimpleText(componente13,"Bc");

 PANEL_show(panel2);
 PANEL_activate(panel2, "Boton12");

 PANEL_Action(panel2);
sleep(20);
 panel =PANEL_create(-1,"p1",
                      &dim_panel,
                      &color_panel);
 componente = COMPONENT_create(panel,"Boton2",C_BUTTON,&dimension,&color,NULL,&moveB1,&DEF_OPMOVE,NULL,NULL,NULL);

 componente2 = COMPONENT_create(panel,"Boton3",C_BUTTON,&dimension2,&color,NULL,&moveB2,&DEF_OPMOVE,NULL,NULL,NULL);
 COMPONENT_addSimpleText(componente,"AA");
 COMPONENT_addSimpleText(componente2,"BB");

 PANEL_addComponent(panel, componente);
 PANEL_addComponent(panel, componente2);
 PANEL_activate(panel, NULL);

 PANEL_show(panel);
 PANEL_Action(panel);

sleep(3);
  endwin();
  return 0;
}

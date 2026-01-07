tButton * BUTTON_create(tPanel * panel,
		       char * name,
                       tDim * dimension,
                       tChAttr * color,
                       char * text);

tButton * BUTTON_createSelect(char * name,
                       tDim * dimension,
                       tChAttr * color,
                       char ** text);

int BUTTON_show(tButton * boton);
int BUTTON_msgshow(WINDOW * win, tChAttr color, tDimPtr dim, char * text);
int BUTTON_activate(tButton * boton);
int BUTTON_deactivate(tButton * boton );
int BUTTON_changeText(tButton * boton ,char * text);
char * BUTTON_getText(tButton * boton);
char * BUTTON_getValue(tButton * boton);
int BUTTON_changeColor(tButton * boton,tChAttr * color);
  
int BUTTON_hide(tButton * boton,tChAttr *parentColor);
   
int BUTTON_move(tButton * boton ,int x, int y);

int BUTTON_resize(tButton *  boton , int alto, int ancho);

int BUTTON_changeText(tButton * boton ,char * text);

int pressButton(tButton * boton);


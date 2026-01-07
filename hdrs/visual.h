tVisual * VISUAL_createComponent(int tipo,
			WINDOW * wParent,
			tDim * dimension,
                        tChAttr * color);

int VISUAL_msgShow(WINDOW * win, tMsg * msg, char  texto[24][128]);

int VISUAL_pintaTitle(tVisual * visual, char * title);
int VISUAL_pintaTexto(tVisual * visual, tText * texto,tEDIT * edit);
int VISUAL_pintaLinea(tVisual * visual, tText * texto,tEDIT * edit);

int VISUAL_cursor(int cursor);

int VISUAL_border(WINDOW * win, int scroll);

int VISUAL_color(WINDOW * win, tChAttr * color);

int VISUAL_changeColor(tVisual * visual,tChAttr * color,tText * texto,tEDIT * edit);

int VISUAL_showComponent(tVisual * visual,tText * texto,tEDIT * edit);

int VISUAL_hideComponent(tVisual * visual,tChAttr *parentColor);
   
int VISUAL_activateComponent(tVisual * visual,tText * texto,tEDIT * edit);

int VISUAL_deactivateComponent(tVisual * visual,tText * texto,tEDIT * edit);

int VISUAL_changeTextComponent(tVisual * visual ,tText * text,tEDIT * edit);

int VISUAL_addChar(tVisual * visual,int tecla);

int VISUAL_destroy(tVisual * visual);
void VISUAL_clear(tVisual * visual);

void VISUAL_changeCheck(int check,int is_check, int no_check);
void VISUAL_changeChCheck(tComponent* component,int caracter);
void VISUAL_changeIsCheck(tComponent* component,int caracter);
void VISUAL_changeNoCheck(tComponent* component,int caracter);

int VISUAL_setXY(tVisual * visual,int linea,int column);

void VISUAL_changeBorder(chtype scroll, chtype chll, chtype chlr, chtype chlu,
                         chtype chld, chtype chlup, chtype chrup,
                         chtype chldw, chtype chrdw);



int VISUAL_pintaTableHead(tTableColumnPtr element,unsigned short vline,
			  unsigned short hline, tVisual * visual);

int VISUAL_pintaTableData(tTableColumnPtr element,tTextPtr data,
                        unsigned short vline, unsigned short hline,
                        tVisual * visual,int update);


int VISUAL_win(WINDOW * win,tChAttrPtr color);
int VISUAL_cleanWin(tVisualPtr visual);

int  VISUAL_activateTableLine(int modo,
		     tTableColumnPtr element,
                     unsigned short vline, unsigned short hline,
                     tVisual * visual,
                     char ** textLine);


int VISUAL_msgSwitchButtons(WINDOW * win, tMsgPtr msg, int button);

int VISUAL_pintaEditData(tTextPtr data, tVisual * visual);

int VISUAL_pintaInsert(tVisual * visual);
int VISUAL_pintaFileName(tVisual * visual,char * nFile);

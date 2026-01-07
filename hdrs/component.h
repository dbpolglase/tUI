

tComponent * COMPONENT_create(tPanel * panel,
			char * name, 
			char type, 
			tDim * dimension, 
			tChAttr * color, 
			tmapKeys * mapkey,
			tMove * move,
			_tFActionPanel * personalAction,
                        _tFComponent * personalFComponent);

void COMPONENT_display(tComponent * component, int display);

int COMPONENT_editMode(tComponent * component, int mode);

void COMPONENT_createEdit(tComponent * component, tEDIT * editMode);

int COMPONENT_simpleText(tComponent * component, char * text,
			unsigned short delete);

int COMPONENT_clean(tComponent * component);

int COMPONENT_delText(tComponent * component,char * texto);

int COMPONENT_setText(tComponent * component,char * text);

int COMPONENT_refresh(tComponent * component);

int COMPONENT_addText(tComponent * component,char * texto);

int COMPONENT_changeColor(tComponent * component, tChAttr * color);

int COMPONENT_show(tComponent * component);

int COMPONENT_hide(tComponent * component,tChAttr *parentColor);
   
int COMPONENT_activate(tComponent * component);

int COMPONENT_deactivate(tComponent * component);

int COMPONENT_changeText(tComponent * component ,char * text);

char * COMPONENT_getText(tComponent * component);

char * COMPONENT_getValue(tComponent * component);
int COMPONENT_setValue(tComponent * component,char * texto);
char * COMPONENT_getSelectValue(tComponent * component,int * line);
int COMPONENT_setSelectValue(tComponent * component,int line,char * texto);
int COMPONENT_isValue(tComponent * component,char * text);

trAction * COMPONENT_Action(tComponent * component,int caracter);


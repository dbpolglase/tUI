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
                      _tFEdit * personalFEdit);

int  EDIT_changeColor(tEdit * edit, tChAttr * color);

int EDIT_show(tEdit * edit);
int EDIT_refresh(tEdit * edit);

int EDIT_activate(tEdit * edit);

int EDIT_deactivate(tEdit * edit);

void EDIT_Action(tEdit * edit,tNextPtr next);

int EDIT_hide(tEdit * edit);

void EDIT_Text(tEdit * edit,tText * text);

int EDIT_loadFile(tEdit * edit,char * fileName,int maxData, int iniLines);
int EDIT_saveFile(tEdit * edit);
int EDIT_saveFile();

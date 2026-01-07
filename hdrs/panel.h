tView * PANEL_create(int id,
		      char * name,
		      unsigned short level,
		      char * title,
                      tDim * dimension,
                      tChAttr * color,
		      unsigned short opToMade,
                      tMove * move,
                      _tFActionPanel * personalAction,
                      _tFPanel * personalFPanel);

tPanel * PANEL_getActivePanel();

char * PANEL_searchXYComponent(tPanelPtr panel,int x,int y);

int PANEL_addComponent(tPanel * panel,
                       tComponent * componente);

int PANEL_delComponent(tPanel * panel,
		       short id,
		       char * name);

tComponent * PANEL_searchComponent(tPanel * panel,
		       char * name);

int  PANEL_changeDim(tPanel * panel,
                  tDim * dimension);

int  PANEL_changeColor(tPanel * panel,
                  tChAttr * color);

int PANEL_show(tPanel * panel);

int PANEL_refresh(tPanel * panel);

int PANEL_opToMade(tPanel * panel);

int PANEL_hide(tPanel * panel);

int PANEL_destroy(tPanel * panel);

int PANEL_activate(tPanel * panel,char * ncomponent);

void PANEL_Action(tPanel * panel,tNextPtr next);

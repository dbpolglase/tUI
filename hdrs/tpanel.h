
tPanel * PANEL_create(char * name,
                      tDim * dimension,
                      tChAttr * color);

int PANEL_addComponent(tPanel * panel,
                       unsigned short type,
                       union uComponent componente);

int PANEL_delComponent(tPanel * panel,
                       short id,
                       char * name);

tComponent * PANEL_searchComponent(tPanel * panel,
                       short id,
                       char * name);

int  PANEL_changeDim(tPanel * panel,
                  tDim * dimension);

int  PANEL_changeColor(tPanel * panel,
                  tChAttr * color);

int  PANEL_show(tPanel * panel);
int  PANEL_hide(tPanel * panel);


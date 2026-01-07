
tView * TABLE_create(int id,
                      char * name,
                      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * colorHead,
                      tChAttr * colorData,
                      unsigned short opToMade,
                      unsigned short head,
                      unsigned short vline,
                      unsigned short hline,
                      tmapKeys * mapkey,
                      tMove * move,
                      _tFActionTable * personalAction,
                      _tFTable * personalFTable);

int TABLE_refresh(tTable * table);
void TABLE_text(tTable * table, tText * text);

int TABLE_addColumn(tTable * table,
                    char * title, unsigned int len);

int  TABLE_changeColor(tTable * table,
                  tChAttr * colorHead,
                  tChAttr * colorData);

int TABLE_show(tTable * table);

int TABLE_activate(tTable * table);

int TABLE_deactivateLine(tTable * table);

void TABLE_Action(tTable * table,tNextPtr next);

int TABLE_hide(tTable * table);

int TABLE_opToMade(tTable * table);

int TABLE_setColumnHead(tTable * table, int column,char * data);

char ** TABLE_getValue(tTable * table);
char * TABLE_getColumnValue(tTable * table,int column);
char ** TABLE_getText(tTable * table);
char * TABLE_getTextValue(tTable * table,int column);

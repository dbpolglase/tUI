void * LVIEW_getElement(char * nView, char * nComponent);

tView * LVIEW_searchView(char * name);

void LVIEW_addView(tView * vista);

void LVIEW_delView(void * view);

char * LVIEW_searchXYView(int x, int y);

tCaller * LVIEW_getCaller();
int LVIEW_refresh(char * name);
void LVIEW_testView();
void LVIEW_clean(char * antCaller,tViewPtr antView,tViewPtr newView);


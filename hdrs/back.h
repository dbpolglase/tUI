int BACK_init();

int BACK_push(tView * view);
WINDOW *  BACK_pushWindow(WINDOW * actual);

int BACK_pop(tView * view);
int BACK_popWindow(WINDOW * view);

int BACK_update(WINDOW * new);

int BACK_restoreWindow(WINDOW *origin,WINDOW * copy);

int BACK_refresh(WINDOW * new);

int BACK_refreshView(WINDOW * old);



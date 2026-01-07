#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/stat.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <color.h>
#include <msg.h>
#include <text.h>
#include <edit.h>
#include <table.h>
#include <panel.h>
#include <visual.h>
#include <lview.h>
#include <component.h>

#include <tparser.h>
#include <tkeymap.h>
#include <tedf.h>
#include <tproyect.h>
#include <tcolor.h>
#include <tview.h>
#include <tcomp.h>
#include <tmsg.h>
#include <ttest.h>

extern SCREEN * scrSTD;

typedef struct isShow{
   int tipo;
   WINDOW * ventana;
   struct isShow * siguiente;
   tView  * vista;
}tisShow;

#define T_COLOR  0
#define T_KEYMAP 1
#define T_VIEW   2

#define K_ENTER    " Enter Key    "
#define K_OUT      " Out Key      "
#define K_NEXT     " Next Key     "
#define K_PREVIOUS " Previous Key "
#define K_UP       " Up Key       "
#define K_DOWN     " Down Key     "
#define K_LEFT     " Left Key     "
#define K_RIGHT    " Right Key    "
#define K_BACK     " Back Key     "
#define K_OTHER    " Other Key    "
#define K_NO       " NO MAP Key   "

static tisShow * cabIsShow=NULL;
static tisShow * ultIsShow=NULL;
static void TEST_add(unsigned int tipo,WINDOW * ventana,tView * vista);
static void TEST_del();
static int TEST_count(unsigned int tipo);

static int TEST_count(unsigned int tipo){
tisShow * aux;
int cuenta=0;

  aux=cabIsShow;
  while (aux != NULL){
    if (aux->tipo == tipo) cuenta++;
    aux = aux->siguiente;
  }
  return cuenta;
}


static void TEST_add(unsigned int tipo,WINDOW * ventana,tView * vista){
  tisShow * aux;
 
  aux = (tisShow *) malloc (sizeof(tisShow));
  aux->tipo=tipo;
  aux->ventana=ventana;
  aux->vista=vista;
  aux->siguiente = NULL;
  
  if (cabIsShow == NULL) {
    cabIsShow = ultIsShow = aux;
  }
  else {
   ultIsShow->siguiente = aux;
   ultIsShow =aux;
  }
}

static void TEST_del() {
 tisShow * aux;
 tlComponent * panelElems;

  aux = cabIsShow;
  while (aux != NULL) {
    switch (aux->tipo){
      case T_COLOR:  werase(aux->ventana);
		     break;
      case T_KEYMAP: werase(aux->ventana);
		     break;
      case T_VIEW:  
		switch (aux->vista->type)
                {
 		  case V_Panel: 
                     panelElems=aux->vista->view.panel->elements;
                     while (panelElems != NULL){
		       werase(panelElems->componente->visual->win);
                       TEXT_free(panelElems->componente->text);
                       free(panelElems->componente);
                       panelElems = panelElems->siguiente;
                     }
		     werase(aux->vista->view.panel->visual->win);
		     break;
 		  case V_Edit: 
		     werase(aux->vista->view.edit->vData->win);
		     if (aux->vista->view.edit->vHead!=NULL)
		      werase(aux->vista->view.edit->vHead->win);
		     break;
 		  case V_Table: 
                     werase(aux->vista->view.table->vData->win);
                     if (aux->vista->view.table->vHead != NULL)
                       werase(aux->vista->view.table->vHead->win);
                     werase(aux->vista->view.table->vTable->win);
                  default:
		     break;
                }
      default:	     break;
    }
    cabIsShow = aux->siguiente;
    aux = cabIsShow;
  }
  cabIsShow = ultIsShow = NULL;
  clear();
  refresh();
}

trAction* TEST_color(tComponent * component,int key){
static trAction action;

SCREEN * scrTest;
WINDOW * win;
tComponent * auxC;
int bcolor=0,fcolor=0,colorpair,attr=0;
int y=0;

 initAction(action);

 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }

 set_term(scrTest);
 if (cabIsShow == NULL) {
  setlocale(LC_ALL, "");
  raw();
  cbreak();
  noecho();
 }

 COLOR_inicializar(1);
 y = TEST_count(T_KEYMAP) + TEST_count(T_COLOR);
 win = newwin(1,70,y,1);
 if (win == NULL)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Error in curses win ");
  set_term(scrSTD);
  action.error=1;
  return &action;
 }

 auxC = (tComponent *)LVIEW_getElement("frmColor","frmCbcolor");
 if (auxC != NULL) {
  bcolor =COMPONENT_getValue(auxC)[0]-'0';
 }
 auxC = (tComponent *)LVIEW_getElement("frmColor","frmCfcolor");
 if (auxC != NULL) {
  fcolor =COMPONENT_getValue(auxC)[0]-'0';
 }
 colorpair=COLOR_get(bcolor,fcolor);

 auxC = (tComponent *)LVIEW_getElement("frmColor","frmCtext");
 if (auxC != NULL)
  attr=COLOR_tipoChTexto(COMPONENT_getValue(auxC));

 if (wbkgd(win,COLOR_PAIR(colorpair)|attr) != OK)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Error in curses");
  set_term(scrSTD);
  action.error=1;
  return &action;
 }

 wprintw(win,"COLOR ");
 auxC = (tComponent *)LVIEW_getElement("frmColor","frmCname");
 wprintw(win,"%s",COMPONENT_getValue(auxC));

 wrefresh(win);

 set_term(scrSTD);

 if (MSG_create(M_WARNING,CENTER_TERMINAL,"Clean Test Terminal ? ") == 0) {
    set_term(scrTest);
    werase(win);
    TEST_del();
    clear();
    set_term(scrSTD);
 }
 else {
  TEST_add(T_COLOR,win,NULL);
 }

 return &action;
}

trAction* TEST_keymap(tComponent * component,int key){
static trAction action;
SCREEN * scrTest;
WINDOW * win;
tComponent * auxC;
int y=0;
int found=0;
int i;
int ch;
char * stecla;
tXmlMapKey * auxKeymap;
char * nKeymap;

 initAction(action);

 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }


 auxC = (tComponent *)LVIEW_getElement("frmkeymap","nkeymap");
 nKeymap = COMPONENT_getValue(auxC);

 auxKeymap =  KEYM_search(nKeymap);
 if (auxKeymap == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Save %s Keymap before test",nKeymap);
  action.error=1;
  return &action;
 }

 MSG_create(M_INFO,CENTER_VIEW,"To continue end the test in the test terminal");

 set_term(scrTest);
 if (cabIsShow == NULL) {
  setlocale(LC_ALL, "");
  raw();
  cbreak();
  noecho();

 }

 y = TEST_count(T_KEYMAP) + TEST_count(T_COLOR);
 win = newwin(1,70,y,1);
 if (win == NULL)
 {
  MSG_create(M_ERROR,CENTER_VIEW,"Error in curses win ");
  set_term(scrSTD);
  action.error=1;
  return &action;
 }
 keypad(win, TRUE);

 wprintw(win,"PRESS MAPKEYS . TO FINISH TEST: ");
 do {
   found = 0;
   ch = wgetch(win);
   if (ch == '.') break;
   wmove(win,y,40);
   for (i=0;i!= MAX_KEYS_FUNC&&!found;i++){
    if (auxKeymap->mapa.enter[i] == ch){
	found=1; stecla=K_ENTER; }
    if (auxKeymap->mapa.out[i] == ch){
	found=1; stecla=K_OUT; }
    if (auxKeymap->mapa.next[i] == ch){
	found=1; stecla=K_NEXT; }
    if (auxKeymap->mapa.previous[i] == ch){
	found=1; stecla=K_PREVIOUS; }
    if (auxKeymap->mapa.up[i] == ch){
	found=1; stecla=K_UP; }
    if (auxKeymap->mapa.down[i] == ch){
	found=1; stecla=K_DOWN; }
    if (auxKeymap->mapa.left[i] == ch){
	found=1; stecla=K_LEFT; }
    if (auxKeymap->mapa.right[i] == ch){
	found=1; stecla=K_RIGHT; }
    if (auxKeymap->mapa.back[i] == ch){
	found=1; stecla=K_BACK; }
  }
  if (!found) stecla=K_NO;
  wprintw(win,"%s",stecla);
 } while (ch != '.');

 wrefresh(win);
 werase(win);
 refresh();

 set_term(scrSTD);

 return &action;
}


trAction* TEST_msg(tComponent * component,int key){
static trAction action;
SCREEN * scrTest;
tXmlMsg * auxMsg;
tXmlcolorPtr auxColor;
tChAttr auxChColor;
extern tChAttr noColor;

 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }

 auxMsg=MSG_getEditActual();
 if (auxMsg == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Save Before Test ");
  action.error=1;
  return &action;
 }
 auxColor=COLOR_searchColor(auxMsg->color);
 if (auxColor != NULL && strcmp(auxColor->name,"noColor") != 0){ 
  auxChColor.attr=auxColor->attr; 
  auxChColor.colorpair=COLOR_get(auxColor->bcolor,auxColor->fcolor);
  MSG_borderColor(auxMsg->type,1,&auxChColor);
 }
 else
  MSG_borderColor(auxMsg->type,1,&noColor);

 MSG_saveView(auxMsg->type);
 MSG_txtButton(auxMsg->type,
                   auxMsg->title,
                   auxMsg->nroButtons,
                   auxMsg->ButtonText1,auxMsg->ButtonText2);

 MSG_create(M_INFO,CENTER_VIEW,"End the test to continue ");

 set_term(scrTest);
 COLOR_inicializar(1);
 MSG_create(auxMsg->type,CENTER_TERMINAL," TEST OF MSG ");
 clear();
 refresh();
 set_term(scrSTD);
 MSG_restoreView(auxMsg->type);

 return &action;
}

trAction* TEST_edit(tComponent * component,int key){
static trAction action;

SCREEN * scrTest;
tComponent * auxC;
char * nEdit;
tXmlEditPtr auxEdit;
tView * auxView;
tChAttr auxChColor;
extern tChAttr noColor;
tXmlcolorPtr auxColor;

 initAction(action);


 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }

 auxC = (tComponent *)LVIEW_getElement("fnedit","fnenombre");
 nEdit = COMPONENT_getValue(auxC);
 if (nEdit == NULL || strcmp(nEdit,"")==0) {
  MSG_create(M_ERROR,CENTER_VIEW,"Edit name require ");
  action.error=1;
  return &action;
 }

 auxEdit = VIEW_searchEdit(nEdit);
 if (auxEdit == NULL) {
  MSG_create(M_ERROR,CENTER_VIEW,"Save/Create view before test ");
  action.error=1;
  return &action;
 }

 auxColor=COLOR_searchColor(auxEdit->visual.color);
 set_term(scrTest);
 COLOR_inicializar(1);
 LVIEW_testView();
 if (auxColor != NULL && strcmp(auxEdit->visual.color,"noColor") != 0){ 
  auxChColor.attr=auxColor->attr; 
  auxChColor.colorpair=COLOR_get(auxColor->bcolor,auxColor->fcolor);
  auxView=EDIT_create(-1,nEdit,0, auxEdit->title,
                      &auxEdit->visual.dimension,
                      &auxChColor,
                      OP_NONE,
                      auxEdit->visual.eMode,
                      NULL, NULL, NULL, NULL);
 }
 else {
  auxView=EDIT_create(-1,nEdit,0, auxEdit->title,
                      &auxEdit->visual.dimension,
                      &noColor,
                      OP_NONE,
                      auxEdit->visual.eMode,
                      NULL, NULL, NULL, NULL);
 }
 if (cabIsShow == NULL) {
   setlocale(LC_ALL, "");
   raw();
   cbreak();
   noecho();
 }
 EDIT_show(auxView->view.edit);
 set_term(scrSTD);

 TEST_add(T_VIEW,NULL,auxView);
 if (MSG_create(M_WARNING,CENTER_TERMINAL,"Clean Test Terminal ? ") == 0) {
    set_term(scrTest);
    TEST_del();
    clear();
    set_term(scrSTD);
 }

  return &action;
}

trAction* TEST_table(tComponent * component,int key){
static trAction action;

SCREEN * scrTest;
tComponent * auxC;
char * nTable;
tXmlTablePtr auxTable;
tView * auxView;
tChAttr auxChColor,auxDChColor;
extern tChAttr noColor;
tXmlcolorPtr auxColor,auxDColor;
tXmlElemsTable  * auxElems;

 initAction(action);


 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }

 auxC = (tComponent *)LVIEW_getElement("fntable","fntnombre");
 nTable = COMPONENT_getValue(auxC);
 if (nTable == NULL || strcmp(nTable,"")==0) {
  MSG_create(M_ERROR,CENTER_VIEW,"Table name require ");
  action.error=1;
  return &action;
 }

 auxTable = VIEW_searchTable(nTable);
 if (auxTable == NULL) {
  MSG_create(M_ERROR,CENTER_VIEW,"Save/Create view before test ");
  action.error=1;
  return &action;
 }

 auxColor=COLOR_searchColor(auxTable->visual.color);
 auxDColor=COLOR_searchColor(auxTable->visual.colorData);

 set_term(scrTest);
 COLOR_inicializar(1);
 if (auxColor != NULL){ 
  auxChColor.attr=auxColor->attr; 
  auxChColor.colorpair=COLOR_get(auxColor->bcolor,auxColor->fcolor);
 }
 if (auxDColor != NULL){ 
  auxDChColor.attr=auxDColor->attr; 
  auxDChColor.colorpair=COLOR_get(auxDColor->bcolor,auxDColor->fcolor);
 }

 LVIEW_testView();
 auxView= TABLE_create(-1, nTable, 0, auxTable->title,
                      &auxTable->visual.dimension,
                      ((auxColor==NULL)?&noColor:&auxChColor), 
                      ((auxDColor==NULL)?&noColor:&auxDChColor), 
                      OP_NONE,
                      auxTable->visual.thead,
                      auxTable->visual.vline,
                      auxTable->visual.hline,
                      NULL, NULL, NULL, NULL);

   auxElems = auxTable->elements;
   while (auxElems != NULL) {
    TABLE_addColumn(auxView->view.table,
                    auxElems->title,auxElems->len);
    auxElems=auxElems->siguiente;
   }

  if (cabIsShow == NULL) {
   setlocale(LC_ALL, "");
   raw();
   cbreak();
   noecho();
  }
  TABLE_show(auxView->view.table);
  set_term(scrSTD);

  TEST_add(T_VIEW,NULL,auxView);
  if (MSG_create(M_WARNING,CENTER_TERMINAL,"Clean Test Terminal ? ") == 0) {
    set_term(scrTest);
    TEST_del();
    clear();
    set_term(scrSTD);
 }

  return &action;
}

trAction* TEST_panel(tComponent * component,int key){
static trAction action;

SCREEN * scrTest;
tComponent * auxC;
char * nPanel;
tXmlPanelPtr auxPanel;
tView * auxView;
tChAttr auxChColor;
extern tChAttr noColor;
tXmlcolorPtr auxColor;
tXmlCompPanel * auxElemns;
tXmlComponent * auxComp;
tComponent * auxNComp;
tXmlText * texto;

 initAction(action);


 if ((scrTest = PROY_testScreen()) == NULL){
  MSG_create(M_ERROR,CENTER_VIEW,"Must Indicate the Test Terminal (project->t.test)");
  action.error=1;
  return &action;
 }

 auxC = (tComponent *)LVIEW_getElement("fnpanel","fnpnombre");
 nPanel = COMPONENT_getValue(auxC);
 if (nPanel == NULL || strcmp(nPanel,"")==0) {
  MSG_create(M_ERROR,CENTER_VIEW,"Panel name require ");
  action.error=1;
  return &action;
 }

 auxPanel = VIEW_searchPanel(nPanel);
 if (auxPanel == NULL) {
  MSG_create(M_ERROR,CENTER_VIEW,"Save/Create view before test ");
  action.error=1;
  return &action;
 }

 auxColor=COLOR_searchColor(auxPanel->visual.color);

 set_term(scrTest);
 COLOR_inicializar(1);
 if (auxColor != NULL){ 
  auxChColor.attr=auxColor->attr; 
  auxChColor.colorpair=COLOR_get(auxColor->bcolor,auxColor->fcolor);
 }

 LVIEW_testView();
 auxView = PANEL_create(-1,
                      nPanel,
                      0,
                      auxPanel->title,
                      &auxPanel->visual.dimension,
                      ((auxColor==NULL)?&noColor:&auxChColor), 
                      OP_NONE,
                      NULL,NULL,NULL);

  auxElemns = auxPanel->elements;

  while (auxElemns != NULL) {
    auxComp = auxElemns->componente;
    auxColor=COLOR_searchColor(auxComp->visual.color);
    if (auxColor != NULL){ 
      auxChColor.attr=auxColor->attr; 
      auxChColor.colorpair=COLOR_get(auxColor->bcolor,auxColor->fcolor);
    }

    
    auxNComp= COMPONENT_create(auxView->view.panel,
                        auxComp->name,
                        auxComp->type,
                        &auxComp->visual.dimension,
                        ((auxColor==NULL)?&noColor:&auxChColor), 
                        NULL, NULL, NULL, NULL);

    if (auxComp->visual.visible != DIS_NORMAL)
        COMPONENT_display(auxNComp,auxComp->visual.visible);


    if (auxNComp->type == C_LSBUTTON || auxNComp->type == C_EDIT){
        auxNComp->text=TEXT_new(RESIZE,1,80,auxNComp->visual->dimension.alto,1);
    }

    if (auxComp->visual.isCheck){
        auxNComp->visual->status.defCheck=1;
    }

    if (auxComp->visual.chCheck !=0 && auxComp->visual.chCheck != CH_CHECK)
        VISUAL_changeChCheck(auxNComp,auxComp->visual.chCheck);

    if (auxComp->visual.chIsCheck !=0 && auxComp->visual.chIsCheck != CH_IS_CHECK)
        VISUAL_changeIsCheck(auxNComp,auxComp->visual.chIsCheck);
    if (auxComp->visual.chNoCheck !=0 && auxComp->visual.chNoCheck != CH_NO_CHECK)
        VISUAL_changeNoCheck(auxNComp,auxComp->visual.chNoCheck);


    texto = auxComp->text;
    if (texto == NULL) COMPONENT_simpleText(auxNComp,"",0);
    else {
    while (texto != NULL) {
     COMPONENT_simpleText(auxNComp,texto->texto,0);
     texto = texto->siguiente;
    }
    }

    PANEL_addComponent(auxView->view.panel, auxNComp);

    auxElemns=auxElemns->siguiente;
  }

  if (cabIsShow == NULL) {
   setlocale(LC_ALL, "");
   raw();
   cbreak();
   noecho();
  }
  PANEL_show(auxView->view.panel);
  set_term(scrSTD);

  TEST_add(T_VIEW,NULL,auxView);
  if (MSG_create(M_WARNING,CENTER_TERMINAL,"Clean Test Terminal ? ") == 0) {
    set_term(scrTest);
    TEST_del();
    clear();
    set_term(scrSTD);
 }

  return &action;
}

#ifndef __TPARSER
#define __TPARSER

#include <tBasic.h>

enum E_TIPOF {
  F_INIT,
  F_END,
  F_EDF,
  F_MOV_COMP,
  F_MOV_COMP_Fn,
  F_MOV_TABLE,
  F_MOV_TABLE_Fn,
  F_MOV_EDIT,
  F_MOV_EDIT_Fn,
  F_CRE_APP_PANEL,
  F_APP_PANEL,
  F_CRE_APP_COMP,
  F_APP_COMP,
  F_CRE_APP_TABLE,
  F_APP_TABLE,
  F_CRE_APP_EDIT,
  F_APP_EDIT,
};

typedef struct tuifunciones{
  enum E_TIPOF tipo;
  char name[MAX_FUNC_NAME];
  unsigned short nroUses;
  struct tuifunciones * siguiente;
  struct tuifunciones * anterior;
}tXmlFunciones,* tXmlFuncionesPtr;

typedef struct {
  unsigned short useMouse;
  unsigned short useColor;
  unsigned short printErrors;
  char ferrors[MAX_NAME_FILE];
  unsigned short chCheck;
  unsigned short chIsCheck;
  unsigned short chNoCheck;
  unsigned int borders[8];
  unsigned int sborders[8];
  char mainFunction[MAX_FUNC_NAME];
  char endFunction[MAX_FUNC_NAME];
  char initView[MAX_NAME_VIEW+MAX_COMPONENT_NAME];
} tXmlProp,* tXmlPropPtr;

#define MAX_NOM_PROYECT 40
#define MAX_DESCRIPCION 100

typedef struct {
   char name[MAX_NOM_PROYECT];
   char description[MAX_DESCRIPCION];
   char fileName[MAX_NAME_FILE]; 
   FILE * fd; 
   int exist;
}tXmlProyect,* tXmlProyectPtr;

#define MAX_N_COLOR  50

typedef struct tuicolor{
 char name[MAX_N_COLOR];
 unsigned int fcolor;
 unsigned int bcolor;
 unsigned int attr;
 struct tuicolor * siguiente;
 struct tuicolor * anterior;
} tXmlcolor, * tXmlcolorPtr;


typedef struct txmledFunction{
 char name[MAX_FUNC_NAME];
 unsigned short tipo;
 unsigned short align;
 unsigned short insert;
 struct txmledFunction * siguiente;
 struct txmledFunction * anterior;
} tXmlCEdFunction, * tXmlCEdFunctionPtr;

typedef struct txmlMapKey{
  char name[MAX_FUNC_NAME];
  tmapKeys  mapa;
  struct txmlMapKey * siguiente;
  struct txmlMapKey * anterior;
}tXmlMapKey,* tXmlMapKeyPtr;

typedef struct {
   enum CMsg type;
   char title[MAX_MSG_TITLE];
   unsigned short nroButtons;
   char ButtonText1[MAX_TEXT_BUTTON];
   char ButtonText2[MAX_TEXT_BUTTON];
   char color[MAX_N_COLOR];
} tXmlMsg, * tXmlMsgPtr;

typedef struct {
   tXmlMsgPtr msg[3];
} tXmlMsgs;

typedef struct {
   unsigned short scroll;
   char color[MAX_N_COLOR];
   char colorData[MAX_N_COLOR];
   tDim dimension;
   unsigned short visible;
   unsigned short isCheck;
   unsigned short chCheck;
   unsigned short chIsCheck;
   unsigned short chNoCheck;
   unsigned short vline;
   unsigned short hline;
   unsigned short thead;
   enum EMode eMode;
} tXmlVisual,*tXmlVisualPtr;

typedef struct {
   char  pre_create[MAX_FUNC_NAME];
   char  post_create[MAX_FUNC_NAME];
   char  pre_show[MAX_FUNC_NAME];
   char  post_show[MAX_FUNC_NAME];
   char  pre_hide[MAX_FUNC_NAME];
   char  post_hide[MAX_FUNC_NAME];
   char  pre_destroy[MAX_FUNC_NAME];
   char  post_destroy[MAX_FUNC_NAME];
   char  pre_activate[MAX_FUNC_NAME];
   char  post_activate[MAX_FUNC_NAME];
   char  pre_deactivate[MAX_FUNC_NAME];
   char  post_deactivate[MAX_FUNC_NAME];
}tXmlFApplication;

typedef struct {
   char enter[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char out[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char next[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char previous[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char up[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char down[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char left[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char right[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char Fn[MAX_Fn_KEYS][MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char back[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
   char other[MAX_NAME_VIEW+MAX_COMPONENT_NAME+1];
}tXmlMove, * tXmlMovePtr;


typedef struct tuitext{
  char * texto;
  struct tuitext * siguiente;
  struct tuitext * anterior;
}tXmlText,* tXmlTextPtr;

typedef struct {
   unsigned short secret;
   int chToEDIT;
   char editFunction[MAX_FUNC_NAME];
   int editType;
   unsigned short autoComplet;
} tXmlEDIT, * tXmlEDITPtr;

typedef struct tuicomponent{
   int id;
   char name[MAX_COMPONENT_NAME];
   char panelName[MAX_NAME_VIEW];
   enum CComponents type;
   void *  panel;
   tXmlVisual visual;
   tXmlTextPtr text;
   tXmlEDIT editMode;
   char mapkey[MAX_FUNC_NAME];
   tXmlMove move;
   tXmlMove personalAction;
   tXmlFApplication personalFComponent;
   struct tuicomponent * siguiente;
   struct tuicomponent * anterior;
}tXmlComponent,*tXmlComponentPtr;

typedef struct tuiCompPanel{
  tXmlComponent * componente;
  struct tuiCompPanel * siguiente;
}tXmlCompPanel,*tXmlCompPanelPtr;

typedef struct tuipanel{
   int id;
   unsigned short level;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade;
   char title[MAX_VIEW_TITLE];
   tXmlVisual visual;
   tXmlMove move;
   tXmlMove personalAction;
   tXmlFApplication personalFPanel;
   tXmlCompPanel * elements;
   struct tuipanel * siguiente;
   struct tuipanel * anterior;
} tXmlPanel, * tXmlPanelPtr;


typedef struct tuiEleTable{
   char title[MAX_VIEW_TITLE];
   unsigned short len;
   struct tuiEleTable * siguiente;
}tXmlElemsTable,*tXmlElemsTablePtr;

typedef struct tuitable{
   int id;
   unsigned short level;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade;
   char title[MAX_VIEW_TITLE];
   char mapkey[MAX_FUNC_NAME];
   tXmlVisual visual;
   tXmlMove move;
   tXmlMove personalAction;
   tXmlFApplication personalFTable;
   tXmlElemsTable  * elements;
   struct tuitable * siguiente;
   struct tuitable * anterior;
} tXmlTable, * tXmlTablePtr;

typedef struct tuiedit{
   int id;
   unsigned short level;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade;
   char title[MAX_VIEW_TITLE];
   char fileName[MAX_NAME_FILE]; 
   char mapkey[MAX_FUNC_NAME];
   tXmlVisual visual;
   tXmlMove move;
   tXmlMove personalAction;
   tXmlFApplication personalFEdit;
   struct tuiedit * siguiente;
   struct tuiedit * anterior;
} tXmlEdit, * tXmlEditPtr;


int PARSER_loadXmlFile(char * fileName,int unescape);

tXmlProyect * PARSER_getProyect();
tXmlProp * PARSER_getProperties();
tXmlcolor * PARSER_getCabColors();
tXmlcolor * PARSER_getUltColors();
tXmlCEdFunctionPtr PARSER_getCabCEdFunctions();
tXmlCEdFunctionPtr PARSER_getUltCEdFunctions();
tXmlMapKeyPtr PARSER_getCabKeymaps();
tXmlMapKeyPtr PARSER_getUltKeymaps();
tXmlMsgs  PARSER_getMsgs();
tXmlFuncionesPtr PARSER_getCabFunciones();
tXmlFuncionesPtr PARSER_getUltFunciones();
tXmlPanelPtr PARSER_getCabPanels();
tXmlPanelPtr PARSER_getUltPanels();
tXmlTablePtr PARSER_getCabTables();
tXmlTablePtr PARSER_getUltTables();
tXmlEditPtr PARSER_getCabEdits();
tXmlEditPtr PARSER_getUltEdits();
tXmlComponentPtr PARSER_getCabComponents();
tXmlComponentPtr PARSER_getUltComponents();
int PARSER_decodeOp(char * x);


#endif /* TPARSER */

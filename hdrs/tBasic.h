#ifndef __TBASIC
#define __TBASIC

#include <ncurses.h>


#define NO_RESIZE 0
#define RESIZE 1


#define CH_CHECK '?'
#define CH_NO_CHECK '_'
#define CH_IS_CHECK 'X'

#define EBUTTON 1

#define MAX_NAME_VIEW 50
#define MAX_COMPONENT_NAME 50
#define MAX_TEXT_AUX 200
#define MAX_EDIT_LINE 300
#define MAX_TEXTO_BOTON  100
#define MAX_Fn_KEYS  12
#define MAX_KEYS_FUNC 3
#define MAX_MOVE 10
#define MAX_VIEW_TITLE 100
#define MAX_NAME_FILE 300

#define MAX_FUNC_NAME   50
#define MAX_NOM_MAP_KEY 50
#define NOM_STD_BUTTON "STD_BUTTON"
#define NOM_STD_EDIT "STD_EDIT"
#define NOM_STD_LABEL "STD_LABEL"
#define NOM_STD_TABLE "STD_TABLE"
#define NOM_STD_COMPONENT "STD_COMPONENT"
#define MAX_T_COLUMN  128

#define CHAR_TO_EDIT  '.'

#define DEF_LUP '+'
#define DEF_LUP_SCR '+'
#define DEF_LDW '+'
#define DEF_LDW_SCR '+'
#define DEF_RUP '+'
#define DEF_RUP_SCR '^'
#define DEF_RDW '+'
#define DEF_RDW_SCR 'v'
#define DEF_LL '|'
#define DEF_LL_SCR  '|'
#define DEF_LR '|'
#define DEF_LR_SCR '#'
#define DEF_LU '-'
#define DEF_LU_SCR '-'
#define DEF_LD '-'
#define DEF_LD_SCR '-'

enum CComponents{
C_LABEL,
C_BUTTON,
C_CKBUTTON,
C_LSBUTTON,
C_EDIT
};

enum EDisplay{
DIS_NORMAL,
DIS_HIDDEN,
DIS_NO_SELECT,
DIS_OPEN 
};

enum Ops{
OP_NONE,
OP_HIDE,
OP_DESTROY,
OP_SHOW,
OP_CREATE, 
OP_ACT,
OP_DEACT
};

enum Actions {
   A_enter,
   A_out,
   A_next,
   A_previous,
   A_up,
   A_down,
   A_left,
   A_right,
   A_Fn,
   A_back,
   A_home,
   A_end,
   A_ic
};

enum CViews {
V_Panel,
V_Table,
V_Edit
};

enum EMode {
 R_ONLY,
 RW
};

enum TMode {
 Fixed,
 Dynamic
};

enum EInsert {
 Insert,
 Replace,
 ReadOnly
};

enum EFormula{
  Line,
  Column,
  Any
};

enum EAlign{
  A_Left,
  A_Right
};


typedef struct {
  char *** text;
  enum TMode mode;
  FILE * fd;
  unsigned short delete;
  unsigned short resize;
  unsigned short maxColumns;
  unsigned short maxLines;
  unsigned short maxFields;
  unsigned short nroColumns;
  unsigned short nroLines;
  unsigned short nroFields;
  unsigned short actColumn;
  unsigned short actLine;
  unsigned short actField;
  unsigned short check;
}tText,*tTextPtr;

typedef struct miFormula{
  enum EFormula tipoFormula;
  int fila;
  int columna;
  char * valor;
  struct miFormula * siguiente;
} tLFormulas, * tLFormulasPtr;

typedef struct Formula{
  tLFormulas * forLine;
  tLFormulas * forColumn;
  tLFormulas * forAny;
}tFormula,*tFormulaPtr;

typedef struct {
   int colorpair;
   int   attr;
}tChAttr,*tChAttrPtr;

typedef struct {
   unsigned short border;
   unsigned short x;
   unsigned short y;
   unsigned short alto;
   unsigned short ancho;
} tDim,*tDimPtr;

typedef struct {
   unsigned short x;
   unsigned short y;
} tCursor,*tCursorPtr; 

typedef struct {
   enum EAlign align;
   enum EDisplay visible;
   unsigned short ckCheck;
   unsigned short ckIsCheck;
   unsigned short ckNoCheck;
   unsigned short defCheck;
   unsigned short activa;
   enum EInsert   insert;
   unsigned short multiLine;
   unsigned short actField;
   unsigned short actLine;
   unsigned short actColumn;
   unsigned short nactFields;
   unsigned short nactLines;
   unsigned short nactColumns;
} tStatus,*tStatusPtr;



enum EditType{
E_NONE,
E_NUMERIC,
E_ALFNUMERIC,
E_7ASCII,
E_UPPER,
E_LOWER,
E_RESER1,
E_RESER2,
E_RESER3,
E_RESER4,
E_RESER5,
E_RESER6,
E_RESER7,
E_RESER8,
E_RESER9,
E_PERSONAL
};

typedef struct feditCheck{
  enum EditType tipo;
  enum EAlign  align;
  enum EInsert insert;
  int (*checkEdit)(int * caracter);
  struct feditCheck * siguiente;
} tfeditCheck, * tfeditCheckPtr;

typedef struct {
   unsigned short secret;
   int chToEDIT;
   int editType;
   unsigned short autoComplet;
} tEDIT, * tEDITPtr;

typedef struct {
   WINDOW * win;
   WINDOW * wBack;
   unsigned short scroll;
   tChAttr color;
   tDim dimension;
   tCursor cursor;
   tStatus status;
} tVisual,*tVisualPtr;

typedef struct {
   char * enter;
   char * out;
   char * next;
   char * previous;
   char * up;
   char * down;
   char * left;
   char * right;
   char * Fn[MAX_Fn_KEYS];
   char * back;
   char * other;
} tMove, *tMovePtr;

typedef struct {
   int enter[MAX_KEYS_FUNC];
   int out[MAX_KEYS_FUNC];
   int next[MAX_KEYS_FUNC];
   int previous[MAX_KEYS_FUNC];
   int up[MAX_KEYS_FUNC];
   int down[MAX_KEYS_FUNC];
   int left[MAX_KEYS_FUNC];
   int right[MAX_KEYS_FUNC];
   int Fn[MAX_Fn_KEYS][MAX_KEYS_FUNC];
   int back[MAX_KEYS_FUNC];
} tmapKeys, * tmapKeysPtr;

typedef struct {
  unsigned short error;
  unsigned short made;
  unsigned short opToMade; 
  char * componentNext;
}trAction, * trActionPtr;

#define initAction(x) {x.error=0;x.made=0;x.opToMade=OP_NONE;x.componentNext=NULL;}

typedef struct _tFActionPanel tFActionPanel;
typedef struct _tFActionTable tFActionTable;
typedef struct _tFActionEdit tFActionEdit;
typedef struct _tFPanel tFPanel;
typedef struct _tFTable tFTable;
typedef struct _tFEdit tFEdit;
typedef struct _tFCalc tFCalc;
typedef struct _tFComponent tFComponent;

typedef struct miComponente{
   int id;
   char name[MAX_COMPONENT_NAME];
   enum CComponents type;
   void * parent;
   tVisual * visual;
   tText * text;
   tEDIT * editMode;
   tmapKeys * mapkey;
   tMove * move;
   tFActionPanel * personalAction;
   tFComponent * personalFComponent;
} tComponent, * tComponentPtr;


typedef struct lComponent{
  tComponent * componente;
  struct lComponent * siguiente;
}tlComponent, * tlComponentPtr;

typedef struct {
  char * View;
  char * Element;
}tCaller,*tCallerPtr;

typedef struct {
  char view[MAX_NAME_VIEW];
  char element[MAX_COMPONENT_NAME];
  tCaller caller; 
  enum Ops opToMade;
}tNext, * tNextPtr;

typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade; 
   char title[MAX_VIEW_TITLE];
   tVisual * visual;
   tFPanel * personalFPanel;
   tMove * move;
   tFActionPanel * personalAction;
   tlComponent * elements;
   tComponent * activeElement;
} tPanel, * tPanelPtr;


typedef struct tableColumn{
   char * title;
   unsigned short len;
   struct tableColumn * next;
} tTableColumn, * tTableColumnPtr;
   

typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade; 
   char title[MAX_VIEW_TITLE];
   tVisualPtr vTable;
   tVisualPtr vHead;
   tVisualPtr vData;
   unsigned short vline;
   unsigned short hline;
   unsigned short nColumns;
   unsigned short nLines;
   tText * text;
   tmapKeys * mapkey;
   tMove * move;
   tFActionTable * personalAction;
   tFTable * personalFTable;
   tTableColumnPtr columns;
} tTable, * tTablePtr;


typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   char file[MAX_NAME_FILE];
   unsigned short opToMade; 
   char title[MAX_VIEW_TITLE];
   tVisualPtr vHead;
   tVisualPtr vData;
   tText * text;
   tmapKeys * mapkey;
   tMove * move;
   enum EMode mode;
   tFActionEdit * personalAction;
   tFEdit * personalFEdit;
} tEdit, * tEditPtr;

typedef struct {
 enum CViews type;
 unsigned short level;
 WINDOW * wBack;
 tCaller caller; 
 union {
    tPanel * panel;
    tTable * table;
    tEdit * edit;
    } view;
}tView,*tViewPtr;


typedef struct lView{
  tViewPtr view;
  struct lView * siguiente;
}tlView, *tlViewPtr;

typedef struct lPanel{
  tPanel * panel;
  struct lPanel * siguiente;
}tlPanel, *tlPanelPtr;

typedef struct lTable{
  tTable * table;
  struct lTable * siguiente;
}tlTable, *tlTablePtr;

typedef struct {
   trAction* (*enter)(tComponent *,int key);
   trAction* (*out)(tComponent *,int key);
   trAction* (*next)(tComponent *,int key);
   trAction* (*previous)(tComponent *,int key);
   trAction* (*up)(tComponent *,int key);
   trAction* (*down)(tComponent *,int key);
   trAction* (*left)(tComponent *,int key);
   trAction* (*right)(tComponent *,int key);
   trAction* (*Fn)(tComponent *,int key, int Fn);
   trAction* (*back)(tComponent *,int key);
   trAction* (*Char)(tComponent *,int);
} _tFActionPanel;

typedef struct {
   trAction* (*enter)(tTable *,int key);
   trAction* (*out)(tTable *,int key);
   trAction* (*next)(tTable *,int key);
   trAction* (*previous)(tTable *,int key);
   trAction* (*up)(tTable *,int key);
   trAction* (*down)(tTable *,int key);
   trAction* (*left)(tTable *,int key);
   trAction* (*right)(tTable *,int key);
   trAction* (*Fn)(tTable *,int key, int Fn);
   trAction* (*back)(tTable *,int key);
   trAction* (*Char)(tTable *,int);
} _tFActionTable;

typedef struct {
   trAction* (*enter)(tEdit *,int key);
   trAction* (*out)(tEdit *,int key);
   trAction* (*next)(tEdit *,int key);
   trAction* (*previous)(tEdit *,int key);
   trAction* (*up)(tEdit *,int key);
   trAction* (*down)(tEdit *,int key);
   trAction* (*left)(tEdit *,int key);
   trAction* (*right)(tEdit *,int key);
   trAction* (*Fn)(tEdit *,int key, int Fn);
   trAction* (*back)(tEdit *,int key);
   trAction* (*Char)(tEdit *,int);
} _tFActionEdit;

typedef struct {
   void (*pre_create)(char * nom);
   void (*post_create)(tPanel *);
   void (*pre_show)(tPanel *);
   void (*post_show)(tPanel *);
   void (*pre_hide)(tPanel *);
   void (*post_hide)(tPanel *);
   void (*pre_destroy)(tPanel *);
   void (*post_destroy)(tPanel *);
   void (*pre_activate)(tPanel *);
   void (*post_activate)(tPanel *);
   void (*pre_deactivate)(tPanel *);
   void (*post_deactivate)(tPanel *); 
} _tFPanel;

typedef struct {
   void (*pre_create)(char * nom);
   void (*post_create)(tTable *);
   void (*pre_show)(tTable *);
   void (*post_show)(tTable *);
   void (*pre_hide)(tTable *);
   void (*post_hide)(tTable *);
   void (*pre_destroy)(tTable *);
   void (*post_destroy)(tTable *);
   void (*pre_activate)(tTable *);
   void (*post_activate)(tTable *);
   void (*pre_deactivate)(tTable *);
   void (*post_deactivate)(tTable *); 
} _tFTable;

typedef struct {
   void (*pre_create)(char * nom);
   void (*post_create)(tEdit *);
   void (*pre_show)(tEdit *);
   void (*post_show)(tEdit *);
   void (*pre_hide)(tEdit *);
   void (*post_hide)(tEdit *);
   void (*pre_destroy)(tEdit *);
   void (*post_destroy)(tEdit *);
   void (*pre_activate)(tEdit *);
   void (*post_activate)(tEdit *);
   void (*pre_deactivate)(tEdit *);
   void (*post_deactivate)(tEdit *); 
} _tFEdit;

typedef struct {
   void (*pre_create)(char * nom);
   void (*post_create)(tComponent *);
   void (*pre_show)(tComponent *);
   void (*post_show)(tComponent *);
   void (*pre_hide)(tComponent *);
   void (*post_hide)(tComponent *);
   void (*pre_destroy)(tComponent *);
   void (*post_destroy)(tComponent *);
   void (*pre_activate)(tComponent *);
   void (*post_activate)(tComponent *);
   void (*pre_deactivate)(tComponent *);
   void (*post_deactivate)(tComponent *); 
} _tFComponent;


typedef struct Lkeys{
  char nomKeys[MAX_NOM_MAP_KEY];
  tmapKeys * mapkeys;
  struct Lkeys * siguiente;
}tLkeys;

#endif /*__TBASIC */

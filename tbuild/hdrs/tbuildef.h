#define CABECERA_HEADERS "#include <stdio.h>\n\
#include <string.h>\n\
#include <stdlib.h>\n\
#include <locale.h>\n\
\n\
#include <ncurses.h>\n\
\n\
#include <tui.h>\n\n"

#define CABECERA_FUNC "#include <stdio.h>\n\
#include <string.h>\n\
#include <stdlib.h>\n\
#include <locale.h>\n\
\n\
#include <ncurses.h>\n\
\n\
#include <error.h>\n\
#include <tBasic.h>\n\
#include <msg.h>\n\
#include <text.h>\n\
#include <color.h>\n\
#include <visual.h>\n\
#include <panel.h>\n\
#include <table.h>\n\
#include <edit.h>\n\
#include <calc.h>\n\
#include <lview.h>\n\
#include <view.h>\n\
#include <component.h>\n\
#include <back.h>\n\n"

#define MOVE "tMove move = {\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   \"%s\",\n\
   {\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"},\n\
   \"%s\"\n\
   };\n\n"

#define CRE_COMPONENT_PASO1 "static tComponentPtr %s(tPanelPtr panel) {\n\
tChAttrPtr pColor=&%s;\n\
tDim pDim ={%d,%d,%d,%d,%d};\n\
tComponentPtr  elemento;\n"

#define CRE_COMPONENT_PASO2 "_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));\n\
 memset(auxFC,0,sizeof(_tFComponent));\n\
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));\n\
 memset(auxFA,0,sizeof(_tFActionPanel));\n"

#define CRE_COMPONENT_PASO3 "elemento=COMPONENT_create(panel,%d,\"%s\",%d,&pDim,pColor,\n\
%s,&move,auxFA,auxFC);\n"

#define CRE_COMPONENT_PASO4 " return elemento;\n}\n\n"


#define CRE_PANEL_PASO1 "static tViewPtr _P%s() {\n\
tChAttrPtr pColor=&%s;\n\
tDim pDim ={%d,%d,%d,%d,%d};\n\
tComponentPtr componente;\n\
tViewPtr view;\n"

#define CRE_PANEL_PASO2 "_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));\n\
memset(auxFP,0,sizeof(_tFPanel));\n\
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));\n\
memset(auxFA,0,sizeof(_tFActionPanel));\n"

#define CRE_PANEL_PASO3 "view=PANEL_create(%d,\"%s\",%d,\"%s\",&pDim,pColor,%d,&move,auxFA,auxFP);\n"

#define CRE_PANEL_COMPONENT "componente = %s(view->view.panel); \n\
PANEL_addComponent(view->view.panel, componente);\n"

#define CRE_PANEL_PASO4 "return view;\n}\n\n"


#define CHECK_EDIT "\nstatic void FEDIT_load(){\n\n"
#define ADD_CHECK_EDIT "  FEDIT_addCheck(%d,%d,%d,%s);\n"
#define CHECK_EDIT_END "}\n"

#define MSG_INI "static void MSGS_load(){\n "
#define ADD_MSG "  MSG_txtButton(%d,\"%s\",%d,\"%s\",\"%s\");\n\
  MSG_borderColor(%d,%d,&%s);\n"
#define MSG_FIN "}\n"

#define CRE_TABLE_PASO1 "tViewPtr _T%s() {\n\
tChAttrPtr pColorHead=&%s;\n\
tChAttrPtr pColorData=&%s;\n\
tDim pDim ={%d,%d,%d,%d,%d};\n\
tViewPtr view;\n"

#define CRE_TABLE_PASO2 "_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));\n\
 memset(auxFT,0,sizeof(_tFTable));\n\
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));\n\
 memset(auxFA,0,sizeof(_tFActionTable));\n"

#define CRE_TABLE_PASO3 "view=TABLE_create(%d,\"%s\",%d,\"%s\",&pDim,pColorHead,pColorData,%d,\n\
%d,%d,%d,%s,&move,auxFA,auxFT);\n"

#define CRE_TABLE_COLUMN "TABLE_addColumn(view->view.table,\"%s\",%d);\n"

#define CRE_TABLE_PASO4 "view->view.table->text=TEXT_new(RESIZE,1,%d,%d,%d);\n\
return view;\n}\n\n"


#define CRE_EDIT_PASO1 "static tViewPtr _E%s() {\n\
tChAttrPtr pColor=&%s;\n\
tDim pDim ={%d,%d,%d,%d,%d};\n\
tViewPtr view;\n"

#define CRE_EDIT_PASO2 "_tFEdit * auxFE=(_tFEdit *)malloc(sizeof(_tFEdit));\n\
 memset(auxFE,0,sizeof(_tFEdit));\n\
 _tFActionEdit * auxFA=(_tFActionEdit *)malloc(sizeof(_tFActionEdit));\n\
 memset(auxFA,0,sizeof(_tFActionTable));\n"

#define CRE_EDIT_PASO3 "view=EDIT_create(%d,\"%s\",%d,\"%s\",&pDim,pColor,%d,\n\
%d,%s,&move,auxFA,auxFE);\n"
#define CRE_EDIT_PASO4 "return view;\n}\n\n"

#define INI_VIEW "typedef struct {\n\
char nombre[MAX_NAME_VIEW];\n\
tViewPtr(* f)();\n\
}tinitView;\n\n\
static tinitView initView[%d] = { \n"


#define FUN_CRE_COLOR_INI "\nstatic void MAIN_createColors() {\n"
#define FUN_CRE_COLOR "%s.colorpair=COLOR_get(%d,%d);\n%s.attr=%d;\n\n"
#define FUN_CRE_COLOR_FIN "}\n"


#define MAIN_PASO0 "if ((retorno=%s(argc,argv) != 0)) exit (retorno);"

#define MAIN_PASO1 "\n\
int main(int argc, char * argv[])\n\
{\n\
  tViewPtr view,aux;\n\
  char initProyect[MAX_NAME_VIEW+MAX_COMPONENT_NAME+2]=\"%s\";\n\
  char nPanel[MAX_NAME_VIEW+2]=\"\";\n\
  char nComponent[MAX_COMPONENT_NAME+2]=\"\";\n\
  char * paux;\n\
  int i;\n\
  int retorno;\n\
\n\
   %s \n\
   scrSTD=TUI_init(%d,%d); \n\
\n\
   MAIN_createColors();\n\
   ERR_printError(%d,\"%s\");\n"

#define MAIN_PASO2 "  if (!strcmp(initProyect,\"\")==0)\n\
  {\n\
    paux=initProyect;\n\
     while (*paux!=':'&& *paux!='\\0') paux ++;\n\
     if (*paux==':') {\n\
        strncpy(nPanel,initProyect,(paux - initProyect));\n\
        paux++;\n\
        strcpy(nComponent,paux);\n\
     }\n\
  }\n\
  for (i=0;i!=%d;i++)\n\
  {\n\
   aux=initView[i].f();\n\
   if (strcmp(nPanel,\"\")==0)\n\
     {if (i==0) view=aux;}\n\
   else\n\
   {\n\
     if (strcmp(nPanel,initView[i].nombre)==0)\n\
      view = aux;\n\
   }\n\
  }\n\
  VIEW_Loop(view,nComponent);\n\
  TUI_end();\n\
  %s\n\
  return 0;\n\
}\n"





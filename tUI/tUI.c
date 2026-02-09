#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <tui.h>

#include <tUI_func.h>
SCREEN * scrSTD;
tChAttr noColor;
tChAttr miColor1;
tChAttr miColor1Inv;
tChAttr miColor2;
tChAttr miColor2Inv;
tChAttr miColor3;
tChAttr miColor4;
tChAttr miColor5;
tChAttr miColor6;
tChAttr miColor7;
tmapKeys propio ={
 {10,0,0},
 {27,0,0},
 {9,0,0},
 {353,0,0},
 {259,0,0},
 {258,0,0},
 {260,0,0},
 {261,0,0},
 {
 {264,0,0},
 {265,0,0},
 {266,0,0},
 {267,0,0},
 {268,0,0},
 {269,0,0},
 {270,0,0},
 {271,0,0},
 {272,0,0},
 {273,0,0},
 {274,0,0},
 {275,0,0},
 },
 {0,0,0}};

static void FEDIT_load(){

  FEDIT_addCheck(17,1,1,OneTo9);
}
static void MSGS_load(){
 }
static tComponentPtr _Cwelc_welcome(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,4,16,28};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"welcome",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"@@@@@@@@@@@@@@@@@@@@@    \n @@@@@@@@@@@@@@@@@@@@@@@  \n @@@@                 @@@ \n @@@@@@@ TERMINAL  @@@@@@ \n @@@@ USER INTERFACE  @@@ \n @@@@@@@           @@@@@@ \n @@@@                 @@@ \n @@@@       TUI       @@@ \n  @@@      =====      @@@ \n  @@@                  #@ \n  @##   Press Enter    #@@\n  @#                  ##@ \n   ### DBP ###############\n      ###########2025#####",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPproyect(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,1,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "mnProyect:mnPnew",
   "",
   ":2",
   ":mnPexit",
   "",
   "",
   ":mnPexit",
   ":mnPgeneral",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,1,"mnPproyect",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Proyect",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPgeneral(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,11,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "mnGeneral:mnGproperties",
   "",
   ":mnPviews",
   ":mnPproyect",
   "",
   "",
   ":mnPproyect",
   ":mnPviews",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,2,"mnPgeneral",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"General",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPviews(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,21,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "mnViews:Vpanels",
   "",
   ":mnPcomponents",
   ":mnPgeneral",
   "",
   "",
   ":mnPgeneral",
   ":mnPcomponents",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,3,"mnPviews",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Views",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPcomponents(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,0,3,12};
tComponentPtr  elemento;
tMove move = {
   "tcomp:",
   "",
   ":mnPlist",
   ":mnPviews",
   "",
   "",
   ":mnPviews",
   ":mnPlist",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,-1,"mnPcomponents",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Components",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPlist(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,44,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "mnList:colors",
   "",
   ":mnPedit",
   ":mnPcomponents",
   "",
   "",
   ":mnPcomponents",
   ":mnPedit",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,-1,"mnPlist",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"List",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPedit(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,54,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "mnEdit:open",
   "",
   ":mnPcompile",
   ":mnPlist",
   "",
   "",
   ":mnPlist",
   ":mnPcompile",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,-1,"mnPedit",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Edit",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPcompile(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,64,0,3,8};
tComponentPtr  elemento;
tMove move = {
   "mnMake:check",
   "",
   ":mnPexit",
   ":mnPedit",
   "",
   "",
   ":mnPedit",
   ":mnPexit",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_checkOpen;
elemento=COMPONENT_create(panel,-1,"mnPcompile",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Make ",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPexit(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,73,0,3,6};
tComponentPtr  elemento;
tMove move = {
   ":",
   "",
   ":mnPproyect",
   ":mnPcompile",
   "",
   "",
   ":mnPcompile",
   ":mnPproyect",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_exit;
elemento=COMPONENT_create(panel,-1,"mnPexit",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Exit",0);
 return elemento;
}

static tComponentPtr _CmnGe_mnGproperties(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,14};
tComponentPtr  elemento;
tMove move = {
   "frmPProyect:frmPPmouse",
   "",
   ":mnGkeymap",
   ":mnGmsgs",
   ":mnGmsgs",
   ":mnGkeymap",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnGproperties",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Properties",0);
 return elemento;
}

static tComponentPtr _CmnGe_mnGkeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,14};
tComponentPtr  elemento;
tMove move = {
   "mnKeymap:mnKnew",
   "",
   ":mnGeditFunction",
   ":mnGproperties",
   ":mnGproperties",
   ":mnGeditFunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnGkeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap",0);
 return elemento;
}

static tComponentPtr _CmnGe_mnGeditFunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,14};
tComponentPtr  elemento;
tMove move = {
   "frmEFunction:frmEFname",
   "",
   ":mnGcolors",
   ":mnGkeymap",
   ":mnGkeymap",
   ":mnGcolors",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnGeditFunction",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ed. Functions",0);
 return elemento;
}

static tComponentPtr _CmnGe_mnGcolors(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,6,3,14};
tComponentPtr  elemento;
tMove move = {
   "colors:Cnew",
   "",
   ":mnGmsgs",
   ":mnGeditFunction",
   ":mnGeditFunction",
   ":mnGmsgs",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnGcolors",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Colors",0);
 return elemento;
}

static tComponentPtr _CmnGe_mnGmsgs(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,8,3,14};
tComponentPtr  elemento;
tMove move = {
   "msgs:information",
   "",
   ":mnGproperties",
   ":mnGcolors",
   ":mnGcolors",
   ":mnGproperties",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnGmsgs",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Msgs",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPnew(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "frmNProyect:frmNPname",
   "",
   ":mnPopen",
   ":mnPtest",
   ":mnPtest",
   ":mnPopen",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnPnew",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"New",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPopen(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,9};
tComponentPtr  elemento;
tMove move = {
   "frmOProyect:frmOPname",
   "",
   ":mnPclose",
   ":mnPnew",
   ":mnPnew",
   ":mnPclose",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnPopen",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Open",0);
 return elemento;
}

static tComponentPtr _CmnPr_mnPclose(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":mnPsave",
   ":mnPopen",
   ":mnPopen",
   ":mnPsave",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_close;
elemento=COMPONENT_create(panel,-1,"mnPclose",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Close",0);
COMPONENT_display(elemento,1);
 return elemento;
}

static tComponentPtr _CmnPr_mnPsave(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,6,3,9};
tComponentPtr  elemento;
tMove move = {
   "frmSave:frmSPname",
   "",
   ":mnPtest",
   ":mnPclose",
   ":mnPclose",
   ":mnPtest",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnPsave",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Save",0);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CmnPr_mnPtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,8,3,9};
tComponentPtr  elemento;
tMove move = {
   "fttest:ttytest",
   "",
   ":mnPnew",
   ":mnPsave",
   ":mnPsave",
   ":mnPnew",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnPtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"T.TEST",0);
 return elemento;
}

static tComponentPtr _CmnKe_mnKnew(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "frmkeymap:nkeymap",
   "",
   ":mnKchange",
   ":mnKchange",
   ":mnKchange",
   ":mnKchange",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"mnKnew",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"New",0);
 return elemento;
}

static tComponentPtr _CmnKe_mnKchange(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,9};
tComponentPtr  elemento;
tMove move = {
   "tmselect:",
   "",
   ":mnKnew",
   ":mnKnew",
   ":mnKnew",
   ":mnKnew",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_change;
elemento=COMPONENT_create(panel,-1,"mnKchange",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Change",0);
 return elemento;
}

static tComponentPtr _CmnLi_colors(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,14};
tComponentPtr  elemento;
tMove move = {
   "tlistColors:",
   "",
   ":views",
   ":calls",
   ":calls",
   ":views",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colors",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Colors",0);
 return elemento;
}

static tComponentPtr _CmnLi_views(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,14};
tComponentPtr  elemento;
tMove move = {
   "tlistViews:",
   "",
   ":calls",
   ":colors",
   ":colors",
   ":calls",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"views",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Views",0);
 return elemento;
}

static tComponentPtr _CmnLi_calls(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,14};
tComponentPtr  elemento;
tMove move = {
   "tlistCalls:",
   "",
   ":colors",
   ":views",
   ":views",
   ":colors",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"calls",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Calls",0);
 return elemento;
}

static tComponentPtr _CmnMa_check(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,14};
tComponentPtr  elemento;
tMove move = {
   "frmCheck:ckenter",
   "",
   ":compile",
   ":run",
   ":run",
   ":compile",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"check",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Check",0);
 return elemento;
}

static tComponentPtr _CmnMa_compile(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,14};
tComponentPtr  elemento;
tMove move = {
   "frCompile:ckenter",
   "",
   ":run",
   ":check",
   ":check",
   ":run",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"compile",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Compile",0);
 return elemento;
}

static tComponentPtr _CmnMa_run(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,14};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":check",
   ":compile",
   ":compile",
   ":check",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=RUN_execute;
elemento=COMPONENT_create(panel,-1,"run",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Execute",0);
 return elemento;
}

static tComponentPtr _Cfrmk_frmK00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmK00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Define a user KEYMAP  ",0);
 return elemento;
}

static tComponentPtr _Cfrmk_frmK01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmK01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_nkeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,3,1,30};
tComponentPtr  elemento;
tMove move = {
   ":bkmEnter",
   "",
   ":bkmEnter",
   "",
   "",
   ":bkmEnter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"nkeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmEnter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,5,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":bkmOut",
   ":nkeymap",
   ":nkeymap",
   ":bkmOut",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmEnter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Enter:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkenter0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,5,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkenter0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_enter0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,5,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"enter0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkenter1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,5,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkenter1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_enter1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,5,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"enter1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkenter2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,5,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkenter2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_enter2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,5,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"enter2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmOut(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,6,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmNext",
   "",
   ":bkmNext",
   ":bkmEnter",
   ":bkmEnter",
   ":bkmNext",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmOut",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Out:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkout0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,6,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkout0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_out0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"out0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkout1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,6,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkout1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_out1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"out1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkout2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,6,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkout2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_out2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,6,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"out2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmNext(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,7,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmPrevious",
   "",
   ":bkmPrevious",
   ":bkmOut",
   ":bkmOut",
   ":bkmPrevious",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmNext",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Next:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etknext0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,7,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etknext0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_next0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"next0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etknext1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,7,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etknext1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_next1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"next1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etknext2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,7,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etknext2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_next2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,7,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"next2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmPrevious(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,8,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmUp",
   "",
   ":bkmUp",
   ":bkmNext",
   ":bkmNext",
   ":bkmUp",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmPrevious",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Previous:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkprevious0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkprevious0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_previous0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,8,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"previous0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkprevious1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkprevious1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_previous1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"previous1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkprevious2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,8,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkprevious2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_previous2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,8,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"previous2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmUp(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,9,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmDown",
   "",
   ":bkmDown",
   ":bkmPrevious",
   ":bkmPrevious",
   ":bkmDown",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmUp",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Up:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkup0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,9,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkup0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_up0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,9,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"up0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkup1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,9,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkup1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_up1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,9,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"up1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkup2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,9,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkup2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_up2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,9,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"up2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmDown(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,10,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmLeft",
   "",
   ":bkmLeft",
   ":bkmUp",
   ":bkmUp",
   ":bkmLeft",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmDown",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Down:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkdown0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,10,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkdown0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_down0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,10,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"down0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkdown1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,10,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkdown1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_down1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,10,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"down1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkdown2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,10,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkdown2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_down2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,10,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"down2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmLeft(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,11,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmRight",
   "",
   ":bkmRight",
   ":bkmDown",
   ":bkmDown",
   ":bkmRight",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmLeft",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Left:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkleft0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,11,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkleft0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_left0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,11,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"left0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkleft1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,11,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkleft1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_left1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,11,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"left1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkleft2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,11,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkleft2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_left2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,11,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"left2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmRight(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,12,1,9};
tComponentPtr  elemento;
tMove move = {
   ":bkmFunction",
   "",
   ":bkmFunction",
   ":bkmLeft",
   ":bkmLeft",
   ":bkmFunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_new;
elemento=COMPONENT_create(panel,-1,"bkmRight",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Right:",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkright0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,12,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkright0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_right0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,12,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"right0",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkright1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,12,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkright1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_right1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,12,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"right1",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_etkright2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,12,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etkright2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_right2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,12,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"right2",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfrmk_bkmFunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,13,1,25};
tComponentPtr  elemento;
tMove move = {
   ":frmKenter",
   "",
   ":frmKenter",
   ":bkmRight",
   ":bkmRight",
   ":frmKenter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"bkmFunction",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Use Keys Functions: ? ",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfrmk_frmKcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,15,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmKtest",
   ":bkmFunction",
   ":bkmFunction",
   "",
   ":frmKenter",
   ":frmKtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmKcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _Cfrmk_frmKtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,17,15,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmKdelete",
   ":bkmFunction",
   ":bkmFunction",
   "",
   ":frmKcancel",
   ":frmKdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_keymap;
elemento=COMPONENT_create(panel,-1,"frmKtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _Cfrmk_frmKdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,15,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmKenter",
   ":bkmFunction",
   ":bkmFunction",
   "",
   ":frmKtest",
   ":frmKenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_delete;
elemento=COMPONENT_create(panel,-1,"frmKdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _Cfrmk_frmKenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,45,15,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":bkmFunction",
   ":bkmFunction",
   "",
   ":frmKdelete",
   ":frmKcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=KEYM_create;
elemento=COMPONENT_create(panel,-1,"frmKenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do it!",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEF00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Define yours Application Check Edit Functions ",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEF01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Existing Edit Functions:",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFlist(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,28,3,5,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmEFname",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=EDF_select;
elemento=COMPONENT_create(panel,-1,"frmEFlist",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,5,1);
 return elemento;
}

static tComponentPtr _CfrmE_frmEF02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,8,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"User Edit Function:",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,8,1,30};
tComponentPtr  elemento;
tMove move = {
   ":frmEFAlign",
   "",
   ":frmEFAlign",
   ":frmEFlist",
   "",
   ":frmEFAlign",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEFname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmE_frmEF03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,9,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Align :",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFAlign(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,18,9,4,7};
tComponentPtr  elemento;
tMove move = {
   ":frmEFMode",
   "",
   ":frmEFMode",
   ":frmEFname",
   "",
   "",
   "",
   ":frmEFMode",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEFAlign",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,2,1);
TEXT_addSimpleLine(elemento->text,"LEFT");
TEXT_addSimpleLine(elemento->text,"RIGHT");
 return elemento;
}

static tComponentPtr _CfrmE_frmEF04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,9,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Mode :",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFMode(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,40,9,4,10};
tComponentPtr  elemento;
tMove move = {
   ":frmEFAdd",
   "",
   ":frmEFAdd",
   ":frmEFAlign",
   "",
   "",
   ":frmEFAlign",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEFMode",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,2,1);
TEXT_addSimpleLine(elemento->text,"INSERT");
TEXT_addSimpleLine(elemento->text,"REPLACE");
 return elemento;
}

static tComponentPtr _CfrmE_frmEFAdd(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmEFDel",
   ":frmEFMode",
   "",
   "",
   ":frmEFenter",
   ":frmEFDel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=EDF_new;
elemento=COMPONENT_create(panel,-1,"frmEFAdd",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Add",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFDel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmEFenter",
   ":frmEFMode",
   "",
   "",
   ":frmEFAdd",
   ":frmEFenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=EDF_delete;
elemento=COMPONENT_create(panel,-1,"frmEFDel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Del",0);
 return elemento;
}

static tComponentPtr _CfrmE_frmEFenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,45,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   "",
   ":frmEFname",
   ":frmEFname",
   "",
   ":frmEFDel",
   ":frmEFAdd",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEFenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Done",0);
 return elemento;
}

static tComponentPtr _Ccolo_Cnew(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "frmColor:frmCname",
   "",
   ":Cchange",
   ":Cchange",
   ":Cchange",
   ":Cchange",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"Cnew",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"New",0);
 return elemento;
}

static tComponentPtr _Ccolo_Cchange(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,9};
tComponentPtr  elemento;
tMove move = {
   "tmselect:",
   "",
   ":Cnew",
   ":Cnew",
   ":Cnew",
   ":Cnew",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COLOR_change;
elemento=COMPONENT_create(panel,-1,"Cchange",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Change",0);
 return elemento;
}

static tComponentPtr _Cmsgs_information(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,13};
tComponentPtr  elemento;
tMove move = {
   "frmMsgs:frmMtitle",
   "",
   ":warning",
   ":error",
   ":error",
   ":warning",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MSG_select;
elemento=COMPONENT_create(panel,-1,"information",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Information",0);
 return elemento;
}

static tComponentPtr _Cmsgs_warning(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,13};
tComponentPtr  elemento;
tMove move = {
   "frmMsgs:frmMtitle",
   "",
   ":error",
   ":information",
   ":information",
   ":error",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MSG_select;
elemento=COMPONENT_create(panel,-1,"warning",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Warning",0);
 return elemento;
}

static tComponentPtr _Cmsgs_error(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,13};
tComponentPtr  elemento;
tMove move = {
   "frmMsgs:frmMtitle",
   "",
   ":information",
   ":warning",
   ":warning",
   ":information",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MSG_select;
elemento=COMPONENT_create(panel,-1,"error",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Error",0);
 return elemento;
}

static tComponentPtr _CmnVi_Vpanels(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,0,3,9};
tComponentPtr  elemento;
tMove move = {
   "telement:",
   "",
   ":Vtables",
   ":Vcopy",
   ":Vcopy",
   ":Vtables",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelChange;
elemento=COMPONENT_create(panel,-1,"Vpanels",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panels",0);
 return elemento;
}

static tComponentPtr _CmnVi_Vtables(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,2,3,9};
tComponentPtr  elemento;
tMove move = {
   "telement:",
   "",
   ":Vedit",
   ":Vpanels",
   ":Vpanels",
   ":Vedit",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_tableChange;
elemento=COMPONENT_create(panel,-1,"Vtables",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Tables",0);
 return elemento;
}

static tComponentPtr _CmnVi_Vedit(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,4,3,9};
tComponentPtr  elemento;
tMove move = {
   "telement:",
   "",
   ":Vcopy",
   ":Vtables",
   ":Vtables",
   ":Vcopy",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_editChange;
elemento=COMPONENT_create(panel,-1,"Vedit",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Edit",0);
 return elemento;
}

static tComponentPtr _CmnVi_Vcopy(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,0,6,3,9};
tComponentPtr  elemento;
tMove move = {
   "telement:",
   "",
   ":Vpanels",
   ":Vedit",
   ":Vedit",
   ":Vpanels",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_copyChange;
elemento=COMPONENT_create(panel,-1,"Vcopy",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Copy",0);
 return elemento;
}

static tComponentPtr _CPLco_Colabel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,1,1,12};
tComponentPtr  elemento;
tMove move = {
   "CoL:CoLid",
   "",
   ":CoButton",
   ":CoField",
   ":CoField",
   ":CoButton",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"Colabel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Label",0);
 return elemento;
}

static tComponentPtr _CPLco_CoButton(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,2,1,12};
tComponentPtr  elemento;
tMove move = {
   "CoB:CoBid",
   "",
   ":CoCheck",
   ":Colabel",
   ":Colabel",
   ":CoCheck",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoButton",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Button",0);
 return elemento;
}

static tComponentPtr _CPLco_CoCheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,3,1,12};
tComponentPtr  elemento;
tMove move = {
   "CoCB:CoCBid",
   "",
   ":CoLsButton",
   ":CoButton",
   ":CoButton",
   ":CoLsButton",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCheck",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ck. Button",0);
 return elemento;
}

static tComponentPtr _CPLco_CoLsButton(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,4,1,12};
tComponentPtr  elemento;
tMove move = {
   "CoLB:CoLBid",
   "",
   ":CoField",
   ":CoCheck",
   ":CoCheck",
   ":CoField",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLsButton",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"List Button",0);
 return elemento;
}

static tComponentPtr _CPLco_CoField(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,5,1,12};
tComponentPtr  elemento;
tMove move = {
   "CoED:CoEDid",
   "",
   ":Colabel",
   ":CoLsButton",
   ":CoLsButton",
   ":Colabel",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoField",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Field",0);
 return elemento;
}

static tComponentPtr _CfrmN_frmNP00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNP00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"INDICATE THE NAME OF THE NEW PROYECT ",0);
 return elemento;
}

static tComponentPtr _CfrmN_frmNP01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,4,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNP01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CfrmN_frmNPname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,4,1,36};
tComponentPtr  elemento;
tMove move = {
   ":frmNPdescripcion",
   "",
   ":frmNPdescripcion",
   "",
   "",
   ":frmNPdescripcion",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNPname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmN_frmNP02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,6,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNP02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Description:",0);
 return elemento;
}

static tComponentPtr _CfrmN_frmNPdescripcion(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,6,2,36};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmNPenter",
   ":frmNPname",
   ":frmNPname",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNPdescripcion",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,2,1);
 return elemento;
}

static tComponentPtr _CfrmN_frmNPcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   ":frmNPenter",
   ":frmNPdescripcion",
   ":frmNPdescripcion",
   "",
   ":frmNPenter",
   ":frmNPenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmNPcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmN_frmNPenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   "",
   ":frmNPdescripcion",
   "mnPrincipal:mnPproyect",
   "",
   ":frmNPcancel",
   ":frmNPcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_new;
elemento=COMPONENT_create(panel,-1,"frmNPenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmO_frmOP00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmOP00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"INDICATE THE NAME OF THE XML PROYECT FILE ",0);
 return elemento;
}

static tComponentPtr _CfrmO_frmOP01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,4,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmOP01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Proyect:",0);
 return elemento;
}

static tComponentPtr _CfrmO_frmOPname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,4,1,36};
tComponentPtr  elemento;
tMove move = {
   ":frmOPenter",
   "",
   ":frmOPenter",
   "",
   "",
   ":frmOPenter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmOPname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmO_frmOPcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   ":frmOPenter",
   ":frmOPname",
   ":frmOPname",
   "",
   ":frmOPenter",
   ":frmOPenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmOPcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmO_frmOPenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   "",
   ":frmOPname",
   ":frmOPname",
   "",
   ":frmOPcancel",
   ":frmOPcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_open;
elemento=COMPONENT_create(panel,-1,"frmOPenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmS_frmSP00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"INDICATE THE NAME OF THE SAVE FILE ",0);
 return elemento;
}

static tComponentPtr _CfrmS_frmSP01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,4,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CfrmS_frmSPname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,4,1,36};
tComponentPtr  elemento;
tMove move = {
   ":frmSPenter",
   "",
   ":frmSPenter",
   "",
   "",
   ":frmSPenter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSPname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmS_frmSPcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   ":frmSPenter",
   ":frmSPname",
   ":frmSPname",
   "",
   ":frmSPenter",
   ":frmSPenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSPcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmS_frmSPenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "mnPrincipal:mnPproyect",
   "",
   ":frmSPname",
   ":frmSPname",
   "",
   ":frmSPcancel",
   ":frmSPcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_save;
elemento=COMPONENT_create(panel,-1,"frmSPenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _Cftte_ett00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ett00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"SPECIFY the TTY  TERM for TEST ",0);
 return elemento;
}

static tComponentPtr _Cftte_ett01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ett01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Term:",0);
 return elemento;
}

static tComponentPtr _Cftte_term(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,4,1,40};
tComponentPtr  elemento;
tMove move = {
   ":ttytest",
   "",
   ":ttytest",
   "",
   "",
   ":ttytest",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"term",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,"xterm-256color",0);
 return elemento;
}

static tComponentPtr _Cftte_ett02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,7,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ett02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Tty:",0);
 return elemento;
}

static tComponentPtr _Cftte_ttytest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,7,1,40};
tComponentPtr  elemento;
tMove move = {
   ":fttenter",
   "",
   ":fttenter",
   ":term",
   ":term",
   ":fttcancel",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ttytest",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,"/dev/pts",0);
 return elemento;
}

static tComponentPtr _Cftte_fttcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   ":fttenter",
   ":ttytest",
   ":ttytest",
   "",
   ":fttenter",
   ":fttenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fttcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _Cftte_fttenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,9,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPproyect",
   "",
   ":term",
   ":fttcancel",
   ":ttytest",
   "",
   ":fttcancel",
   ":fttcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_test;
elemento=COMPONENT_create(panel,-1,"fttenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"SPECIFY the Proyect Properties ",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPmouse(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,15};
tComponentPtr  elemento;
tMove move = {
   ":frmPPcolor",
   "",
   ":frmPPcolor",
   "",
   "",
   ":frmPPerror",
   "",
   ":frmPPcolor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPmouse",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Use Mouse: ? ",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,25,3,1,15};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmPPerror",
   ":frmPPmouse",
   "",
   ":frmPPferror",
   ":frmPPmouse",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPcolor",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Use Colors: ? ",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmP_frmPPerror(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmPPferror",
   ":frmPPcolor",
   ":frmPPmouse",
   ":chCheck",
   "",
   ":frmPPferror",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPerror",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Print Errors: ? to File: ",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
 return elemento;
}

static tComponentPtr _CfrmP_frmPPferror(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,31,4,1,20};
tComponentPtr  elemento;
tMove move = {
   ":chCheck",
   "",
   ":chCheck",
   ":frmPPerror",
   ":frmPPmouse",
   ":chCheck",
   ":frmPPerror",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPferror",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,"errors.err",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP21(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP21",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch. Check:",0);
 return elemento;
}

static tComponentPtr _CfrmP_chCheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,17,5,1,1};
tComponentPtr  elemento;
tMove move = {
   ":chisCheck",
   "",
   ":chisCheck",
   ":frmPPerror",
   ":frmPPerror",
   ":frmPPup",
   "",
   ":chisCheck",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"chCheck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP22(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,5,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP22",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch. is Check:",0);
 return elemento;
}

static tComponentPtr _CfrmP_chisCheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,5,1,1};
tComponentPtr  elemento;
tMove move = {
   ":chnoCheck",
   "",
   ":chnoCheck",
   ":chisCheck",
   ":frmPPerror",
   ":frmPPup",
   ":chCheck",
   ":chnoCheck",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"chisCheck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP23(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,5,1,14};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP23",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch. No Check:",0);
 return elemento;
}

static tComponentPtr _CfrmP_chnoCheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,54,5,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPup",
   "",
   ":frmPPup",
   ":chisCheck",
   ":frmPPerror",
   ":frmPPup",
   ":chisCheck",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"chnoCheck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Borders:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,18,6,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Up:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPup(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPdw",
   "",
   ":frmPPdw",
   ":chCheck",
   ":chCheck",
   ":frmSPup",
   "",
   ":frmPPdw",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPup",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,23,6,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dw:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPdw(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPlf",
   "",
   ":frmPPlf",
   ":frmPPup",
   ":chCheck",
   ":frmSPdw",
   ":frmPPup",
   ":frmPPlf",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPdw",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,28,6,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Lf:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPlf(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,31,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPrg",
   "",
   ":frmPPrg",
   ":frmPPdw",
   ":chCheck",
   ":frmSPlf",
   ":frmPPdw",
   ":frmPPrg",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPlf",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,6,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Rg:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPrg(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPcul",
   "",
   ":frmPPcul",
   ":frmPPlf",
   ":chCheck",
   ":frmSPrg",
   ":frmPPlf",
   ":frmPPcul",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPrg",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cul:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcul(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,42,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPcur",
   "",
   ":frmPPcur",
   ":frmPPrg",
   ":chCheck",
   ":frmSPcul",
   ":frmPPrg",
   ":frmPPcur",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPcul",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cur:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcur(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,48,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPcdl",
   "",
   ":frmPPcdl",
   ":frmPPcul",
   ":chCheck",
   ":frmSPcur",
   ":frmPPcul",
   ":frmPPcdl",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPcur",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cdl:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcdl(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,54,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPcdr",
   "",
   ":frmPPcdr",
   ":frmPPcur",
   ":chCheck",
   ":frmSPcdl",
   ":frmPPcur",
   ":frmPPcdr",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPcdl",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,6,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cdr:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcdr(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,60,6,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPup",
   "",
   ":frmSPup",
   ":frmPPcdl",
   ":chCheck",
   ":frmSPcdr",
   ":frmPPcdl",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmPPcdr",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,13};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Scr. Borders:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,18,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Up:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPup(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPdw",
   "",
   ":frmSPdw",
   ":frmPPcdr",
   ":frmPPup",
   ":frmPPmainf",
   "",
   ":frmSPdw",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPup",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,23,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dw:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPdw(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPlf",
   "",
   ":frmSPlf",
   ":frmSPup",
   ":frmPPdw",
   ":frmPPmainf",
   ":frmSPup",
   ":frmSPlf",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPdw",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,28,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Lf:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPlf(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,31,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPrg",
   "",
   ":frmSPrg",
   ":frmSPdw",
   ":frmPPlf",
   ":frmPPmainf",
   ":frmSPdw",
   ":frmSPrg",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPlf",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Rg:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPrg(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPcul",
   "",
   ":frmSPcul",
   ":frmSPlf",
   ":frmPPrg",
   ":frmPPmainf",
   ":frmSPlf",
   ":frmSPcul",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPrg",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cul:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPcul(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,42,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPcur",
   "",
   ":frmSPcur",
   ":frmSPrg",
   ":frmPPcul",
   ":frmPPmainf",
   ":frmSPrg",
   ":frmSPcur",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPcul",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cur:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPcur(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,48,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPcdl",
   "",
   ":frmSPcdl",
   ":frmSPcul",
   ":frmPPcur",
   ":frmPPmainf",
   ":frmSPcul",
   ":frmSPcdl",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPcur",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cdl:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPcdl(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,54,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmSPcdr",
   "",
   ":frmSPcdr",
   ":frmSPcur",
   ":frmPPcdl",
   ":frmPPmainf",
   ":frmSPcur",
   ":frmSPcdr",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPcdl",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,7,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cdr:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmSPcdr(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,60,7,1,1};
tComponentPtr  elemento;
tMove move = {
   ":frmPPmainf",
   "",
   ":frmPPmainf",
   ":frmSPcdl",
   ":frmPPcdr",
   ":frmPPmainf",
   ":frmSPcdl",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_create=PROY_replace;
elemento=COMPONENT_create(panel,-1,"frmSPcdr",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmSP10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmSP10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"User Main Function:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPmainf(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,8,1,30};
tComponentPtr  elemento;
tMove move = {
   ":frmPPendf",
   "",
   ":frmPPendf",
   ":frmSPup",
   ":frmSPup",
   ":frmPPendf",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPmainf",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"User End  Function:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPendf(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,9,1,30};
tComponentPtr  elemento;
tMove move = {
   ":frmPPinit",
   "",
   ":frmPPinit",
   ":frmPPmainf",
   ":frmPPmainf",
   ":frmPPinit",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPendf",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmP_frmPP12(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPP12",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Init View:",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPinit(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,10,1,30};
tComponentPtr  elemento;
tMove move = {
   ":frmPPenter",
   "",
   ":frmPPenter",
   ":frmPPendf",
   ":frmPPendf",
   ":frmPPenter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPinit",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,"<view:component>",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,12,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmPPenter",
   ":frmPPinit",
   ":frmPPinit",
   "",
   "",
   ":frmPPenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmPPcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmP_frmPPenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,12,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   "",
   ":frmPPinit",
   ":frmPPinit",
   "",
   ":frmPPcancel",
   ":frmPPcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_propertiesDoIt;
elemento=COMPONENT_create(panel,-1,"frmPPenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMet00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"SPECIFY the Characteristics for the Message ",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMet01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,3,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Title:",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMtitle(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,3,1,40};
tComponentPtr  elemento;
tMove move = {
   ":frmMnbuttons",
   "",
   ":frmMnbuttons",
   "",
   "",
   ":frmMnbuttons",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMtitle",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmM_frmMet02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,4,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Nro Buttons:",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMnbuttons(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,18,4,4,5};
tComponentPtr  elemento;
tMove move = {
   ":frmMcolor",
   "",
   ":frmMcolor",
   ":frmMtitle",
   "",
   "",
   "",
   ":frmMcolor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MSG_buttons;
elemento=COMPONENT_create(panel,-1,"frmMnbuttons",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,3,1);
TEXT_addSimpleLine(elemento->text,"0");
TEXT_addSimpleLine(elemento->text,"1");
TEXT_addSimpleLine(elemento->text,"2");
 return elemento;
}

static tComponentPtr _CfrmM_frmMet03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,25,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,36,4,4,20};
tComponentPtr  elemento;
tMove move = {
   ":frmMbutton1",
   "",
   ":frmMbutton1",
   ":frmMnbuttons",
   "",
   "",
   ":frmMnbuttons",
   ":frmMbutton1",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CfrmM_frmMet04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,9,1,14};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Button1 Text:",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMbutton1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,9,1,20};
tComponentPtr  elemento;
tMove move = {
   ":frmMbutton2",
   "",
   ":frmMbutton2",
   ":frmMcolor",
   ":frmMcolor",
   ":frmMbutton2",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMbutton1",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmM_frmMet05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,5,10,1,14};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMet05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Button2 Text:",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMbutton2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,10,1,20};
tComponentPtr  elemento;
tMove move = {
   ":frmMenter",
   "",
   ":frmMenter",
   ":frmMbutton1",
   ":frmMbutton1",
   ":frmMenter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMbutton2",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmM_frmMcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,12,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmMtest",
   ":frmMbutton2",
   ":frmMbutton2",
   "",
   ":frmMenter",
   ":frmMtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmMcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,12,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmMenter",
   ":frmMbutton2",
   ":frmMbutton2",
   "",
   ":frmMcancel",
   ":frmMenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_msg;
elemento=COMPONENT_create(panel,-1,"frmMtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"TEST",0);
 return elemento;
}

static tComponentPtr _CfrmM_frmMenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,45,12,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmMtitle",
   ":frmMbutton2",
   ":frmMbutton2",
   "",
   ":frmMtest",
   ":frmMcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MSG_change;
elemento=COMPONENT_create(panel,-1,"frmMenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmC00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmC00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Define the Colors",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmC01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmC01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,3,1,36};
tComponentPtr  elemento;
tMove move = {
   ":frmCbcolor",
   "",
   ":frmCbcolor",
   "",
   "",
   ":frmCbcolor",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmCname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmC_frmC02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmC02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Background:",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCbcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,16,4,4,12};
tComponentPtr  elemento;
tMove move = {
   ":frmCfcolor",
   "",
   ":frmCfcolor",
   ":frmCname",
   "",
   "",
   "",
   ":frmCfcolor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmCbcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,8,1);
TEXT_addSimpleLine(elemento->text,"0-BLACK");
TEXT_addSimpleLine(elemento->text,"1-BLUE");
TEXT_addSimpleLine(elemento->text,"2-GREEN");
TEXT_addSimpleLine(elemento->text,"3-CYAN");
TEXT_addSimpleLine(elemento->text,"4-RED");
TEXT_addSimpleLine(elemento->text,"5-MAGENTA");
TEXT_addSimpleLine(elemento->text,"6-YELLOW");
TEXT_addSimpleLine(elemento->text,"7-WHITE");
 return elemento;
}

static tComponentPtr _CfrmC_frmC03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,4,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmC03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Foreground:",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCfcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,42,4,5,12};
tComponentPtr  elemento;
tMove move = {
   ":frmCtext",
   "",
   ":frmCtext",
   ":frmCbcolor",
   "",
   "",
   ":frmCbcolor",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmCfcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,8,1);
TEXT_addSimpleLine(elemento->text,"0-BLACK");
TEXT_addSimpleLine(elemento->text,"1-BLUE");
TEXT_addSimpleLine(elemento->text,"2-GREEN");
TEXT_addSimpleLine(elemento->text,"3-CYAN");
TEXT_addSimpleLine(elemento->text,"4-RED");
TEXT_addSimpleLine(elemento->text,"5-MAGENTA");
TEXT_addSimpleLine(elemento->text,"6-YELLOW");
TEXT_addSimpleLine(elemento->text,"7-WHITE");
 return elemento;
}

static tComponentPtr _CfrmC_frmC04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmC04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Type Text:",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCtext(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,16,9,4,20};
tComponentPtr  elemento;
tMove move = {
   ":frmCcreate",
   "",
   ":frmCcreate",
   ":frmCfcolor",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmCtext",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,17,1);
TEXT_addSimpleLine(elemento->text,"WA_NORMAL");
TEXT_addSimpleLine(elemento->text,"WA_STANDOUT");
TEXT_addSimpleLine(elemento->text,"WA_UNDERLINE");
TEXT_addSimpleLine(elemento->text,"WA_REVERSE");
TEXT_addSimpleLine(elemento->text,"WA_BLINK");
TEXT_addSimpleLine(elemento->text,"WA_DIM");
TEXT_addSimpleLine(elemento->text,"WA_BOLD");
TEXT_addSimpleLine(elemento->text,"WA_ALTCHARSET");
TEXT_addSimpleLine(elemento->text,"WA_INVIS");
TEXT_addSimpleLine(elemento->text,"WA_PROTECT");
TEXT_addSimpleLine(elemento->text,"WA_HORIZONTAL");
TEXT_addSimpleLine(elemento->text,"WA_LEFT");
TEXT_addSimpleLine(elemento->text,"WA_LOW");
TEXT_addSimpleLine(elemento->text,"WA_RIGHT");
TEXT_addSimpleLine(elemento->text,"WA_TOP");
TEXT_addSimpleLine(elemento->text,"WA_VERTICAL");
TEXT_addSimpleLine(elemento->text,"WA_ITALIC");
 return elemento;
}

static tComponentPtr _CfrmC_frmCcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,4,14,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmCtest",
   ":frmCtext",
   ":frmCtext",
   "",
   ":frmCcreate",
   ":frmCtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmCcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,14,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmCdelete",
   ":frmCcancel",
   ":frmCtext",
   ":frmCbcolor",
   ":frmCcancel",
   ":frmCdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_color;
elemento=COMPONENT_create(panel,-1,"frmCtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,14,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPgeneral",
   "",
   ":frmCcreate",
   ":frmCtext",
   ":frmCtext",
   "",
   ":frmCtest",
   ":frmCcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COLOR_delete;
elemento=COMPONENT_create(panel,-1,"frmCdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmCcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,14,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":frmCname",
   ":frmCdelete",
   ":frmCtext",
   "",
   ":frmCdelete",
   ":frmCcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COLOR_new;
elemento=COMPONENT_create(panel,-1,"frmCcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _Cfnpa_npe00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"npe00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a PANEL View",0);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"ID:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":fnpnombre",
   "",
   ":fnpnombre",
   "",
   "",
   ":ptitle",
   "",
   ":fnpnombre",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpnombre(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":plevel",
   "",
   ":plevel",
   ":pid",
   "",
   ":ptitle",
   ":pid",
   ":plevel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpnombre",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,48,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Level:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_plevel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,55,2,1,2};
tComponentPtr  elemento;
tMove move = {
   ":ptitle",
   "",
   ":ptitle",
   ":fnpnombre",
   "",
   ":ptitle",
   ":fnpnombre",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"plevel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet14(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet14",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Title:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_ptitle(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,3,1,37};
tComponentPtr  elemento;
tMove move = {
   ":pop",
   "",
   ":pop",
   ":plevel",
   ":pid",
   ":pcolor",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ptitle",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet15(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,49,3,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet15",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Op:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pop(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,53,3,4,6};
tComponentPtr  elemento;
tMove move = {
   ":pcolor",
   "",
   ":pcolor",
   ":ptitle",
   "",
   "",
   ":ptitle",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pop",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,3,1);
TEXT_addSimpleLine(elemento->text,"NONE");
TEXT_addSimpleLine(elemento->text,"HIDE");
TEXT_addSimpleLine(elemento->text,"DELE");
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,4,4,18};
tComponentPtr  elemento;
tMove move = {
   ":fnpborder",
   "",
   ":fnpborder",
   ":pop",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpborder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   ":pX",
   "",
   ":pX",
   ":pcolor",
   ":pcolor",
   ":comps",
   "",
   ":pX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpborder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border : ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"DIMENSIONS",0);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":pY",
   "",
   ":pY",
   ":fnpborder",
   ":pcolor",
   ":comps",
   ":fnpborder",
   ":pY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":pWidth",
   "",
   ":pWidth",
   ":pX",
   ":pcolor",
   ":comps",
   ":pX",
   ":pWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":pHigh",
   "",
   ":pHigh",
   ":pY",
   ":pcolor",
   ":comps",
   ":pY",
   ":pHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_fnpet10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnpet10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":npfunctions",
   "",
   ":comps",
   ":pWidth",
   ":pcolor",
   ":comps",
   ":pWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"pHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnpa_comps(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,15,9,3,35};
tComponentPtr  elemento;
tMove move = {
   "tselect:",
   "",
   ":npfunctions",
   ":fnpborder",
   ":fnpborder",
   ":npfunctions",
   ":pmove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelComps;
elemento=COMPONENT_create(panel,-1,"comps",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"COMPONENTS:",0);
 return elemento;
}

static tComponentPtr _Cfnpa_npfunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,12,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":pmove",
   ":comps",
   ":comps",
   ":npcancel",
   "",
   ":pmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelCalls;
elemento=COMPONENT_create(panel,-1,"npfunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Functions",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,29,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":pamove",
   ":npfunctions",
   ":comps",
   ":nptest",
   ":npfunctions",
   ":pamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"pmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Moves",0);
 return elemento;
}

static tComponentPtr _Cfnpa_pamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,45,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":npcreate",
   ":pmove",
   ":comps",
   ":npcreate",
   ":pmove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"pamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Moves",0);
 return elemento;
}

static tComponentPtr _Cfnpa_npcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPviews",
   "",
   ":npdelete",
   ":npfunctions",
   ":npfunctions",
   "",
   "",
   ":npdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"npcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _Cfnpa_npdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,18,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":nptest",
   ":npcancel",
   ":pmove",
   "",
   ":npcancel",
   ":nptest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelDelete;
elemento=COMPONENT_create(panel,-1,"npdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _Cfnpa_nptest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":npcreate",
   ":npfunctions",
   ":pamove",
   "",
   ":npdelete",
   ":npcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_panel;
elemento=COMPONENT_create(panel,-1,"nptest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _Cfnpa_npcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,44,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":pid",
   ":npfunctions",
   ":pamove",
   "",
   ":nptest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelDoIt;
elemento=COMPONENT_create(panel,-1,"npcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _Cfned_nee00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"nee00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a EDIT View",0);
 return elemento;
}

static tComponentPtr _Cfned_fepet00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fepet00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"ID:",0);
 return elemento;
}

static tComponentPtr _Cfned_epid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":fnenombre",
   "",
   ":fnenombre",
   "",
   "",
   ":etitle",
   "",
   ":fnenombre",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"epid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _Cfned_fnenombre(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":elevel",
   "",
   ":elevel",
   ":epid",
   "",
   ":etitle",
   ":epid",
   ":elevel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fnenombre",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,48,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Level:",0);
 return elemento;
}

static tComponentPtr _Cfned_elevel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,55,2,1,2};
tComponentPtr  elemento;
tMove move = {
   ":etitle",
   "",
   ":etitle",
   ":fnenombre",
   "",
   ":ecolor",
   ":fnenombre",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"elevel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet14(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet14",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Title:",0);
 return elemento;
}

static tComponentPtr _Cfned_etitle(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,3,1,37};
tComponentPtr  elemento;
tMove move = {
   ":eop",
   "",
   ":eop",
   ":elevel",
   ":epid",
   ":eread",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etitle",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet15(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,49,3,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet15",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Op:",0);
 return elemento;
}

static tComponentPtr _Cfned_eop(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,53,3,4,6};
tComponentPtr  elemento;
tMove move = {
   ":eread",
   "",
   ":eread",
   ":etitle",
   "",
   "",
   ":etitle",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eop",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,3,1);
TEXT_addSimpleLine(elemento->text,"NONE");
TEXT_addSimpleLine(elemento->text,"HIDE");
TEXT_addSimpleLine(elemento->text,"DELE");
 return elemento;
}

static tComponentPtr _Cfned_eread(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":efile",
   "",
   ":efile",
   ":eop",
   ":etitle",
   ":efile",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eread",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Read Only: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfned_fneet24(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet24",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"File: ",0);
 return elemento;
}

static tComponentPtr _Cfned_efile(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,5,1,37};
tComponentPtr  elemento;
tMove move = {
   ":fneborder",
   "",
   ":fneborder",
   ":eread",
   ":eread",
   ":fneborder",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"efile",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneborder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,11};
tComponentPtr  elemento;
tMove move = {
   ":eX",
   "",
   ":eX",
   ":efile",
   ":efile",
   ":ecolor",
   "",
   ":eX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneborder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border : ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfned_fneet06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,7,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"DIMENSIONS",0);
 return elemento;
}

static tComponentPtr _Cfned_fneet07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _Cfned_eX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,7,1,2};
tComponentPtr  elemento;
tMove move = {
   ":eY",
   "",
   ":eY",
   ":fneborder",
   ":efile",
   ":ecolor",
   ":fneborder",
   ":eY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,7,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _Cfned_eY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,7,1,2};
tComponentPtr  elemento;
tMove move = {
   ":eWidth",
   "",
   ":eWidth",
   ":eX",
   ":efile",
   ":ecolor",
   ":eX",
   ":eWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,7,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _Cfned_eWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,7,1,2};
tComponentPtr  elemento;
tMove move = {
   ":eHigh",
   "",
   ":eHigh",
   ":eY",
   ":efile",
   ":emove",
   ":eY",
   ":eHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,7,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _Cfned_eHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,7,1,2};
tComponentPtr  elemento;
tMove move = {
   ":ecolor",
   "",
   ":ecolor",
   ":eWidth",
   ":efile",
   ":eamove",
   ":eWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"eHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_fneet05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fneet05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _Cfned_ecolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,9,4,18};
tComponentPtr  elemento;
tMove move = {
   ":ekeymap",
   "",
   ":ekeymap",
   ":eHigh",
   "",
   "",
   "",
   ":ekeymap",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ecolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _Cfned_ekeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,9,1,8};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":efunctions",
   ":ecolor",
   ":fneborder",
   ":emove",
   ":ecolor",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"ekeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap:",0);
 return elemento;
}

static tComponentPtr _Cfned_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,38,10,4,18};
tComponentPtr  elemento;
tMove move = {
   ":efunctions",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _Cfned_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,9,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfned_efunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,13,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":emove",
   ":ekeymap",
   ":ecolor",
   ":necancel",
   "",
   ":emove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelCalls;
elemento=COMPONENT_create(panel,-1,"efunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Functions",0);
 return elemento;
}

static tComponentPtr _Cfned_emove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,29,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":eamove",
   ":efunctions",
   ":ekeymap",
   ":netest",
   ":efunctions",
   ":eamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"emove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Moves",0);
 return elemento;
}

static tComponentPtr _Cfned_eamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,45,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":necreate",
   ":emove",
   ":ekeymap",
   ":necreate",
   ":emove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"eamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Moves",0);
 return elemento;
}

static tComponentPtr _Cfned_necancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPviews",
   "",
   ":nedelete",
   ":ekeymap",
   ":efunctions",
   "",
   "",
   ":nedelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"necancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _Cfned_nedelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,18,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":netest",
   ":necancel",
   ":efunctions",
   "",
   ":necancel",
   ":netest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_editDelete;
elemento=COMPONENT_create(panel,-1,"nedelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _Cfned_netest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":necreate",
   ":nedelete",
   ":emove",
   "",
   ":nedelete",
   ":necreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_edit;
elemento=COMPONENT_create(panel,-1,"netest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _Cfned_necreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,44,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":epid",
   ":netest",
   ":eamove",
   "",
   ":netest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_editDoIt;
elemento=COMPONENT_create(panel,-1,"necreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _Cfnta_fntet00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,1,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"ID:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tpid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,1,1,3};
tComponentPtr  elemento;
tMove move = {
   ":fntnombre",
   "",
   ":fntnombre",
   "",
   "",
   ":ttitle",
   "",
   ":fntnombre",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tpid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,1,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _Cfnta_fntnombre(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,1,1,25};
tComponentPtr  elemento;
tMove move = {
   ":tlevel",
   "",
   ":tlevel",
   ":tpid",
   "",
   ":ttitle",
   ":tpid",
   ":tlevel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntnombre",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,48,1,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Level:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tlevel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,55,1,1,2};
tComponentPtr  elemento;
tMove move = {
   ":ttitle",
   "",
   ":ttitle",
   ":fntnombre",
   "",
   ":top",
   ":fntnombre",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tlevel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet44(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet44",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Title:",0);
 return elemento;
}

static tComponentPtr _Cfnta_ttitle(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,2,1,37};
tComponentPtr  elemento;
tMove move = {
   ":top",
   "",
   ":top",
   ":tlevel",
   ":tpid",
   ":tlcolumn",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ttitle",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet15(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,49,2,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet15",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Op:",0);
 return elemento;
}

static tComponentPtr _Cfnta_top(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,53,2,4,6};
tComponentPtr  elemento;
tMove move = {
   ":tlcolumn",
   "",
   ":tlcolumn",
   ":ttitle",
   "",
   "",
   ":ttitle",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"top",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,3,1);
TEXT_addSimpleLine(elemento->text,"NONE");
TEXT_addSimpleLine(elemento->text,"HIDE");
TEXT_addSimpleLine(elemento->text,"DELE");
 return elemento;
}

static tComponentPtr _Cfnta_fntet34(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={0,2,3,5,47};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet34",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _Cfnta_fntet14(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={0,3,3,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet14",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Columns Len:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tlcolumn(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={0,15,3,1,3};
tComponentPtr  elemento;
tMove move = {
   ":tcolumn",
   "",
   ":tcolumn",
   ":top",
   ":ttitle",
   ":tcolumn",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tlcolumn",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_tcolumn(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={0,3,4,1,24};
tComponentPtr  elemento;
tMove move = {
   ":taddElem",
   "",
   ":taddElem",
   ":tlcolumn",
   ":ttitle",
   ":taddElem",
   "",
   ":tElemens",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tcolumn",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_taddElem(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,5,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":tdelElem",
   ":tcolumn",
   ":tlcolumn",
   ":tborder",
   "",
   ":tdelElem",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_addTableColumn;
elemento=COMPONENT_create(panel,-1,"taddElem",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Add:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tdelElem(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,12,5,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":tElemens",
   ":taddElem",
   ":tlcolumn",
   ":tborder",
   ":taddElem",
   ":tElemens",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delTableColumn;
elemento=COMPONENT_create(panel,-1,"tdelElem",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Del:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tElemens(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,27,3,5,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":tborder",
   ":tdelElem",
   "",
   "",
   ":tdelElem",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selTableColumn;
elemento=COMPONENT_create(panel,-1,"tElemens",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,5,1);
 return elemento;
}

static tComponentPtr _Cfnta_tborder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   ":tX",
   "",
   ":tX",
   ":taddElem",
   ":tlcolumn",
   ":thcolor",
   "",
   ":tX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tborder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border: ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfnta_fntet06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"DIMENSIONS",0);
 return elemento;
}

static tComponentPtr _Cfnta_fntet07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":tY",
   "",
   ":tY",
   ":tborder",
   ":tlcolumn",
   ":thcolor",
   ":tborder",
   ":tY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":tWidth",
   "",
   ":tWidth",
   ":tX",
   ":tlcolumn",
   ":thcolor",
   ":tX",
   ":tWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":tHigh",
   "",
   ":tHigh",
   ":tY",
   ":tlcolumn",
   ":tdcolor",
   ":tY",
   ":tHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":thcolor",
   "",
   ":thcolor",
   ":tWidth",
   ":tlcolumn",
   ":tdcolor",
   ":tWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,2,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Head C.:",0);
 return elemento;
}

static tComponentPtr _Cfnta_thcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,12,9,3,18};
tComponentPtr  elemento;
tMove move = {
   ":tdcolor",
   "",
   ":tdcolor",
   ":tHigh",
   "",
   "",
   "",
   ":tdcolor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"thcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,3,1);
 return elemento;
}

static tComponentPtr _Cfnta_fntet25(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,31,9,2,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fntet25",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Data C.:",0);
 return elemento;
}

static tComponentPtr _Cfnta_tdcolor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,40,9,3,18};
tComponentPtr  elemento;
tMove move = {
   ":head",
   "",
   ":head",
   ":thcolor",
   "",
   "",
   ":thcolor",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tdcolor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,3,1);
 return elemento;
}

static tComponentPtr _Cfnta_head(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,12,1,15};
tComponentPtr  elemento;
tMove move = {
   ":vline",
   "",
   ":vline",
   ":tdcolor",
   ":thcolor",
   ":vline",
   "",
   ":tkeymap",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"head",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Show Head: ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfnta_vline(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,13,1,15};
tComponentPtr  elemento;
tMove move = {
   ":hline",
   "",
   ":hline",
   ":head",
   ":head",
   ":tfunctions",
   "",
   ":hline",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"vline",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Vtl. Line: ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfnta_hline(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,18,13,1,15};
tComponentPtr  elemento;
tMove move = {
   ":tkeymap",
   "",
   ":tkeymap",
   ":vline",
   ":head",
   ":tfunctions",
   ":vline",
   ":tkeymap",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"hline",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Hzt. Line: ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _Cfnta_tkeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,12,1,8};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":tfunctions",
   ":hline",
   ":tdcolor",
   ":tmove",
   ":hline",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"tkeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap:",0);
 return elemento;
}

static tComponentPtr _Cfnta_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,38,13,4,18};
tComponentPtr  elemento;
tMove move = {
   ":tfunctions",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _Cfnta_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,38,12,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _Cfnta_tfunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,14,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":tmove",
   ":tkeymap",
   ":vline",
   ":ntcancel",
   "",
   ":tmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelCalls;
elemento=COMPONENT_create(panel,-1,"tfunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Functions",0);
 return elemento;
}

static tComponentPtr _Cfnta_tmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,29,14,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":tamove",
   ":tfunctions",
   ":hline",
   ":ntcancel",
   ":tfunctions",
   ":tamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"tmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Moves",0);
 return elemento;
}

static tComponentPtr _Cfnta_tamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,45,14,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":ntcreate",
   ":tmove",
   ":tkeymap",
   ":ntcreate",
   ":tmove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_panelMove;
elemento=COMPONENT_create(panel,-1,"tamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"App. Moves",0);
 return elemento;
}

static tComponentPtr _Cfnta_ntcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPviews",
   "",
   ":ntdelete",
   ":tamove",
   ":tfunctions",
   "",
   "",
   ":ntdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ntcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _Cfnta_ntdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,18,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":nttest",
   ":tfunctions",
   ":tfunctions",
   "",
   ":ntcancel",
   ":nttest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_tableDelete;
elemento=COMPONENT_create(panel,-1,"ntdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _Cfnta_nttest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":ntcreate",
   ":tfunctions",
   ":tmove",
   "",
   ":ntdelete",
   ":ntcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_table;
elemento=COMPONENT_create(panel,-1,"nttest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _Cfnta_ntcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,44,17,3,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":tpid",
   ":tfunctions",
   ":tamove",
   "",
   ":nttest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_tableDoIt;
elemento=COMPONENT_create(panel,-1,"ntcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmV_frmEF00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Create a View by Copy ",0);
 return elemento;
}

static tComponentPtr _CfrmV_frmEF01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,3,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"From:",0);
 return elemento;
}

static tComponentPtr _CfrmV_fromView(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,3,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fromView",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmV_to(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,4,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"to",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"To:",0);
 return elemento;
}

static tComponentPtr _CfrmV_toView(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,4,1,30};
tComponentPtr  elemento;
tMove move = {
   ":component",
   "",
   ":component",
   "",
   "",
   ":component",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"toView",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmV_component(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,31};
tComponentPtr  elemento;
tMove move = {
   ":moves",
   "",
   ":moves",
   ":toView",
   ":toView",
   ":moves",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"component",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Copy components .......... : ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmV_moves(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,31};
tComponentPtr  elemento;
tMove move = {
   ":appMoves",
   "",
   ":appMoves",
   ":component",
   ":component",
   ":appMoves",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"moves",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Copy moves ............... : ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmV_appMoves(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,31};
tComponentPtr  elemento;
tMove move = {
   ":appCalls",
   "",
   ":appCalls",
   ":moves",
   ":moves",
   ":appCalls",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"appMoves",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Copy applications moves .. : ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmV_appCalls(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,31};
tComponentPtr  elemento;
tMove move = {
   ":enter",
   "",
   ":enter",
   ":appMoves",
   ":appMoves",
   ":enter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"appCalls",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Copy applications calls .. : ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CfrmV_cancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,15,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPviews",
   "",
   ":enter",
   ":appCalls",
   ":appCalls",
   "",
   "",
   ":enter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CfrmV_enter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPviews",
   "",
   "",
   ":appCalls",
   ":appCalls",
   "",
   ":cancel",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=VIEW_copyDoIt;
elemento=COMPONENT_create(panel,-1,"enter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEF00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEF01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,3,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEF01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_fromComponent(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,3,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fromComponent",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmC_to(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,4,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"to",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_toComponent(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,26,4,1,30};
tComponentPtr  elemento;
tMove move = {
   ":attach",
   "",
   ":attach",
   "",
   "",
   ":attach",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"toComponent",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfrmC_etAttach(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"etAttach",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_attach(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,30,6,4,25};
tComponentPtr  elemento;
tMove move = {
   ":moves",
   "",
   ":moves",
   ":toComponent",
   "",
   ":moves",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"attach",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CfrmC_moves(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,25};
tComponentPtr  elemento;
tMove move = {
   ":appMoves",
   "",
   ":appMoves",
   ":attach",
   ":appMoves",
   ":appMoves",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"moves",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_appMoves(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,25};
tComponentPtr  elemento;
tMove move = {
   ":appCalls",
   "",
   ":appCalls",
   ":moves",
   ":appCalls",
   ":appCalls",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"appMoves",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_appCalls(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,25};
tComponentPtr  elemento;
tMove move = {
   ":enter",
   "",
   ":enter",
   ":appMoves",
   ":enter",
   ":enter",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"appCalls",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_cancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,15,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":enter",
   ":appCalls",
   "",
   "",
   "",
   ":enter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CfrmC_enter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,13,3,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":appCalls",
   "",
   "",
   ":cancel",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"enter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"",0);
 return elemento;
}

static tComponentPtr _CaMov_em00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe Moves",0);
 return elemento;
}

static tComponentPtr _CaMov_panel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,40};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"panel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,1);
 return elemento;
}

static tComponentPtr _CaMov_em01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Enter   :",0);
 return elemento;
}

static tComponentPtr _CaMov_em11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Out     :",0);
 return elemento;
}

static tComponentPtr _CaMov_em21(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em21",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Next    :",0);
 return elemento;
}

static tComponentPtr _CaMov_em31(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em31",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Previous:",0);
 return elemento;
}

static tComponentPtr _CaMov_em41(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em41",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Up      :",0);
 return elemento;
}

static tComponentPtr _CaMov_em51(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em51",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Down    :",0);
 return elemento;
}

static tComponentPtr _CaMov_em61(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em61",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Left    :",0);
 return elemento;
}

static tComponentPtr _CaMov_em71(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em71",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Right   :",0);
 return elemento;
}

static tComponentPtr _CaMov_em81(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,11,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em81",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Fn :",0);
 return elemento;
}

static tComponentPtr _CaMov_em83(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,12,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em83",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Fn :",0);
 return elemento;
}

static tComponentPtr _CaMov_em84(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,13,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em84",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Fn :",0);
 return elemento;
}

static tComponentPtr _CaMov_em85(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,14,1,4};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em85",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Fn :",0);
 return elemento;
}

static tComponentPtr _CaMov_empanelenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompenter",
   "",
   ":emcompenter",
   "",
   "",
   ":empanelout",
   "",
   ":emcompenter",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelenter",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelout(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,4,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompout",
   "",
   ":emcompout",
   ":emcompenter",
   ":empanelenter",
   ":empanelnext",
   "",
   ":emcompout",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelout",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelnext(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,5,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompnext",
   "",
   ":emcompnext",
   ":emcompout",
   ":empanelout",
   ":empanelprev",
   "",
   ":emcompnext",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelnext",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelprev(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,6,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompprev",
   "",
   ":emcompprev",
   ":emcompnext",
   ":empanelnext",
   ":empanelup",
   "",
   ":emcompprev",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelprev",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelup(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,7,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompup",
   "",
   ":emcompup",
   ":emcompprev",
   ":empanelprev",
   ":empaneldown",
   "",
   ":emcompup",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelup",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empaneldown(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,8,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompdown",
   "",
   ":emcompdown",
   ":emcompup",
   ":empanelup",
   ":empanelleft",
   "",
   ":emcompdown",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empaneldown",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelleft(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,9,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompleft",
   "",
   ":emcompleft",
   ":emcompdown",
   ":empaneldown",
   ":empanelright",
   "",
   ":emcompleft",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelleft",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelright(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,10,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompright",
   "",
   ":emcompright",
   ":emcompleft",
   ":empanelleft",
   ":empanelFn0",
   "",
   ":emcompright",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelright",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelFn0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,7,11,1,1};
tComponentPtr  elemento;
tMove move = {
   ":empanelF0",
   "",
   ":empanelF0",
   ":emcompright",
   ":empanelright",
   ":empanelFn1",
   "",
   ":empanelF0",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"empanelFn0",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,17,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelF0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,11,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompF0",
   "",
   ":emcompF0",
   ":empanelFn0",
   ":empanelright",
   ":empanelF1",
   ":empanelFn0",
   ":emcompF0",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelF0",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelFn1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,7,12,1,1};
tComponentPtr  elemento;
tMove move = {
   ":empanelF1",
   "",
   ":empanelF1",
   ":emcompF0",
   ":empanelFn0",
   ":empanelFn2",
   "",
   ":empanelF1",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"empanelFn1",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,17,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelF1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,12,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompF1",
   "",
   ":emcompF1",
   ":empanelFn1",
   ":empanelF0",
   ":empanelF2",
   ":empanelFn1",
   ":emcompF1",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelF1",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelFn2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,7,13,1,1};
tComponentPtr  elemento;
tMove move = {
   ":empanelF2",
   "",
   ":empanelF2",
   ":emcompF1",
   ":empanelFn1",
   ":empanelFn3",
   "",
   ":empanelF2",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"empanelFn2",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,17,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelF2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,13,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompF2",
   "",
   ":emcompF2",
   ":empanelFn2",
   ":empanelF1",
   ":empanelF3",
   ":empanelFn2",
   ":emcompF2",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelF2",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelFn3(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,7,14,1,1};
tComponentPtr  elemento;
tMove move = {
   ":empanelF3",
   "",
   ":empanelF3",
   ":emcompF2",
   ":empanelFn2",
   ":nesave",
   "",
   ":empanelF3",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"empanelFn3",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,17,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_empanelF3(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,14,1,20};
tComponentPtr  elemento;
tMove move = {
   ":emcompF3",
   "",
   ":emcompF3",
   ":empanelFn3",
   ":empanelF2",
   ":nesave",
   ":empanelFn3",
   ":emcompF3",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
auxFA->enter=MOVE_enterPanel;
elemento=COMPONENT_create(panel,-1,"empanelF3",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_em12(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,3,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em12",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em22(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,4,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em22",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em32(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,5,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em32",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em42(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,6,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em42",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em52(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,7,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em52",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em62(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,8,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em62",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em72(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,9,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em72",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em82(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,10,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em82",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em92(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,11,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em92",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em93(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,12,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em93",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em94(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,13,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em94",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_em95(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,34,14,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em95",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,":",0);
 return elemento;
}

static tComponentPtr _CaMov_emcompenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,3,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelout",
   "",
   ":empanelout",
   ":empanelenter",
   "",
   ":emcompout",
   ":empanelenter",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompenter",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompout(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,4,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelnext",
   "",
   ":empanelnext",
   ":empanelout",
   ":emcompenter",
   ":emcompnext",
   ":empanelout",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompout",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompnext(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,5,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelprev",
   "",
   ":empanelprev",
   ":empanelnext",
   ":emcompout",
   ":emcompprev",
   ":empanelnext",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompnext",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompprev(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,6,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelup",
   "",
   ":empanelup",
   ":empanelprev",
   ":emcompnext",
   ":emcompup",
   ":empanelprev",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompprev",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompup(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,7,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empaneldown",
   "",
   ":empaneldown",
   ":empanelup",
   ":emcompprev",
   ":emcompdown",
   ":empanelup",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompup",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompdown(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelleft",
   "",
   ":empanelleft",
   ":empaneldown",
   ":emcompup",
   ":emcompleft",
   ":empaneldown",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompdown",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompleft(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,9,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelright",
   "",
   ":empanelright",
   ":empanelleft",
   ":emcompdown",
   ":emcompright",
   ":empanelleft",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompleft",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompright(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,10,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelFn0",
   "",
   ":empanelFn0",
   ":empanelright",
   ":emcompleft",
   ":emcompF0",
   ":empanelright",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompright",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompF0(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,11,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelFn1",
   "",
   ":empanelFn1",
   ":empanelF0",
   ":emcompright",
   ":emcompF1",
   ":empanelF0",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompF0",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompF1(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,12,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelFn2",
   "",
   ":empanelFn2",
   ":empanelF1",
   ":emcompF0",
   ":emcompF2",
   ":empanelF1",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompF1",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompF2(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,13,1,20};
tComponentPtr  elemento;
tMove move = {
   ":empanelFn3",
   "",
   ":empanelFn3",
   ":empanelF2",
   ":emcompF1",
   ":emcompF3",
   ":empanelF2",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompF2",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_emcompF3(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,14,1,20};
tComponentPtr  elemento;
tMove move = {
   ":nesave",
   "",
   ":nesave",
   ":empanelF3",
   ":emcompF2",
   ":nesave",
   ":empanelF3",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->pre_activate=COMP_preEnterPanel;
elemento=COMPONENT_create(panel,-1,"emcompF3",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CaMov_em99(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,6,18,1,50};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"em99",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," F2 to Select List ",0);
 return elemento;
}

static tComponentPtr _CaMov_nesave(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   "",
   ":emcompF3",
   ":empanelFn3",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MOVE_save;
elemento=COMPONENT_create(panel,-1,"nesave",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe Life Cicle Callbacks ",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Create     :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Create    :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Show       :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Show      :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Activate   :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Activate  :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Deactivate :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Deactivate:",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,11,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Hide       :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,12,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Hide      :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,13,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"PRE Destroy    :",0);
 return elemento;
}

static tComponentPtr _CfApp_frmac12(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,14,1,16};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmac12",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"POST Destroy   :",0);
 return elemento;
}

static tComponentPtr _CfApp_fACPreCr(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,3,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostCr",
   "",
   ":fACPostCr",
   ":fACPostDest",
   "",
   ":fACPostCr",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreCr",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostCr(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,4,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPreSh",
   "",
   ":fACPreSh",
   ":fACPreCr",
   ":fACPreCr",
   ":fACPreSh",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostCr",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPreSh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,5,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostSh",
   "",
   ":fACPostSh",
   ":fACPostCr",
   ":fACPostCr",
   ":fACPostSh",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreSh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostSh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,6,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPreAct",
   "",
   ":fACPreAct",
   ":fACPreSh",
   ":fACPreSh",
   ":fACPreAct",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostSh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPreAct(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,7,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostAct",
   "",
   ":fACPostAct",
   ":fACPostSh",
   ":fACPostSh",
   ":fACPostAct",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreAct",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostAct(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,8,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPreDAct",
   "",
   ":fACPreDAct",
   ":fACPreAct",
   ":fACPreAct",
   ":fACPreDAct",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostAct",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPreDAct(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,9,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostDAct",
   "",
   ":fACPostDAct",
   ":fACPostAct",
   ":fACPostAct",
   ":fACPostDAct",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreDAct",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostDAct(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,10,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPreHide",
   "",
   ":fACPreHide",
   ":fACPreDAct",
   ":fACPreDAct",
   ":fACPreHide",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostDAct",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPreHide(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,11,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostHide",
   "",
   ":fACPostHide",
   ":fACPostDAct",
   ":fACPostDAct",
   ":fACPostHide",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreHide",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostHide(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,12,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPreDest",
   "",
   ":fACPreDest",
   ":fACPreHide",
   ":fACPreHide",
   ":fACPreDest",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostHide",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPreDest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,13,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACPostDest",
   "",
   ":fACPostDest",
   ":fACPostHide",
   ":fACPostHide",
   ":fACPostDest",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPreDest",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACPostDest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,20,14,1,30};
tComponentPtr  elemento;
tMove move = {
   ":fACsave",
   "",
   ":fACsave",
   ":fACPreDest",
   ":fACPreDest",
   ":fACsave",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"fACPostDest",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfApp_fACsave(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,15,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   "",
   ":fACPostDest",
   ":fACPostDest",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=FUNC_save;
elemento=COMPONENT_create(panel,-1,"fACsave",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfMov_am00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe Application Moves Functions",0);
 return elemento;
}

static tComponentPtr _CfMov_am01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,3,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Enter   :",0);
 return elemento;
}

static tComponentPtr _CfMov_am11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Out     :",0);
 return elemento;
}

static tComponentPtr _CfMov_am21(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,5,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am21",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Next    :",0);
 return elemento;
}

static tComponentPtr _CfMov_am31(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,6,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am31",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Previous:",0);
 return elemento;
}

static tComponentPtr _CfMov_am41(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,7,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am41",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Up      :",0);
 return elemento;
}

static tComponentPtr _CfMov_am51(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,8,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am51",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Down    :",0);
 return elemento;
}

static tComponentPtr _CfMov_am61(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,9,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am61",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Left    :",0);
 return elemento;
}

static tComponentPtr _CfMov_am71(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,10,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am71",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Right   :",0);
 return elemento;
}

static tComponentPtr _CfMov_am81(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,11,1,9};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"am81",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Fn      :",0);
 return elemento;
}

static tComponentPtr _CfMov_amenterfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,3,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amoutfunction",
   "",
   ":amoutfunction",
   "",
   "",
   ":amoutfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amenterfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amoutfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,4,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amnextfunction",
   "",
   ":amnextfunction",
   ":amenterfunction",
   ":amenterfunction",
   ":amnextfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amoutfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amnextfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,5,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amprevfunction",
   "",
   ":amprevfunction",
   ":amoutfunction",
   ":amoutfunction",
   ":amprevfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amnextfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amprevfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,6,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amupfunction",
   "",
   ":amupfunction",
   ":amnextfunction",
   ":amnextfunction",
   ":amupfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amprevfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amupfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,7,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amdownfunction",
   "",
   ":amdownfunction",
   ":amprevfunction",
   ":amprevfunction",
   ":amdownfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amupfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amdownfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,8,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amleftfunction",
   "",
   ":amleftfunction",
   ":amupfunction",
   ":amupfunction",
   ":amleftfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amdownfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amleftfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,9,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amrightfunction",
   "",
   ":amrightfunction",
   ":amdownfunction",
   ":amdownfunction",
   ":amrightfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amleftfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amrightfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,10,1,30};
tComponentPtr  elemento;
tMove move = {
   ":amFnfunction",
   "",
   ":amFnfunction",
   ":amleftfunction",
   ":amleftfunction",
   ":amFnfunction",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amrightfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_amFnfunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,11,1,30};
tComponentPtr  elemento;
tMove move = {
   ":nasave",
   "",
   ":nasave",
   ":amrightfunction",
   ":amrightfunction",
   ":nasave",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"amFnfunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CfMov_nasave(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,25,13,3,10};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   "",
   ":amFnfunction",
   ":amFnfunction",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=MOVE_saveFunction;
elemento=COMPONENT_create(panel,-1,"nasave",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CCoL_col00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a New Label Component ",0);
 return elemento;
}

static tComponentPtr _CCoL_col01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"ID:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":cname",
   "",
   ":cname",
   "",
   "",
   ":CoLVisible",
   "",
   ":cname",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CCoL_cname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":CoLVisible",
   "",
   ":CoLVisible",
   ":CoLid",
   "",
   ":CoLColor",
   ":CoLid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panel:",0);
 return elemento;
}

static tComponentPtr _CCoL_cpanel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cpanel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_CoLVisible(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoLColor",
   "",
   ":CoLColor",
   ":cname",
   ":CoLid",
   ":CoLBorder",
   "",
   ":CoLColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLVisible",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Visible: ? ",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoL_CoLSelect(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoLColor",
   "",
   ":CoLColor",
   ":CoLVisible",
   ":CoLid",
   ":CoLBorder",
   ":CoLVisible",
   ":CoLColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLSelect",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Select.: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoL_col04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color :",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLColor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,38,4,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoLBorder",
   "",
   ":CoLBorder",
   ":CoLVisible",
   "",
   "",
   ":CoLVisible",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLColor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoL_CoLBorder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   ":CoLX",
   "",
   ":CoLX",
   ":CoLColor",
   ":CoLVisible",
   ":CoLText",
   "",
   ":CoLX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBorder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border : ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoL_col05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dimensions ",0);
 return elemento;
}

static tComponentPtr _CCoL_col06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLY",
   "",
   ":CoLY",
   ":CoLBorder",
   ":CoLVisible",
   ":CoLText",
   ":CoLBorder",
   ":CoLY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLWidth",
   "",
   ":CoLWidth",
   ":CoLX",
   ":CoLVisible",
   ":CoLText",
   ":CoLX",
   ":CoLWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLHigh",
   "",
   ":CoLHigh",
   ":CoLY",
   ":CoLVisible",
   ":CoLText",
   ":CoLY",
   ":CoLHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLText",
   "",
   ":CoLText",
   ":CoLWidth",
   ":CoLVisible",
   ":CoLText",
   ":CoLWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoL_col03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"col03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Text:",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLText(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,9,2,45};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoLFunctions",
   ":CoLHigh",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLText",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,2,1);
 return elemento;
}

static tComponentPtr _CCoL_CoLFunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,11,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":CoLcancel",
   ":CoLText",
   ":CoLText",
   ":CoLcreate",
   "",
   ":CoLcancel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqCalls;
elemento=COMPONENT_create(panel,-1,"CoLFunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Functions ",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoLdelete",
   ":CoLFunctions",
   ":CoLFunctions",
   "",
   "",
   ":CoLdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_out;
elemento=COMPONENT_create(panel,-1,"CoLcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoLtest",
   ":CoLcancel",
   ":CoLFunctions",
   "",
   ":CoLcancel",
   ":CoLtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delete;
elemento=COMPONENT_create(panel,-1,"CoLdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoLcreate",
   ":CoLdelete",
   ":CoLFunctions",
   "",
   ":CoLdelete",
   ":CoLcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_componentPanel;
elemento=COMPONENT_create(panel,-1,"CoLtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _CCoL_CoLcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":CoLFunctions",
   ":CoLFunctions",
   "",
   ":CoLtest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_labelDoIt;
elemento=COMPONENT_create(panel,-1,"CoLcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CCoB_cob00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a New BUTTON Component",0);
 return elemento;
}

static tComponentPtr _CCoB_cob01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Id:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":cname",
   "",
   "",
   ":CoBVisible",
   "",
   ":cname",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CCoB_cname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBVisible",
   ":CoBid",
   "",
   ":CoBColor",
   ":CoBid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panel:",0);
 return elemento;
}

static tComponentPtr _CCoB_cpanel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cpanel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_CoBVisible(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoBSelect",
   "",
   ":CoBSelect",
   ":cname",
   ":CoBid",
   ":CoBKeymap",
   "",
   ":CoBSelect",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_Visible;
elemento=COMPONENT_create(panel,-1,"CoBVisible",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Visible: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoB_CoBSelect(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoBColor",
   "",
   ":CoBColor",
   ":CoBVisible",
   ":CoBid",
   ":CoBKeymap",
   ":CoBVisible",
   ":CoBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBSelect",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Select.: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoB_CoBKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,7};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":CoBBorder",
   ":CoBColor",
   ":CoBVisible",
   ":CoBBorder",
   "",
   ":CoBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"CoBKeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap",0);
 return elemento;
}

static tComponentPtr _CCoB_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,6,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoBBorder",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _CCoB_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CCoB_cob04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBColor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,4,4,18};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBKeymap",
   ":CoBSelect",
   "",
   "",
   ":CoBSelect",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBColor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoB_CoBBorder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBX",
   ":CoBKeymap",
   ":CoBKeymap",
   ":CoBText",
   "",
   ":CoBX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBBorder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border: ? ",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoB_cob05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dimensions:",0);
 return elemento;
}

static tComponentPtr _CCoB_cob06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBY",
   ":CoBBorder",
   ":CoBColor",
   ":CoBText",
   ":CoBBorder",
   ":CoBY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBWidth",
   ":CoBX",
   ":CoBColor",
   ":CoBText",
   ":CoBX",
   ":CoBWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBHigh",
   ":CoBY",
   ":CoBColor",
   ":CoBText",
   ":CoBY",
   ":CoBHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBText",
   ":CoBWidth",
   ":CoBColor",
   ":CoBText",
   ":CoBWidth",
   ":CoBText",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoB_cob03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cob03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Text:",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBText(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,9,2,45};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBFunctions",
   ":CoBHigh",
   ":CoBBorder",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoBText",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,2,1);
 return elemento;
}

static tComponentPtr _CCoB_CoBFunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,12,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":CoBamove",
   ":CoBText",
   ":CoBText",
   ":CoBcancel",
   "",
   ":CoBamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqCalls;
elemento=COMPONENT_create(panel,-1,"CoBFunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Functions ",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,25,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":CoBpmove",
   ":CoBFunctions",
   ":CoBText",
   ":CoBtest",
   ":CoBFunctions",
   ":CoBpmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoBamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," Moves ",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBpmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,43,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":CoBcancel",
   ":CoBamove",
   ":CoBText",
   ":CoBcreate",
   ":CoBamove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoBpmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Moves ",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoBdelete",
   ":CoBpmove",
   ":CoBFunctions",
   "",
   "",
   ":CoBdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_out;
elemento=COMPONENT_create(panel,-1,"CoBcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoBtest",
   ":CoBcancel",
   ":CoBFunctions",
   "",
   ":CoBcancel",
   ":CoBtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delete;
elemento=COMPONENT_create(panel,-1,"CoBdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoBcreate",
   ":CoBdelete",
   ":CoBamove",
   "",
   ":CoBdelete",
   ":CoBcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_componentPanel;
elemento=COMPONENT_create(panel,-1,"CoBtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _CCoB_CoBcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":CoBtest",
   ":CoBpmove",
   "",
   ":CoBtest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_buttonDoIt;
elemento=COMPONENT_create(panel,-1,"CoBcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CCoCB_cocb00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a New Check Button Component",0);
 return elemento;
}

static tComponentPtr _CCoCB_cocb01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Id:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":cname",
   "",
   ":cname",
   "",
   "",
   ":CoCBVisible",
   "",
   ":cname",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CCoCB_cname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":CoCBVisible",
   "",
   ":CoCBVisible",
   ":CoCBid",
   "",
   ":CoCBVisible",
   ":CoCBid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cbol11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cbol11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panel:",0);
 return elemento;
}

static tComponentPtr _CCoCB_cpanel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoCBVisible",
   ":CoCBid",
   "",
   ":CoCBColor",
   ":CoCBid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cpanel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBVisible(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoCBSelect",
   "",
   ":CoCBSelect",
   ":cname",
   ":CoCBid",
   ":CoCBKeymap",
   "",
   ":CoCBSelect",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_Visible;
elemento=COMPONENT_create(panel,-1,"CoCBVisible",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Visible: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoCB_CoCBSelect(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoCBColor",
   "",
   ":CoCBColor",
   ":CoCBVisible",
   ":CoCBid",
   ":CoCBKeymap",
   ":CoCBVisible",
   ":CoCBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBSelect",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Select.: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoCB_CoCBKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,7};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":CoCBBorder",
   ":CoCBColor",
   ":CoCBVisible",
   ":CoCBBorder",
   "",
   ":CoCBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"CoCBKeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,6,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoCBBorder",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _CCoCB_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CCoCB_cocb04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBColor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,4,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoCBKeymap",
   "",
   ":CoCBKeymap",
   ":CoCBSelect",
   "",
   "",
   ":CoCBSelect",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBColor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBBorder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   ":CoCBX",
   "",
   ":CoCBX",
   ":CoCBColor",
   ":CoCBKeymap",
   ":CoCBText",
   "",
   ":CoCBX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBBorder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoCB_cocb05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dimensions",0);
 return elemento;
}

static tComponentPtr _CCoCB_cocb06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoCBY",
   "",
   ":CoCBY",
   ":CoCBBorder",
   ":CoCBColor",
   ":CoCBText",
   ":CoCBBorder",
   ":CoCBY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoCBWidth",
   "",
   ":CoCBWidth",
   ":CoCBX",
   ":CoCBColor",
   ":CoCBText",
   ":CoCBX",
   ":CoCBWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoCBHigh",
   "",
   ":CoCBHigh",
   ":CoCBY",
   ":CoCBColor",
   ":CoCBText",
   ":CoCBY",
   ":CoCBHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoCBText",
   "",
   ":CoCBText",
   ":CoCBWidth",
   ":CoCBColor",
   ":CoCBText",
   ":CoCBWidth",
   ":CoCBText",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Text:",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBText(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,9,2,45};
tComponentPtr  elemento;
tMove move = {
   ":CoCBisCheck",
   "",
   ":CoCBisCheck",
   ":CoCBHigh",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBText",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,2,1);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBisCheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,11,1,11};
tComponentPtr  elemento;
tMove move = {
   ":CoCBchcheck",
   "",
   ":CoCBchcheck",
   ":CoCBText",
   ":CoCBText",
   ":CoCBFunctions",
   "",
   ":CoCBchcheck",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBisCheck",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Check: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoCB_cocb21(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,16,11,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb21",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch Check",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBchcheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,11,1,1};
tComponentPtr  elemento;
tMove move = {
   ":CoCBchischeck",
   "",
   ":CoCBchischeck",
   ":CoCBisCheck",
   ":CoCBText",
   ":CoCBamove",
   ":CoCBisCheck",
   ":CoCBchischeck",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBchcheck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,29,11,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch Is Check",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBchischeck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,42,11,1,1};
tComponentPtr  elemento;
tMove move = {
   ":CoCBchncheck",
   "",
   ":CoCBchncheck",
   ":CoCBchcheck",
   ":CoCBText",
   ":CoCBamove",
   ":CoCBchcheck",
   ":CoCBchncheck",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBchischeck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_cocb12(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,11,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cocb12",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch No Check",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBchncheck(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,57,11,1,1};
tComponentPtr  elemento;
tMove move = {
   ":CoCBFunctions",
   "",
   ":CoCBFunctions",
   ":CoCBchischeck",
   ":CoCBText",
   ":CoCBpmove",
   ":CoCBchischeck",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoCBchncheck",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBFunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,12,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":CoCBamove",
   ":CoCBchncheck",
   ":CoCBisCheck",
   ":CoCBcancel",
   "",
   ":CoCBamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqCalls;
elemento=COMPONENT_create(panel,-1,"CoCBFunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Functions ",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,25,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":CoCBpmove",
   ":CoCBFunctions",
   ":CoCBchischeck",
   ":CoCBtest",
   ":CoCBFunctions",
   ":CoCBpmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoCBamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"  Moves ",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBpmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,43,12,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":CoCBcreate",
   ":CoCBamove",
   ":CoCBchncheck",
   ":CoCBcreate",
   ":CoCBamove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoCBpmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Moves ",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoCBdelete",
   ":CoCBpmove",
   ":CoCBFunctions",
   "",
   "",
   ":CoCBdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_out;
elemento=COMPONENT_create(panel,-1,"CoCBcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoCBtest",
   ":CoCBcancel",
   ":CoCBFunctions",
   "",
   ":CoCBcancel",
   ":CoCBtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delete;
elemento=COMPONENT_create(panel,-1,"CoCBdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoCBcreate",
   ":CoCBdelete",
   ":CoCBamove",
   "",
   ":CoCBdelete",
   ":CoCBcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_componentPanel;
elemento=COMPONENT_create(panel,-1,"CoCBtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _CCoCB_CoCBcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,15,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":CoCBtest",
   ":CoCBpmove",
   "",
   ":CoCBtest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_ckbuttonDoIt;
elemento=COMPONENT_create(panel,-1,"CoCBcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CCoLB_colb00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a New Component List Button",0);
 return elemento;
}

static tComponentPtr _CCoLB_colb01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Id:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":cname",
   "",
   ":cname",
   "",
   "",
   ":CoDisplay",
   "",
   ":cname",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CCoLB_cname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":CoDisplay",
   "",
   ":CoDisplay",
   ":CoLBid",
   "",
   ":CoDisplay",
   ":CoLBid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_lbol11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"lbol11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panel:",0);
 return elemento;
}

static tComponentPtr _CCoLB_cpanel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cpanel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb98(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb98",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Display:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoDisplay(tPanelPtr panel) {
tChAttrPtr pColor=&miColor2;
tDim pDim ={0,15,4,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoLBColor",
   ":cname",
   "",
   "",
   "",
   ":CoLBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoDisplay",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,4,1);
TEXT_addSimpleLine(elemento->text,"NORMAL");
TEXT_addSimpleLine(elemento->text,"HIDDEN");
TEXT_addSimpleLine(elemento->text,"NOT SELECT");
TEXT_addSimpleLine(elemento->text,"OPEN");
 return elemento;
}

static tComponentPtr _CCoLB_CoLBKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,7};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":CoLBBorder",
   ":CoLBColor",
   ":CoDisplay",
   ":CoLBBorder",
   "",
   ":CoLBColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLBKeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,6,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoLBBorder",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _CCoLB_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CCoLB_colb04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBColor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,4,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoLBKeymap",
   "",
   ":CoLBKeymap",
   ":CoDisplay",
   "",
   "",
   ":CoDisplay",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBColor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBBorder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,11};
tComponentPtr  elemento;
tMove move = {
   ":CoLBX",
   "",
   ":CoLBX",
   ":CoLBKeymap",
   ":CoLBKeymap",
   ":CoLBText",
   "",
   ":CoLBX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBBorder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoLB_colb05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,8,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dimensions",0);
 return elemento;
}

static tComponentPtr _CCoLB_colb06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLBY",
   "",
   ":CoLBY",
   ":CoLBBorder",
   ":CoLBKeymap",
   ":CoLBText",
   ":CoLBBorder",
   ":CoLBY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,8,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLBWidth",
   "",
   ":CoLBWidth",
   ":CoLBX",
   ":CoLBColor",
   ":CoLBText",
   ":CoLBX",
   ":CoLBWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLBHigh",
   "",
   ":CoLBHigh",
   ":CoLBY",
   ":CoLBColor",
   ":CoLBText",
   ":CoLBY",
   ":CoLBHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,8,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,8,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoLBText",
   "",
   ":CoLBText",
   ":CoLBWidth",
   ":CoLBColor",
   ":CoLBText",
   ":CoLBWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_colb10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"colb10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Text:",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBText(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,25};
tComponentPtr  elemento;
tMove move = {
   ":CoLBTAdd",
   "",
   ":CoLBTAdd",
   ":CoLBHigh",
   ":CoLBBorder",
   ":CoLBTAdd",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoLBText",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBData(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,29,9,4,28};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoLBFunctions",
   ":CoLBText",
   "",
   "",
   ":CoLBText",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_lbData;
elemento=COMPONENT_create(panel,-1,"CoLBData",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBTAdd(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,6,11,2,5};
tComponentPtr  elemento;
tMove move = {
   ":CoLBText",
   "",
   ":CoLBTdel",
   ":CoLBText",
   ":CoLBText",
   ":CoLBFunctions",
   "",
   ":CoLBTdel",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_addList;
elemento=COMPONENT_create(panel,-1,"CoLBTAdd",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Add",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBTdel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,11,2,5};
tComponentPtr  elemento;
tMove move = {
   ":CoLBText",
   "",
   ":CoLBFunctions",
   ":CoLBTAdd",
   ":CoLBText",
   ":CoLBFunctions",
   ":CoLBTAdd",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delList;
elemento=COMPONENT_create(panel,-1,"CoLBTdel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Del",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBFunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,13,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":CoLBamove",
   ":CoLBText",
   ":CoLBText",
   ":CoLBcancel",
   "",
   ":CoLBamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqCalls;
elemento=COMPONENT_create(panel,-1,"CoLBFunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,0,80,2,1);
TEXT_addSimpleLine(elemento->text," App. Functions ");
TEXT_addSimpleLine(elemento->text,"Del");
 return elemento;
}

static tComponentPtr _CCoLB_CoLBamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,25,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":CoLBpmove",
   ":CoLBFunctions",
   ":CoLBText",
   ":CoLBtest",
   ":CoLBFunctions",
   ":CoLBpmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoLBamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"  Moves ",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBpmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,43,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":CoLBcreate",
   ":CoLBamove",
   ":CoLBText",
   ":CoLBcreate",
   ":CoLBamove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoLBpmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Moves ",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoLBdelete",
   ":CoLBpmove",
   ":CoLBFunctions",
   "",
   "",
   ":CoLBdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_out;
elemento=COMPONENT_create(panel,-1,"CoLBcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoLBtest",
   ":CoLBcancel",
   ":CoLBFunctions",
   "",
   ":CoLBcancel",
   ":CoLBtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delete;
elemento=COMPONENT_create(panel,-1,"CoLBdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoLBcreate",
   ":CoLBdelete",
   ":CoLBamove",
   "",
   ":CoLBdelete",
   ":CoLBcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_componentPanel;
elemento=COMPONENT_create(panel,-1,"CoLBtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test",0);
 return elemento;
}

static tComponentPtr _CCoLB_CoLBcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":CoLBpmove",
   ":CoLBpmove",
   "",
   ":CoLBtest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_lsbuttonDoIt;
elemento=COMPONENT_create(panel,-1,"CoLBcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CCoED_coed00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Describe a New Field Component",0);
 return elemento;
}

static tComponentPtr _CCoED_coed01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,2,1,5};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Id:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDid(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,9,2,1,3};
tComponentPtr  elemento;
tMove move = {
   ":cname",
   "",
   ":cname",
   "",
   "",
   ":CoEDVisible",
   "",
   ":cname",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDid",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_coed02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,2,1,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Name:",0);
 return elemento;
}

static tComponentPtr _CCoED_cname(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,22,2,1,25};
tComponentPtr  elemento;
tMove move = {
   ":CoEDVisible",
   "",
   ":CoEDVisible",
   ":CoEDid",
   "",
   ":CoEDColor",
   ":CoEDid",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cname",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_edol11(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,3,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"edol11",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Panel:",0);
 return elemento;
}

static tComponentPtr _CCoED_cpanel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,13,3,1,25};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"cpanel",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_CoEDVisible(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoEDSelect",
   "",
   ":CoEDSelect",
   ":cname",
   ":CoEDid",
   ":CoEDAuto",
   "",
   ":CoEDSelect",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_Visible;
elemento=COMPONENT_create(panel,-1,"CoEDVisible",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Visible: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoED_CoEDSelect(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,4,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoEDColor",
   "",
   ":CoEDColor",
   ":CoEDVisible",
   ":CoEDid",
   ":CoEDAuto",
   ":CoEDVisible",
   ":CoEDColor",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDSelect",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Select.: ?",0);
elemento->visual->status.defCheck=1;
if (elemento->text != NULL) elemento->text->check=1;
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoED_CoEDAuto(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,5,1,15};
tComponentPtr  elemento;
tMove move = {
   ":CoEDSecret",
   "",
   ":CoEDSecret",
   ":CoEDColor",
   ":CoEDVisible",
   ":CoEDKeymap",
   "",
   ":CoEDSecret",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDAuto",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Auto Enter: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoED_CoEDSecret(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,19,5,1,12};
tComponentPtr  elemento;
tMove move = {
   ":CoEDKeymap",
   "",
   ":CoEDKeymap",
   ":CoEDAuto",
   ":CoEDColor",
   ":CoEDKeymap",
   ":CoEDAuto",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDSecret",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Secret: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoED_CoEDKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,6,1,7};
tComponentPtr  elemento;
tMove move = {
   ":CoLKeymap",
   "",
   ":CoEDmode",
   ":CoEDSecret",
   ":CoEDAuto",
   ":CoEDmode",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_selectKEYM;
elemento=COMPONENT_create(panel,-1,"CoEDKeymap",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Keymap",0);
 return elemento;
}

static tComponentPtr _CCoED_CoLKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,7,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoEDmode",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectKEYM;
elemento=COMPONENT_create(panel,-1,"CoLKeymap",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _CCoED_CoTKeymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,7,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoTKeymap",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CCoED_coed04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,4,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Color:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDColor(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,35,4,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoEDAuto",
   "",
   ":CoEDAuto",
   ":CoEDSelect",
   "",
   "",
   ":CoEDSelect",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDColor",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
 return elemento;
}

static tComponentPtr _CCoED_coed34(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,8,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed34",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Ch ED:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDmode(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,8,1,1};
tComponentPtr  elemento;
tMove move = {
   ":CoEDBFunction",
   "",
   ":CoEDBFunction",
   ":CoEDKeymap",
   ":CoEDKeymap",
   ":CoEDBorder",
   "",
   ":CoEDBFunction",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDmode",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,".",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDBFunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,16,8,1,15};
tComponentPtr  elemento;
tMove move = {
   ":CoEDLEFunction",
   "",
   ":CoEDBorder",
   ":CoEDmode",
   ":CoEDKeymap",
   ":CoEDBorder",
   ":CoEDmode",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDBFunction",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Edit Functions",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDLEFunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,16,9,4,18};
tComponentPtr  elemento;
tMove move = {
   ":CoEDBFunction",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFC->post_deactivate=COMP_deselectEdFunc;
elemento=COMPONENT_create(panel,-1,"CoEDLEFunction",3,&pDim,pColor,
NULL,&move,auxFA,auxFC);
elemento->text=TEXT_new(RESIZE,1,80,4,1);
COMPONENT_display(elemento,3);
 return elemento;
}

static tComponentPtr _CCoED_CoEDTEFunction(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,37,8,1,20};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDTEFunction",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,0,0,0};
COMPONENT_createEdit(elemento,&auxEDIT);
COMPONENT_simpleText(elemento,"none",0);
COMPONENT_display(elemento,2);
 return elemento;
}

static tComponentPtr _CCoED_CoEDBorder(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,9,1,11};
tComponentPtr  elemento;
tMove move = {
   ":CoEDX",
   "",
   ":CoEDX",
   ":CoEDBFunction",
   ":CoEDmode",
   ":CoEDText",
   "",
   ":CoEDX",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDBorder",2,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Border: ?",0);
VISUAL_changeIsCheck(elemento,'Y');
VISUAL_changeNoCheck(elemento,'N');
 return elemento;
}

static tComponentPtr _CCoED_coed05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,15,9,1,12};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Dimensions",0);
 return elemento;
}

static tComponentPtr _CCoED_coed06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,27,9,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"X:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDX(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,30,9,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoEDY",
   "",
   ":CoEDY",
   ":CoEDBorder",
   ":CoEDBFunction",
   ":CoEDText",
   ":CoEDBorder",
   ":CoEDY",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDX",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_coed07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,33,9,1,3};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Y:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDY(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,36,9,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoEDWidth",
   "",
   ":CoEDWidth",
   ":CoEDX",
   ":CoEDBFunction",
   ":CoEDText",
   ":CoEDX",
   ":CoEDWidth",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDY",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_coed08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,39,9,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Width:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDWidth(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,46,9,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoEDHigh",
   "",
   ":CoEDHigh",
   ":CoEDY",
   ":CoEDBFunction",
   ":CoEDText",
   ":CoEDY",
   ":CoEDHigh",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDWidth",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_coed09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,50,9,1,6};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"High:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDHigh(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,56,9,1,2};
tComponentPtr  elemento;
tMove move = {
   ":CoEDText",
   "",
   ":CoEDText",
   ":CoEDWidth",
   ":CoEDBFunction",
   ":CoEDText",
   ":CoEDWidth",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDHigh",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,1,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,1,1);
 return elemento;
}

static tComponentPtr _CCoED_coed10(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,10,1,7};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"coed10",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Text:",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDText(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,3,11,2,50};
tComponentPtr  elemento;
tMove move = {
   ":CoEDFunctions",
   "",
   ":CoEDFunctions",
   ":CoEDHigh",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"CoEDText",4,&pDim,pColor,
NULL,&move,auxFA,auxFC);
tEDIT auxEDIT={0,46,4,1};
COMPONENT_createEdit(elemento,&auxEDIT);
elemento->text=TEXT_new(RESIZE,1,80,2,1);
 return elemento;
}

static tComponentPtr _CCoED_CoEDFunctions(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,3,13,3,19};
tComponentPtr  elemento;
tMove move = {
   "fAppCalls:fACPreCr",
   "",
   ":CoEDamove",
   ":CoEDText",
   ":CoEDText",
   ":CoEDcancel",
   "",
   ":CoEDamove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqCalls;
elemento=COMPONENT_create(panel,-1,"CoEDFunctions",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Functions ",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDamove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,25,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "aMove:empanelenter",
   "",
   ":CoEDpmove",
   ":CoEDFunctions",
   ":CoEDText",
   ":CoEDtest",
   ":CoEDFunctions",
   ":CoEDpmove",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoEDamove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," Moves ",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDpmove(tPanelPtr panel) {
tChAttrPtr pColor=&miColor6;
tDim pDim ={1,43,13,3,14};
tComponentPtr  elemento;
tMove move = {
   "fMove:amenterfunction",
   "",
   ":CoEDcreate",
   ":CoEDamove",
   ":CoEDText",
   ":CoEDcreate",
   ":CoEDamove",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_reqMoves;
elemento=COMPONENT_create(panel,-1,"CoEDpmove",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento," App. Moves ",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDcancel(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,5,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoEDdelete",
   ":CoEDpmove",
   ":CoEDFunctions",
   "",
   "",
   ":CoEDdelete",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_out;
elemento=COMPONENT_create(panel,-1,"CoEDcancel",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Cancel",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDdelete(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "-:",
   "",
   ":CoEDtest",
   ":CoEDcancel",
   ":CoEDFunctions",
   "",
   ":CoEDcancel",
   ":CoEDtest",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_delete;
elemento=COMPONENT_create(panel,-1,"CoEDdelete",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Delete",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDtest(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,33,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":CoEDcreate",
   ":CoEDdelete",
   ":CoEDamove",
   "",
   ":CoEDdelete",
   ":CoEDcreate",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=TEST_componentPanel;
elemento=COMPONENT_create(panel,-1,"CoEDtest",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Test ",0);
 return elemento;
}

static tComponentPtr _CCoED_CoEDcreate(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,47,16,3,8};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   ":CoEDpmove",
   ":CoEDpmove",
   "",
   ":CoEDtest",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=COMP_fieldDoIt;
elemento=COMPONENT_create(panel,-1,"CoEDcreate",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Do It!",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  The Proyect ",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,3,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  The Properties ",0);
 return elemento;
}

static tComponentPtr _CfrmC_prop(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,3,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"prop",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,4,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Keymaps        ",0);
 return elemento;
}

static tComponentPtr _CfrmC_keymap(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"keymap",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,5,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Edit Functions ",0);
 return elemento;
}

static tComponentPtr _CfrmC_edf(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,5,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"edf",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC04(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,6,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC04",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Colors         ",0);
 return elemento;
}

static tComponentPtr _CfrmC_color(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,6,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"color",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC05(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,7,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC05",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Message  Box   ",0);
 return elemento;
}

static tComponentPtr _CfrmC_msgs(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,7,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"msgs",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC06(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,8,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC06",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Components     ",0);
 return elemento;
}

static tComponentPtr _CfrmC_comps(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,8,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"comps",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC07(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,9,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC07",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Panel Views    ",0);
 return elemento;
}

static tComponentPtr _CfrmC_panels(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,9,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"panels",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC08(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,10,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC08",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Table Views    ",0);
 return elemento;
}

static tComponentPtr _CfrmC_tables(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,10,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"tables",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_frmEC09(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,11,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC09",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Checking  Edits Views    ",0);
 return elemento;
}

static tComponentPtr _CfrmC_edit(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,11,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"edit",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrmC_ckenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,30,13,3,10};
tComponentPtr  elemento;
tMove move = {
   "CheckFile:",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"ckenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Result ",0);
 return elemento;
}

static tComponentPtr _CfrCo_frmEC00(tPanelPtr panel) {
tChAttrPtr pColor=&miColor4;
tDim pDim ={0,1,1,1,58};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC00",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Compiling The Proyect ",0);
 return elemento;
}

static tComponentPtr _CfrCo_frmEC01(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,3,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC01",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Creating  The Directory     : ",0);
 return elemento;
}

static tComponentPtr _CfrCo_directory(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,3,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"directory",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrCo_frmEC02(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,4,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC02",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Saving & copy the Proyect   : ",0);
 return elemento;
}

static tComponentPtr _CfrCo_saving(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,4,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"saving",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrCo_frmEC03(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,2,5,1,30};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"frmEC03",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Compiling the Proyect       : ",0);
 return elemento;
}

static tComponentPtr _CfrCo_compile(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,35,5,1,10};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
elemento=COMPONENT_create(panel,-1,"compile",0,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"pending",0);
 return elemento;
}

static tComponentPtr _CfrCo_ckenter(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,30,13,3,10};
tComponentPtr  elemento;
tMove move = {
   "CheckFile:",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=RUN_compileFile;
elemento=COMPONENT_create(panel,-1,"ckenter",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"Results",0);
 return elemento;
}

static tComponentPtr _CmnEd_open(tPanelPtr panel) {
tChAttrPtr pColor=&miColor5;
tDim pDim ={1,1,0,3,15};
tComponentPtr  elemento;
tMove move = {
   "101:",
   "",
   ":save",
   ":close",
   "",
   "",
   ":close",
   ":save",
   {"","101:","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_editOpen;
elemento=COMPONENT_create(panel,-1,"open",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"F2 - Open",0);
 return elemento;
}

static tComponentPtr _CmnEd_save(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,16,0,3,15};
tComponentPtr  elemento;
tMove move = {
   "",
   "",
   ":close",
   ":open",
   "",
   "",
   ":open",
   ":close",
   {"","","","","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_editSave;
elemento=COMPONENT_create(panel,-1,"save",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"F3 - Save",0);
COMPONENT_display(elemento,1);
 return elemento;
}

static tComponentPtr _CmnEd_close(tPanelPtr panel) {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,31,0,3,15};
tComponentPtr  elemento;
tMove move = {
   "mnPrincipal:mnPedit",
   "",
   ":open",
   ":save",
   "",
   "",
   ":save",
   ":open",
   {"","","","mnPrincipal:mnPedit","","","","","","","",""},
   ""
   };

_tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
 memset(auxFC,0,sizeof(_tFComponent));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
 memset(auxFA,0,sizeof(_tFActionPanel));
auxFA->enter=PROY_editClose;
elemento=COMPONENT_create(panel,-1,"close",1,&pDim,pColor,
NULL,&move,auxFA,auxFC);
COMPONENT_simpleText(elemento,"F4 - Close",0);
 return elemento;
}

static tViewPtr _Pwelcome() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,0,0,24,80};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"welcome",999,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _Cwelc_welcome(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnPrincipal() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,0,0,3,80};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnPrincipal",0,"",&pDim,pColor,0,&move,auxFA,auxFP);
componente = _CmnPr_mnPproyect(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPgeneral(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPviews(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPcomponents(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPlist(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPedit(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPcompile(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPexit(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnGeneral() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,11,3,11,14};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "mnPrincipal:mnPproyect",
   "mnPrincipal:mnPviews",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnGeneral",2,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnGe_mnGproperties(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnGe_mnGkeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnGe_mnGeditFunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnGe_mnGcolors(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnGe_mnGmsgs(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnProyect() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,1,3,11,9};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "mnPrincipal:mnPexit",
   "mnPrincipal:mnPgeneral",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnProyect",4,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnPr_mnPnew(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPopen(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPclose(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPsave(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnPr_mnPtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnKeymap() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,25,5,5,9};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnGeneral:mnGkeymap",
   "",
   "",
   "",
   "",
   "mnGeneral:mnGkeymap",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnKeymap",3,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnKe_mnKnew(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnKe_mnKchange(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnList() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,44,3,7,14};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPlist",
   "",
   "",
   "",
   "",
   "mnPrincipal:mnPcomponents",
   "mnPrincipal:mnPedit",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnList",2,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnLi_colors(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnLi_views(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnLi_calls(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnMake() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,64,3,7,14};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPcompile",
   "",
   "",
   "",
   "",
   "mnPrincipal:mnPedit",
   "mnPrincipal:mnPexit",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnMake",2,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnMa_check(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnMa_compile(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnMa_run(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pfrmkeymap() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,4,19,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=KEYM_load;
view=PANEL_create(-1,"frmkeymap",1,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _Cfrmk_frmK00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_frmK01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_nkeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmEnter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkenter0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_enter0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkenter1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_enter1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkenter2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_enter2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmOut(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkout0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_out0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkout1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_out1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkout2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_out2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmNext(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etknext0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_next0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etknext1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_next1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etknext2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_next2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmPrevious(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkprevious0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_previous0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkprevious1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_previous1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkprevious2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_previous2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmUp(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkup0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_up0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkup1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_up1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkup2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_up2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmDown(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkdown0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_down0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkdown1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_down1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkdown2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_down2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmLeft(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkleft0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_left0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkleft1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_left1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkleft2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_left2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmRight(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkright0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_right0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkright1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_right1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_etkright2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_right2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_bkmFunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_frmKcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_frmKtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_frmKdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfrmk_frmKenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmEFunction() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,17,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=EDF_load;
view=PANEL_create(-1,"frmEFunction",1,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CfrmE_frmEF00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEF01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFlist(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEF02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEF03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFAlign(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEF04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFMode(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFAdd(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFDel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmE_frmEFenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pcolors() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,25,9,5,9};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnGeneral:mnGcolors",
   "",
   "",
   "",
   "",
   "mnGeneral:mnGcolors",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"colors",3,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _Ccolo_Cnew(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Ccolo_Cchange(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pmsgs() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,10,7,13};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnGeneral:mnGmsgs",
   "",
   "",
   "",
   "",
   "mnGeneral:mnGmsgs",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"msgs",3,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _Cmsgs_information(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cmsgs_warning(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cmsgs_error(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnViews() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={0,21,3,9,9};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPviews",
   "",
   "",
   "",
   "",
   "mnPrincipal:mnPgeneral",
   "mnPrincipal:mnPcomponents",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"mnViews",2,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnVi_Vpanels(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnVi_Vtables(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnVi_Vedit(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnVi_Vcopy(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PPLcomponents() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,4,10,7,14};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"PLcomponents",9,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CPLco_Colabel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CPLco_CoButton(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CPLco_CoCheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CPLco_CoLsButton(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CPLco_CoField(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmNProyect() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,14,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"frmNProyect",2,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmN_frmNP00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNP01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNPname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNP02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNPdescripcion(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNPcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmN_frmNPenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmOProyect() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,14,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"frmOProyect",2,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmO_frmOP00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmO_frmOP01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmO_frmOPname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmO_frmOPcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmO_frmOPenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmSave() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,14,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=PROY_loadSave;
view=PANEL_create(-1,"frmSave",2,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmS_frmSP00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmS_frmSP01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmS_frmSPname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmS_frmSPcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmS_frmSPenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pfttest() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,15,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPproyect",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

view=PANEL_create(-1,"fttest",1,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _Cftte_ett00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_ett01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_term(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_ett02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_ttytest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_fttcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cftte_fttenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmPProyect() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,16,64};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=PROY_loadProperties;
view=PANEL_create(-1,"frmPProyect",1,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CfrmP_frmPP00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPmouse(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPerror(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPferror(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP21(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_chCheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP22(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_chisCheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP23(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_chnoCheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPup(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPdw(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPlf(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPrg(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcul(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcur(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcdl(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcdr(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPup(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPdw(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPlf(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPrg(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPcul(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPcur(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPcdl(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSPcdr(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmSP10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPmainf(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPendf(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPP12(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPinit(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmP_frmPPenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmMsgs() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,16,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=MSG_load;
view=PANEL_create(-1,"frmMsgs",1,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CfrmM_frmMet00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMet01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMtitle(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMet02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMnbuttons(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMet03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMet04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMbutton1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMet05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMbutton2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmM_frmMenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmColor() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,18,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPgeneral",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COLOR_load;
view=PANEL_create(-1,"frmColor",1,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmC_frmC00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmC01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmC02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCbcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmC03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCfcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmC04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCtext(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmCcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pfnpanel() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,19,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=PANEL_load;
view=PANEL_create(-1,"fnpanel",2,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _Cfnpa_npe00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpnombre(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_plevel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet14(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_ptitle(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet15(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pop(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpborder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_fnpet10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_comps(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_npfunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_pamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_npcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_npdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_nptest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnpa_npcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pfnedit() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,3,21,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=EDIT_load;
view=PANEL_create(-1,"fnedit",2,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _Cfned_nee00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fepet00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_epid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fnenombre(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_elevel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet14(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_etitle(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet15(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eop(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eread(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet24(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_efile(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneborder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_fneet05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_ecolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_ekeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_efunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_emove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_eamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_necancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_nedelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_netest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfned_necreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _Pfntable() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,3,21,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=TABLE_load;
view=PANEL_create(-1,"fntable",2,"Describe a TABLE View",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _Cfnta_fntet00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tpid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntnombre(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tlevel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet44(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_ttitle(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet15(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_top(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet34(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet14(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tlcolumn(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tcolumn(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_taddElem(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tdelElem(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tElemens(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tborder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_thcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_fntet25(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tdcolor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_head(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_vline(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_hline(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tkeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tfunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_tamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_ntcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_ntdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_nttest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _Cfnta_ntcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmVCopy() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,17,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPviews",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=VIEW_copyLoad;
view=PANEL_create(-1,"frmVCopy",12,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmV_frmEF00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_frmEF01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_fromView(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_to(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_toView(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_component(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_moves(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_appMoves(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_appCalls(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_cancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmV_enter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmCCopy() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,17,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadCopy;
view=PANEL_create(-1,"frmCCopy",12,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmC_frmEF00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEF01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_fromComponent(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_to(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_toComponent(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_etAttach(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_attach(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_moves(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_appMoves(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_appCalls(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_cancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_enter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PaMove() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,4,20,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","tmselect:","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=MOVE_load;
auxFA->Fn=MOVE_selectHelp;
view=PANEL_create(-1,"aMove",11,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CaMov_em00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_panel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em21(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em31(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em41(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em51(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em61(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em71(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em81(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em83(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em84(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em85(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelout(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelnext(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelprev(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelup(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empaneldown(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelleft(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelright(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelFn0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelF0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelFn1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelF1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelFn2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelF2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelFn3(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_empanelF3(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em12(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em22(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em32(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em42(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em52(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em62(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em72(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em82(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em92(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em93(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em94(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em95(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompout(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompnext(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompprev(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompup(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompdown(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompleft(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompright(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompF0(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompF1(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompF2(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_emcompF3(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_em99(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CaMov_nesave(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfAppCalls() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,4,20,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=FUNC_load;
view=PANEL_create(-1,"fAppCalls",11,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfApp_frmac00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_frmac12(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreCr(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostCr(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreSh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostSh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreAct(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostAct(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreDAct(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostDAct(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreHide(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostHide(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPreDest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACPostDest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfApp_fACsave(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfMove() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,4,19,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=MOVE_loadFunction;
view=PANEL_create(-1,"fMove",11,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfMov_am00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am21(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am31(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am41(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am51(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am61(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am71(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_am81(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amenterfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amoutfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amnextfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amprevfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amupfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amdownfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amleftfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amrightfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_amFnfunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfMov_nasave(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PCoL() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,19,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadLABEL;
auxFA->out=COMP_out;
view=PANEL_create(-1,"CoL",10,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CCoL_col00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_cname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_cpanel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLVisible(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLSelect(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLColor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLBorder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_col03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLText(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLFunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoL_CoLcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PCoB() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,19,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadButton;
auxFA->out=COMP_out;
view=PANEL_create(-1,"CoB",10,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CCoB_cob00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cpanel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBVisible(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBSelect(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBColor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBBorder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_cob03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBText(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBFunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBpmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoB_CoBcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PCoCB() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,19,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadCkButton;
auxFA->out=COMP_out;
view=PANEL_create(-1,"CoCB",10,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CCoCB_cocb00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cbol11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cpanel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBVisible(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBSelect(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBColor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBBorder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBText(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBisCheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb21(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBchcheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBchischeck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_cocb12(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBchncheck(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBFunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBpmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoCB_CoCBcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PCoLB() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,20,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadLsButton;
auxFA->out=COMP_out;
view=PANEL_create(-1,"CoLB",10,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CCoLB_colb00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_cname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_lbol11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_cpanel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb98(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoDisplay(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBColor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBBorder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_colb10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBText(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBData(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBTAdd(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBTdel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBFunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBpmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoLB_CoLBcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PCoED() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,19,4,20,61};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->pre_show=COMP_loadField;
auxFA->out=COMP_out;
view=PANEL_create(-1,"CoED",10,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CCoED_coed00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDid(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_cname(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_edol11(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_cpanel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDVisible(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDSelect(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDAuto(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDSecret(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoLKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoTKeymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDColor(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed34(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDmode(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDBFunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDLEFunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDTEFunction(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDBorder(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDX(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDY(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDWidth(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDHigh(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_coed10(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDText(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDFunctions(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDamove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDpmove(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDcancel(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDdelete(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDtest(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CCoED_CoEDcreate(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrmCheck() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,17,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPcompile",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->post_activate=RUN_check;
view=PANEL_create(-1,"frmCheck",1,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrmC_frmEC00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_prop(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_keymap(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_edf(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC04(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_color(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC05(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_msgs(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC06(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_comps(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC07(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_panels(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC08(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_tables(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_frmEC09(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_edit(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrmC_ckenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PfrCompile() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,10,5,17,60};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "mnPrincipal:mnPcompile",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

auxFP->post_activate=RUN_compile;
view=PANEL_create(-1,"frCompile",1,"",&pDim,pColor,2,&move,auxFA,auxFP);
componente = _CfrCo_frmEC00(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_frmEC01(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_directory(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_frmEC02(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_saving(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_frmEC03(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_compile(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CfrCo_ckenter(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

static tViewPtr _PmnEdit() {
tChAttrPtr pColor=&miColor5;
tDim pDim ={0,0,0,3,80};
tComponentPtr componente;
tViewPtr view;
_tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
memset(auxFP,0,sizeof(_tFPanel));
 _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
memset(auxFA,0,sizeof(_tFActionPanel));
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","101:","","mnPrincipal:mnPedit","","","","","","","",""},
   ""
   };

auxFA->Fn=PROY_editMenu;
view=PANEL_create(-1,"mnEdit",2,"",&pDim,pColor,1,&move,auxFA,auxFP);
componente = _CmnEd_open(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnEd_save(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
componente = _CmnEd_close(view->view.panel); 
PANEL_addComponent(view->view.panel, componente);
return view;
}

tViewPtr _Ttelement() {
tChAttrPtr pColorHead=&miColor4;
tChAttrPtr pColorData=&miColor5;
tDim pDim ={1,1,4,18,18};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_load;
auxFA->enter=SELECT_enter;
auxFA->out=SELECT_out;
view=TABLE_create(20,"telement",1,"",&pDim,pColorHead,pColorData,1,
1,0,0,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"ELEMENT",15);
view->view.table->text=TEXT_new(RESIZE,1,17,18,1);
return view;
}

tViewPtr _Ttmselect() {
tChAttrPtr pColorHead=&miColor4;
tChAttrPtr pColorData=&miColor5;
tDim pDim ={1,35,10,10,33};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_load;
auxFA->enter=SELECT_enter;
view=TABLE_create(20,"tmselect",12,"",&pDim,pColorHead,pColorData,1,
1,0,0,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"SELECT VALUE",27);
view->view.table->text=TEXT_new(RESIZE,1,29,10,1);
return view;
}

tViewPtr _Ttselect() {
tChAttrPtr pColorHead=&miColor4;
tChAttrPtr pColorData=&miColor5;
tDim pDim ={1,35,10,10,33};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_optionLoad;
auxFT->pre_activate=SELECT_optionUpdate;
auxFA->enter=SELECT_optionEnter;
view=TABLE_create(20,"tselect",9,"",&pDim,pColorHead,pColorData,1,
1,0,0,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"SELECT VALUE",27);
view->view.table->text=TEXT_new(RESIZE,1,29,10,1);
return view;
}

tViewPtr _TtlistViews() {
tChAttrPtr pColorHead=&miColor5;
tChAttrPtr pColorData=&miColor1;
tDim pDim ={1,3,3,20,75};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_listViews;
view=TABLE_create(20,"tlistViews",9,"",&pDim,pColorHead,pColorData,2,
1,0,1,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"V. TYPE",8);
TABLE_addColumn(view->view.table,"V. NAME ",25);
TABLE_addColumn(view->view.table,"C. NAME ",25);
TABLE_addColumn(view->view.table,"C. TYPE",9);
view->view.table->text=TEXT_new(RESIZE,1,27,20,4);
return view;
}

tViewPtr _TtlistColors() {
tChAttrPtr pColorHead=&miColor5;
tChAttrPtr pColorData=&miColor1;
tDim pDim ={1,3,3,20,75};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_listColors;
view=TABLE_create(20,"tlistColors",9,"",&pDim,pColorHead,pColorData,2,
1,0,1,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"COLOR",25);
TABLE_addColumn(view->view.table,"FOREGROUND",12);
TABLE_addColumn(view->view.table,"BACKGROUND",12);
TABLE_addColumn(view->view.table,"ESPECIAL",12);
view->view.table->text=TEXT_new(RESIZE,1,27,20,4);
return view;
}

tViewPtr _TtlistCalls() {
tChAttrPtr pColorHead=&miColor5;
tChAttrPtr pColorData=&miColor1;
tDim pDim ={1,3,3,20,75};
tViewPtr view;
tMove move = {
   "",
   "-:",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_listCalls;
view=TABLE_create(20,"tlistCalls",9,"",&pDim,pColorHead,pColorData,2,
1,0,1,&propio,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"VIEW",20);
TABLE_addColumn(view->view.table,"COMPONENT",20);
TABLE_addColumn(view->view.table,"TYPE",12);
TABLE_addColumn(view->view.table,"EVENT",12);
TABLE_addColumn(view->view.table,"FUNCTION",20);
view->view.table->text=TEXT_new(RESIZE,1,22,20,5);
return view;
}

tViewPtr _Ttcomp() {
tChAttrPtr pColorHead=&miColor4;
tChAttrPtr pColorData=&miColor5;
tDim pDim ={1,1,4,18,18};
tViewPtr view;
tMove move = {
   "",
   "mnPrincipal:mnPcomponents",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFTable * auxFT=(_tFTable *)malloc(sizeof(_tFTable));
 memset(auxFT,0,sizeof(_tFTable));
 _tFActionTable * auxFA=(_tFActionTable *)malloc(sizeof(_tFActionTable));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFT->pre_show=SELECT_compLoad;
auxFA->enter=SELECT_compEnter;
view=TABLE_create(-1,"tcomp",2,"",&pDim,pColorHead,pColorData,2,
1,0,0,NULL,&move,auxFA,auxFT);
TABLE_addColumn(view->view.table,"PANEL",13);
TABLE_addColumn(view->view.table,"COMPONENT",13);
view->view.table->text=TEXT_new(RESIZE,1,15,18,2);
return view;
}

static tViewPtr _EXmlFile() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,3,20,75};
tViewPtr view;
tMove move = {
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","mnPrincipal:mnPedit","","","","","","","",""},
   ""
   };

_tFEdit * auxFE=(_tFEdit *)malloc(sizeof(_tFEdit));
 memset(auxFE,0,sizeof(_tFEdit));
 _tFActionEdit * auxFA=(_tFActionEdit *)malloc(sizeof(_tFActionEdit));
 memset(auxFA,0,sizeof(_tFActionTable));
auxFA->Fn=PROY_editPanel;
view=EDIT_create(101,"XmlFile",2,"",&pDim,pColor,1,
1,NULL,&move,auxFA,auxFE);
return view;
}

static tViewPtr _ECheckFile() {
tChAttrPtr pColor=&miColor1;
tDim pDim ={1,3,3,20,75};
tViewPtr view;
tMove move = {
   "mnPrincipal:mnPcompile",
   "mnPrincipal:mnPcompile",
   "",
   "",
   "",
   "",
   "",
   "",
   {"","","","","","","","","","","",""},
   ""
   };

_tFEdit * auxFE=(_tFEdit *)malloc(sizeof(_tFEdit));
 memset(auxFE,0,sizeof(_tFEdit));
 _tFActionEdit * auxFA=(_tFActionEdit *)malloc(sizeof(_tFActionEdit));
 memset(auxFA,0,sizeof(_tFActionTable));
view=EDIT_create(22,"CheckFile",9,"",&pDim,pColor,2,
0,NULL,&move,auxFA,auxFE);
return view;
}


static void MAIN_createColors() {
noColor.colorpair=COLOR_get(0,7);
noColor.attr=0;

miColor1.colorpair=COLOR_get(2,1);
miColor1.attr=0;

miColor1Inv.colorpair=COLOR_get(1,2);
miColor1Inv.attr=0;

miColor2.colorpair=COLOR_get(1,2);
miColor2.attr=0;

miColor2Inv.colorpair=COLOR_get(1,2);
miColor2Inv.attr=0;

miColor3.colorpair=COLOR_get(4,2);
miColor3.attr=2621440;

miColor4.colorpair=COLOR_get(2,7);
miColor4.attr=0;

miColor5.colorpair=COLOR_get(3,4);
miColor5.attr=0;

miColor6.colorpair=COLOR_get(3,1);
miColor6.attr=0;

miColor7.colorpair=COLOR_get(6,2);
miColor7.attr=2097152;

}
typedef struct {
char nombre[MAX_NAME_VIEW];
tViewPtr(* f)();
}tinitView;

static tinitView initView[45] = { 
{"welcome",_Pwelcome},
{"mnPrincipal",_PmnPrincipal},
{"mnGeneral",_PmnGeneral},
{"mnProyect",_PmnProyect},
{"mnKeymap",_PmnKeymap},
{"mnList",_PmnList},
{"mnMake",_PmnMake},
{"frmkeymap",_Pfrmkeymap},
{"frmEFunction",_PfrmEFunction},
{"colors",_Pcolors},
{"msgs",_Pmsgs},
{"mnViews",_PmnViews},
{"PLcomponents",_PPLcomponents},
{"frmNProyect",_PfrmNProyect},
{"frmOProyect",_PfrmOProyect},
{"frmSave",_PfrmSave},
{"fttest",_Pfttest},
{"frmPProyect",_PfrmPProyect},
{"frmMsgs",_PfrmMsgs},
{"frmColor",_PfrmColor},
{"fnpanel",_Pfnpanel},
{"fnedit",_Pfnedit},
{"fntable",_Pfntable},
{"frmVCopy",_PfrmVCopy},
{"frmCCopy",_PfrmCCopy},
{"aMove",_PaMove},
{"fAppCalls",_PfAppCalls},
{"fMove",_PfMove},
{"CoL",_PCoL},
{"CoB",_PCoB},
{"CoCB",_PCoCB},
{"CoLB",_PCoLB},
{"CoED",_PCoED},
{"frmCheck",_PfrmCheck},
{"frCompile",_PfrCompile},
{"mnEdit",_PmnEdit},
{"telement",_Ttelement},
{"tmselect",_Ttmselect},
{"tselect",_Ttselect},
{"tlistViews",_TtlistViews},
{"tlistColors",_TtlistColors},
{"tlistCalls",_TtlistCalls},
{"tcomp",_Ttcomp},
{"XmlFile",_EXmlFile},
{"CheckFile",_ECheckFile}
};


int main(int argc, char * argv[])
{
  tViewPtr view,aux;
  char initProyect[MAX_NAME_VIEW+MAX_COMPONENT_NAME+2]="welcome:welcome";
  char nPanel[MAX_NAME_VIEW+2]="";
  char nComponent[MAX_COMPONENT_NAME+2]="";
  char * paux;
  int i;
  int retorno;

   if ((retorno=MyMain(argc,argv) != 0)) exit (retorno); 
   scrSTD=TUI_init(1,1); 

   MAIN_createColors();
   ERR_printError(1,"errores.txt");
  VISUAL_changeCheck(0,0,0);
  FEDIT_load();
  MSGS_load();
  BACK_init();
  if (!strcmp(initProyect,"")==0)
  {
    paux=initProyect;
     while (*paux!=':'&& *paux!='\0') paux ++;
     if (*paux==':') {
        strncpy(nPanel,initProyect,(paux - initProyect));
        paux++;
        strcpy(nComponent,paux);
     }
  }
  for (i=0;i!=45;i++)
  {
   aux=initView[i].f();
   if (strcmp(nPanel,"")==0)
     {if (i==0) view=aux;}
   else
   {
     if (strcmp(nPanel,initView[i].nombre)==0)
      view = aux;
   }
  }
  VIEW_Loop(view,nComponent);
  TUI_end();
   return MyEnd();
  return 0;
}

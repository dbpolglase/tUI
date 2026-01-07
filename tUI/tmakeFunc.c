#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <text.h>
#include <color.h>
#include <visual.h>
#include <panel.h>
#include <table.h>
#include <edit.h>
#include <calc.h>
#include <lview.h>
#include <view.h>
#include <component.h>
#include <back.h>

#include <tmakeFunc.h>
void PROY_loadProperties(tPanel * panel){
return ;
}
trAction* PROY_close (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_change (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_new (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_test (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_create (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void KEYM_load(tPanel * panel){
return ;
}
trAction* EDF_select (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* EDF_new (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* EDF_delete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COLOR_change (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* MSG_select (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_callFrm (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_callSelect (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_setCallFrm (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_panelChange (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_new (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_open (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_save (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void PROY_loadSave(tPanel * panel){
return ;
}
trAction* PROY_test (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void PROY_replace(tComponent *  component){
return;
}
trAction* PROY_properties (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* MSG_buttons (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* MSG_change (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void MSG_load(tPanel * panel){
return ;
}
trAction* COLOR_test (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COLOR_delete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COLOR_new (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COLOR_load(tPanel * panel){
return ;
}
trAction* VIEW_panelCalls (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void PANEL_load(tPanel * panel){
return ;
}
trAction* COMP_reqMoves (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_preEnterPanel(tComponent *  component){
return;
}
trAction* VIEW_showView (tComponent * component,int key,int Fn){
static trAction action;
 initAction(action)
return &action;
}
void COMP_prePanelEnter(tPanel * panel){
return ;
}
void FUNC_load(tPanel * panel){
return ;
}
void MOVE_load(tPanel * panel){
return ;
}
void COMP_loadLABEL(tPanel * panel){
return ;
}
void COMP_loadBUTTON(tPanel * panel){
return ;
}
void SELECT_load(tTable * table){
return ;
}
trAction* SELECT_enter (tTable * table,int key){
static trAction action;
 initAction(action)
return &action;
}
void SELECT_list(tTable * table){
return ;
}
void SELECT_filePreShow(tEdit * edit){
return ;
}

int MyMain(int argc, char * argv[])
{
return 0;
}

int MyEnd()
{
return 0;
}

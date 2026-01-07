#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include <ncurses.h>

#include <tui.h>

extern SCREEN * scrSTD;
int MyMain(int argc, char * argv[])
{
 return 0;
}
int MyEnd()
{
return 0;
}
int OneTo9(int * caracter) {
 return 0;
}
trAction* PROY_checkOpen (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_exit (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
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
trAction* RUN_execute (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void KEYM_load(tPanel * panel){
return;
}
trAction* KEYM_new (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* TEST_keymap (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_delete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* KEYM_create (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void EDF_load(tPanel * panel){
return;
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
trAction* VIEW_panelChange (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_tableChange (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_editChange (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_copyChange (tComponent * component,int key){
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
void PROY_loadSave(tPanel * panel){
return;
}
trAction* PROY_save (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_test (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void PROY_loadProperties(tPanel * panel){
return;
}
void PROY_replace(tComponent * component){
return;
}
trAction* PROY_propertiesDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void MSG_load(tPanel * panel){
return;
}
trAction* MSG_buttons (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* TEST_msg (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* MSG_change (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COLOR_load(tPanel * panel){
return;
}
trAction* TEST_color (tComponent * component,int key){
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
void PANEL_load(tPanel * panel){
return;
}
trAction* VIEW_panelComps (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_panelCalls (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_panelMove (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_panelDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* TEST_panel (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_panelDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void EDIT_load(tPanel * panel){
return;
}
trAction* COMP_selectKEYM (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_deselectKEYM(tComponent * component){
return;
}
trAction* VIEW_editDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* TEST_edit (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_editDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void TABLE_load(tPanel * panel){
return;
}
trAction* COMP_addTableColumn (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_delTableColumn (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_selTableColumn (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_tableDelete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* TEST_table (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* VIEW_tableDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void VIEW_copyLoad(tPanel * panel){
return;
}
trAction* VIEW_copyDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadCopy(tPanel * panel){
return;
}
void MOVE_load(tPanel * panel){
return;
}
trAction* MOVE_selectHelp (tComponent * component,int key,int Fn){
static trAction action;
 initAction(action);
return &action;
}
trAction* MOVE_enterPanel (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_preEnterPanel(tComponent * component){
return;
}
trAction* MOVE_save (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void FUNC_load(tPanel * panel){
return;
}
trAction* FUNC_save (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void MOVE_loadFunction(tPanel * panel){
return;
}
trAction* MOVE_saveFunction (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadLABEL(tPanel * panel){
return;
}
trAction* COMP_out (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_reqCalls (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_delete (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_labelDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadButton(tPanel * panel){
return;
}
trAction* COMP_Visible (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_reqMoves (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_buttonDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadCkButton(tPanel * panel){
return;
}
trAction* COMP_ckbuttonDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadLsButton(tPanel * panel){
return;
}
trAction* COMP_lbData (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_addList (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_delList (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* COMP_lsbuttonDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void COMP_loadField(tPanel * panel){
return;
}
void COMP_deselectEdFunc(tComponent * component){
return;
}
trAction* COMP_fieldDoIt (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void RUN_check(tPanel * panel){
return;
}
void RUN_compile(tPanel * panel){
return;
}
trAction* RUN_compileFile (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_editMenu (tComponent * component,int key,int Fn){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_editOpen (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_editSave (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_editClose (tComponent * component,int key){
static trAction action;
 initAction(action);
return &action;
}
void SELECT_load(tTable * table){
return;
}
trAction* SELECT_enter (tTable * table,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* SELECT_out (tTable * table,int key){
static trAction action;
 initAction(action);
return &action;
}
void SELECT_optionLoad(tTable * table){
return;
}
void SELECT_optionUpdate(tTable * table){
return;
}
trAction* SELECT_optionEnter (tTable * table,int key){
static trAction action;
 initAction(action);
return &action;
}
void SELECT_listViews(tTable * table){
return;
}
void SELECT_listColors(tTable * table){
return;
}
void SELECT_listCalls(tTable * table){
return;
}
void SELECT_compLoad(tTable * table){
return;
}
trAction* SELECT_compEnter (tTable * table,int key){
static trAction action;
 initAction(action);
return &action;
}
trAction* PROY_editPanel (tEdit * edit,int key,int Fn){
static trAction action;
 initAction(action);
return &action;
}

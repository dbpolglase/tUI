#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <tBasic.h>
#include <msg.h>
#include <tparser.h>
#include <tproyect.h>
#include <tedf.h>
#include <tcolor.h>
#include <tmsg.h>
#include <tkeymap.h>
#include <tview.h>
#include <tprintXml.h>

#define INI_XML "<?xml version=\"1.0\"?>\n\
<TUI xmlns:tui=\"http://tui\">\n"

#define FIN_XML "</TUI>"
#define INI_PROYECT  "\t<Proyect>\n"
#define FIN_PROYECT  "\t</Proyect>\n"
#define NAME_PROYECT  "\t\t<Name>%s</Name>\n"
#define DESC_PROYECT  "\t\t<Description>%s</Description>\n"
#define MAIN_PROYECT  "\t\t<Main>%s</Main>\n"
#define END_PROYECT  "\t\t<End>%s</End>\n"
#define INIT_PROYECT  "\t\t<Init>%s</Init>\n"
#define INI_PROPERTIES  "\t\t<Properties>\n"
#define END_PROPERTIES  "\t\t</Properties>\n"
#define PROP_MOUSE  "\t\t\t<Mouse/>\n"
#define PROP_COLOR  "\t\t\t<Color/>\n"
#define PROP_ERROR  "\t\t\t<Error>%s</Error>\n"
#define PROP_CHECK "\t\t\t<Check chCheck=\"%d\" chIsCheck=\"%d\" chNoCheck=\"%d\" />\n"
#define PROP_BORDER "\t\t\t<Borders Up=\"%d\" Dw=\"%d\" Lf=\"%d\" Rg=\"%d\" Cul=\"%d\" Cur=\"%d\" Cdl=\"%d\" Cdr=\"%d\"/>\n"
#define PROP_SBORDER "\t\t\t<SBorders Up=\"%d\" Dw=\"%d\" Lf=\"%d\" Rg=\"%d\" Cul=\"%d\" Cur=\"%d\" Cdl=\"%d\" Cdr=\"%d\"/>\n"

#define INI_CHECKEDIT "\t<checksEdit>\n"
#define FIN_CHECKEDIT "\t</checksEdit>\n"
#define CHECKEDIT "\t\t<checkEdit Name=\"%s\" Align=\"%s\" Mode=\"%s\" />\n"

#define INI_COLORS "\t<Colors>\n"
#define FIN_COLORS "\t</Colors>\n"
#define COLOR "\t\t<Color Name=\"%s\" foreground=\"%d\" background=\"%d\" attr=\"%s\"/>\n"


#define INI_KEYMAPS "\t<Keymaps>\n"
#define FIN_KEYMAPS "\t</Keymaps>\n"
#define INI_KEYMAP "\t\t<Keymap Name=\"%s\">\n"
#define FIN_KEYMAP "\t\t</Keymap>\n"
#define KEYMAP "\t\t<%s ch1=\"%d\" ch2=\"%d\" ch3=\"%d\"/>\n"
#define KEYMAP_Fn "\t\t<Fn/>\n"

#define INI_MSGS "\t<Msgs>\n"
#define FIN_MSGS "\t</Msgs>\n"

#define INI_MSG "\t<Msg type=\"%s\" nroButtons=\"%d\">\n"
#define FIN_MSG "\t</Msg>\n"
#define MSG_TITLE "\t\t<Title>%s</Title>\n"
#define MSG_COLOR "\t\t<Color>%s</Color>\n"
#define MSG_INI_BUTTON "\t\t<Buttons>\n"
#define MSG_BUTTON1 "\t\t\t<Button1>%s</Button1>\n"
#define MSG_BUTTON2 "\t\t\t<Button2>%s</Button2>\n"
#define MSG_FIN_BUTTON "\t\t</Buttons>\n"


#define INI_PANELS "\t<Panels>\n"
#define INI_PANEL "\t\t<Panel Id=\"%d\" Name=\"%s\" opToMade=\"%s\" Level=\"%d\">\n"
#define FIN_PANEL "\t\t</Panel>\n"
#define PANEL_TITLE "\t\t<Title>%s</Title>\n"
#define PANEL_COLOR "\t\t\t<Color>%s</Color>\n"
#define PANEL_DIMENSION "\t\t\t<Dimension border=\"%d\" x=\"%d\" y=\"%d\" high=\"%d\" width=\"%d\"/>\n"
#define PANEL_INI_FPanel "\t\t\t<FPanel "
#define PANEL_FIN_FPanel "/>\n"
#define PANEL_INI_FAction "\t\t\t<FAction "
#define PANEL_FIN_FAction "/>\n"
#define FIN_PANELS "\t</Panels>\n"
#define PANEL_INI_Move "\t\t\t<Move "
#define PANEL_FIN_Move "/>\n"

#define INI_TABLES "\t<Tables>\n"
#define INI_TABLE "\t\t<Table Id=\"%d\" Name=\"%s\" opToMade=\"%s\" Level=\"%d\">\n"
#define TABLE_STYLE "\t\t<Style %s %s %s %s %s />\n"
#define INI_TABLE_ELEMENT "\t\t<Elements>\n"
#define TABLE_ELEMENT "\t\t\t<Element size=\"%d\">%s</Element>\n"
#define FIN_TABLE_ELEMENT "\t\t</Elements>\n"
#define TABLE_TITLE "\t\t<Title>%s</Title>\n"
#define TABLE_MAPKEY "\t\t<Keymap>%s</Keymap>\n"

#define TABLE_DIMENSION "\t\t<Dimension border=\"%d\" x=\"%d\" y=\"%d\" high=\"%d\" width=\"%d\"/>\n"
#define FIN_TABLE "\t\t</Table>\n"
#define FIN_TABLES "\t</Tables>\n"
#define TABLE_INI_FTable "\t\t<FTable "
#define TABLE_FIN_FTable "/>\n"
#define TABLE_INI_FAction "\t\t<FAction "
#define TABLE_FIN_FAction "/>\n"
#define TABLE_INI_Move "\t\t<Move "
#define TABLE_FIN_Move "/>\n"

#define INI_EDITS "\t<Edits>\n"
#define FIN_EDITS "\t</Edits>\n"

#define INI_EDIT "\t\t<Edit Name=\"%s\" opToMade=\"%s\" Level=\"%d\" Id=\"%d\" "
#define FIN_EDIT "\t\t</Edit>\n" 
#define EDIT_COLOR "\t\t<Color>%s</Color>\n"
#define EDIT_TITLE "\t\t<Title>%s</Title>\n"
#define EDIT_MAPKEY "\t\t<Keymap>%s</Keymap>\n"
#define EDIT_FILE "\t\t\t<File>%s</File>\n"
#define EDIT_DIMENSION "\t\t<Dimension border=\"%d\" x=\"%d\" y=\"%d\" high=\"%d\" width=\"%d\"/>\n"
#define EDIT_INI_FEdit "\t\t<FEdit "
#define EDIT_FIN_FEdit "/>\n"
#define EDIT_INI_FAction "\t\t<FAction "
#define EDIT_FIN_FAction "/>\n"
#define EDIT_INI_Move "\t\t<Move "
#define EDIT_FIN_Move "/>\n"


#define INI_COMPONENTS  "\t\t<Components>\n"
#define FIN_COMPONENTS  "\t\t</Components>\n"
#define INI_COMPONENT  "\t\t<Component Id=\"%d\" Name=\"%s\" Type=\"%s\" "
#define FIN_INI_COMPONENT ">\n"
#define FIN_COMPONENT  "\t\t</Component>\n"
#define INI_COMP_EDIT "\t\t\t<Edit editType=\"%s\" "
#define FIN_COMP_EDIT "/>\n"
#define COMP_COLOR "\t\t\t<Color>%s</Color>\n"
#define COMP_MAPKEY "\t\t\t<Keymap>%s</Keymap>\n"
#define COMP_DIMENSION "\t\t\t<Dimension border=\"%d\" x=\"%d\" y=\"%d\" high=\"%d\" width=\"%d\"/>\n"
#define COMP_TEXT "\t\t\t<Text>%s</Text>\n"
#define COMP_INI_FComponent "\t\t\t<FComponent "
#define COMP_FIN_FComponent "/>\n"
#define COMP_INI_FAction "\t\t\t<FAction "
#define COMP_FIN_FAction "/>\n"
#define COMP_INI_Move "\t\t\t<Move "
#define COMP_FIN_Move "/>\n"

static char * WXML_escapeText(char * text);
static int WXML_proyect(FILE * fd);
static int WXML_checkEditFunctions(FILE * fd);
static char * WXML_encodeATTR(int x);
static char * WXML_encodeOP(int x);
static char * WXML_encodeTYPE(int x);
static char * WXML_encodeALIGN(int x);
static char * WXML_encodeINSERT(int x);
static char * WXML_encodeVisible(int x);
static int WXML_color(FILE * fd);
static int WXML_keymap(FILE * fd);
static int WXML_msgs(FILE * fd);
static int WXML_panels(FILE * fd);
static int WXML_tables(FILE * fd);
static int WXML_edits(FILE * fd);
static int WXML_components(FILE * fd,tXmlCompPanel * components);
static void WXML_move(FILE * fd,tXmlMovePtr move,int tipo);
static void WXML_application(FILE * fd,tXmlFApplication * app);

int WXML_print(char * filename)
{
  FILE * fd;

  fd = fopen(filename,"w");
  if (fd == NULL) {
    ERR_Error(ERR_FILE,"Can't open %s \n",filename);
    return -1;
  }

  fprintf(fd,INI_XML);
  
  WXML_proyect(fd);
  WXML_checkEditFunctions(fd);
  WXML_color(fd);
  WXML_keymap(fd);
  WXML_msgs(fd);
  WXML_panels(fd);
  WXML_tables(fd);
  WXML_edits(fd);
  fprintf(fd,FIN_XML);
  fclose(fd);
  return 0;
}

static int WXML_proyect(FILE * fd)
{
tXmlProyectPtr proyect;
tXmlPropPtr    properties;

  proyect=PROY_getProyect();
  properties=PROY_getProperties();

  fprintf(fd,INI_PROYECT);
  fprintf(fd,NAME_PROYECT,proyect->name);
  fprintf(fd,DESC_PROYECT,WXML_escapeText(proyect->description));
  fprintf(fd,MAIN_PROYECT,properties->mainFunction);
  fprintf(fd,END_PROYECT,properties->endFunction);
  fprintf(fd,INIT_PROYECT,properties->initView);
  fprintf(fd,INI_PROPERTIES);
  if (properties->useMouse)
   fprintf(fd,PROP_MOUSE);
  if (properties->useColor)
   fprintf(fd,PROP_COLOR);
  if (properties->printErrors)
   fprintf(fd,PROP_ERROR,properties->ferrors);

  if ((properties->chCheck != 0 && properties->chCheck != CH_CHECK)  ||
      (properties->chIsCheck != 0 && properties->chIsCheck != CH_IS_CHECK)  ||
      (properties->chNoCheck != 0 && properties->chNoCheck != CH_NO_CHECK))
  fprintf(fd,PROP_CHECK,properties->chCheck,properties->chIsCheck,properties->chNoCheck);

  fprintf(fd,PROP_BORDER,properties->borders[0],properties->borders[1],
     properties->borders[2], properties->borders[3], properties->borders[4],
     properties->borders[5], properties->borders[6], properties->borders[7]);
  fprintf(fd,PROP_SBORDER,properties->sborders[0],properties->sborders[1],
     properties->sborders[2], properties->sborders[3], properties->sborders[4],
     properties->sborders[5], properties->sborders[6], properties->sborders[7]);
  fprintf(fd,END_PROPERTIES);
  fprintf(fd,FIN_PROYECT);

  return 0;
}

static int WXML_checkEditFunctions(FILE * fd)
{
tXmlCEdFunctionPtr cEditFunctions;

  cEditFunctions=EDF_get();
  if (cEditFunctions == NULL) return -1;
  fprintf(fd,INI_CHECKEDIT);
  while (cEditFunctions != NULL) {
   fprintf(fd,CHECKEDIT,cEditFunctions->name,
		WXML_encodeALIGN(cEditFunctions->align),
                WXML_encodeINSERT(cEditFunctions->insert));
   cEditFunctions = cEditFunctions->siguiente;
  }
  fprintf(fd,FIN_CHECKEDIT);

  return 0;
}

static int WXML_color(FILE * fd)
{
tXmlcolor * cColor;

  cColor=COLOR_getXml();

  if (cColor == NULL) return -1;

  fprintf(fd,INI_COLORS);
  while (cColor != NULL) {
   fprintf(fd,COLOR,cColor->name,cColor->fcolor,cColor->bcolor,WXML_encodeATTR(cColor->attr));
   cColor = cColor->siguiente;
  }
  fprintf(fd,FIN_COLORS);

  return 0;
}

static int WXML_msgs(FILE * fd)
{
tXmlMsgs * msgs;

  msgs=MSG_get();

  if (msgs == NULL) return -1;

  fprintf(fd,INI_MSGS);
  if (msgs->msg[M_INFO] != NULL){
   fprintf(fd,INI_MSG,"info",msgs->msg[M_INFO]->nroButtons);
   if (strcmp(msgs->msg[M_INFO]->title,"")!=0)
     fprintf(fd,MSG_TITLE,msgs->msg[M_INFO]->title);
   if (strcmp(msgs->msg[M_INFO]->color,"")!=0)
     fprintf(fd,MSG_COLOR, msgs->msg[M_INFO]->color);
   if (msgs->msg[M_INFO]->nroButtons !=0){
     fprintf(fd,MSG_INI_BUTTON);
     if (strcmp(msgs->msg[M_INFO]->ButtonText1,"") != 0)
      fprintf(fd,MSG_BUTTON1,msgs->msg[M_INFO]->ButtonText1);
     if (msgs->msg[M_INFO]->nroButtons == 2 && strcmp(msgs->msg[M_INFO]->ButtonText2,"") != 0)
      fprintf(fd,MSG_BUTTON2,msgs->msg[M_INFO]->ButtonText2);
     fprintf(fd,MSG_FIN_BUTTON);
   }
   fprintf(fd,FIN_MSG);
  }
  if (msgs->msg[M_WARNING] != NULL){
   fprintf(fd,INI_MSG,"warning",msgs->msg[M_WARNING]->nroButtons);
   if (strcmp(msgs->msg[M_WARNING]->title,"")!=0)
     fprintf(fd,MSG_TITLE,msgs->msg[M_WARNING]->title);
   if (strcmp(msgs->msg[M_WARNING]->color,"")!=0)
     fprintf(fd,MSG_COLOR, msgs->msg[M_WARNING]->color);
   if (msgs->msg[M_WARNING]->nroButtons !=0){
     fprintf(fd,MSG_INI_BUTTON);
     if (strcmp(msgs->msg[M_WARNING]->ButtonText1,"") != 0)
      fprintf(fd,MSG_BUTTON1,msgs->msg[M_WARNING]->ButtonText1);
     if (msgs->msg[M_WARNING]->nroButtons == 2 && strcmp(msgs->msg[M_WARNING]->ButtonText2,"") != 0)
      fprintf(fd,MSG_BUTTON2,msgs->msg[M_WARNING]->ButtonText2);
     fprintf(fd,MSG_FIN_BUTTON);
   }
   fprintf(fd,FIN_MSG);
  }
  if (msgs->msg[M_ERROR] != NULL){
   fprintf(fd,INI_MSG,"error",msgs->msg[M_ERROR]->nroButtons);
   if (strcmp(msgs->msg[M_ERROR]->title,"")!=0)
     fprintf(fd,MSG_TITLE,msgs->msg[M_ERROR]->title);
   if (strcmp(msgs->msg[M_ERROR]->color,"")!=0)
     fprintf(fd,MSG_COLOR, msgs->msg[M_ERROR]->color);
   if (msgs->msg[M_ERROR]->nroButtons !=0){
     fprintf(fd,MSG_INI_BUTTON);
     if (strcmp(msgs->msg[M_ERROR]->ButtonText1,"") != 0)
      fprintf(fd,MSG_BUTTON1,msgs->msg[M_ERROR]->ButtonText1);
     if (msgs->msg[M_ERROR]->nroButtons == 2 && strcmp(msgs->msg[M_ERROR]->ButtonText2,"") != 0)
      fprintf(fd,MSG_BUTTON2,msgs->msg[M_ERROR]->ButtonText2);
     fprintf(fd,MSG_FIN_BUTTON);
   }
   fprintf(fd,FIN_MSG);
  }

  fprintf(fd,FIN_MSGS);

  return 0;
}

static int WXML_keymap(FILE * fd)
{
tXmlMapKeyPtr keymaps;

  keymaps=KEYMAP_get();
  if (keymaps == NULL) return 0;

  fprintf(fd,INI_KEYMAPS);
  while (keymaps != NULL) {
   fprintf(fd,INI_KEYMAP,keymaps->name);
   if (keymaps->mapa.enter[0]!=0 || keymaps->mapa.enter[1] != 0 ||
       keymaps->mapa.enter[2] !=0)
   fprintf(fd,KEYMAP,"Enter",keymaps->mapa.enter[0],
		keymaps->mapa.enter[1],keymaps->mapa.enter[2]);
   if (keymaps->mapa.out[0]!=0 || keymaps->mapa.out[1] != 0 ||
       keymaps->mapa.out[2] !=0)
   fprintf(fd,KEYMAP,"Out", keymaps->mapa.out[0],
		keymaps->mapa.out[1],keymaps->mapa.out[2]);
   if (keymaps->mapa.next[0]!=0 || keymaps->mapa.next[1] != 0 ||
       keymaps->mapa.next[2] !=0)
   fprintf(fd,KEYMAP,"Next", keymaps->mapa.next[0],
		keymaps->mapa.next[1],keymaps->mapa.next[2]);
   if (keymaps->mapa.previous[0]!=0 || keymaps->mapa.previous[1] != 0 ||
       keymaps->mapa.previous[2] !=0)
   fprintf(fd,KEYMAP,"Previous", keymaps->mapa.previous[0],
		keymaps->mapa.previous[1],keymaps->mapa.previous[2]);
   if (keymaps->mapa.up[0]!=0 || keymaps->mapa.up[1] != 0 ||
       keymaps->mapa.up[2] !=0)
   fprintf(fd,KEYMAP,"Up", keymaps->mapa.up[0],
		keymaps->mapa.up[1],keymaps->mapa.up[2]);
   if (keymaps->mapa.down[0]!=0 || keymaps->mapa.down[1] != 0 ||
       keymaps->mapa.down[2] !=0)
   fprintf(fd,KEYMAP,"Down", keymaps->mapa.down[0],
		keymaps->mapa.down[1],keymaps->mapa.down[2]);
   if (keymaps->mapa.left[0]!=0 || keymaps->mapa.left[1] != 0 ||
       keymaps->mapa.left[2] !=0)
   fprintf(fd,KEYMAP,"Left", keymaps->mapa.left[0],
		keymaps->mapa.left[1],keymaps->mapa.left[2]);
   if (keymaps->mapa.right[0]!=0 || keymaps->mapa.right[1] != 0 ||
       keymaps->mapa.right[2] !=0)
   fprintf(fd,KEYMAP,"Right", keymaps->mapa.right[0],
		keymaps->mapa.right[1],keymaps->mapa.right[2]);
   if (keymaps->mapa.back[0]!=0 || keymaps->mapa.back[1] != 0 ||
       keymaps->mapa.back[2] !=0)
   fprintf(fd,KEYMAP,"Back" ,keymaps->mapa.back[0],
		keymaps->mapa.back[1],keymaps->mapa.back[2]);
   if (keymaps->mapa.Fn[0][0] != 0) fprintf(fd,KEYMAP_Fn);
   fprintf(fd,FIN_KEYMAP);
   keymaps = keymaps->siguiente;
  }
  fprintf(fd,FIN_KEYMAPS);

  return 0;
}

static int WXML_panels(FILE * fd)
{
tXmlPanelPtr panels;

  panels=PANEL_get();
  if (panels == NULL) return 0;

  fprintf(fd,INI_PANELS);
  while (panels != NULL) {
   fprintf(fd,INI_PANEL,panels->id,panels->name,WXML_encodeOP(panels->opToMade),panels->level);
   if (!strcmp(panels->title,"")==0)
     fprintf(fd,PANEL_TITLE,panels->title);
   if (!strcmp(panels->visual.color,"")==0)
     fprintf(fd,PANEL_COLOR,panels->visual.color);
   fprintf(fd,PANEL_DIMENSION,panels->visual.dimension.border,
			panels->visual.dimension.x,
			panels->visual.dimension.y,
			panels->visual.dimension.alto,
			panels->visual.dimension.ancho);

   fprintf(fd,PANEL_INI_FPanel); 
   WXML_application(fd,&panels->personalFPanel);
   fprintf(fd,PANEL_FIN_FPanel); 

   fprintf(fd,PANEL_INI_Move);
   WXML_move(fd,&panels->move,0);
   fprintf(fd,PANEL_FIN_Move);

   fprintf(fd,PANEL_INI_FAction);
   WXML_move(fd,&panels->personalAction,1);
   fprintf(fd,PANEL_FIN_FAction);

   WXML_components(fd,panels->elements);

   fprintf(fd,FIN_PANEL);
   panels = panels->siguiente;
  }
  fprintf(fd,FIN_PANELS);

  return 0;
}

static int WXML_components(FILE * fd,tXmlCompPanel * components)
{
 tXmlTextPtr auxText;
 
 if (components != NULL) {
   fprintf(fd,INI_COMPONENTS);
   while (components != NULL){
    fprintf(fd,INI_COMPONENT,components->componente->id,
			components->componente->name,
			WXML_encodeTYPE(components->componente->type));

    if (components->componente->visual.visible != DIS_NORMAL) 
        fprintf(fd," display=\"%s\" ",WXML_encodeVisible(components->componente->visual.visible));

    if (components->componente->type == C_CKBUTTON) {
       if (components->componente->visual.isCheck) 
        fprintf(fd," Check=\"y\" ");
       if ((components->componente->visual.chCheck != CH_CHECK) &&
           (components->componente->visual.chCheck != 0) )
        fprintf(fd," chCheck=\"%c\" ",components->componente->visual.chCheck);
       if ((components->componente->visual.chIsCheck != CH_IS_CHECK) &&
           (components->componente->visual.chIsCheck != 0)) 
        fprintf(fd," chIsCheck=\"%c\" ",components->componente->visual.chIsCheck);
       if ((components->componente->visual.chNoCheck != CH_NO_CHECK) &&
           (components->componente->visual.chNoCheck != 0))
        fprintf(fd," chNoCheck=\"%c\" ",components->componente->visual.chNoCheck);
    }
    fprintf(fd,FIN_INI_COMPONENT);

   if (!strcmp(components->componente->mapkey,"")==0)
     fprintf(fd,COMP_MAPKEY,components->componente->mapkey);

    if (components->componente->type == C_EDIT) {
       fprintf(fd,INI_COMP_EDIT,components->componente->editMode.editFunction);
	if ((components->componente->editMode.chToEDIT != CHAR_TO_EDIT) &&
	    (components->componente->editMode.chToEDIT != 0))
          fprintf(fd," chToEDIT=\"%c\" ",
		components->componente->editMode.chToEDIT);
	if (components->componente->editMode.secret)
          fprintf(fd," secret=\"y\" ");
	if (components->componente->editMode.autoComplet)
          fprintf(fd," auto=\"y\" ");
       fprintf(fd,FIN_COMP_EDIT);
    }

    fprintf(fd,COMP_COLOR,components->componente->visual.color);
    fprintf(fd,COMP_DIMENSION,components->componente->visual.dimension.border,
			components->componente->visual.dimension.x,
			components->componente->visual.dimension.y,
			components->componente->visual.dimension.alto,
			components->componente->visual.dimension.ancho);

    auxText = components->componente->text;
    while (auxText != NULL && auxText->texto != NULL){
      fprintf(fd,COMP_TEXT,WXML_escapeText(auxText->texto));
      auxText = auxText->siguiente;
    }

    fprintf(fd,COMP_INI_Move);
    WXML_move(fd,&components->componente->move,0);
    fprintf(fd,COMP_FIN_Move);
    fprintf(fd,COMP_INI_FAction);
    WXML_move(fd,&components->componente->personalAction,1);
    fprintf(fd,COMP_FIN_FAction);

    fprintf(fd,COMP_INI_FComponent);
    WXML_application(fd,&components->componente->personalFComponent);
    fprintf(fd,COMP_FIN_FComponent);
    fprintf(fd,FIN_COMPONENT);
    components = components->siguiente;
   }
   fprintf(fd,FIN_COMPONENTS);
 }
 return 0;
}

static int WXML_tables(FILE * fd)
{
tXmlTablePtr tables;
tXmlElemsTablePtr elements;
char auxBuffer[70];
char auxBuffer2[70];

  tables=TABLE_get();
  if (tables == NULL) return 0;

  fprintf(fd,INI_TABLES);
  while (tables != NULL) {
   fprintf(fd,INI_TABLE,tables->id,tables->name,WXML_encodeOP(tables->opToMade),tables->level);
   if (!strcmp(tables->title,"")==0)
     fprintf(fd,TABLE_TITLE,tables->title);
   if (!strcmp(tables->mapkey,"")==0)
     fprintf(fd,TABLE_MAPKEY,tables->mapkey);

   fprintf(fd,TABLE_DIMENSION,tables->visual.dimension.border,
			tables->visual.dimension.x,
			tables->visual.dimension.y,
			tables->visual.dimension.alto,
			tables->visual.dimension.ancho);

   if (strcmp(tables->visual.color,"") !=0)
    sprintf(auxBuffer,"colorHead=\"%s\" ",tables->visual.color);
   else
    strcpy(auxBuffer,"");

   if (strcmp(tables->visual.colorData,"") !=0)
    sprintf(auxBuffer2,"colorData=\"%s\" ",tables->visual.colorData);
   else
    strcpy(auxBuffer2,"");

   fprintf(fd,TABLE_STYLE,
	(tables->visual.thead?"head=\"1\" ":""),
	(tables->visual.hline?"hLine=\"1\" ":""),
	(tables->visual.vline?"vLine=\"1\" ":""),
	auxBuffer, auxBuffer2);
   elements=tables->elements;
   if (elements != NULL){
    fprintf(fd,INI_TABLE_ELEMENT);
    while (elements!=NULL){
     fprintf(fd,TABLE_ELEMENT,elements->len,elements->title);
     elements=elements->siguiente;
    }
    fprintf(fd,FIN_TABLE_ELEMENT);
   }

   fprintf(fd,TABLE_INI_FTable);
   WXML_application(fd,&tables->personalFTable);
   fprintf(fd,TABLE_FIN_FTable);

   fprintf(fd,TABLE_INI_Move);
   WXML_move(fd,&tables->move,0);
   fprintf(fd,TABLE_FIN_Move);
   fprintf(fd,TABLE_INI_FAction);
   WXML_move(fd,&tables->personalAction,1);
   fprintf(fd,TABLE_FIN_FAction);

   fprintf(fd,FIN_TABLE);
   tables = tables->siguiente;
  }
  fprintf(fd,FIN_TABLES);

  return 0;
}

static int WXML_edits(FILE * fd)
{
tXmlEditPtr edits;

  edits=EDIT_get();
  if (edits == NULL) return 0;

  fprintf(fd,INI_EDITS);
  while (edits != NULL) {

   fprintf(fd,INI_EDIT,edits->name,WXML_encodeOP(edits->opToMade),edits->level,edits->id);
   if (edits->visual.eMode==R_ONLY)
    fprintf(fd," ReadOnly=\"s\" ");
   fprintf(fd," >\n");

   if (!strcmp(edits->title,"")==0)
     fprintf(fd,EDIT_TITLE,edits->title);

   if (!strcmp(edits->mapkey,"")==0)
     fprintf(fd,EDIT_MAPKEY,edits->mapkey);

   fprintf(fd,EDIT_DIMENSION,edits->visual.dimension.border,
			edits->visual.dimension.x,
			edits->visual.dimension.y,
			edits->visual.dimension.alto,
			edits->visual.dimension.ancho);

   if (strcmp(edits->visual.color,"") !=0)
     fprintf(fd,EDIT_COLOR,edits->visual.color);

   if (strcmp(edits->fileName,"") !=0)
     fprintf(fd,EDIT_FILE,edits->fileName);

   fprintf(fd,EDIT_INI_FEdit);
   WXML_application(fd,&edits->personalFEdit);
   fprintf(fd,EDIT_FIN_FEdit);
   fprintf(fd,EDIT_INI_Move);
   WXML_move(fd,&edits->move,0);
   fprintf(fd,EDIT_FIN_Move);
   fprintf(fd,EDIT_INI_FAction);
   WXML_move(fd,&edits->personalAction,1);
   fprintf(fd,EDIT_FIN_FAction);

   fprintf(fd,FIN_EDIT);
   edits = edits->siguiente;
 }
 fprintf(fd,FIN_EDITS);

  return 0;
}

static char * WXML_encodeOP(int x){
  switch(x) {
    case OP_NONE: return "none";
    case OP_CREATE: return "create";
    case OP_DESTROY: return "destroy";
    case OP_SHOW: return "show";
    case OP_HIDE: return "hide";
    case OP_ACT: return "activate";
    case OP_DEACT: return "deactivate";
    default:  return "none";
  }
}

static char * WXML_encodeATTR(int x){
  switch (x) {
         case WA_NORMAL: return "WA_NORMAL";
         case WA_STANDOUT: return "WA_STANDOUT";
         case WA_UNDERLINE: return "WA_UNDERLINE";
         case WA_REVERSE: return "WA_REVERSE";
         case WA_BLINK: return "WA_BLINK";
         case WA_DIM: return "WA_DIM";
         case WA_BOLD: return "WA_BOLD";
         case WA_ALTCHARSET: return "WA_ALTCHARSET";
         case WA_INVIS: return "WA_INVIS";
         case WA_PROTECT: return "WA_PROTECT";
         case WA_HORIZONTAL: return "WA_HORIZONTAL";
         case WA_LEFT: return "WA_LEFT";
         case WA_LOW: return "WA_LOW";
         case WA_RIGHT: return "WA_RIGHT";
         case WA_TOP: return "WA_TOP";
         case WA_VERTICAL: return "WA_VERTICAL";
         case WA_ITALIC: return "WA_ITALIC";
    default: return "WA_NORMAL";
  }
}

static char * WXML_encodeTYPE(int x){
  switch (x) {
     case C_LABEL:
            return "label";
     case C_BUTTON:
            return "button";
     case C_CKBUTTON:
            return "ckbutton";
     case C_LSBUTTON:
            return "lsbutton";
     case C_EDIT:
            return "field";
     default:
            return "label";
   }
}

static char * WXML_encodeVisible(int x){
  switch (x) {
     case DIS_NORMAL:
            return "normal";
     case DIS_HIDDEN:
            return "hidden";
     case DIS_NO_SELECT:
            return "nSelect";
     case DIS_OPEN:
            return "open";
     default:
            return "normal";
   }
}

static char * WXML_encodeALIGN(int x){
  switch (x) {
     case A_Left:
            return "left";
     case A_Right:
            return "right";
     default:
            return "left";
   }
}

static char * WXML_encodeINSERT(int x){
  switch (x) {
     case Insert:
            return "insert";
     case Replace:
            return "replace";
     case ReadOnly:
            return "readonly";
     default:
            return "insert";
   }
}

static void WXML_move(FILE * fd,tXmlMovePtr move,int tipo)
{
int i;

   if (strcmp(move->enter,"")!=0)
    fprintf(fd," enter=\"%s\" ",move->enter);
   if (strcmp(move->out,"")!=0)
    fprintf(fd," out=\"%s\" ",move->out);
   if (strcmp(move->next,"")!=0)
    fprintf(fd," next=\"%s\" ",move->next);
   if (strcmp(move->previous,"")!=0)
    fprintf(fd," previous=\"%s\" ",move->previous);
   if (strcmp(move->up,"")!=0)
    fprintf(fd," up=\"%s\" ",move->up);
   if (strcmp(move->down,"")!=0)
    fprintf(fd," down=\"%s\" ",move->down);
   if (strcmp(move->left,"")!=0)
    fprintf(fd," left=\"%s\" ",move->left);
   if (strcmp(move->right,"")!=0)
    fprintf(fd," right=\"%s\" ",move->right);

   if (tipo==0){
     for (i=0;i!=MAX_Fn_KEYS;i++){
      if (strcmp(move->Fn[i],"")!=0)
        fprintf(fd," F%d=\"%s\" ",(i+1),move->Fn[i]);
     }
   }
   else {
     for (i=0;i!=MAX_Fn_KEYS;i++){
      if (strcmp(move->Fn[i],"")!=0){
        fprintf(fd," Fn=\"%s\" ",move->Fn[i]);
        break;
      }
     }
   }

   if (strcmp(move->back,"")!=0)
    fprintf(fd," back=\"%s\" ",move->back);
   if (strcmp(move->other,"")!=0)
    fprintf(fd," other=\"%s\" ",move->other);
}

static void WXML_application(FILE * fd,tXmlFApplication * app)
{
   if (strcmp(app->pre_create,"")!=0)
    fprintf(fd," preCreate=\"%s\" ",app->pre_create);
   if (strcmp(app->post_create,"")!=0)
    fprintf(fd," postCreate=\"%s\" ",app->post_create);
   if (strcmp(app->pre_show,"")!=0)
    fprintf(fd," preShow=\"%s\" ",app->pre_show);
   if (strcmp(app->post_show,"")!=0)
    fprintf(fd," postShow=\"%s\" ",app->post_show);
   if (strcmp(app->pre_hide,"")!=0)
    fprintf(fd," preHide=\"%s\" ",app->pre_hide);
   if (strcmp(app->post_hide,"")!=0)
    fprintf(fd," postHide=\"%s\" ",app->post_hide);
   if (strcmp(app->pre_destroy,"")!=0)
    fprintf(fd," preDestroy=\"%s\" ",app->pre_destroy);
   if (strcmp(app->post_destroy,"")!=0)
    fprintf(fd," postDestroy=\"%s\" ",app->post_destroy);
   if (strcmp(app->pre_activate,"")!=0)
    fprintf(fd," preActivate=\"%s\" ",app->pre_activate);
   if (strcmp(app->post_activate,"")!=0)
    fprintf(fd," postActivate=\"%s\" ",app->post_activate);
   if (strcmp(app->pre_deactivate,"")!=0)
    fprintf(fd," preDeactivate=\"%s\" ",app->pre_deactivate);
   if (strcmp(app->post_deactivate,"")!=0)
    fprintf(fd," postDeactivate=\"%s\" ",app->post_deactivate);
}

static char * WXML_escapeText(char * text)
{
  static char * escText=NULL;
  static int len=0;
  int ltext=0;
  char * pTexto;
  char * pescText;

  ltext = strlen(text);
  if (len < ltext){
     if (escText == NULL)
       escText = (char *)malloc(sizeof(char)*(ltext+100));
     else
       escText = (char *)realloc(escText,sizeof(char)*(ltext+100));
     len=ltext +100;
  }
  memset(escText,'\0',len);
  for (pTexto = text,pescText=escText;*pTexto!='\0';pTexto++) 
  {
    switch(*pTexto){
      case '\n': {*pescText++='\\';*pescText++='n';}
		break;
      case '\t': {*pescText++='\\';*pescText++='t';}
		break;
      default: *pescText++=*pTexto;
    }
  }
  return escText;
}


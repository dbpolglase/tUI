#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <libgen.h>

#include <tBasic.h>
#include <msg.h>
#include <tparser.h>
#include <error.h>
#include <tbuild.h>
#include <tbuildef.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static tXmlPropPtr parseProperties;
static tXmlProyectPtr parseProyect;

static tXmlFuncionesPtr  cabListaFunciones;

static tXmlMapKeyPtr cabKeymaps = NULL;

static tXmlcolorPtr cabColores = NULL;

static tXmlCEdFunctionPtr cabCEdFunctions = NULL;

static tXmlPanelPtr cabPanels = NULL;

static tXmlTablePtr cabTables = NULL;

static tXmlEditPtr cabEdits = NULL;

static tXmlComponentPtr cabComponents = NULL;

static tXmlMsgs Msgs = {{NULL,NULL,NULL}};

static void BUILD_writeIncludes(FILE * fBuild, char * nomFichH);

static void BUILD_writeGlobalVariables(FILE * fBuild);

static void BUILD_writeComponents(FILE * fBuild);

static void BUILD_writeAFunctions(FILE * fBuild, char tipo,
				tXmlFApplication * funciones);

static void BUILD_writeActions(FILE * fBuild,
				char tipo, tXmlMove *acciones);

static void BUILD_writeCompTexts(FILE * fBuild, tXmlTextPtr textos);

static void BUILD_writePanels(FILE * fBuild);

static void BUILD_writeTables(FILE * fBuild);

static void BUILD_writeEdits(FILE * fBuild,FILE * fInterfaz);

static void BUILD_writeCkEDF(FILE * fBuild);

static int BUILD_writeViews(FILE * fBuild);

static void BUILD_writeMain(FILE * fBuild);

static void BUILD_writeCreateColor(FILE * fBuild);
static void BUILD_writeMsgs(FILE * fBuild);
static void BUILD_writeInterfaz(FILE * fInterfaz);
static void BUILD_writePrototipe(FILE * fPrototipe);

int BUILD_do(unsigned short rewrite, 
	     unsigned short interfaz,
	     unsigned short prototipe)
{
  char fileName[MAX_NAME_FILE];
  char fileInterfaz[MAX_NAME_FILE];
  char filePrototipe[MAX_NAME_FILE];
  FILE * fBuild=NULL;
  FILE * fInterfaz=NULL;
  FILE * fPrototipe=NULL;

  parseProyect = PARSER_getProyect();
  parseProperties = PARSER_getProperties();
  cabColores = PARSER_getCabColors();
  cabKeymaps = PARSER_getCabKeymaps();
  cabCEdFunctions = PARSER_getCabCEdFunctions();
  cabComponents= PARSER_getCabComponents();
  cabPanels= PARSER_getCabPanels();
  cabTables= PARSER_getCabTables();
  cabEdits= PARSER_getCabEdits();
  Msgs = PARSER_getMsgs();
  cabListaFunciones = PARSER_getCabFunciones();

  if (strcmp(parseProyect->fileName,"")==0){
    sprintf(fileName,"%s.c",parseProyect->name);
    sprintf(fileInterfaz,"%s/%s_func.h",dirname(parseProyect->fileName),
			parseProyect->name);
    sprintf(filePrototipe,"%s/%s_func.c",dirname(parseProyect->fileName),
			parseProyect->name);
  }
  else{
    sprintf(fileName,"%s_main.c",parseProyect->name);
    sprintf(fileInterfaz,"%s_func.h", parseProyect->name);
    sprintf(filePrototipe,"%s_func.c", parseProyect->name);
  }
    
  if (!rewrite){
    if (access(fileName, F_OK) == 0){
      printf("File %s exists, use -r \n",fileName);
      exit(1);
    }
    if (interfaz) {
      if (access(fileInterfaz, F_OK) == 0){
        printf("File %s exists, use -r \n",fileInterfaz);
        exit(1);
      }
    }
    if (prototipe) {
      if (access(filePrototipe, F_OK) == 0){
        printf("File %s exists, use -r \n",filePrototipe);
        exit(1);
      }
    }
  }
  fBuild = fopen(fileName,"w+");
  if (fBuild == NULL) {
        printf("Can't open %s \n",fileName);
        exit(1);
  }
  if (interfaz) {
   fInterfaz = fopen(fileInterfaz,"w+");
   if (fInterfaz == NULL) {
        printf("Can't open %s \n",fileInterfaz);
        fclose(fBuild);
        exit(1);
   }
 }
 if (prototipe) {
   fPrototipe = fopen(filePrototipe,"w+");
   if (fPrototipe == NULL){
        printf("Can't open %s \n",fileInterfaz);
        fclose(fBuild);
        if (fInterfaz != NULL) fclose(fInterfaz);
        exit(1);
   }
 }

 BUILD_writeIncludes(fBuild,fileInterfaz);
 BUILD_writeGlobalVariables(fBuild);
 BUILD_writeCkEDF(fBuild);
 BUILD_writeMsgs(fBuild);
 BUILD_writeComponents(fBuild);
 BUILD_writePanels( fBuild);
 BUILD_writeTables( fBuild);
 BUILD_writeEdits( fBuild,fInterfaz);
 BUILD_writeMain( fBuild);

 if (fInterfaz) BUILD_writeInterfaz(fInterfaz);
 if (fPrototipe) BUILD_writePrototipe(fPrototipe);
 
 return 0;
}


static void BUILD_writeIncludes(FILE * fBuild,char * nomFichH)
{
char buffer[70];

  sprintf(buffer,"%s_func.h",parseProyect->name);

  fprintf(fBuild,"%s",CABECERA_HEADERS);
  fprintf(fBuild,"#include <%s>\n",buffer);
}

static void BUILD_writeGlobalVariables(FILE * fBuild)
{
  int i;
  tXmlcolor * auxColor;
  tXmlMapKey * auxKeymap;
  auxColor = cabColores;
  auxKeymap = cabKeymaps;

  fprintf(fBuild,"SCREEN * scrSTD;\n");
  fprintf(fBuild,"tChAttr %s;\n","noColor");
  while (auxColor != NULL){
   fprintf(fBuild,"tChAttr %s;\n",auxColor->name);
   auxColor = auxColor->siguiente;
  }

  while (auxKeymap != NULL){
   fprintf(fBuild,"tmapKeys %s ={\n",auxKeymap->name);

   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.enter[0],
		auxKeymap->mapa.enter[1],auxKeymap->mapa.enter[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.out[0],
		auxKeymap->mapa.out[1],auxKeymap->mapa.out[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.next[0],
		auxKeymap->mapa.next[1],auxKeymap->mapa.next[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.previous[0],
		auxKeymap->mapa.previous[1],auxKeymap->mapa.previous[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.up[0],
		auxKeymap->mapa.up[1],auxKeymap->mapa.up[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.down[0],
		auxKeymap->mapa.down[1],auxKeymap->mapa.down[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.left[0],
		auxKeymap->mapa.left[1],auxKeymap->mapa.left[2]);
   fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.right[0],
		auxKeymap->mapa.right[1],auxKeymap->mapa.right[2]);
   fprintf(fBuild," {\n");
   for (i=0;i!=MAX_Fn_KEYS;i++){
    fprintf(fBuild," {%d,%d,%d},\n",auxKeymap->mapa.Fn[i][0],
		auxKeymap->mapa.Fn[i][1],auxKeymap->mapa.Fn[i][2]);
   }
   fprintf(fBuild," },\n");
   fprintf(fBuild," {%d,%d,%d}};\n",auxKeymap->mapa.back[0],
		auxKeymap->mapa.back[1],auxKeymap->mapa.back[2]);
   auxKeymap=auxKeymap->siguiente;
  }
}

static void BUILD_writeComponents(FILE * fBuild)
{
 tXmlComponentPtr aux;
 tXmlTextPtr textos;
 char sname[120];
 char buf[MAX_FUNC_NAME +3]="&";

  aux = cabComponents;

  while (aux != NULL){
    sprintf(sname,"_C%.4s_%s",aux->panelName,aux->name);
    fprintf(fBuild,CRE_COMPONENT_PASO1,sname,aux->visual.color,
                                  aux->visual.dimension.border,
                                  aux->visual.dimension.x,
                                  aux->visual.dimension.y,
                                  aux->visual.dimension.alto,
                                  aux->visual.dimension.ancho);

    fprintf(fBuild,MOVE,aux->move.enter, aux->move.out, aux->move.next,
                aux->move.previous, aux->move.up, aux->move.down,
                aux->move.left, aux->move.right, aux->move.Fn[0],
                aux->move.Fn[1], aux->move.Fn[2], aux->move.Fn[3],
                aux->move.Fn[4], aux->move.Fn[5], aux->move.Fn[6],
                aux->move.Fn[7], aux->move.Fn[8], aux->move.Fn[9],
                aux->move.Fn[10], aux->move.Fn[11], aux->move.back);

    fprintf(fBuild,CRE_COMPONENT_PASO2);


    BUILD_writeAFunctions(fBuild, 'C',&aux->personalFComponent);

    BUILD_writeActions(fBuild, 'C',&aux->personalAction);

    fprintf(fBuild,CRE_COMPONENT_PASO3,aux->id,aux->name,aux->type,(strcmp(aux->mapkey,"")==0?"NULL":strcat(buf,aux->mapkey)));

    if (aux->type == C_EDIT){
     fprintf(fBuild,"tEDIT auxEDIT={%d,%d,%d,%d};\nCOMPONENT_createEdit(elemento,&auxEDIT);\n",aux->editMode.secret,aux->editMode.chToEDIT,aux->editMode.editType,aux->editMode.autoComplet);
    }
    
    if (aux->text != NULL){
       textos=aux->text;
       if (textos->siguiente == NULL) /* Solo 1 texto */{
          fprintf(fBuild,"COMPONENT_simpleText(elemento,\"%s\",0);\n",textos->texto);
       }
       else
         BUILD_writeCompTexts(fBuild,textos);
    }
    else {
      if (aux->type == C_LSBUTTON || aux->type == C_EDIT){
        fprintf(fBuild,"elemento->text=TEXT_new(RESIZE,1,80,%d,1);\n",
						aux->visual.dimension.alto);
      }
      else
        fprintf(fBuild,"COMPONENT_simpleText(elemento,\"\",0);\n");
    }
    
    if (aux->visual.visible != DIS_NORMAL)
        fprintf(fBuild,"COMPONENT_display(elemento,%d);\n",
						aux->visual.visible);
    if (aux->visual.isCheck){
        fprintf(fBuild,"elemento->visual->status.defCheck=1;\n");
        fprintf(fBuild,"if (elemento->text != NULL) elemento->text->check=1;\n");
    }

    if (aux->visual.chCheck !=0 && aux->visual.chCheck != CH_CHECK)
        fprintf(fBuild,"VISUAL_changeChCheck(elemento,'%c');\n",aux->visual.chCheck);
    if (aux->visual.chIsCheck !=0 && aux->visual.chIsCheck != CH_IS_CHECK)
        fprintf(fBuild,"VISUAL_changeIsCheck(elemento,'%c');\n",aux->visual.chIsCheck);
    if (aux->visual.chNoCheck !=0 && aux->visual.chNoCheck != CH_NO_CHECK)
        fprintf(fBuild,"VISUAL_changeNoCheck(elemento,'%c');\n",aux->visual.chNoCheck);

     fprintf(fBuild,CRE_COMPONENT_PASO4);
    aux = aux->siguiente;
  }
}

static void BUILD_writeAFunctions(FILE * fBuild,char tipo,
					tXmlFApplication * funciones)
{
  if (strcmp(funciones->pre_create,"")!=0){
   fprintf(fBuild,"auxF%c->pre_create=%s;\n",tipo,funciones->pre_create);
  }
  if (strcmp(funciones->post_create,"")!=0){
   fprintf(fBuild,"auxF%c->post_create=%s;\n",tipo,funciones->post_create);
  }
  if (strcmp(funciones->pre_show,"")!=0){
   fprintf(fBuild,"auxF%c->pre_show=%s;\n",tipo,funciones->pre_show);
  }
  if (strcmp(funciones->post_show,"")!=0){
   fprintf(fBuild,"auxF%c->post_show=%s;\n",tipo,funciones->post_show);
  }
  if (strcmp(funciones->pre_hide,"")!=0){
   fprintf(fBuild,"auxF%c->pre_hide=%s;\n",tipo,funciones->pre_hide);
  }
  if (strcmp(funciones->post_hide,"")!=0){
   fprintf(fBuild,"auxF%c->post_hide=%s;\n",tipo,funciones->post_hide);
  }
  if (strcmp(funciones->pre_destroy,"")!=0){
   fprintf(fBuild,"auxF%c->pre_destroy=%s;\n",tipo,funciones->pre_destroy);
  }
  if (strcmp(funciones->post_destroy,"")!=0){
   fprintf(fBuild,"auxF%c->post_destroy=%s;\n",tipo,funciones->post_destroy);
  }
  if (strcmp(funciones->pre_activate,"")!=0){
   fprintf(fBuild,"auxF%c->pre_activate=%s;\n",tipo,funciones->pre_activate);
  }
  if (strcmp(funciones->post_activate,"")!=0){
   fprintf(fBuild,"auxF%c->post_activate=%s;\n",tipo,funciones->post_activate);
  }
  if (strcmp(funciones->pre_deactivate,"")!=0){
   fprintf(fBuild,"auxF%c->pre_deactivate=%s;\n",tipo,funciones->pre_deactivate);
  }
  if (strcmp(funciones->post_deactivate,"")!=0){
   fprintf(fBuild,"auxF%c->post_deactivate=%s;\n",tipo,funciones->post_deactivate);
  }
}

static void BUILD_writeActions(FILE * fBuild,
				char tipo, tXmlMove *acciones)
{
  if (strcmp(acciones->enter,"")!=0){
   fprintf(fBuild,"auxFA->enter=%s;\n",acciones->enter);
  }
  if (strcmp(acciones->out,"")!=0){
   fprintf(fBuild,"auxFA->out=%s;\n",acciones->out);
  }
  if (strcmp(acciones->next,"")!=0){
   fprintf(fBuild,"auxFA->next=%s;\n",acciones->next);
  }
  if (strcmp(acciones->previous,"")!=0){
   fprintf(fBuild,"auxFA->previous=%s;\n",acciones->previous);
  }
  if (strcmp(acciones->up,"")!=0){
   fprintf(fBuild,"auxFA->up=%s;\n",acciones->up);
  }
  if (strcmp(acciones->down,"")!=0){
   fprintf(fBuild,"auxFA->down=%s;\n",acciones->down);
  }
  if (strcmp(acciones->left,"")!=0){
   fprintf(fBuild,"auxFA->left=%s;\n",acciones->left);
  }
  if (strcmp(acciones->right,"")!=0){
   fprintf(fBuild,"auxFA->right=%s;\n",acciones->right);
  }
  if (strcmp(acciones->back,"")!=0){
   fprintf(fBuild,"auxFA->back=%s;\n",acciones->back);
  }
  if (strcmp(acciones->other,"")!=0){
   fprintf(fBuild,"auxFA->other=%s;\n",acciones->other);
  }
  if (strcmp(acciones->Fn[0],"")!=0){
     fprintf(fBuild,"auxFA->Fn=%s;\n",acciones->Fn[0]);
  }
}

static void BUILD_writeCompTexts(FILE * fBuild, tXmlTextPtr textos)
{
  int nTextos=0;
  tXmlTextPtr aux;

  aux = textos;
  while(aux!=NULL){nTextos++;aux=aux->siguiente;} 

  fprintf(fBuild,"elemento->text=TEXT_new(RESIZE,0,80,%d,1);\n",nTextos);
  aux=textos;
  while (aux!=NULL) {
    fprintf(fBuild,"TEXT_addSimpleLine(elemento->text,\"%s\");\n",aux->texto);
    aux = aux->siguiente;
  }
}

static void BUILD_writePanels(FILE * fBuild)
{
 tXmlPanelPtr aux = NULL;
 tXmlCompPanel * auxComp;
 char sCompName[120];

  aux = cabPanels;

  while (aux != NULL){
    fprintf(fBuild,CRE_PANEL_PASO1,aux->name,aux->visual.color,
                                  aux->visual.dimension.border,
                                  aux->visual.dimension.x,
                                  aux->visual.dimension.y,
                                  aux->visual.dimension.alto,
                                  aux->visual.dimension.ancho);
    fprintf(fBuild,CRE_PANEL_PASO2);

    fprintf(fBuild,MOVE,aux->move.enter, aux->move.out, aux->move.next,
                aux->move.previous, aux->move.up, aux->move.down,
                aux->move.left, aux->move.right, aux->move.Fn[0],
                aux->move.Fn[1], aux->move.Fn[2], aux->move.Fn[3],
                aux->move.Fn[4], aux->move.Fn[5], aux->move.Fn[6],
                aux->move.Fn[7], aux->move.Fn[8], aux->move.Fn[9],
                aux->move.Fn[10], aux->move.Fn[11], aux->move.back);

    BUILD_writeAFunctions(fBuild, 'P',&aux->personalFPanel);
    BUILD_writeActions(fBuild, 'P',&aux->personalAction);

    fprintf(fBuild,CRE_PANEL_PASO3,aux->id,aux->name,
			aux->level,aux->title,aux->opToMade);

    auxComp = aux->elements;
    while(auxComp != NULL)
    {
      sprintf(sCompName,"_C%.4s_%s",aux->name,auxComp->componente->name);
      fprintf(fBuild,CRE_PANEL_COMPONENT,sCompName);
      auxComp= auxComp->siguiente;
    }

    fprintf(fBuild,CRE_PANEL_PASO4);

    aux = aux->siguiente;
  }
}

static void BUILD_writeMsgs(FILE * fBuild)
{
    fprintf(fBuild,MSG_INI);
    if (Msgs.msg[0]!=NULL){
      fprintf(fBuild,ADD_MSG,Msgs.msg[0]->type,Msgs.msg[0]->title,
              Msgs.msg[0]->nroButtons, Msgs.msg[0]->ButtonText1,
	      Msgs.msg[0]->ButtonText2, Msgs.msg[0]->type,1,Msgs.msg[0]->color);
    }
    if (Msgs.msg[1]!=NULL){
      fprintf(fBuild,ADD_MSG,Msgs.msg[1]->type,Msgs.msg[1]->title,
              Msgs.msg[1]->nroButtons, Msgs.msg[1]->ButtonText1,
	      Msgs.msg[1]->ButtonText2, Msgs.msg[1]->type,1,Msgs.msg[1]->color);
    }
    if (Msgs.msg[2]!=NULL){
      fprintf(fBuild,ADD_MSG,Msgs.msg[2]->type,Msgs.msg[2]->title,
              Msgs.msg[2]->nroButtons, Msgs.msg[2]->ButtonText1,
	      Msgs.msg[2]->ButtonText2, Msgs.msg[2]->type,1,Msgs.msg[2]->color);
    }
    fprintf(fBuild,MSG_FIN);
}

static void BUILD_writeCkEDF(FILE * fBuild)
{
 tXmlCEdFunctionPtr aux = NULL;

  aux = cabCEdFunctions;

  fprintf(fBuild,CHECK_EDIT);
  if (aux != NULL){
    while (aux != NULL){
     fprintf(fBuild,ADD_CHECK_EDIT,aux->tipo,aux->align,aux->insert,aux->name);
     aux=aux->siguiente;
    }
  }
  fprintf(fBuild,CHECK_EDIT_END);
}

static void BUILD_writeTables(FILE * fBuild)
{
 tXmlTablePtr aux = NULL;
 tXmlElemsTable * auxElem;
 char buf[MAX_FUNC_NAME +3]="&";
 int nroColumns=0;
 int maxColumn=0;

  aux = cabTables;

  while (aux != NULL){
    fprintf(fBuild,CRE_TABLE_PASO1,aux->name,aux->visual.color,
				  aux->visual.colorData,
                                  aux->visual.dimension.border,
                                  aux->visual.dimension.x,
                                  aux->visual.dimension.y,
                                  aux->visual.dimension.alto,
                                  aux->visual.dimension.ancho);
    fprintf(fBuild,MOVE,aux->move.enter, aux->move.out, aux->move.next,
                aux->move.previous, aux->move.up, aux->move.down,
                aux->move.left, aux->move.right, aux->move.Fn[0],
                aux->move.Fn[1], aux->move.Fn[2], aux->move.Fn[3],
                aux->move.Fn[4], aux->move.Fn[5], aux->move.Fn[6],
                aux->move.Fn[7], aux->move.Fn[8], aux->move.Fn[9],
                aux->move.Fn[10], aux->move.Fn[11], aux->move.back);

    fprintf(fBuild,CRE_TABLE_PASO2);

    BUILD_writeAFunctions(fBuild, 'T',&aux->personalFTable);

    BUILD_writeActions(fBuild, 'T',&aux->personalAction);

    fprintf(fBuild,CRE_TABLE_PASO3, aux->id,aux->name,aux->level,
		aux->title,aux->opToMade, aux->visual.thead,
		aux->visual.vline,aux->visual.hline,
            (strcmp(aux->mapkey,"")==0?"NULL":strcat(buf,aux->mapkey)));

    auxElem = aux->elements;
    nroColumns=0;
    maxColumn=0;
    while(auxElem != NULL)
    {
      nroColumns++;
      if (auxElem->len > maxColumn) maxColumn=auxElem->len;
      fprintf(fBuild,CRE_TABLE_COLUMN,auxElem->title,auxElem->len);
      auxElem= auxElem->siguiente;
    }

    fprintf(fBuild,CRE_TABLE_PASO4,maxColumn+2,
			aux->visual.dimension.alto,nroColumns);

    aux = aux->siguiente;
 }
}

static void BUILD_writeEdits(FILE * fBuild,FILE * fInterfaz)
{
 tXmlEditPtr aux = NULL;
 char buf[MAX_FUNC_NAME +3]="&";

  aux = cabEdits;

  while (aux != NULL){
    fprintf(fBuild,CRE_EDIT_PASO1,aux->name,aux->visual.color,
                                  aux->visual.dimension.border,
                                  aux->visual.dimension.x,
                                  aux->visual.dimension.y,
                                  aux->visual.dimension.alto,
                                  aux->visual.dimension.ancho);

    fprintf(fBuild,MOVE,aux->move.enter, aux->move.out, aux->move.next,
                aux->move.previous, aux->move.up, aux->move.down,
                aux->move.left, aux->move.right, aux->move.Fn[0],
                aux->move.Fn[1], aux->move.Fn[2], aux->move.Fn[3],
                aux->move.Fn[4], aux->move.Fn[5], aux->move.Fn[6],
                aux->move.Fn[7], aux->move.Fn[8], aux->move.Fn[9],
                aux->move.Fn[10], aux->move.Fn[11], aux->move.back);

    fprintf(fBuild,CRE_EDIT_PASO2);

    BUILD_writeAFunctions(fBuild, 'E',&aux->personalFEdit);

    BUILD_writeActions(fBuild, 'E',&aux->personalAction);

    fprintf(fBuild,CRE_EDIT_PASO3,aux->id,
               aux->name,aux->level,aux->title,aux->opToMade,aux->visual.eMode,
              (strcmp(aux->mapkey,"")==0?"NULL":strcat(buf,aux->mapkey)));

     if (strcmp(aux->fileName,"")!=0) {
       fprintf(fInterfaz,"#define SIZE_%s_LINE  80\n",aux->name);
       fprintf(fInterfaz,"#define MAX_%s_LINES  24\n",aux->name);
       fprintf(fBuild,"EDIT_loadFile(view->view.edit,\"%s\",SIZE_%s_LINE,MAX_%s_LINES);\n", aux->fileName,aux->name,aux->name);
     }
     fprintf(fBuild,CRE_EDIT_PASO4);


    aux = aux->siguiente;
 }
}

static void BUILD_writeMain(FILE * fBuild)
{
 int nViews=0;
 char auxBuffer[100];

  BUILD_writeCreateColor(fBuild);
  nViews = BUILD_writeViews(fBuild);

  if (strcmp(parseProperties->mainFunction,"")==0){
    fprintf(fBuild,MAIN_PASO1,parseProperties->initView,"",
           parseProperties->useColor,parseProperties->useMouse,
	   parseProperties->printErrors,parseProperties->ferrors);
  }
  else
  {
    sprintf(auxBuffer,MAIN_PASO0,parseProperties->mainFunction);
    fprintf(fBuild,MAIN_PASO1,parseProperties->initView,auxBuffer,
              parseProperties->useColor,parseProperties->useMouse,
	      parseProperties->printErrors,parseProperties->ferrors);
  }

  fprintf(fBuild,"  VISUAL_changeCheck(%d,%d,%d);\n",
		parseProperties->chCheck,parseProperties->chIsCheck,
	        parseProperties->chNoCheck);

  if (memcmp(parseProperties->borders,"\0\0\0\0\0\0\0\0",8) != 0)
    fprintf(fBuild,"  VISUAL_changeBorder(0,%d,%d,%d,%d,%d,%d,%d,%d);\n",
              parseProperties->borders[0],parseProperties->borders[1],
              parseProperties->borders[2],parseProperties->borders[3],
              parseProperties->borders[4],parseProperties->borders[5],
              parseProperties->borders[6],parseProperties->borders[7]);

  if (memcmp(parseProperties->sborders,"\0\0\0\0\0\0\0\0",8) != 0)
    fprintf(fBuild,"  VISUAL_changeBorder(1,%d,%d,%d,%d,%d,%d,%d,%d);\n",
              parseProperties->sborders[0],parseProperties->sborders[1],
              parseProperties->sborders[2],parseProperties->sborders[3],
              parseProperties->sborders[4],parseProperties->sborders[5],
              parseProperties->sborders[6],parseProperties->sborders[7]);


  fprintf(fBuild,"  FEDIT_load();\n");
  fprintf(fBuild,"  MSGS_load();\n");
  fprintf(fBuild,"  BACK_init();\n");

  if (strcmp(parseProperties->endFunction,"")==0)
    fprintf(fBuild,MAIN_PASO2,nViews,"");
  else
  {
    sprintf(auxBuffer," return %s();",parseProperties->endFunction);
    fprintf(fBuild,MAIN_PASO2,nViews,auxBuffer);
  }
}

static void BUILD_writeCreateColor(FILE * fBuild)
{
  tXmlcolorPtr aux;
  aux = cabColores;

    fprintf(fBuild,FUN_CRE_COLOR_INI);
    if (cabColores !=NULL){
     fprintf(fBuild,FUN_CRE_COLOR, "noColor",0,7,"noColor",0);
     while(aux != NULL) {
      fprintf(fBuild,FUN_CRE_COLOR, aux->name, aux->bcolor,
          aux->fcolor,aux->name,aux->attr);
      aux = aux->siguiente;
     }
    }
    fprintf(fBuild,FUN_CRE_COLOR_FIN);
}

static int BUILD_writeViews(FILE * fBuild)
{
 int nroViews=0,tViews=0;
 tXmlPanelPtr auxP = cabPanels;
 tXmlTablePtr auxT = cabTables;
 tXmlEditPtr auxE = cabEdits;

 while(auxP!=NULL) {nroViews++;auxP=auxP->siguiente;}
 while(auxT!=NULL) {nroViews++;auxT=auxT->siguiente;}
 while(auxE!=NULL) {nroViews++;auxE=auxE->siguiente;}

 tViews = nroViews;

 fprintf(fBuild,INI_VIEW,nroViews);

 auxP=cabPanels;
 while (auxP != NULL) {
   if (nroViews > 1)
    fprintf(fBuild,"{\"%s\",_P%s},\n",auxP->name, auxP->name);
   else
    fprintf(fBuild,"{\"%s\",_P%s}\n",auxP->name,auxP->name);

   nroViews --;
   auxP=auxP->siguiente;
 }
 auxT=cabTables;
 while (auxT != NULL) {
   if (nroViews > 1)
    fprintf(fBuild,"{\"%s\",_T%s},\n",auxT->name,auxT->name);
   else
    fprintf(fBuild,"{\"%s\",_T%s}\n",auxT->name,auxT->name);

   nroViews --;
   auxT=auxT->siguiente;
 }
 auxE=cabEdits;
 while (auxE != NULL) {
   if (nroViews > 1)
    fprintf(fBuild,"{\"%s\",_E%s},\n",auxE->name,auxE->name);
   else
    fprintf(fBuild,"{\"%s\",_E%s}\n",auxE->name,auxE->name);

   nroViews --;
   auxE=auxE->siguiente;
 }

 fprintf(fBuild,"};\n\n");
  return tViews;
}

static void BUILD_writeInterfaz(FILE * fInterfaz)
{
  tXmlFuncionesPtr aux;

  aux = cabListaFunciones;

  fprintf(fInterfaz,"extern SCREEN * scrSTD;\n");
  while (aux!= NULL) {
   switch (aux->tipo){
  	case F_INIT:
          fprintf(fInterfaz,"int %s(int argc, char * argv[]);\n",aux->name);
          break;
	case F_END:
          fprintf(fInterfaz,"int %s();\n",aux->name);
          break;
	case F_EDF:
          fprintf(fInterfaz,"int %s(int * caracter);\n",aux->name);
          break;
	case F_MOV_COMP:
          fprintf(fInterfaz,"trAction* %s (tComponent *,int );\n",aux->name);
          break;
	case F_MOV_COMP_Fn:
          fprintf(fInterfaz,"trAction* %s (tComponent *,int,int );\n",aux->name);
          break;
	case F_MOV_TABLE:
          fprintf(fInterfaz,"trAction* %s (tTable *,int );\n",aux->name);
          break;
	case F_MOV_TABLE_Fn:
          fprintf(fInterfaz,"trAction* %s (tTable *,int,int );\n",aux->name);
          break;
	case F_MOV_EDIT:
          fprintf(fInterfaz,"trAction* %s (tEdit *,int );\n",aux->name);
          break;
	case F_MOV_EDIT_Fn:
          fprintf(fInterfaz,"trAction* %s (tEdit *,int,int );\n",aux->name);
          break;
	case F_CRE_APP_PANEL:
          fprintf(fInterfaz,"void %s(char * panel);\n",aux->name);
          break;
	case F_APP_PANEL:
          fprintf(fInterfaz,"void %s(tPanel * panel);\n",aux->name);
          break;
	case F_CRE_APP_COMP:
          fprintf(fInterfaz,"void %s(char * component);\n",aux->name);
          break;
	case F_APP_COMP:
          fprintf(fInterfaz,"void %s(tComponent * component);\n",aux->name);
          break;
	case F_CRE_APP_TABLE:
          fprintf(fInterfaz,"void %s(char * table);\n",aux->name);
          break;
	case F_APP_TABLE:
          fprintf(fInterfaz,"void %s(tTable * table);\n",aux->name);
          break;
	case F_CRE_APP_EDIT:
          fprintf(fInterfaz,"void %s(char * edit);\n",aux->name);
          break;
	case F_APP_EDIT:
          fprintf(fInterfaz,"void %s(tEdit * edit);\n",aux->name);
          break;
     default:
   }
   aux=aux->siguiente;
  }
}

static void BUILD_writePrototipe(FILE * fPrototipe)
{
  tXmlFuncionesPtr aux;

  aux = cabListaFunciones;

  fprintf(fPrototipe,"%s",CABECERA_HEADERS);
  fprintf(fPrototipe,"extern SCREEN * scrSTD;\n");
  while (aux!= NULL) {
   switch (aux->tipo){
  	case F_INIT:
          fprintf(fPrototipe,
	    "int %s(int argc, char * argv[])\n{\n return 0;\n}\n",aux->name);
          break;
	case F_END:
          fprintf(fPrototipe,"int %s()\n{\nreturn 0;\n}\n",aux->name);
          break;
	case F_EDF:
          fprintf(fPrototipe,"int %s(int * caracter) {\n return 0;\n}\n",aux->name);
          break;
	case F_MOV_COMP:
          fprintf(fPrototipe,"trAction* %s (tComponent * component,int key){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_MOV_COMP_Fn:
          fprintf(fPrototipe,"trAction* %s (tComponent * component,int key,int Fn){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_MOV_TABLE:
          fprintf(fPrototipe,"trAction* %s (tTable * table,int key){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_MOV_TABLE_Fn:
          fprintf(fPrototipe,"trAction* %s (tTable * table,int key,int Fn){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_MOV_EDIT:
          fprintf(fPrototipe,"trAction* %s (tEdit * edit,int key){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_MOV_EDIT_Fn:
          fprintf(fPrototipe,"trAction* %s (tEdit * edit,int key,int Fn){\nstatic trAction action;\n initAction(action);\nreturn &action;\n}\n",aux->name);
          break;
	case F_CRE_APP_PANEL:
          fprintf(fPrototipe,
		"void %s(char * panel){\nreturn;\n}\n",aux->name);
          break;
	case F_APP_PANEL:
          fprintf(fPrototipe,
		"void %s(tPanel * panel){\nreturn;\n}\n",aux->name);
          break;
	case F_CRE_APP_COMP:
          fprintf(fPrototipe,
		"void %s(char * component){\nreturn;\n}\n",aux->name);
          break;
	case F_APP_COMP:
          fprintf(fPrototipe,
		"void %s(tComponent * component){\nreturn;\n}\n",aux->name);
          break;
	case F_CRE_APP_TABLE:
          fprintf(fPrototipe,
		"void %s(char * table){\nreturn;\n}\n",aux->name);
          break;
	case F_APP_TABLE:
          fprintf(fPrototipe,
		"void %s(tTable * table){\nreturn;\n}\n",aux->name);
          break;
	case F_CRE_APP_EDIT:
          fprintf(fPrototipe,
		"void %s(char * edit){\nreturn;\n}\n",aux->name);
          break;
	case F_APP_EDIT:
          fprintf(fPrototipe,
		"void %s(tEdit * edit){\nreturn;\n}\n",aux->name);
          break;
     default:
   }
   aux=aux->siguiente;
  }
}


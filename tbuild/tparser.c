#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <tBasic.h>
#include <msg.h>
#include <tparser.h>
#include <error.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static tXmlFuncionesPtr cabListaFunciones=NULL;
static tXmlFuncionesPtr ultListaFunciones=NULL;

static tXmlProp parseProperties;
static tXmlProyect parseProyect;

static tXmlMapKeyPtr cabKeymaps = NULL;
static tXmlMapKeyPtr ultKeymaps = NULL;

static tXmlcolorPtr cabColores = NULL;
static tXmlcolorPtr ultColores = NULL;

static tXmlCEdFunctionPtr cabCEdFunctions = NULL;
static tXmlCEdFunctionPtr ultCEdFunctions = NULL;

static tXmlPanelPtr cabPanels = NULL;
static tXmlPanelPtr ultPanels = NULL;

static tXmlTablePtr cabTables = NULL;
static tXmlTablePtr ultTables = NULL;

static tXmlEditPtr cabEdits = NULL;
static tXmlEditPtr ultEdits = NULL;

static tXmlComponentPtr cabComponents = NULL;
static tXmlComponentPtr ultComponents = NULL;

static tXmlMsgs Msgs = {{NULL,NULL,NULL}};

static unsigned short tipoEDF=E_PERSONAL+2;

static void PARSER_unescapeText(char * str);
static int PARSER_addListaFuncion(enum E_TIPOF tipo, char * name);
static void PARSER_reset();
static int PARSER_parseTuiFile(char *filename ); 
static int
PARSER_Proyect(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);
static tXmlcolorPtr
PARSER_color(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur); 
static void PARSER_addColor(tXmlcolorPtr color);
static void PARSER_addKeymap(tXmlMapKeyPtr keymap);
static void PARSER_addMsg(tXmlMsgPtr msg);
static void PARSER_addPanel(tXmlPanelPtr panel);
static void PARSER_addTable(tXmlTablePtr table);
static void PARSER_addEdit(tXmlEditPtr edit);
static unsigned int PARSER_decodeATTR(char * x);
static int PARSER_decodeVisible(char * x);
static int PARSER_decodeMsgType(char * x);
static tXmlCEdFunctionPtr
PARSER_CheckEditFunction(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur); 
static void PARSER_addCheckEditFunction(tXmlCEdFunctionPtr CEdFunction);
static tXmlMapKeyPtr
PARSER_keymap(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);
static tXmlMsgPtr
PARSER_msg(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);
static tXmlPanelPtr
PARSER_panel(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur); 
static tXmlComponentPtr
PARSER_component(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur,char * panel);
static int PARSER_decodeType(char * x);
static int PARSER_decodeEditType(char * x);
static int  PARSER_addComponentText(tXmlComponent * component,char * texto);
static void PARSER_addComponentPanel(tXmlPanel *  panel,
					tXmlComponent * componente);
static tXmlTablePtr
PARSER_table(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);
static tXmlEditPtr
PARSER_edit(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);

static tXmlElemsTablePtr
PARSER_elemTable(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur);
static void  PARSER_addElemTable(tXmlTablePtr table,tXmlElemsTablePtr auxElem);

static int PARSER_BuscaEditCheck(char * x);
static int unescape=0;

int PARSER_loadXmlFile(char * fileName,int noEsc)
{
 int error;

    unescape=noEsc;
    
    PARSER_reset();
    tipoEDF=E_PERSONAL+2;

    /* COMPAT: Do not generate nodes for formatting spaces */
    xmlKeepBlanksDefault(0);
 

    error = PARSER_parseTuiFile(fileName);

    xmlCleanupParser();
  return error;
}

tXmlFunciones * PARSER_getCabFunciones(){
  return cabListaFunciones;
}

tXmlFunciones * PARSER_getUltFunciones(){
  return ultListaFunciones;
}

tXmlProyect * PARSER_getProyect(){
   return &parseProyect;
}

tXmlProp * PARSER_getProperties(){
   return &parseProperties;
}

tXmlcolor * PARSER_getCabColors(){
   return cabColores;
}

tXmlcolor * PARSER_getUltColors(){
   return ultColores;
}

tXmlCEdFunctionPtr PARSER_getCabCEdFunctions(){
  return cabCEdFunctions;
}

tXmlCEdFunctionPtr PARSER_getUltCEdFunctions(){
  return ultCEdFunctions;
}

tXmlMapKeyPtr PARSER_getCabKeymaps(){
  return cabKeymaps;
}

tXmlMapKeyPtr PARSER_getUltKeymaps(){
  return ultKeymaps;
}

tXmlPanelPtr PARSER_getCabPanels(){
  return cabPanels;
}

tXmlPanelPtr PARSER_getUltPanels(){
  return ultPanels;
}

tXmlTablePtr PARSER_getCabTables(){
  return cabTables;
}

tXmlTablePtr PARSER_getUltTables(){
  return ultTables;
}

tXmlEditPtr PARSER_getCabEdits(){
  return cabEdits;
}

tXmlEditPtr PARSER_getUltEdits(){
  return ultEdits;
}


tXmlComponentPtr PARSER_getCabComponents(){
  return cabComponents;
}

tXmlComponentPtr PARSER_getUltComponents(){
  return ultComponents;
}

tXmlMsgs  PARSER_getMsgs(){
  return Msgs;
}

static int
PARSER_parseTuiFile(char *filename ) {
    xmlDocPtr doc;
    xmlNsPtr ns;
    xmlNodePtr cur;
    xmlNodePtr cur2;
    int error;
    tXmlcolorPtr auxColor;
    tXmlCEdFunctionPtr auxCEdFunction;
    tXmlMapKeyPtr auxKeymap;
    tXmlMsgPtr auxMsg;
    tXmlPanelPtr auxPanel;
    tXmlTablePtr auxTable;
    tXmlEditPtr auxEdit;

    doc = xmlParseFile(filename);
    if (doc == NULL) return -1;

    /*
     * Check the document is of the right kind
     */
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        ERR_Error(ERR_PARSE,"empty document");
        xmlFreeDoc(doc);
        return -1;
    }
    ns = xmlSearchNsByHref(doc, cur,
            (const xmlChar *) "http://tui");
    if (ns == NULL) {
        ERR_Error(ERR_PARSE,
                "document of the wrong type, TUI Namespace not found\n");
        xmlFreeDoc(doc);
        return -1;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "TUI")) {
        ERR_Error(ERR_PARSE,"document of the wrong type, root node != TUI");
        xmlFreeDoc(doc);
        return -1;
    }

    /*
     * Now, walk the tree.
     */
    cur = cur->xmlChildrenNode;
    while ( cur && xmlIsBlankNode ( cur ) ) {
        cur = cur -> next;
    }
    if ( cur == 0 ) {
        xmlFreeDoc(doc);
        return 0;
    }

    while (cur != NULL)
    {
     if (xmlStrcmp(cur->name, (const xmlChar *) "Proyect") == 0)
     {
       cur2 = cur->xmlChildrenNode;
       error = PARSER_Proyect(doc, ns, cur2);
       if (error < 0) return error;
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "Keymaps") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Keymap")) {
          if ((auxKeymap = PARSER_keymap(doc, ns, cur2))== NULL)
              return -1;
          PARSER_addKeymap(auxKeymap);
        }
        cur2 = cur2->next;
      }
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "Colors") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Color")) {
          if ((auxColor = PARSER_color(doc, ns, cur2))== NULL)
              return -1;
          PARSER_addColor(auxColor);
        }
        cur2 = cur2->next;
      }
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "checksEdit") == 0)
     {
       cur2 = cur->xmlChildrenNode;
       while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "checkEdit"))  {
          if ((auxCEdFunction = PARSER_CheckEditFunction(doc, ns, cur2))== NULL)
              return -1;
          PARSER_addCheckEditFunction(auxCEdFunction);
        }
        cur2 = cur2->next;
       }
     }

     if (xmlStrcmp(cur->name, (const xmlChar *) "Msgs") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Msg")){
          if ((auxMsg = PARSER_msg(doc, ns, cur2))== NULL)
              return -1;
           PARSER_addMsg(auxMsg);
        }
        cur2 = cur2->next;
      }
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "Panels") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Panel")) {
          if ((auxPanel = PARSER_panel(doc, ns, cur2))== NULL)
              return -1;
           PARSER_addPanel(auxPanel);
        }
        cur2 = cur2->next;
      }
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "Tables") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Table")) {
          if ((auxTable = PARSER_table(doc, ns, cur2))== NULL)
              return -1;
           PARSER_addTable(auxTable);
        }
        cur2 = cur2->next;
      }
     }
     if (xmlStrcmp(cur->name, (const xmlChar *) "Edits") == 0)
     {
      cur2 = cur->xmlChildrenNode;
      while (cur2 != NULL) {
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Edit")) {
          if ((auxEdit = PARSER_edit(doc, ns, cur2))== NULL)
              return -1;
           PARSER_addEdit(auxEdit);
        }
        cur2 = cur2->next;
      }
     }

     cur = cur->next;
   }
  return 0;
}


static int
PARSER_Proyect(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
  char * x;
  xmlNodePtr cur2;

    memset(&parseProyect,'\0',sizeof(parseProyect));
    memset(&parseProperties,'\0',sizeof(parseProperties));

    while (cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar *) "Name") == 0)
        {
          x=(char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
          if (x==NULL)
          {
             ERR_Error(ERR_PARSE,"Need a proyect Name \n");
             return -2;
          }
          strcpy(parseProyect.name,x);
       }
       if (xmlStrcmp(cur->name, (const xmlChar *) "Description") == 0)
       {
          x=(char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
          if (x!=NULL)
            strcpy(parseProyect.description,x);
       }

       if (xmlStrcmp(cur->name, (const xmlChar *) "Properties") == 0)
       {
          /* Second level is a list of properties */
          cur2 = cur->xmlChildrenNode;
          while (cur2 != NULL) {
           if (!xmlStrcmp(cur2->name, (const xmlChar *) "Mouse")) 
            parseProperties.useMouse=1;
           if (!xmlStrcmp(cur2->name, (const xmlChar *) "Color"))
            parseProperties.useColor=1;
           if (!xmlStrcmp(cur2->name, (const xmlChar *) "Error")){
              x =(char *)xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
              if (x != NULL){ strcpy(parseProperties.ferrors,x);
                              parseProperties.printErrors=1;
              }
           }
           if (xmlStrcmp(cur2->name, (const xmlChar *) "Check") == 0)
           {
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "chCheck");
              if (x != NULL){
               if (isdigit(x[0]))
                parseProperties.chCheck=atoi(x);
               else
                parseProperties.chCheck=(int)x[0];
              }

              x = (char *)xmlGetProp(cur2, (const xmlChar *) "chIsCheck");
              if (x != NULL){
               if (isdigit(x[0]))
                parseProperties.chIsCheck=atoi(x);
               else
                parseProperties.chIsCheck=(int)x[0];
              }

              x = (char *)xmlGetProp(cur2, (const xmlChar *) "chNoCheck");
              if (x != NULL) {
               if (isdigit(x[0]))
                parseProperties.chNoCheck=atoi(x);
               else
                parseProperties.chNoCheck=(int)x[0];
              }
           }
           if (!xmlStrcmp(cur2->name, (const xmlChar *) "Borders")){
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Lf");
              if (x != NULL)
               parseProperties.borders[0]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Rg");
              if (x != NULL)
               parseProperties.borders[1]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Up");
              if (x != NULL)
               parseProperties.borders[2]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Dw");
              if (x != NULL)
               parseProperties.borders[3]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cul");
              if (x != NULL)
               parseProperties.borders[4]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cur");
              if (x != NULL)
               parseProperties.borders[5]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cdl");
              if (x != NULL)
               parseProperties.borders[6]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cdr");
              if (x != NULL)
               parseProperties.borders[7]=(isdigit(x[0]))?atoi(x):(int)x[0];
           }
           if (!xmlStrcmp(cur2->name, (const xmlChar *) "SBorders")){
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Lf");
              if (x != NULL)
               parseProperties.sborders[0]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Rg");
              if (x != NULL)
               parseProperties.sborders[1]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Up");
              if (x != NULL)
               parseProperties.sborders[2]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Dw");
              if (x != NULL)
               parseProperties.sborders[3]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cul");
              if (x != NULL)
               parseProperties.sborders[4]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cur");
              if (x != NULL)
               parseProperties.sborders[5]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cdl");
              if (x != NULL)
               parseProperties.sborders[6]=(isdigit(x[0]))?atoi(x):(int)x[0];
              x = (char *)xmlGetProp(cur2, (const xmlChar *) "Cdr");
              if (x != NULL)
               parseProperties.sborders[7]=(isdigit(x[0]))?atoi(x):(int)x[0];
           }
          cur2 = cur2->next;
        }
       }

       if (xmlStrcmp(cur->name, (const xmlChar *) "Init") == 0)
       {
          x=(char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
          if (x==NULL)
             strcpy(parseProperties.initView,"");
          else
             strcpy(parseProperties.initView,x);
       }

       if (xmlStrcmp(cur->name, (const xmlChar *) "Main") == 0)
       {
          x=(char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
          if (x==NULL)
             strcpy(parseProperties.mainFunction,"");
          else {
             strcpy(parseProperties.mainFunction,x);
             PARSER_addListaFuncion(F_INIT,x);
          }
       }
       if (xmlStrcmp(cur->name, (const xmlChar *) "End") == 0)
       {
          x=(char *)xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
          if (x==NULL)
             strcpy(parseProperties.endFunction,"");
          else
          {
             strcpy(parseProperties.endFunction,x);
             PARSER_addListaFuncion(F_END,x);
          }
       }
       cur = cur->next;
     }
  return 0;
}

static tXmlcolorPtr
PARSER_color(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
   tXmlcolorPtr ret = NULL;
   xmlChar * x;

    /*
     * allocate the struct
     */
    ret = (tXmlcolorPtr) malloc(sizeof(tXmlcolor));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlcolor));
    }
    memset(ret, 0, sizeof(tXmlcolor));

    /* We don't care what the top level element name is */
    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_DATA, "Color has no name \n");
	free(ret);
        return NULL;
    }
    strncpy(ret->name,(char *)x,MAX_N_COLOR-2);
    x  = xmlGetProp(cur, (const xmlChar *) "foreground");
    if (x == NULL)
        ret->fcolor = 0;
    else
        ret->fcolor = atoi((const char *)x);
    x = xmlGetProp(cur, (const xmlChar *) "background");
    if (x== NULL)
        ret->bcolor = 0;
    else
        ret->bcolor = atoi((const char *)x);
    x = xmlGetProp(cur, (const xmlChar *) "attr");
    if (x == NULL)
        ret->attr=WA_NORMAL;
    else
        ret->attr = PARSER_decodeATTR((char *)x);
    x = xmlGetProp(cur, (const xmlChar *) "attr2");
    if (x != NULL)
        ret->attr |= PARSER_decodeATTR((char*)x);

   return ret;
}

static tXmlCEdFunctionPtr
PARSER_CheckEditFunction(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
    xmlChar * x;
    tXmlCEdFunctionPtr ret;

    ret = (tXmlCEdFunctionPtr) malloc(sizeof(tXmlCEdFunction));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlCEdFunction));
    }

    memset(ret, 0, sizeof(tXmlCEdFunction));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_fatalError(ERR_MEM,"Check Edit has no name \n");
    }
    strcpy(ret->name,(char *)x);
    x = xmlGetProp(cur, (const xmlChar *) "Align");
    if (x == NULL) {
        ret->align=A_Left;
    }
    else{
      if (strcmp((char *)x,"left")==0) ret->align=A_Left;
      else {
       if (strcmp((char *)x,"right")==0) ret->align=A_Right;
        else {
         ERR_Error(ERR_PARSE,"Check Align Edit Function wrong");
         free(ret);
         return NULL;
	}
      }
    }
    x = xmlGetProp(cur, (const xmlChar *) "Mode");
    if (x == NULL) {
        ret->insert=Insert;
    }
    else{
      if (strcmp((char *)x,"insert")==0) ret->insert=Insert;
      else {
       if (strcmp((char *)x,"replace")==0) ret->insert=Replace;
        else {
         ERR_Error(ERR_PARSE,"Check Mode Edit Function wrong");
         free(ret);
         return NULL;
	}
      }
    }
    ret->tipo=tipoEDF; tipoEDF++;
    PARSER_addListaFuncion(F_EDF,ret->name); 
    return ret;
}


static void PARSER_addColor(tXmlcolorPtr color)
{
   color->siguiente=color->anterior=NULL;

   if (cabColores == NULL) {
     cabColores = ultColores = color;
     return;
   }
   
   color->anterior = ultColores;
   ultColores->siguiente=color;
   ultColores = color;
}

static void PARSER_addPanel(tXmlPanelPtr panel)
{
   panel->siguiente=panel->anterior=NULL;
   if (cabPanels == NULL) {
     cabPanels = ultPanels = panel;
     return;
   }
   
   panel->anterior = ultPanels;
   ultPanels->siguiente=panel;
   ultPanels = panel;
}

static void PARSER_addTable(tXmlTablePtr table)
{
   table->siguiente=table->anterior=NULL;
   if (cabTables == NULL) {
     cabTables = ultTables = table;
     return;
   }
   
   table->anterior = ultTables;
   ultTables->siguiente=table;
   ultTables = table;
}

static void PARSER_addEdit(tXmlEditPtr edit)
{
   edit->siguiente=edit->anterior=NULL;
   if (cabEdits == NULL) {
     cabEdits = ultEdits = edit;
     return;
   }
   
   edit->anterior = ultEdits;
   ultEdits->siguiente=edit;
   ultEdits = edit;
}

static void PARSER_addKeymap(tXmlMapKeyPtr keymap)
{
   keymap->siguiente=keymap->anterior=NULL;
   if (cabKeymaps == NULL) {
     cabKeymaps = ultKeymaps = keymap;
     return;
   }
   
   keymap->anterior = ultKeymaps;
   ultKeymaps->siguiente=keymap;
   ultKeymaps = keymap;
}

static void PARSER_addCheckEditFunction(tXmlCEdFunctionPtr CEdFunction)
{
   CEdFunction->siguiente=CEdFunction->anterior=NULL;

   if (cabCEdFunctions == NULL) {
     cabCEdFunctions = ultCEdFunctions = CEdFunction;
     return;
   }
   
   CEdFunction->anterior = ultCEdFunctions;
   ultCEdFunctions->siguiente=CEdFunction;
   ultCEdFunctions = CEdFunction;
}

static void PARSER_addMsg(tXmlMsgPtr msg)
{
  if (Msgs.msg[msg->type] != NULL){
    ERR_Error(ERR_PARSE,"Redefinition of Msg %d",msg->type);
    return;
  }
  Msgs.msg[msg->type]=msg;
}

static unsigned int PARSER_decodeATTR(char * x){

if (strcmp(x,"WA_NORMAL")==0) return       WA_NORMAL;
if (strcmp(x,"WA_STANDOUT")==0) return     WA_STANDOUT;
if (strcmp(x,"WA_UNDERLINE")==0) return    WA_UNDERLINE;
if (strcmp(x,"WA_REVERSE")==0) return      WA_REVERSE;
if (strcmp(x,"WA_BLINK")==0) return        WA_BLINK;
if (strcmp(x,"WA_DIM")==0) return          WA_DIM;
if (strcmp(x,"WA_BOLD")==0) return         WA_BOLD;
if (strcmp(x,"WA_ALTCHARSET")==0) return   WA_ALTCHARSET;
if (strcmp(x,"WA_INVIS")==0) return        WA_INVIS;
if (strcmp(x,"WA_PROTECT")==0) return      WA_PROTECT;
if (strcmp(x,"WA_HORIZONTAL")==0) return   WA_HORIZONTAL;
if (strcmp(x,"WA_LEFT")==0) return         WA_LEFT;
if (strcmp(x,"WA_LOW")==0) return          WA_LOW;
if (strcmp(x,"WA_RIGHT")==0) return        WA_RIGHT;
if (strcmp(x,"WA_TOP")==0) return          WA_TOP;
if (strcmp(x,"WA_VERTICAL")==0) return     WA_VERTICAL;
if (strcmp(x,"WA_ITALIC")==0) return      WA_ITALIC  ;

 return WA_NORMAL;
}

static int PARSER_decodeMsgType(char * x){
   if (strcmp(x,"info") == 0 )  return M_INFO;
   if (strcmp(x,"warning") == 0 )  return M_WARNING;
   if (strcmp(x,"error") == 0 )  return M_ERROR;
  return 0;
}



static tXmlMapKeyPtr
PARSER_keymap(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
   xmlChar * x;
   tXmlMapKeyPtr ret;
   xmlNodePtr cur2;
   int j,fn,mv;int (*i)[3];

    ret = (tXmlMapKeyPtr) malloc(sizeof(tXmlMapKey));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlMapKey));
    }

    memset(ret, 0, sizeof(tXmlMapKey));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_PARSE,"Keymap has no name \n");
        free(ret);
        return NULL;
    }
    strcpy(ret->name,(char *)x);
    cur2 = cur->xmlChildrenNode;
    while (cur2 != NULL) {
        fn=0;mv=0;
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Enter")){ i = &ret->mapa.enter; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Out")) {i=&ret->mapa.out; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Next")){ i=&ret->mapa.next; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Previous")){ i=&ret->mapa.previous; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Up")) {i=&ret->mapa.up; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Down")) {i=&ret->mapa.down; mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Left")) {i=&ret->mapa.left;mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Right")){ i=&ret->mapa.right;mv=1;}
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Fn")) fn=1; 
        if (!xmlStrcmp(cur2->name, (const xmlChar *) "Back")) {i=&ret->mapa.back; mv=1;}

        if (mv) {
          x = xmlGetProp(cur2, (const xmlChar *) "ch1");
          if (x != NULL){
           if (isdigit(x[0]))
                (*i)[0]= atoi((char *)x);
           else {
            ERR_Error(ERR_PARSE," Keymap ch1 not digit ");
            return NULL;
           }
          }
          x = xmlGetProp(cur2, (const xmlChar *) "ch2");
          if (x != NULL){
           if (isdigit(x[0]))
                (*i)[1]= atoi((char *)x);
           else {
            ERR_Error(ERR_PARSE," Keymap ch2 not digit ");
            return NULL;
           }
          }
          x = xmlGetProp(cur2, (const xmlChar *) "ch3");
          if (x != NULL){
           if (isdigit(x[0]))
                (*i)[2]= atoi((char *)x);
           else {
            ERR_Error(ERR_PARSE," Keymap ch3 not digit ");
            return NULL;
           }
          }
        }
        if (fn){
           for (j=0;j!=MAX_Fn_KEYS;j++)
             ret->mapa.Fn[j][0]=KEY_F(j);
        }
       cur2 = cur2->next;
     }
    return ret;
}

static tXmlMsgPtr
PARSER_msg(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
   xmlChar * x;
   tXmlMsgPtr ret;
   xmlNodePtr cur2,cur3;

    ret = (tXmlMsgPtr) malloc(sizeof(tXmlMsg));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlMsg));
    }

    memset(ret, 0, sizeof(tXmlMsg));

    x = xmlGetProp(cur, (const xmlChar *) "type");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Msg has no type ");
        free(ret);
        return NULL;
    }

    ret->type=PARSER_decodeMsgType((char *)x);
    x  = xmlGetProp(cur, (const xmlChar *) "nroButtons");
    if (x == NULL)
        ret->nroButtons=0;
    else {
        ret->nroButtons = atoi((const char *)x);
        if (ret->nroButtons <0 || ret->nroButtons > 2){
          ERR_Error(ERR_PARSE, "Msg nro buttons  wrong %d ",ret->nroButtons);
	  free(ret);
          return NULL;
        }
    }
    cur2 = cur->xmlChildrenNode;
    while (cur2 != NULL) {
        if (xmlStrcmp(cur2->name, (const xmlChar *) "Title") == 0)
        {
            x=xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
            if (x!=NULL){
             strncpy(ret->title,(const char *)x,MAX_MSG_TITLE);
            }
            else {
             strcpy(ret->title,"");
            }
        }
        if (xmlStrcmp(cur2->name, (const xmlChar *) "Color") == 0)
          strncpy(ret->color, 
	    	(char *)xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1),
		MAX_N_COLOR);

        if (xmlStrcmp(cur2->name, (const xmlChar *) "Buttons") == 0)
        {
            cur3 = cur2->xmlChildrenNode;
            while (cur3 != NULL) {
              if (xmlStrcmp(cur3->name, (const xmlChar *) "Button1") == 0)
              {
                x=xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
                if (x!=NULL){
                 strncpy(ret->ButtonText1,(const char *)x,MAX_TEXT_BUTTON);
                 if (unescape) PARSER_unescapeText(ret->ButtonText1);
                }
                else 
                 strncpy(ret->ButtonText1,"",MAX_TEXT_BUTTON);
              }
              if (xmlStrcmp(cur3->name, (const xmlChar *) "Button2") == 0)
              {
                x=xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
                if (x!=NULL) {
                 strncpy(ret->ButtonText2,(const char *)x,MAX_TEXT_BUTTON);
                 if (unescape) PARSER_unescapeText(ret->ButtonText2);
                }
                else
                 strncpy(ret->ButtonText2,"",MAX_TEXT_BUTTON);
              }
              cur3=cur3->next;
            }
        }
        cur2 = cur2->next;
      }
    return(ret);
}

static tXmlPanelPtr
PARSER_panel(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur){
   xmlChar * x;
   tXmlPanelPtr ret;
   xmlNodePtr cur2;
   tXmlComponentPtr auxComponent;
   int i;

    ret = (tXmlPanelPtr) malloc(sizeof(tXmlPanel));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlPanelPtr));
    }
    memset(ret,'\0',sizeof(tXmlPanel));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Panel has no name ");
        free(ret);
        return NULL;
    }
    else
     strcpy(ret->name,(char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "opToMade");
    if (x != NULL)
      ret->opToMade=PARSER_decodeOp((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Id");
    if (x == NULL)
        ret->id = -1;
    else
        ret->id = atoi((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Level");
    if (x == NULL)
        ret->level = 0;
    else
        ret->level = atoi((char *)x);

    ret->elements = NULL;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
      if (xmlStrcmp(cur->name, (const xmlChar *) "Title") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
           strncpy(ret->title,(const char *)x,MAX_MSG_TITLE);
         else
           strcpy(ret->title,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Color") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
            strncpy(ret->visual.color,(char*)x,MAX_N_COLOR);
         else
            strcpy(ret->visual.color,"noColor");
      }

      if (xmlStrcmp(cur->name, (const xmlChar *) "Dimension") == 0)
      {
         x = xmlGetProp(cur, (const xmlChar *) "border");
         if (x!= NULL && x[0]!='0')
          ret->visual.dimension.border = 1;
         else
          ret->visual.dimension.border = 0;
         x = xmlGetProp(cur, (const xmlChar *) "x");
         if (x!=NULL) ret->visual.dimension.x = atoi((char*)x);
         x = xmlGetProp(cur, (const xmlChar *) "y");
         if (x!=NULL) ret->visual.dimension.y = atoi((char*)x);
         x = xmlGetProp(cur, (const xmlChar *) "width");
         if (x!=NULL) ret->visual.dimension.ancho = atoi((char*)x);
         x = xmlGetProp(cur, (const xmlChar *) "high");
         if (x!=NULL) ret->visual.dimension.alto = atoi((char*)x);
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "FPanel") == 0)
      {
  	x= xmlGetProp(cur, (const xmlChar *) "preCreate");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_create,(char *)x);
             PARSER_addListaFuncion(F_CRE_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postCreate");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_create,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preShow");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_show,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postShow");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_show,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preHide");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postHide");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDestroy");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDestroy");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preActivate");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postActivate");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDeactivate");
          if (x!=NULL){ strcpy(ret->personalFPanel.pre_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDeactivate");
          if (x!=NULL){ strcpy(ret->personalFPanel.post_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_PANEL,(char *)x); }
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "FAction") == 0)
        {
  	  x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL){strcpy(ret->personalAction.enter,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
  	  x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL){strcpy(ret->personalAction.out,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL){strcpy(ret->personalAction.next,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL){strcpy(ret->personalAction.previous,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL){strcpy(ret->personalAction.up,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL){strcpy(ret->personalAction.down,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL){strcpy(ret->personalAction.left,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL){strcpy(ret->personalAction.right,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL){strcpy(ret->personalAction.back,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL){strcpy(ret->personalAction.other,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "Fn");
          if (x!=NULL){
             PARSER_addListaFuncion(F_MOV_COMP_Fn,(char *)x); 
           for (i=0;i!=MAX_Fn_KEYS;i++)
            strcpy(ret->personalAction.Fn[i],(char *)x);
          }
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "Move") == 0)
        {
          x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL)strcpy(ret->move.enter,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL) strcpy(ret->move.out,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL) strcpy(ret->move.next,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL)strcpy(ret->move.previous,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL) strcpy(ret->move.up,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL)strcpy(ret->move.down,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL)strcpy(ret->move.left,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL)strcpy(ret->move.right,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL)strcpy(ret->move.back,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL)strcpy(ret->move.other,(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F1");
          if (x!=NULL) strcpy(ret->move.Fn[0],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F2");
          if (x!=NULL) strcpy(ret->move.Fn[1],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F3");
          if (x!=NULL) strcpy(ret->move.Fn[2],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F4");
          if (x!=NULL) strcpy(ret->move.Fn[3],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F5");
          if (x!=NULL) strcpy(ret->move.Fn[4],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F6");
          if (x!=NULL) strcpy(ret->move.Fn[5],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F7");
          if (x!=NULL) strcpy(ret->move.Fn[6],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F8");
          if (x!=NULL) strcpy(ret->move.Fn[7],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F9");
          if (x!=NULL) strcpy(ret->move.Fn[8],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F10");
          if (x!=NULL) strcpy(ret->move.Fn[9],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F11");
          if (x!=NULL) strcpy(ret->move.Fn[10],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F12");
          if (x!=NULL) strcpy(ret->move.Fn[11],(char *)x);
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "Components") == 0)
        {
           cur2 = cur->xmlChildrenNode;
           while (cur2 != NULL) {
           if (xmlStrcmp(cur2->name, (const xmlChar *) "Component") == 0) {
            auxComponent = PARSER_component(doc, ns, cur2,ret->name);
           if (auxComponent != NULL) 
             PARSER_addComponentPanel(ret,auxComponent);
           }
          cur2 = cur2->next;
         }
        }
      cur = cur->next;
    }
  return ret;
}

static tXmlTablePtr
PARSER_table(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur){
   xmlChar * x;
   tXmlTablePtr ret;
   xmlNodePtr cur2;
   tXmlElemsTable  * auxElem;
   int i;

    ret = (tXmlTablePtr) malloc(sizeof(tXmlTable));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlTablePtr));
    }
    memset(ret,'\0',sizeof(tXmlTable));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Table has no name ");
        free(ret);
        return NULL;
    }
    else
     strcpy(ret->name,(char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "opToMade");
    if (x != NULL)
      ret->opToMade=PARSER_decodeOp((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Id");
    if (x == NULL)
        ret->id = -1;
    else
        ret->id = atoi((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Level");
    if (x == NULL)
        ret->level = 0;
    else
        ret->level = atoi((char *)x);

    ret->elements = NULL;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
      if (xmlStrcmp(cur->name, (const xmlChar *) "Keymap") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
           strncpy(ret->mapkey,(const char *)x,MAX_FUNC_NAME);
         else
           strcpy(ret->mapkey,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Title") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
           strncpy(ret->title,(const char *)x,MAX_MSG_TITLE);
         else
           strcpy(ret->title,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Style") == 0)
      {
         x = xmlGetProp(cur, (const xmlChar *) "head");
         if (x!= NULL) ret->visual.thead=1; else ret->visual.thead=0;
         x = xmlGetProp(cur, (const xmlChar *) "vLine");
         if (x!= NULL) ret->visual.vline =1; else ret->visual.vline=0;
         x = xmlGetProp(cur, (const xmlChar *) "hLine");
         if (x!= NULL) ret->visual.hline =1; else ret->visual.hline=0;
         x = xmlGetProp(cur, (const xmlChar *) "colorHead");
         if (x!=NULL)
           strncpy(ret->visual.color,(char *)x,MAX_N_COLOR);
         else
           strcpy(ret->visual.color,"noColor");
         x = xmlGetProp(cur, (const xmlChar *) "colorData");
         if (x!=NULL)
           strncpy(ret->visual.colorData,(char *)x,MAX_N_COLOR);
         else
           strcpy(ret->visual.colorData,"noColor");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Dimension") == 0)
      {
         x = xmlGetProp(cur, (const xmlChar *) "border");
         if (x!= NULL && x[0]!='0')
          ret->visual.dimension.border = 1;
         else
          ret->visual.dimension.border = 0;
         x = xmlGetProp(cur, (const xmlChar *) "x");
         if (x!=NULL) ret->visual.dimension.x = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "y");
         if (x!=NULL) ret->visual.dimension.y = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "width");
         if (x!=NULL) ret->visual.dimension.ancho = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "high");
         if (x!=NULL) ret->visual.dimension.alto = atoi((char *)x);
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "FTable") == 0)
      {
  	x= xmlGetProp(cur, (const xmlChar *) "preCreate");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_create,(char *)x);
             PARSER_addListaFuncion(F_CRE_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postCreate");
          if (x!=NULL) {strcpy(ret->personalFTable.post_create,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preShow");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_show,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postShow");
          if (x!=NULL) {strcpy(ret->personalFTable.post_show,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preHide");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postHide");
          if (x!=NULL) {strcpy(ret->personalFTable.post_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDestroy");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDestroy");
          if (x!=NULL) {strcpy(ret->personalFTable.post_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preActivate");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postActivate");
          if (x!=NULL) {strcpy(ret->personalFTable.post_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDeactivate");
          if (x!=NULL) {strcpy(ret->personalFTable.pre_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDeactivate");
          if (x!=NULL) {strcpy(ret->personalFTable.post_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_TABLE,(char *)x); }
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "FAction") == 0)
      {
  	  x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL){strcpy(ret->personalAction.enter,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
  	  x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL){strcpy(ret->personalAction.out,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL){strcpy(ret->personalAction.next,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL){strcpy(ret->personalAction.previous,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL){strcpy(ret->personalAction.up,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL){strcpy(ret->personalAction.down,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL){strcpy(ret->personalAction.left,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL){strcpy(ret->personalAction.right,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL){strcpy(ret->personalAction.back,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL){strcpy(ret->personalAction.other,(char *)x);
             PARSER_addListaFuncion(F_MOV_TABLE,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "Fn");
          if (x!=NULL){
           PARSER_addListaFuncion(F_MOV_TABLE_Fn,(char *)x); 
           for (i=0;i!=MAX_Fn_KEYS;i++)
            strcpy(ret->personalAction.Fn[i],(char *)x);
          }
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Move") == 0)
      {
          x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL)strcpy(ret->move.enter,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL) strcpy(ret->move.out,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL) strcpy(ret->move.next,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL)strcpy(ret->move.previous,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL) strcpy(ret->move.up,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL)strcpy(ret->move.down,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL)strcpy(ret->move.left,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL)strcpy(ret->move.right,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL)strcpy(ret->move.back,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL)strcpy(ret->move.other,(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F1");
          if (x!=NULL) strcpy(ret->move.Fn[0],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F2");
          if (x!=NULL) strcpy(ret->move.Fn[1],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F3");
          if (x!=NULL) strcpy(ret->move.Fn[2],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F4");
          if (x!=NULL) strcpy(ret->move.Fn[3],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F5");
          if (x!=NULL) strcpy(ret->move.Fn[4],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F6");
          if (x!=NULL) strcpy(ret->move.Fn[5],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F7");
          if (x!=NULL) strcpy(ret->move.Fn[6],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F8");
          if (x!=NULL) strcpy(ret->move.Fn[7],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F9");
          if (x!=NULL) strcpy(ret->move.Fn[8],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F10");
          if (x!=NULL) strcpy(ret->move.Fn[9],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F11");
          if (x!=NULL) strcpy(ret->move.Fn[10],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F12");
          if (x!=NULL) strcpy(ret->move.Fn[11],(char *)x);
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Elements") == 0)
      {
        cur2 = cur->xmlChildrenNode;
        while (cur2 != NULL) {
          if (xmlStrcmp(cur2->name, (const xmlChar *) "Element") == 0) {
            auxElem = PARSER_elemTable(doc, ns, cur2);
            if (auxElem != NULL) PARSER_addElemTable(ret,auxElem);
          }
          cur2 = cur2->next;
        }
      }
      cur = cur->next;
    }
  return ret;
}

static tXmlEditPtr
PARSER_edit(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur){
   xmlChar * x;
   tXmlEditPtr ret;
   int i;

    ret = (tXmlEditPtr) malloc(sizeof(tXmlEdit));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlEditPtr));
    }
    memset(ret,'\0',sizeof(tXmlEdit));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Edit View has no name ");
        free(ret);
    }
    else
     strcpy(ret->name,(char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "opToMade");
    if (x != NULL) ret->opToMade=PARSER_decodeOp((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Id");
    if (x == NULL) ret->id = -1; else ret->id = atoi((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "Level");
    if (x == NULL) ret->level = 0; else ret->level = atoi((char *)x);

    x  = xmlGetProp(cur, (const xmlChar *) "ReadOnly");
    if (x != NULL) ret->visual.eMode=R_ONLY; else ret->visual.eMode=RW;

    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
      if (xmlStrcmp(cur->name, (const xmlChar *) "Keymap") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
           strncpy(ret->mapkey,(const char *)x,MAX_FUNC_NAME);
         else
           strcpy(ret->mapkey,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Color") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
            strncpy(ret->visual.color,(char *)x,MAX_N_COLOR);
         else
            strcpy(ret->visual.color,"noColor");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Title") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
            strncpy(ret->title,(const char *)x,MAX_MSG_TITLE);
         else
            strcpy(ret->title,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "File") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
            strncpy(ret->fileName,(char *)x,MAX_NAME_FILE);
         else
            strcpy(ret->fileName,"");
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Dimension") == 0)
      {
         x = xmlGetProp(cur, (const xmlChar *) "border");
         if (x!= NULL && x[0]!='0')
          ret->visual.dimension.border = 1;
         else
          ret->visual.dimension.border = 0;
         x = xmlGetProp(cur, (const xmlChar *) "x");
         if (x!=NULL) ret->visual.dimension.x = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "y");
         if (x!=NULL) ret->visual.dimension.y = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "width");
         if (x!=NULL) ret->visual.dimension.ancho = atoi((char *)x);
         x = xmlGetProp(cur, (const xmlChar *) "high");
         if (x!=NULL) ret->visual.dimension.alto = atoi((char *)x);
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "FEdit") == 0)
      {
  	x= xmlGetProp(cur, (const xmlChar *) "preCreate");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_create,(char *)x);
             PARSER_addListaFuncion(F_CRE_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postCreate");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_create,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preShow");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_show,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postShow");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_show,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preHide");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postHide");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDestroy");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDestroy");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preActivate");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postActivate");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "preDeactivate");
          if (x!=NULL){ strcpy(ret->personalFEdit.pre_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
        x=xmlGetProp(cur, (const xmlChar *) "postDeactivate");
          if (x!=NULL){ strcpy(ret->personalFEdit.post_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_EDIT,(char *)x); }
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "FAction") == 0)
      {
  	  x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL){strcpy(ret->personalAction.enter,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
  	  x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL){strcpy(ret->personalAction.out,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL){strcpy(ret->personalAction.next,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL){strcpy(ret->personalAction.previous,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL){strcpy(ret->personalAction.up,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL){strcpy(ret->personalAction.down,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL){strcpy(ret->personalAction.left,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL){strcpy(ret->personalAction.right,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL){strcpy(ret->personalAction.back,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL){strcpy(ret->personalAction.other,(char *)x);
             PARSER_addListaFuncion(F_MOV_EDIT,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "Fn");
          if (x!=NULL){
             PARSER_addListaFuncion(F_MOV_EDIT_Fn,(char *)x); 
           for (i=0;i!=MAX_Fn_KEYS;i++)
            strcpy(ret->personalAction.Fn[i],(char *)x);
          }
      }
      if (xmlStrcmp(cur->name, (const xmlChar *) "Move") == 0)
      {
          x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL)strcpy(ret->move.enter,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL) strcpy(ret->move.out,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL) strcpy(ret->move.next,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL)strcpy(ret->move.previous,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL) strcpy(ret->move.up,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL)strcpy(ret->move.down,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL)strcpy(ret->move.left,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL)strcpy(ret->move.right,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL)strcpy(ret->move.back,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL)strcpy(ret->move.other,(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F1");
          if (x!=NULL) strcpy(ret->move.Fn[0],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F2");
          if (x!=NULL) strcpy(ret->move.Fn[1],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F3");
          if (x!=NULL) strcpy(ret->move.Fn[2],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F4");
          if (x!=NULL) strcpy(ret->move.Fn[3],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F5");
          if (x!=NULL) strcpy(ret->move.Fn[4],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F6");
          if (x!=NULL) strcpy(ret->move.Fn[5],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F7");
          if (x!=NULL) strcpy(ret->move.Fn[6],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F8");
          if (x!=NULL) strcpy(ret->move.Fn[7],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F9");
          if (x!=NULL) strcpy(ret->move.Fn[8],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F10");
          if (x!=NULL) strcpy(ret->move.Fn[9],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F11");
          if (x!=NULL) strcpy(ret->move.Fn[10],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F12");
          if (x!=NULL) strcpy(ret->move.Fn[11],(char *)x);
      }
      cur = cur->next;
    }
  return ret;
}

static void  PARSER_addElemTable(tXmlTablePtr table,tXmlElemsTablePtr auxElem){
tXmlElemsTablePtr aux;

  if (table->elements ==NULL) table->elements=auxElem;
  else {
    aux = table->elements;
    while (aux->siguiente !=NULL) aux=aux->siguiente;
    aux->siguiente=auxElem;
  }
}

static tXmlElemsTablePtr
PARSER_elemTable(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur){
 tXmlElemsTablePtr ret;
 xmlChar * x;

  ret = (tXmlElemsTablePtr) malloc(sizeof(tXmlElemsTable));
  if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlElemsTable));
  }
  memset(ret,'\0',sizeof(tXmlElemsTable));
  ret->siguiente=NULL;
  ret->len=0;
  x=xmlGetProp(cur, (const xmlChar *) "size");
  if (x!=NULL) ret->len=atoi((char *)x); 
  x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
  if (x!=NULL){
       strncpy(ret->title,(char *)x,MAX_VIEW_TITLE);
       if (unescape) PARSER_unescapeText(ret->title);
  }
  else strcpy(ret->title,"");

  if (ret->len==0) ret->len=strlen(ret->title);

  return ret;
}

static tXmlComponentPtr
PARSER_component(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur,char * panel){
   xmlChar * x;
   tXmlComponentPtr ret;
   int i;

    ret = (tXmlComponent *) malloc(sizeof(tXmlComponent));
    if (ret == NULL) {
        ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlComponent));
    }
    memset(ret,'\0',sizeof(tXmlComponent));

    x = xmlGetProp(cur, (const xmlChar *) "Name");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Component has no name \n");
	free(ret);
        return NULL;
    }
    else
     strcpy(ret->name,(char *)x);

    strcpy(ret->panelName,panel);
    x = xmlGetProp(cur, (const xmlChar *) "Type");
    if (x == NULL) {
        ERR_Error(ERR_PARSE, "Component has no Type ");
	free(ret);
        return NULL;
    }

    ret->type = PARSER_decodeType((char *)x);
    if (ret->type == -1){
        ERR_Error(ERR_PARSE, "Wrong type %s ",x);
	free(ret);
        return NULL;
    }
    ret->visual.visible = DIS_NORMAL;
    x = xmlGetProp(cur, (const xmlChar *) "display");
    if (x!=NULL)
     ret->visual.visible = PARSER_decodeVisible((char *)x);
    
    ret->visual.chCheck = 0;
    x = xmlGetProp(cur, (const xmlChar *) "chCheck");
    if (x != NULL) ret->visual.chCheck = x[0];

    ret->visual.chIsCheck = 0;
    x = xmlGetProp(cur, (const xmlChar *) "chIsCheck");
    if (x != NULL) ret->visual.chIsCheck = x[0];

    ret->visual.chNoCheck = 0;
    x = xmlGetProp(cur, (const xmlChar *) "chNoCheck");
    if (x != NULL) ret->visual.chNoCheck = x[0];

    x = xmlGetProp(cur, (const xmlChar *) "Check");
    if (x != NULL) ret->visual.isCheck=1;

    ret->id=-1;
    x  = xmlGetProp(cur, (const xmlChar *) "Id");
    if (x != NULL) ret->id = atoi((char *)x);

    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
      if (xmlStrcmp(cur->name, (const xmlChar *) "Keymap") == 0)
      {
         x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (x!=NULL)
           strncpy(ret->mapkey,(const char *)x,MAX_FUNC_NAME);
         else
           strcpy(ret->mapkey,"");
      }
       if (xmlStrcmp(cur->name, (const xmlChar *) "Color") == 0)
       {
            x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            if (x!=NULL)
              strncpy(ret->visual.color,(char *)x,MAX_N_COLOR);
            else
              strcpy(ret->visual.color,"noColor");
       }

       if (xmlStrcmp(cur->name, (const xmlChar *) "Edit") == 0)
       {
          x = xmlGetProp(cur, (const xmlChar *) "secret");
          ret->editMode.secret=0;
          if (x != NULL && x[0]!='0') ret->editMode.secret = 1;
          ret->editMode.chToEDIT=CHAR_TO_EDIT;
          x = xmlGetProp(cur, (const xmlChar *) "chToEDIT");
          if (x != NULL) ret->editMode.chToEDIT = x[0];
          
          ret->editMode.editType=E_NONE;
          x = xmlGetProp(cur, (const xmlChar *) "editType");
          if (x != NULL) {
           strncpy(ret->editMode.editFunction,(char *)x,MAX_FUNC_NAME-2);
           ret->editMode.editType = PARSER_decodeEditType((char *)x);
          }
          ret->editMode.autoComplet = 0;
          x = xmlGetProp(cur, (const xmlChar *) "auto");
          if (x != NULL && x[0]!='0') ret->editMode.autoComplet = 1;
       }
       if (xmlStrcmp(cur->name, (const xmlChar *) "Text") == 0)
       {
            x=xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            if (PARSER_addComponentText(ret,(char *)x) < 0){
              return NULL;
            }
       }
       if (xmlStrcmp(cur->name, (const xmlChar *) "Dimension") == 0)
       {
             x = xmlGetProp(cur, (const xmlChar *) "border");
             if (x!= NULL && x[0]!='0')
              ret->visual.dimension.border = 1;
             else
              ret->visual.dimension.border = 0;
             x = xmlGetProp(cur, (const xmlChar *) "x");
             ret->visual.dimension.x = atoi((char *)x);
             x = xmlGetProp(cur, (const xmlChar *) "y");
             ret->visual.dimension.y = atoi((char *)x);
             x = xmlGetProp(cur, (const xmlChar *) "width");
             ret->visual.dimension.ancho = atoi((char *)x);
             x = xmlGetProp(cur, (const xmlChar *) "high");
             ret->visual.dimension.alto = atoi((char *)x);
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "FComponent") == 0)
        {
	  x=xmlGetProp(cur, (const xmlChar *) "preCreate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_create,(char *)x);
             PARSER_addListaFuncion(F_CRE_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postCreate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_create,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "preShow");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_show,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postShow");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_show,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "preHide");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postHide");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_hide,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "preDestroy");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postDestroy");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_destroy,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "preActivate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postActivate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_activate,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "preDeactivate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.pre_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "postDeactivate");
	  if (x!=NULL && strcmp((char *)x,"")!=0) {
		strcpy(ret->personalFComponent.post_deactivate,(char *)x);
             PARSER_addListaFuncion(F_APP_COMP,(char *)x); }
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "FAction") == 0)
        {
  	  x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL){strcpy(ret->personalAction.enter,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
  	  x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL){strcpy(ret->personalAction.out,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL){strcpy(ret->personalAction.next,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x=xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL){strcpy(ret->personalAction.previous,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL){strcpy(ret->personalAction.up,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL){strcpy(ret->personalAction.down,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL){strcpy(ret->personalAction.left,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL){strcpy(ret->personalAction.right,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL){strcpy(ret->personalAction.back,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL){strcpy(ret->personalAction.other,(char *)x);
             PARSER_addListaFuncion(F_MOV_COMP,(char *)x); }
	  x = xmlGetProp(cur, (const xmlChar *) "Fn");
          if (x!=NULL){
             PARSER_addListaFuncion(F_MOV_COMP_Fn,(char *)x); 
           for (i=0;i!=MAX_Fn_KEYS;i++)
            strcpy(ret->personalAction.Fn[i],(char *)x);
          }
        }
        if (xmlStrcmp(cur->name, (const xmlChar *) "Move") == 0)
        {
          x = xmlGetProp(cur, (const xmlChar *) "enter");
          if (x!=NULL)strcpy(ret->move.enter,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "out");
          if (x!=NULL) strcpy(ret->move.out,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "next");
          if (x!=NULL) strcpy(ret->move.next,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "previous");
          if (x!=NULL)strcpy(ret->move.previous,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "up");
          if (x!=NULL) strcpy(ret->move.up,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "down");
          if (x!=NULL)strcpy(ret->move.down,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "left");
          if (x!=NULL)strcpy(ret->move.left,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "right");
          if (x!=NULL)strcpy(ret->move.right,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "back");
          if (x!=NULL)strcpy(ret->move.back,(char *)x);
          x = xmlGetProp(cur, (const xmlChar *) "other");
          if (x!=NULL)strcpy(ret->move.other,(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F1");
          if (x!=NULL) strcpy(ret->move.Fn[0],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F2");
          if (x!=NULL) strcpy(ret->move.Fn[1],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F3");
          if (x!=NULL) strcpy(ret->move.Fn[2],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F4");
          if (x!=NULL) strcpy(ret->move.Fn[3],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F5");
          if (x!=NULL) strcpy(ret->move.Fn[4],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F6");
          if (x!=NULL) strcpy(ret->move.Fn[5],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F7");
          if (x!=NULL) strcpy(ret->move.Fn[6],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F8");
          if (x!=NULL) strcpy(ret->move.Fn[7],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F9");
          if (x!=NULL) strcpy(ret->move.Fn[8],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F10");
          if (x!=NULL) strcpy(ret->move.Fn[9],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F11");
          if (x!=NULL) strcpy(ret->move.Fn[10],(char *)x);
	  x = xmlGetProp(cur, (const xmlChar *) "F12");
          if (x!=NULL) strcpy(ret->move.Fn[11],(char *)x);
        }
        cur = cur->next;
    }
  return ret;
}

static void PARSER_reset() {
  cabKeymaps = ultKeymaps = NULL;
  cabColores = ultColores = NULL;
  cabCEdFunctions = ultCEdFunctions = NULL;
  Msgs.msg[M_INFO]=Msgs.msg[M_WARNING]=Msgs.msg[M_ERROR]=NULL;
  cabListaFunciones=ultListaFunciones=NULL;
  cabPanels =ultPanels = NULL;
  cabTables = ultTables = NULL;
  cabEdits = ultEdits = NULL;
  cabComponents = ultComponents = NULL;
}

int PARSER_decodeOp(char * x){
  if (x==NULL) return OP_NONE;
   if (strcmp(x,"none") == 0 || strcmp(x,"NONE")==0)  return OP_NONE;
   if (strcmp(x,"create") == 0 || strcmp(x,"CREATE")==0)  return OP_CREATE;
   if (strcmp(x,"destroy") == 0 || strcmp(x,"DELE")==0 || strcmp(x,"DELE")==0)  return OP_DESTROY;
   if (strcmp(x,"show") == 0 || strcmp(x,"SHOW")==0)  return OP_SHOW;
   if (strcmp(x,"hide") == 0 || strcmp(x,"HIDE")==0)  return OP_HIDE;
   if (strcmp(x,"activate") == 0 || strcmp(x,"ACTIVATE")==0)  return OP_ACT;
   if (strcmp(x,"deactivate") == 0 || strcmp(x,"DEACTIVATE")==0)  return OP_DEACT;
 return OP_NONE;
}

static int PARSER_decodeType(char * x){
   if (x == NULL) return -1;
   if (strcmp(x,"label") == 0 )  return C_LABEL;
   if (strcmp(x,"button") == 0 )  return C_BUTTON;
   if (strcmp(x,"ckbutton") == 0 )  return C_CKBUTTON;
   if (strcmp(x,"lsbutton") == 0 )  return C_LSBUTTON;
   if (strcmp(x,"field") == 0 )  return C_EDIT;
  return -1;
}


static int PARSER_decodeEditType(char * x){
 if (x==NULL) return E_NONE;
   if (strcmp(x,"none") == 0 )  return E_NONE;
   if (strcmp(x,"numeric") == 0 )  return E_NUMERIC;
   if (strcmp(x,"alpha") == 0 )  return E_ALPHA;
   if (strcmp(x,"alfnumeric") == 0 )  return E_ALFNUMERIC;
   if (strcmp(x,"7ascii") == 0 )  return E_7ASCII;
   if (strcmp(x,"upper") == 0 )  return E_UPPER;
   if (strcmp(x,"lower") == 0 )  return E_LOWER;

 return PARSER_BuscaEditCheck(x);
}

static int PARSER_decodeVisible(char * x){
  if (x==NULL) return DIS_NORMAL;

   if (strcmp(x,"hidden") == 0 )  return DIS_HIDDEN;
   if (strcmp(x,"normal") == 0 )  return DIS_NORMAL;
   if (strcmp(x,"open") == 0 )    return DIS_OPEN;
   if (strcmp(x,"nSelect") == 0 ) return DIS_NO_SELECT;

 return DIS_NORMAL;
}

static int PARSER_BuscaEditCheck(char * x)
{
tXmlCEdFunctionPtr aux;
   aux =cabCEdFunctions;
   while (aux!=NULL){
     if (strcmp(aux->name,x)==0) return aux->tipo;
     aux=aux->siguiente;
   }
  return 0;
}

static int  PARSER_addComponentText(tXmlComponent * component,char * texto){
  tXmlText * aux,*aux2;

  if (texto == NULL) return 0;
  aux = (tXmlText *) malloc(sizeof(tXmlText));
  if (aux == NULL) {
    ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlMsg));
  }
  aux->texto = (char *) malloc(strlen(texto) + 2);
  if (aux->texto == NULL){
    ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlMsg));
  }
  strcpy(aux->texto,texto);
  if (unescape) PARSER_unescapeText(aux->texto);
  aux->siguiente=NULL;

  if (component->text == NULL){ component->text = aux; return 0;}

  aux2 = component->text;
  while (aux2->siguiente != NULL) aux2=aux2->siguiente; 
  aux2->siguiente=aux;

  return 0;
}

static void PARSER_addComponentPanel(tXmlPanel *  panel,
					tXmlComponent * componente)
{
 tXmlCompPanelPtr auxCompPanel,aux2CompPanel;

  if (componente==NULL) return;
  auxCompPanel = (tXmlCompPanelPtr) malloc(sizeof(tXmlCompPanel));
  if (auxCompPanel == NULL)
    ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlMsg));

  auxCompPanel->componente = componente;
  auxCompPanel->siguiente = NULL;

  if (panel->elements== NULL) 
	panel->elements = auxCompPanel; 
  else {
   aux2CompPanel=panel->elements;
   while(aux2CompPanel->siguiente != NULL) aux2CompPanel = aux2CompPanel->siguiente;
   aux2CompPanel->siguiente = auxCompPanel;
  }
  componente->panel=panel;
   
  if (cabComponents == NULL) {
     cabComponents = ultComponents = componente;
     return;
  }
   
  componente->anterior = ultComponents;
  ultComponents->siguiente=componente;
  ultComponents = componente;
}

static int PARSER_addListaFuncion(enum E_TIPOF tipo, char * name)
{
  tXmlFuncionesPtr aux;

  if (name == NULL) return 0;

  aux = cabListaFunciones;
  while (aux!=NULL) {
    if (strcmp(aux->name,name)==0) {
      aux->nroUses++; break; }
    aux=aux->siguiente;
  }
  if (aux!=NULL) {
    if (aux->tipo == tipo) return 0;
    return -1;
  }
  aux = (tXmlFuncionesPtr) malloc(sizeof(tXmlFunciones));
  if (aux == NULL){
     ERR_fatalError(ERR_MEM,"out of memory <%d>\n",sizeof(tXmlFunciones));
  }
  aux->tipo=tipo;
  strcpy(aux->name,name);
  aux->nroUses=1;
  aux->siguiente = aux->anterior = NULL;
  if (cabListaFunciones == NULL) cabListaFunciones = ultListaFunciones = aux;
  else {
    ultListaFunciones->siguiente = aux;
    aux->anterior=ultListaFunciones;
    ultListaFunciones = aux;
  }
  return 0;
}

static void PARSER_unescapeText(char * str){
    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src == '\\' && *(src + 1) == 'n') {
            *dst++ = '\n';
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}



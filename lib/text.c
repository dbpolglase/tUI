#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ncurses.h>

#include <error.h>
#include <tBasic.h>
#include <text.h>

static tBufferSnd * bufferSnd=NULL;

static int TEXT_miStrTok(char * cadena,char busca);
static int TEXT_addMem(tText * miText, unsigned short filas,
			unsigned short fields, unsigned short columns);
static void TEXT_espandeTab(char * dest, char * orig);

tText * TEXT_new(int resize, unsigned short delete,
		int maxData, int nroLines,int nroFields)
{
  int i,j;
  tText * newText;

   newText = malloc(sizeof(tText));
   if (newText == NULL)
   {
     ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(tText));
     return NULL;
   }
   newText->delete = delete;
   newText->resize = resize;
   newText->mode = Fixed;
   newText->fd = NULL;

   newText->actField=0;
   newText->actLine=0;
   newText->actColumn=0;

   newText->nroColumns = 0;
   newText->nroLines = 0;
   newText->nroFields = 0;

   newText->maxColumns=maxData;
   newText->maxLines =nroLines;
   newText->maxFields=nroFields;

   if (maxData == 0)
     newText->maxColumns = DEFAULT_DATA_SIZE;
   if (nroLines == 0)
     newText->maxLines = ADD_EDIT_LINES;
   if (nroFields == 0)
     newText->maxFields=1;


   newText->check = 0;

   newText->text = (char ***)malloc (sizeof(char**) * newText->maxLines);
   if (newText->text == NULL)
   {
     ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char**)*newText->maxLines));
     free(newText);
     return NULL;
   }
   for (i=0;i!=newText->maxLines;i++)
   {
    newText->text[i] = (char **)malloc (sizeof(char*) * newText->maxFields);
    if (newText->text[i] == NULL)
    {
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*newText->maxFields));
    }
    for (j=0;j!=newText->maxFields;j++)
    {
     newText->text[i][j] = (char *)malloc (sizeof(char) * newText->maxColumns);
     if (newText->text[i][j] == NULL)
     {
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char)*newText->maxColumns));
     }
     strcpy(newText->text[i][j],"");
    }
   }
   return newText;
}

tText * TEXT_newEdit(int maxData, int nroLines,unsigned short delete) 
{
  int i;
  tText * newText;

   newText = malloc(sizeof(tText));
   if (newText == NULL)
   {
     ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(tText));
     return NULL;
   }
   newText->delete = delete;
   newText->resize = RESIZE;
   newText->mode = Dynamic;
   newText->fd = NULL;

   newText->actField=0;
   newText->actLine=0;
   newText->actColumn=0;

   newText->nroColumns = 0;
   newText->nroLines = 0;
   newText->nroFields = 1;

   newText->maxColumns=(maxData==0)?DEFAULT_DATA_SIZE+2:maxData;
   newText->maxLines=(nroLines==0)?MAX_EDIT_LINE+2:nroLines;

   newText->maxLines = nroLines;
   newText->maxFields=1;


   newText->check = 0;

   newText->text = (char ***)malloc (sizeof(char**) * newText->maxLines);
   if (newText->text == NULL)
   {
     ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char**)*newText->maxLines));
     free(newText);
     return NULL;
   }
   for (i=0;i!=newText->maxLines;i++)
   {
    newText->text[i] = (char **)malloc(sizeof(char*) * newText->maxFields);
    if (newText->text[i] == NULL)
    {
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*newText->maxFields));
    }
    newText->text[i][0] = NULL;
   }
   return newText;
}

int TEXT_insEditLine(tText * texto,int linea,int pos)
{
  int i,len,extra;
  int retorno;

   if (texto->maxLines <= texto->nroLines)
   {
     if (texto->resize == NO_RESIZE) return ERR_TEXT_PLACE;
     if ((retorno = TEXT_addMem(texto, texto->maxLines + ADD_LINES, 
			texto->maxFields,0)) != 0)
         return retorno;
   }
   
   texto->nroLines++;

   for (i=texto->nroLines-1;i>linea;i--){
     texto->text[i] = texto->text[i-1];
   }
   len = strlen(texto->text[linea+1][0]+pos);
   extra = ADD_COLUMNS - (len%ADD_COLUMNS) +2;
   texto->text[linea]=(char **)malloc(sizeof(char*) * texto->maxFields);
   if (texto->text[linea]==NULL)
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*texto->maxFields));
   texto->text[linea][0]=malloc(sizeof(char) * len+extra);
   if (texto->text[linea][0]==NULL)
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*len));
   if (pos > 0){
    strncpy(texto->text[linea][0],texto->text[linea+1][0],pos);
    *(texto->text[linea][0]+pos+1)='\0';
    strcpy(texto->text[linea+1][0],texto->text[linea+1][0]+pos);
  }
  else
    strcpy(texto->text[linea][0],"");

  return 0;
}

int TEXT_joinEditLine(tText * texto,int lineaA,int lineaB)
{
  int i,lenA,lenB,extraA;

   lenA = strlen(texto->text[lineaA][0]);
   extraA = ADD_COLUMNS - (lenA%ADD_COLUMNS);
   lenB = strlen(texto->text[lineaB][0]);

   if (lenB > extraA){
    lenA += lenB;
    extraA = ADD_COLUMNS - (lenA%ADD_COLUMNS) + 2;
    texto->text[lineaA][0] = 
	realloc(texto->text[lineaA][0], sizeof(char *) * (lenA+extraA));
    if (texto->text[lineaA][0] == NULL)
        ERR_fatalError(ERR_MEM, " Fail realloc of %ld \n",sizeof((lenA+extraA) * sizeof(char*)));
   }
   strcat(texto->text[lineaA][0],texto->text[lineaB][0]);
   free(texto->text[lineaB][0]);

   for (i=lineaB;i<texto->maxLines-1;i++){
     texto->text[i] = texto->text[i+1];
   }
   texto->text[i] = NULL;

   texto->nroLines --;

  return 0;
}

int TEXT_free(tText * texto)
{
  int i,j; 

  if (texto == NULL) return ERR_TEXT_PLACE;

  for (i=0;i!=texto->maxLines;i++)
  {
   if (texto->text[i] != NULL)
   {
     for (j=0;j!=texto->maxFields;j++)
     {
      if (texto->text[i][j] !=NULL) free(texto->text[i][j]); 
     }
     texto->text[i]=NULL;
   }
  }
  free(texto->text);
  texto->text = NULL;
  texto->nroColumns = 0;
  texto->nroLines = 0;
  texto->nroFields = 0;
  texto->maxColumns =0;
  texto->maxLines = 0;
  texto->maxFields= 0;
  texto->actColumn =0;
  texto->actLine = 0;
  texto->actField= 0;
 
  return 0;
}

int TEXT_clear(tText * texto)
{
  int i,j; 

  if (texto == NULL) return ERR_TEXT_PLACE;

  if (!texto->delete) return 0;

  for (i=0;i!=texto->maxLines;i++)
  {
   if (texto->text[i] != NULL)
   {
     for (j=0;j!=texto->maxFields;j++)
     {
      if (texto->text[i][j] !=NULL) strcpy(texto->text[i][j],"");
     }
   }
  }

  texto->nroColumns = 0;
  texto->nroLines = 0;
  texto->nroFields = 0;
  texto->actColumn =0;
  texto->actLine = 0;
  texto->actField= 0;
 
 return 0;
}

void TEXT_check(tText * text)
{
  if (text->check == 0)
   text->check = 1;
  else
   text->check = 0;
}

void TEXT_reset(tText *text)
{
  text->actColumn =0;
  text->actLine = 0;
  text->actField= 0;
  text->check = 0;
}

tText * TEXT_newSimpleText(tDim * dim, char * newText,unsigned short delete)
{
  tText * miText;

  if (!dim->border)
    miText = TEXT_new(NO_RESIZE, delete,dim->ancho, dim->alto,1);
   else
    miText = TEXT_new(NO_RESIZE, delete,dim->ancho-2, dim->alto-2,1);
  miText->nroFields=miText->maxFields=1;
  TEXT_addSimpleData(miText, newText);
  return miText;
}

tText * TEXT_newSimpleLineText(tDim * dim, char ** newText,unsigned short delete)
{
  tText * miText;
  char ** pText;

  if (!dim->border)
    miText = TEXT_new(RESIZE, delete,dim->ancho, dim->alto,1);
  else
    miText = TEXT_new(RESIZE, delete,dim->ancho-2, dim->alto-2,1);

  miText->nroFields=miText->maxFields=1;
  pText = newText;
  for ( ;*pText != NULL;pText++)
  {
    TEXT_addSimpleLine(miText, *pText);
  }
  return miText;
}


int TEXT_addSimpleLine(tText * miText, char * newText)
{
  int l=0;
  int i=0,j=0;
  int len;
  int incrColumns;
  int retorno;
  char textAux[500];

  if (miText == NULL) return -1;
  strcpy(textAux,newText);
  len=strlen(textAux);

   while (i<=len){
     j=TEXT_miStrTok(newText+i,'\n');
     memcpy(textAux,newText+i,j);
     textAux[j]='\0';
     /* -----------------
      *  solo 1 linea por fila.
      * ----------------------------- */
      if (miText->nroLines == miText->maxLines)
      {
         if ((retorno = TEXT_addMem(miText, miText->maxLines + ADD_LINES, 
			miText->maxFields,miText->maxColumns)) != 0)
           return retorno;
      }
      miText->actColumn = 0;
      l = strlen(textAux);
      if (l > miText->maxColumns)
      {
        incrColumns = (miText->maxColumns+ADD_COLUMNS > l)?miText->maxColumns+ADD_COLUMNS: l;
        if ((retorno = TEXT_addMem(miText, miText->maxLines,
			miText->maxFields, incrColumns)) != 0)
        {
           strncpy((char*) (miText->text[miText->nroLines][miText->actField]), 
			textAux,miText->maxColumns);
           miText->nroColumns = miText->maxColumns;
        }
        else
        {
           strcpy((char*)miText->text[miText->nroLines][miText->actField],textAux);
           miText->nroColumns = l;
        }
      }
      else
      {
       strcpy(miText->text[miText->nroLines][miText->actField] ,textAux);
       if (l> miText->nroColumns) miText->nroColumns = l;
      }
     miText->nroLines++;
     i+=j+1;
   }

   return 0; 
}

int TEXT_addSimpleData(tText * miText, char * newText)
{
  int l=0;
  int i=0,j=0;
  int len;
  int incrColumns;
  int retorno;
  char textAux[500];

  if (miText == NULL || newText == NULL) return ERR_DATA;

  strcpy(textAux,newText);
  len=strlen(textAux);

  while (i<=len){
     j=TEXT_miStrTok(newText+i,'\n');
     memcpy(textAux,newText+i,j);
     textAux[j]='\0';

     if (miText->nroLines == miText->maxLines)
     {
         if ((retorno = TEXT_addMem(miText, miText->maxLines + ADD_LINES, 
				miText->maxFields,miText->maxColumns)) != 0)
           return retorno;
     }
     miText->actColumn = 0;
     l = strlen(textAux);
     if (l > miText->maxColumns)
     {
        incrColumns = (miText->maxColumns+ADD_COLUMNS > l)?miText->maxColumns+ADD_COLUMNS: l;
        if ((retorno = TEXT_addMem(miText, miText->maxLines,
		        miText->maxFields,  incrColumns)) != 0)
        {
           strncpy((char*) (miText->text[miText->nroLines][miText->actField]) , textAux,miText->maxColumns);
           miText->nroColumns = miText->maxColumns;
        }
        else
        {
           strncpy((char*)miText->text[miText->nroLines][miText->actField],textAux,miText->maxColumns);
           miText->nroColumns = l;
        }
     }
     else
     {
       strcpy(miText->text[miText->nroLines][miText->actField] ,textAux);
       if (l> miText->nroColumns) miText->nroColumns = l;
     }
     miText->nroLines++;
     i+=j+1;
   }
   miText->actLine=0;
   return 0; 
}

int TEXT_delSimpleData(tText * miText, char * text)
{
 int i,j,k;
 int found=0;

  if (miText == NULL || text == NULL) return ERR_DATA;

  if (!miText->delete) return 0;

  for (i=0;i!=miText->nroLines;i++){
    if (strcmp(miText->text[i][0],text)==0){found=1; break;}
  }

  if (!found) return ERR_TEXT_PLACE;
  
  for (j=i;j!=miText->nroLines-1;j++){
   for (k=0;k!=miText->maxFields;k++)
    strcpy(miText->text[j][k],miText->text[j+1][k]);
  }

  for (j=0;j!=miText->maxFields;j++)
    strcpy(miText->text[miText->nroLines-1][j],"");

  miText->nroLines --;

  return 0; 
}

int TEXT_replaceLine(tText * miText,int line,int field,char * text)
{
 int l;

  char * token = strtok(text, "\n");

  if (miText == NULL || text==NULL) return ERR_DATA;
  if (token != NULL) return ERR_MULTILINE;
  
  if (field > miText->maxFields || line > miText->maxLines)
   return ERR_TEXT_PLACE;
  
  l=strlen(text);
  if (l > miText->maxColumns)
  {
    strncpy(miText->text[line][field],text,miText->maxColumns);
  }
  
  strcpy(miText->text[line][field],text);
  if (l > miText->nroColumns)
   miText->nroColumns = l;

  return 0;
}

int TEXT_delField(tText * miText,int line,int field)
{
  if (miText == NULL) return ERR_DATA;

  if (field > miText->maxFields || line > miText->maxLines)
   return ERR_TEXT_PLACE;
  
  if (miText->text[line][field] != NULL)
    miText->text[line][field][0] = '\0';
  miText->nroFields --;

  return 0;
}

int TEXT_addField(tText * miText,char ** newText)
{
 char ** pTexto;

  if (miText == NULL || newText == NULL) return ERR_DATA;

  if (miText->nroFields >= miText->maxFields)
  {
    if (TEXT_addMem(miText, miText->maxLines, miText->maxFields + ADD_FIELDS, 
				miText->maxColumns) != 0)
     return -1;
  }
  miText->actField ++;
  miText->nroFields ++;
  pTexto = newText;

  for (pTexto = newText;*pTexto != NULL;pTexto ++) 
    TEXT_addSimpleData(miText, *pTexto);

  return 0;
}


int TEXT_delLine(tText * miText,unsigned short line)
{
 int i;

  if (miText == NULL) return ERR_DATA;

   if (line > miText->maxLines)
     return ERR_TEXT_PLACE;

   if (miText->text[line] != NULL)
   {
      for (i=0;i!=miText->maxFields;i++)
      {
         if( miText->text[line][i] != NULL) miText->text[line][i][0]='\0'; 
      }
      miText->nroLines --;
   }
   return 0;
}

int TEXT_delLineText(tText * miText,char * text)
{
 int i,j,line=0;

  if (miText == NULL || text == NULL || strcmp(text,"")==0) return ERR_DATA;

  for (i=0;i!=miText->nroLines;i++){
     if (strcmp(miText->text[i][0],text)==0){
        line = i;
        break;
     }
  }
  if (line == miText->nroLines) return ERR_TEXT_PLACE;

  for (i=line;i!=miText->nroLines-1;i++){
    for (j=0;j!=miText->maxFields;j++)
     miText->text[i][j] = miText->text[i+1][j];
  }

  for (i=0;i!=miText->maxFields;i++)
   miText->text[miText->nroLines-1][i][0]='\0';

  miText->nroLines--;
  return 0;
}

int TEXT_replaceChar(tText * miText,int line,int field,int column, char text)
{
   if (miText == NULL) return ERR_DATA;

   if (field > miText->maxFields || line > miText->maxLines || column > miText->maxColumns)
      return ERR_TEXT_PLACE;

   if (miText->text[line] == NULL || miText->text[line][field] == NULL) 
	return ERR_DATA;

   if (strlen(miText->text[line][field]) < column) return ERR_TEXT_PLACE;
   miText->text[line][field][column]=text;

  return 0;
}

int TEXT_insertChar(tText * miText,int line,int field,int column, char text)
{
 char buffer[MAX_EDIT_LINE];

   if (miText == NULL) return ERR_DATA;

   if (field > miText->maxFields || line > miText->maxLines || column > miText->maxColumns-1)
      return ERR_TEXT_PLACE;

   if (miText->text[line] == NULL || miText->text[line][field] == NULL) 
	return ERR_DATA;

   sprintf(buffer,"%.*s%c%s",column,miText->text[line][field],text,miText->text[line][field]+column);

   memcpy(miText->text[line][field],buffer,strlen(buffer));

   if (strlen(buffer) > miText->nroColumns) miText->nroColumns = strlen(buffer);
   return 0;
}

int TEXT_addChar(tText * miText,int line,int field,
				int column, char text,unsigned short insert)
{
  int l,i;
  char *p;

   if (miText == NULL) return ERR_DATA;
   
   if (field >= miText->maxFields && line >= miText->maxLines)
      return ERR_TEXT_PLACE;

   l = strlen(miText->text[line][field]);

   if (insert == Replace){
        if (l>column) {
          miText->text[line][field][column]=text;
        }
        else {
          if ( column >= miText->maxColumns) return ERR_TEXT_PLACE;

          *(miText->text[line][field]+column) = text;
          *(miText->text[line][field]+column+1) = '\0';
        }
        return 0;
   }

   if (insert == Insert){
        if ( l >= miText->maxColumns) return ERR_TEXT_PLACE;

        if (l>column) {
          p = miText->text[line][field]+l;
          for (i=l+1;i!=column;i--,p--)
            *p = *(p-1);

          *(miText->text[line][field]+(l+1)) = '\0';
          miText->text[line][field][column]=text;
        }
        else 
        {
          *(miText->text[line][field]+column) = text;
          *(miText->text[line][field]+column+1) = '\0';
        }
       return 0;
   }
   return 0;
}

char TEXT_getChar(tText * miText,int line,int field,int column)
{
  if (miText == NULL) return '\0';

  if (field >= miText->maxFields || line >= miText->maxLines || column >= miText->maxColumns)
   return ERR_TEXT_PLACE;

  if ( strlen((char *)(miText->text[line][field])) > column)
    return '\0';
 
  return (miText->text[line][field][column]);
}

char TEXT_getActChar(tText * miText)
{
  if (miText == NULL) return '\0';

  if (miText->actField >= miText->maxFields || 
	miText->actLine >= miText->maxLines || 
        miText->actColumn >= miText->maxColumns)
   return ERR_TEXT_PLACE;

  if ( strlen((char *)(miText->text[miText->actLine][miText->actField])) > miText->actColumn)
    return '\0';
 
  return (miText->text[miText->actLine][miText->actField][miText->actColumn]);
}

char * TEXT_getData(tText * miText, int line,int field)
{
  if (miText == NULL || miText->text == NULL) return NULL;

  if ((field !=0 && field >= miText->nroFields) || (line != 0 && line >= miText->nroLines))
   return NULL;

  if (miText->text[line][field] != NULL)
    return (char *)(miText->text[line][field]);
  else
    return TEXT_nextData(miText,line);
}

char * TEXT_getActLine(tText * miText)
{
  if (miText == NULL) return NULL;

  if (miText->text[miText->actLine][miText->actField] != NULL)
    return (char *)(miText->text[miText->actLine][miText->actField]);
  else
    return TEXT_nextData(miText,miText->actLine);
}

char * TEXT_nextData(tText * miText, int line)
{
  char * p;

  if (miText == NULL) return NULL;

  if (miText->actField  == miText->maxFields-1) 
    return NULL;

  miText->actField++;
  for (
    p = (char *)(miText->text[miText->actLine][miText->actField]);
    miText->actField != miText->maxFields;p++)
    {
     if (p != NULL) return p;
    }
  return NULL;
}

char ** TEXT_getLine(tText * miText, unsigned short line)
{
  char ** retorno=NULL;
  int i;

  retorno = (char **)malloc(sizeof(char *) * miText->nroFields); 
  if (retorno == NULL) {
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*miText->nroFields));
     return NULL;
  }
  for (i=0;i!=miText->nroFields;i++){
    retorno[i]=miText->text[line][i];
  }

  return retorno;
}

char ** TEXT_getField(tText * miText, unsigned short field)
{
  int i;
  char ** retorno;
  retorno = (char **)malloc(sizeof(char *) * miText->nroLines); 
  if (retorno == NULL) {
      ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(sizeof(char *)*miText->nroLines));
     return NULL;
  }
  for (i=0;i!=miText->nroLines;i++){
    retorno[i]=miText->text[i][field];
  }

  return retorno;
}


static int TEXT_addMem(tText * miText, unsigned short filas,
			unsigned short fields, unsigned short columns)
{
 int i,j;

   int oldFields,oldLines,oldColumns;

   oldColumns =miText->maxColumns;
   oldLines =miText->maxLines;
   oldFields =miText->maxFields;

    if (miText->resize == NO_RESIZE) return ERR_RESIZE;
    
    if (filas != miText->maxLines)
    {
      miText->text = realloc(miText->text, sizeof(char ***) * filas );
      if (miText->text == NULL)
      {
        ERR_fatalError(ERR_MEM, " Fail realloc of %ld \n",sizeof(fields * sizeof(char***)));
        return ERR_MEM;
      }
    }

    for (i=0;i!=filas;i++)
    {
       if (i < oldLines ) 
       {
          if (oldFields != fields)
          {
             miText->text[i] = realloc(miText->text[i],sizeof(char **) * fields);
             if (miText->text[i] == NULL){
              ERR_fatalError(ERR_MEM, " Fail realloc of %ld \n",sizeof(char**)*fields);
              return ERR_MEM;
             }
          }
       }
       else
       {
         miText->text[i] = malloc(sizeof(char **) * fields); 
         for (j=0;j!=fields;j++){
           if (columns !=0) {
             miText->text[i][j]= malloc(sizeof(char) * columns);
             if (miText->text[i][j] == NULL){
              ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(char)*columns);
              return ERR_MEM;
             }
	     memset(miText->text[i][j],'\0',columns);
           }
           else  miText->text[i][j]=NULL;
         }
       }
    }

    if (columns !=0 && oldColumns != columns)
    {
      for (i=0;i<oldLines;i++)
      {
        for (j=0;j<oldFields;j++)
        {
         miText->text[i][j]= realloc(miText->text[i][j],sizeof(char)*columns);
         if (miText->text[i][j] == NULL){
           ERR_fatalError(ERR_MEM, " Fail realloc of %ld \n",sizeof(char)*columns);
           return ERR_MEM;
         }
        }
      }
    }

    miText->maxFields = fields;
    miText->maxLines = filas;
    miText->maxColumns = columns;

    return 0;
}

int TEXT_addData(tText * miText, char * data)
{
  int retorno,l,incrColumns;

  if (miText == NULL) return ERR_TEXT_PLACE;

  l=strlen(data);
  if (l> miText->maxColumns)
  {
   incrColumns = (miText->maxColumns+ADD_COLUMNS > l)?miText->maxColumns+ADD_COLUMNS: l;}
  else incrColumns=miText->maxColumns;

   if (l > miText->maxColumns || 
       miText->nroLines >= miText->maxLines-1)
   {
     if (miText->resize == NO_RESIZE){
       miText->actField=miText->maxFields;
       return ERR_TEXT_PLACE;
     }
     else
     {
       if (l > miText->maxColumns) {
        if ((retorno = TEXT_addMem(miText, miText->maxLines, 
		miText->maxFields, incrColumns)) != 0)
         return retorno;
       }
       if (miText->nroLines >= miText->maxLines-1) {
        if ((retorno = TEXT_addMem(miText, miText->maxLines+ADD_LINES, 
		miText->maxFields, incrColumns)) != 0)
         return retorno;
       } 
     }
   }

   strcpy(miText->text[miText->nroLines][miText->actField],data);

   if (miText->actField < miText->maxFields-1) 
      miText->actField++;
   else
   {
      if (miText->nroLines < miText->maxLines-1){
         miText->nroLines++;
         miText->actField=0;
      }
   }

   
   miText->actLine=miText->nroLines-1;
   return 0;
}

int TEXT_delData(tText * miText, char * data,int all)
{
  int i,j;
  int borrados=0;


  for (i=0;i!=miText->nroLines;i++){
   for (j=0;j!=miText->nroFields;j++){
     if (strcmp(miText->text[i][j],data)==0)
     {
       strcpy(miText->text[i][j],"");
       borrados++;
       if (!all) return borrados;
     }
   }
  }
  return borrados;
}

int TEXT_addLine(tText * miText, int fields, char * data[])
{
  int i,retorno;
  char **aux;

  if (miText == NULL) return ERR_TEXT_PLACE;

  if (miText->nroLines >= miText->maxLines-1) {
     if (miText->resize == NO_RESIZE) return ERR_TEXT_PLACE;
     else {
         if ((retorno = TEXT_addMem(miText, miText->maxLines + ADD_LINES, 
			miText->maxFields,miText->maxColumns)) != 0)
           return retorno;
     }
  }

  if (fields> miText->maxFields)
  {
     if (miText->resize == NO_RESIZE) return ERR_TEXT_PLACE;
     else {
         if ((retorno = TEXT_addMem(miText, miText->maxLines, 
			miText->maxFields+ADD_FIELDS,miText->maxColumns)) != 0)
             return retorno;
     }
  }
  
  aux = &data[0];
  for (i=0;i!=fields;i++,aux++){
    memset(miText->text[miText->nroLines][i],'\0',miText->maxColumns);
    strncpy(miText->text[miText->nroLines][i],*aux,miText->maxColumns);
  }
  miText->nroLines++;
 return 0;
}

int TEXT_delDataLine(tText * miText, char * data[],int all)
{
  int i,j,k,l;
  char **aux;
  int math=0;
  int borradas = 0;

  do {
    for (i=0;i!=miText->nroLines;i++) {
      math=1;
      for (j=0;j!=miText->nroFields;j++){
        aux = &data[0];
        if (strcmp(miText->text[i][j],*aux) != 0) math=0;
      }
      if (math){
       for (k=i;k!=miText->nroLines-1;k++){
        for (l=0;l!=miText->nroFields;l++)
         miText->text[k][l] = miText->text[k+1][l]; 
       }
       for (l=0;l!=miText->nroFields;l++)
         strcpy(miText->text[miText->nroLines][l],"");
       miText->nroLines --;
       borradas++;
       break;
      } 
    }
  } while(math && all && miText->nroLines > 0);

 if (miText->actLine > miText->nroLines) miText->actLine = miText->nroLines;
 return borradas;
}

int TEXT_addEditData(tText * miText, char * data)
{
  int retorno,ln,lold,extra;

   if (miText->actLine >= miText->maxLines-1 )
   {
     if (miText->resize == NO_RESIZE){
       miText->actLine--;
       miText->actField=miText->maxFields;
       return ERR_TEXT_PLACE;
     }
     else
     {
        if (miText->maxFields == 0) miText->maxFields=1;
        if ((retorno = TEXT_addMem(miText, miText->maxLines+ADD_LINES, 
		miText->maxFields, 0)) != 0)
        return retorno;
     }
   }

   ln = strlen(data)+2;
   extra = ADD_COLUMNS - (ln%ADD_COLUMNS) +2;
   if (miText->text[miText->actLine][miText->actField] == NULL) {
     miText->text[miText->actLine][miText->actField] = malloc (sizeof(char) *ln+extra);
     if (miText->text[miText->actLine][miText->actField] == NULL)
     {
       ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(char)*ln);
       return ERR_MEM;
     }
   }
   else {
    lold=strlen(miText->text[miText->actLine][miText->actField])+2;
    if (ln > lold && (ln%ADD_COLUMNS == 0)) {
     miText->text[miText->actLine][miText->actField] = realloc(
                   miText->text[miText->actLine][miText->actField],
                   sizeof(char) *ln);
     if (miText->text[miText->actLine][miText->actField] == NULL)
     {
       ERR_fatalError(ERR_MEM, " Fail realloc of %ld \n",sizeof(char)*ln);
       return ERR_MEM;
     }
    }
   }

   strcpy(miText->text[miText->actLine][miText->actField],data);

   if (miText->actField < miText->maxFields-1) 
      miText->actField++;
   else
   {
      if (miText->actLine < miText->maxLines-1){
         miText->actLine++;
         miText->actField=0;
      }
   }

   miText->nroLines=miText->actLine;
   return 0;
}

int TEXT_loadFile(tText * miText,char  * fileName)
{
  int retorno,l,extra;
  char * buffer;
  int oldMaxColumns = miText->maxColumns;

   miText->fd = fopen(fileName,"r");
   if (miText->fd == NULL) {
       ERR_Error(ERR_FILE, "Can't open file %s \n",fileName);
       return ERR_FILE;
   }

   buffer = (char *)malloc(sizeof(char) * miText->maxColumns + 2);
   if (buffer == NULL) {
      ERR_fatalError(ERR_MEM, " Fail malloc of %d \n",sizeof(char)*miText->maxColumns);
      return ERR_MEM;
   }
    
   while (fgets(buffer,miText->maxColumns,miText->fd))
   {
      if (buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1]='\0';
      if (miText->actLine >= miText->maxLines){
         miText->maxColumns=0; 
         if ((retorno = TEXT_addMem(miText, miText->maxLines + ADD_LINES, 
			miText->maxFields,0)) != 0)
           return retorno;
         miText->maxColumns=oldMaxColumns; 

      }
      l=strlen(buffer)+2;
      extra = ADD_COLUMNS - (l%ADD_COLUMNS) +2;
      miText->text[miText->actLine][0] = (char *)malloc(sizeof(char)* (l+extra));
      if (miText->text[miText->actLine][0] == NULL) {
           ERR_fatalError(ERR_MEM, " Fail malloc of %d \n",sizeof(char)*miText->maxColumns);
           return ERR_MEM;
       }
/*       strcpy(miText->text[miText->actLine][0],buffer);*/
       TEXT_espandeTab(miText->text[miText->actLine][0],buffer);
       miText->actLine++;
   }
   miText->maxLines=miText->nroLines=miText->actLine;
   miText->nroColumns=1;
  return 0;
}

int TEXT_loadTableFile(tText * miText,char  * fileName,char separator)
{
  int retorno,len,i,j,field;
  char * buffer;

  miText->fd = fopen(fileName,"r");
  if (miText->fd == NULL) {
       ERR_Error(ERR_FILE, "Can't open file %s \n",fileName);
       return ERR_FILE;
  }

  buffer = (char *)malloc(sizeof(char) * miText->maxColumns * miText->maxFields + 2);
  if (buffer == NULL) {
      ERR_fatalError(ERR_MEM, " Fail malloc of %d \n",sizeof(char)*miText->maxColumns);
      return ERR_MEM;
  }
    
  while (fgets(buffer,(miText->maxColumns*miText->maxFields),miText->fd))
  {
      if (buffer[strlen(buffer)-1]=='\n') buffer[strlen(buffer)-1]='\0';
      if (miText->actLine >= miText->maxLines){
         if ((retorno = TEXT_addMem(miText, miText->maxLines + ADD_LINES, 
			miText->maxFields,miText->maxColumns)) != 0)
           return retorno;
      }
      len=strlen(buffer);i=0;field=0;
      while (i<=len){
         j=TEXT_miStrTok(buffer+i,separator);
         if (j < miText->maxColumns-1) {
           memcpy(miText->text[miText->actLine][field],buffer+i,j);
           miText->text[miText->actLine][field][j]='\0';
         }
         else {
           memcpy(miText->text[miText->actLine][field],buffer+i,miText->maxColumns -1);
           miText->text[miText->actLine][field][miText->maxColumns]='\0';
         }
         field ++;
         i+=j+1;
      }
      miText->actLine++;
   }
   miText->maxLines=miText->nroLines=miText->actLine;
   miText->nroColumns=1;
  return 0;
}

static void TEXT_espandeTab(char * dest, char * orig){
int i,j,len,extra,pos;

  len = strlen(orig);
  pos=i=0;
  while (i<=len){
     extra = 0;
     j=TEXT_miStrTok(orig+i,'\t');
     memcpy(dest+pos,orig+i,j); pos +=j;
     if (*(orig+i+j)=='\t'){
        extra = 4 - ((i+j)%4);
	strncpy(dest+pos,"     ",extra); pos+=extra;
     }
     i+=j+1;
  }
  *(dest+pos)='\0';
}

int TEXT_saveFile(tText * miText, char  * fileName){
  return TEXT_saveTabFile(miText,fileName,' '); 
}

int TEXT_saveTabFile(tText * miText, char  * fileName,char separator)
{
  int i,j;

   miText->fd = fopen(fileName,"w+");
   if (miText->fd == NULL) {
       ERR_Error(ERR_FILE, "Can't open file %s \n",fileName);
       return ERR_FILE;
   }

   for (i=0;i!=miText->nroLines;i++){
    for (j=0;j!=miText->nroFields;i++){
     if (j==0)
      fprintf(miText->fd,"%s",miText->text[i][j]); 
     else {
      fprintf(miText->fd,"%c%s",separator,miText->text[i][j]); 
     }
    }
    fprintf(miText->fd,"\n");
   }
  
   fclose(miText->fd);

  return 0;
}

int TEXT_strVisLen(char *cadena,int comienzo)
{
  int len=0;
  char * tabAux, * tabRec; 

  tabRec = cadena;

   tabRec = cadena;
   tabAux =strchr(tabRec,'\t');
   while (tabAux!=NULL) {
      len+=TABSIZE-((tabAux-tabRec)%TABSIZE);
      len--; /* menos el \t */
      tabRec=tabAux; tabRec++;
      tabAux=strchr(tabRec,'\t');
   }
   len += strlen(cadena);
   return (len <= comienzo)?0:(len-comienzo);
}

int TEXT_send(char * texto,int init)
{
  if (bufferSnd == NULL) {
     bufferSnd = (tBufferSnd *)malloc(sizeof(tBufferSnd));
     if (bufferSnd == NULL) {
       ERR_fatalError(ERR_MEM, " Fail Malloc of %ld \n",sizeof(tText));
       return ERR_MEM;
     }
     bufferSnd->rbuffer=0;
     memset(bufferSnd->text,'\0',sizeof(bufferSnd->text));
  }
  if (init) bufferSnd->rbuffer=0;
  if (bufferSnd->rbuffer >= MAX_SEND_TEXT){
    return ERR_SIZE;
  }
  bufferSnd->text[bufferSnd->rbuffer]=texto;
  bufferSnd->rbuffer++;
  return 0;
}

char *  TEXT_recv()
{
  if (bufferSnd == NULL) return NULL;
  if (bufferSnd->rbuffer==0) {
     memset(bufferSnd->text,'\0',sizeof(bufferSnd->text));
     return NULL;
  }

  bufferSnd->rbuffer --;
  return bufferSnd->text[bufferSnd->rbuffer];
}

static int TEXT_miStrTok(char * cadena,char busca){
  int i,len;
   len =strlen(cadena);
   for (i=0; *cadena != busca && i < len;i++,cadena++);
   return i;
}


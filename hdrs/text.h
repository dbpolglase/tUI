
#define ADD_FIELDS             1
#define ADD_LINES              5
#define ADD_EDIT_LINES        24 
#define ADD_COLUMNS           10
#define DEFAULT_DATA_SIZE     80

#define MAX_SEND_TEXT 40
typedef struct{
 char * text[MAX_SEND_TEXT];
 unsigned short rbuffer;
}tBufferSnd;

tText * TEXT_new(int resize, unsigned short delete,int maxData, 
			int nroLines,int nroFields);
tText * TEXT_newEdit(int maxData, int nroLines,unsigned short delete);

int TEXT_free(tText * texto);
void TEXT_check(tText * text);
int TEXT_clear(tText *text);
void TEXT_reset(tText *text);

tText * TEXT_newSimpleText(tDim * dim, char * newText,unsigned short delete);
tText * TEXT_newSimpleLineText(tDim * dim, char ** newText,unsigned short delete);
int TEXT_addSimpleLine(tText * miText, char * newText);
int TEXT_addSimpleData(tText * miText, char * text);
int TEXT_delSimpleData(tText * miText, char * text);

int TEXT_replaceLine(tText * miText,int line,int field,char * text); 
int TEXT_delLine(tText * miText,unsigned short  line); 
int TEXT_delLineText(tText * miText,char * text);
int TEXT_addFields(tText * miText,unsigned short nFields); 
int TEXT_delField(tText * miText,int line,int field);

int TEXT_addChar(tText * miText,int line,int field,int column, char text,unsigned short insert); 
char TEXT_getChar(tText * miText,int line,int field,int column); 
char TEXT_getActChar(tText * miText);

char * TEXT_getActLine(tText * miText); 
char * TEXT_getData(tText * miText, int line,int field); 
char ** TEXT_getLine(tText * miText, unsigned short line);
char ** TEXT_getField(tText * miText, unsigned short field);
char * TEXT_nextData(tText * miText, int field);

int TEXT_addData(tText * miText, char * data);
int TEXT_delData(tText * miText, char * data,int global);
int TEXT_addLine(tText * miText, int columns, char * data[]);
int TEXT_delDataLine(tText * miText, char * data[],int global);
int TEXT_insEditLine(tText * texto,int linea,int pos);
int TEXT_joinEditLine(tText * texto,int lineaA,int lineaB);
int TEXT_addEditData(tText * miText, char * data);

int TEXT_loadFile(tText * miText, char  * fileName);
int TEXT_loadTableFile(tText * miText,char  * fileName,char separator);
int TEXT_saveFile(tText * miText, char  * fileName);
int TEXT_saveTabFile(tText * miText, char  * fileName, char separator);

int TEXT_strVisLen(char *cadena,int comienzo);

int TEXT_send(char * texto,int init);
char * TEXT_recv();

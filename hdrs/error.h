#define ERR_MEM        -1
#define ERR_NCURSES    -2
#define ERR_MULTILINE  -3
#define ERR_TEXT_PLACE -4
#define ERR_SIZE       -5
#define ERR_RESIZE     -6
#define ERR_TYPE       -7
#define ERR_FOUND      -8
#define ERR_COMPONENT  -9
#define ERR_OVERLAY    -10
#define ERR_FILE       -11
#define ERR_VIEW       -12
#define ERR_DATA       -13
#define ERR_PARSE      -14

void ERR_printError(int print,char * file);

void ERR_fatalError(int error, char* format,...);

void ERR_Error(int error, char * format,... );

int ERR_isError();

int ERR_lastError();


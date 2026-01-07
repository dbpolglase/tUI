enum CMsg{
M_INFO,
M_WARNING,
M_ERROR
};

#define MSG_TIME_INFO  5

#define MAX_MSG_DATA    150
#define MAX_TEXT_BUTTON 80
#define MAX_MSG_TITLE   80


typedef struct {
   enum CMsg type;
   char title[MAX_MSG_TITLE];
   unsigned short nroButtons;
   char ButtonText1[MAX_TEXT_BUTTON];
   char ButtonText2[MAX_TEXT_BUTTON];
   char * Text;
   tChAttr color;
   tDim dimension;
   tDim dimButton1;
   tDim dimButton2;
   WINDOW * wBack;
   WINDOW * wButton1;
   WINDOW * wButton2;
} tMsg, * tMsgPtr;

#define COLOR_BACK_INFO      0 
#define COLOR_FORE_INFO      7
#define ATTR_INFO            WA_NORMAL
#define COLOR_BACK_WARNING   0
#define COLOR_FORE_WARNING   7
#define ATTR_WARNING         WA_BOLD
#define COLOR_BACK_ERROR     0
#define COLOR_FORE_ERROR     7
#define ATTR_ERROR           WA_BLINK

#define DEF_INFO_TITLE       "Info"
#define DEF_INFO_BORDER      1
#define DEF_INFO_NBUTTONS    0
#define DEF_INFO_BUTTON1     "OK"
#define DEF_INFO_BUTTON2     "CANCEL"

#define DEF_WARNING_TITLE    "Warning"
#define DEF_WARNING_BORDER    1
#define DEF_WARNING_NBUTTONS  2
#define DEF_WARNING_BUTTON1  "OK"
#define DEF_WARNING_BUTTON2  "CANCEL"

#define DEF_ERROR_TITLE      "Error"
#define DEF_ERROR_BORDER      1
#define DEF_ERROR_NBUTTONS    1
#define DEF_ERROR_BUTTON1    "OK"
#define DEF_ERROR_BUTTON2    "CANCEL"

#define CENTER_VIEW	0
#define CENTER_TERMINAL	1

void MSG_Init();
int MSG_create(enum CMsg type, unsigned int center, char * formato,...);
void MSG_borderColor(enum CMsg type, unsigned short border,tChAttr * color);
void MSG_txtButton(enum CMsg type,
                   char * title,
                   unsigned short nButtons,
                   char * text1, char * text2);

void MSG_saveView(enum CMsg type);
void MSG_restoreView(enum CMsg type);
void MSG_setSegInfo(unsigned int nseg);

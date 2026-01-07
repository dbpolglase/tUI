
#define KEY_ESC 27

#define ACT_NO       0
#define ACT_ENTER    1
#define ACT_OUT      2
#define ACT_NEXT     3
#define ACT_PREVIOUS 4
#define ACT_UP       5
#define ACT_DOWN     6
#define ACT_LEFT     7
#define ACT_RIGHT    8
#define ACT_BACK     9
#define ACT_Fn(n)    (10+n)

extern tmapKeys KEY_STD_EDIT;
extern tmapKeys KEY_STD_LABEL;
extern tmapKeys KEY_STD_BUTTON;
extern tmapKeys KEY_STD_PANEL;
extern tmapKeys KEY_STD_TABLE;
extern tmapKeys KEY_STD_CALC;

int KEYS_iniatilize();

int KEYS_newMapKey(char * nomKeys, tmapKeys * mapKey);

tmapKeys * KEYS_getMapKey(char * nomKeys);

int KEYS_getMouse();

void KEYS_setMouse(int mouse);
int KEYS_isEnter(int caracter);
int KEYS_isInsert(int caracter);
int KEYS_isBackspace(int caracter);
int KEYS_isDelete(int caracter);
int KEYS_isHome(int caracter);
int KEYS_isEnd(int caracter);


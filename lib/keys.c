#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <tBasic.h>
#include <keys.h>


static tLkeys * comienzo = NULL;
static tLkeys * final = NULL;

int hasMouse = 1; /* Has mouse */ 

#include <mapKeys.h> 

int KEYS_iniatilize()
{
  tLkeys * teclas;

  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
 
  comienzo = final = teclas;
  strcpy(teclas->nomKeys,NOM_STD_COMPONENT);
  teclas->mapkeys=(tmapKeys *)&KEY_STD_PANEL;
  teclas->siguiente = NULL;

  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
  final->siguiente = teclas;
  strcpy(teclas->nomKeys,NOM_STD_TABLE);
  teclas->mapkeys = (tmapKeys *)&KEY_STD_TABLE;
  teclas->siguiente = NULL;
  final = teclas;

  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
  final->siguiente = teclas;
  strcpy(teclas->nomKeys,NOM_STD_LABEL);
  teclas->mapkeys = (tmapKeys *)&KEY_STD_LABEL;
  teclas->siguiente = NULL;
  final = teclas;
  
  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
  final->siguiente = teclas;  
  strcpy(teclas->nomKeys,NOM_STD_BUTTON);
  teclas->mapkeys = (tmapKeys *)&KEY_STD_BUTTON;
  teclas->siguiente = NULL;
  final = teclas;

  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
  final->siguiente = teclas;  
  strcpy(teclas->nomKeys,NOM_STD_EDIT);
  teclas->mapkeys = (tmapKeys *)&KEY_STD_EDIT;
  teclas->siguiente = NULL;
  final = teclas;
  return 0;
}

int KEYS_newMapKey(char * nomKeys, tmapKeys * mapKey)
{
  tLkeys * teclas;

  teclas = malloc(sizeof(tLkeys));
  if (teclas == NULL)
  {
    ERR_fatalError(ERR_MEM," Error key malloc (%d)\n",sizeof(tLkeys));
  }
  final->siguiente = teclas;  
  strcpy(teclas->nomKeys,nomKeys);
  teclas->mapkeys = mapKey;
  teclas->siguiente = NULL;
  final = teclas;
  return 0;
}

tmapKeys * KEYS_getMapKey(char * nomKeys)
{
  
  tLkeys * teclas;

  teclas = comienzo;
  while (teclas != NULL)
  {
     if (strcmp(teclas->nomKeys,nomKeys) == 0)
     {
        return teclas->mapkeys;
     }
     teclas = teclas->siguiente;
  }
  return NULL;
}

int KEY_action(char * nomKeys,int key)
{
  tmapKeys * mapKey;
  int i,j;

  mapKey = KEYS_getMapKey(nomKeys);

  if (mapKey == NULL)
    return -1; 

  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->enter[i] == key) return ACT_ENTER;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->out[i] == key) return ACT_OUT;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->next[i] == key) return ACT_NEXT;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->previous[i] == key) return ACT_PREVIOUS;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->up[i] == key) return ACT_UP;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->down[i] == key) return ACT_DOWN;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->left[i] == key) return ACT_LEFT;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->right[i] == key) return ACT_RIGHT;
  for (i=0;i!= MAX_KEYS_FUNC;i++) 
    if (mapKey->back[i] == key) return ACT_BACK;
  for (i=0;i!= MAX_Fn_KEYS;i++) 
   for (j=0;j!= MAX_KEYS_FUNC;j++) 
    if (mapKey->Fn[i][j] == key) return ACT_Fn(i);

  return ACT_NO;
}

int KEYS_getMouse()
{
  return hasMouse;
}

void KEYS_setMouse(int mouse)
{
  hasMouse = mouse;
}

int KEYS_isEnter(int caracter)
{
 if (caracter==14 || caracter == 10 || caracter== KEY_ENTER)
  return 1;

 return 0;
}

int KEYS_isInsert(int caracter)
{
 if (caracter == KEY_IC || caracter == 589)
  return 1;

 return 0;
}

int KEYS_isBackspace(int caracter)
{
 if (caracter == KEY_BACKSPACE)
  return 1;

 return 0;
}

int KEYS_isDelete(int caracter)
{
  if (caracter == KEY_DC || caracter == 586 )
   return 1;

 return 0;
}

int KEYS_isHome(int caracter)
{
  if (caracter == KEY_A1)
   return 1;

 return 0;
}

int KEYS_isEnd(int caracter)
{
  if (caracter == KEY_C1)
   return 1;

 return 0;
}


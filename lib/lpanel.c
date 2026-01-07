#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>
#include <error.h>
#include <tBasic.h>
#include <lpanel.h>

static tlPanel * listaPaneles = NULL;

tPanel * LPANEL_searchPanel(short id, char * name)
{
 tlPanel * pPanels;

 pPanels = listaPaneles;

 while (pPanels != NULL)
 {
    if (id > 0)
    {
	if (pPanels->panel->id == id)
            return pPanels->panel;
    }
    else
    {
      if (strcmp(pPanels->panel->name,name) == 0)
        return pPanels->panel;
    }
   pPanels = pPanels->siguiente;
 }
 return NULL;
}

void LPANEL_addPanel(tPanel * panel)
{
  tlPanel * pLPaneles = NULL;
  tlPanel * pLAux = NULL;
  
  if (LPANEL_searchPanel(0,panel->name) == NULL)
  {
    pLPaneles = malloc(sizeof(tlPanel));
    if (pLPaneles == NULL) 
     ERR_fatalError(ERR_MEM,"Fail malloc of panel <%d>\n",sizeof(tlPanel));

    pLPaneles->panel = panel; 
    pLPaneles->siguiente = NULL; 
    if (listaPaneles == NULL) listaPaneles = pLPaneles;
    else
    {
      pLAux = listaPaneles;
      while (pLAux->siguiente != NULL)
       pLAux = pLAux->siguiente;
      pLAux->siguiente = pLPaneles;
    }
  }
}

void LPANEL_delPanel(tPanel * panel)
{
  tlPanel * pLAux = NULL;

  if (panel == listaPaneles->panel)
  {
      listaPaneles = listaPaneles->siguiente;
      return;
  }
  pLAux = listaPaneles;
  while (pLAux != NULL)
  {
    if (pLAux->siguiente->panel == panel)
     pLAux->siguiente = pLAux->siguiente->siguiente;

    pLAux= pLAux->siguiente;
  }
  return;
}


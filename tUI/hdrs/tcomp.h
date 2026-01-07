void COMP_set(tXmlComponentPtr cab, tXmlComponentPtr ult);

void COMP_reset();

tXmlComponentPtr COMP_get();

trAction* COMP_reqMoves (tComponent * component,int key);
trAction* COMP_reqCalls (tComponent * component,int key);

void COMP_addComp(tXmlComponentPtr comp);
void COMP_delComp(tXmlComponentPtr comp);

tXmlMove * COMP_getCompMove(char * dato);

tXmlMove * COMP_getCompAppMove(char * dato);

trAction* COMP_setCallFrm (tComponent * component,int key); 

trAction* COMP_callFrm (tComponent * component,int key);

trAction* COMP_callSelect (tComponent * component,int key);

tXmlComponentPtr COMP_searchComp(char * panel, char * name);
unsigned short int COMP_searchUseColor(char * color);
unsigned short int COMP_searchUseKeymap(char * keymap);
unsigned short int COMP_searchUseEdf(char * edf);
tXmlFApplication * COMP_getCalls();

SCREEN * PROY_testScreen();
char * PROY_getTestTerm();
char * PROY_getTestTty();
tXmlProyectPtr PROY_getProyect();
tXmlPropPtr PROY_getProperties();
void PROY_loadProperties(tPanel * panel);
trAction* PROY_close (tComponent *,int );
trAction* PROY_new (tComponent *,int );
trAction* PROY_open (tComponent *,int );
trAction* PROY_save (tComponent *,int );
void PROY_loadSave(tPanel * panel);
trAction* PROY_test (tComponent *,int );
void PROY_replace(tComponent * component);
trAction* PROY_properties (tComponent *,int );
int PROY_isColor();


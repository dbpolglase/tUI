tXmlMapKeyPtr KEYMAP_get();
void KEYMAP_set(tXmlMapKeyPtr cab, tXmlMapKeyPtr ult);
void KEYMAP_reset();
tXmlMapKeyPtr KEYM_get();

trAction* KEYM_new (tComponent *,int );
trAction* KEYM_change (tComponent * component,int key);
tXmlMapKey * KEYM_search(char * name);
void KEYM_load();


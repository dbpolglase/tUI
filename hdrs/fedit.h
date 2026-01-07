int FEDIT_checkEdit(int tipo, int * caracter);
int FEDIT_checkPersonal(int tipo, int * caracter);
int FEDIT_addCheck(unsigned short tipo, unsigned short align,
		  unsigned short insert,
		  int (*checkEdit)(int * caracter));
int FEDIT_getAlign(int tipo );
int FEDIT_getInsert(int tipo );

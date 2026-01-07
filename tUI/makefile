CFLAGS = -c -Wall -g -I./hdrs -I../hdrs -Dlinux -I/usr/include/libxml2

LFLAGS = -g -I.
CC = gcc -ansi  -D__USE_GNU -D_GNU_SOURCE
#cc = gcc 
AR = ar r
LINT= lint
LEX=lex
YACC=yacc
LFLAGS=-o
#LFLAGS=-d -o 
#YFLAGS=-t -H -o
YFLAGS=-H -o 
DIR_RESULTADOS=../liberacion
DIR_CABECERAS=../includes
ODIR=obj

PROYECT=tUI

_OBJETOS_PROYECT=tmain.o tproyect.o tcolor.o tmsg.o tedf.o tview.o tprintXml.o tkeymap.o tselect.o tview.o tcomp.o tmove.o trun.o tfunc.o ttest.o $(PROYECT).o

OBJETOS_PROYECT = $(patsubst %,$(ODIR)/%,$(_OBJETOS_PROYECT))
LBFLAGS=-L../$(ODIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

todo: dotmake maketUI 

dotmake: 
	../$(ODIR)/tbuildo -f tUI.xml -r
	mv *.h hdrs
	$(CC) $(CFLAGS) -o obj/$(PROYECT).o $(PROYECT).c

maketUI: $(OBJETOS_PROYECT) 
	$(CC) $^ -o ../$(ODIR)/$(PROYECT) $(LBFLAGS) -ltui -L../tbuild -lparser -lncursesw -lxml2
	$(CC) $^ -o ../$(ODIR)/$(PROYECT)o $(LBFLAGS) -l:libtui.a -L../tbuild -l:libparser.a -lncursesw -lxml2


clean:	
	rm -f $(ODIR)/*
	rm -f $(PROYECT).c
	rm -f $(PROYECT)_*

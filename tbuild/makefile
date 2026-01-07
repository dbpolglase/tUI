CFLAGS = -c -Wall -fPIC -g -I./hdrs -I../hdrs -Dlinux -I/usr/include/libxml2

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

_OBJETOS_BUILD=main.o tparser.o tbuild.o
OBJETOS_BUILD = $(patsubst %,$(ODIR)/%,$(_OBJETOS_BUILD))

OBJETOS_LIB=./obj/tparser.o 
LBFLAGS=-L../../install/lib
ODIR=obj


$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

todo: build  libreria install

build: $(OBJETOS_BUILD)
	$(CC) $^ -o ./obj/tbuild  -L../obj -ltui -lncursesw -lxml2
	$(CC) $^ -o ./obj/tbuildo  -L../obj -l:libtui.a -lncursesw -lxml2

libreria: $(OBJETOS_LIB)
	ar $(AR) ./obj/libparser.a $(OBJETOS_LIB);
	$(CC) -shared -o ./obj/libparser.so $(OBJETOS_LIB);


proyect1: doproyect1 makeproyect1 

doproyect1:
	./build x3.xml

makeproyect1: $(OBJETOS_PROYECT1)
	$(CC) $^ -o pr1 -L../tcurses/obj -ltui -lncursesw
	$(CC) $^ -o pr1o -L../tcurses/obj -l:libtui.a -lncursesw


clean:	
	rm -f $(ODIR)/*

install:
	cp $(ODIR)/*.a ../obj
	cp $(ODIR)/*.so ../obj
	cp $(ODIR)/tbuild* ../obj 2> /dev/null
	cp $(ODIR)/tbuildo* ../obj 2> /dev/null
	cp *.xsd ../obj 2> /dev/null

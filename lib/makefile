CFLAGS = -c -g -I./hdrs -I../hdrs -Dlinux -fPIC
LFLAGS = -g -I.
#CC = gcc -ansi  -Wall -D__USE_GNU -D_GNU_SOURCE -D_XOPEN_SOURCE=700
CC = gcc -ansi  -Wall -D_XOPEN_SOURCE=700
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

_OBJETOS=msg.o fedit.o error.o keys.o text.o color.o back.o visual.o  component.o view.o lview.o panel.o table.o edit.o 
OBJETOS = $(patsubst %,$(ODIR)/%,$(_OBJETOS))
LBFLAGS=-L../../install/lib


$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

todo: libreria 

libreria: $(OBJETOS)
	ar $(AR) ../obj/libtui.a $(OBJETOS);
	$(CC) -shared -o ../obj/libtui.so $(OBJETOS);


clean:	
	rm -f $(ODIR)/*.o
	rm -f $(ODIR)/*.a

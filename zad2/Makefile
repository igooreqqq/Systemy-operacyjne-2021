.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = cw2
NAME2 = exec


#program wykonawczy
EXEC1  = $(NAME1).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS1  = 
#pliki naglowkowe
HEADS1 = 

#program wykonawczy
EXEC2  = $(NAME2).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS2  = $(NAME2).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS2  = 
#pliki naglowkowe
HEADS2 = 

#----------------------------------------------------------------------
#opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O
LDLIBS = -lm
CO = gcc
LD = $(CO)
AR = ar
ARFLAGS = rsv
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2) 
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runcw2
runcw2: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2)
	

#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

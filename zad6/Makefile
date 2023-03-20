.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = powielacz
NAME2 = wykluczanie
NAME3 = funkcje
NAME4 = biblioteka

#program wykonawczy
EXEC1  = $(NAME1).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
OBJS3  = $(NAME3).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS1  = 
#pliki naglowkowe
HEADS1 = $(NAME4).h

#program wykonawczy
EXEC2  = $(NAME2).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS2  = 
#pliki naglowkowe
HEADS2 = $(NAME4).h


#----------------------------------------------------------------------
#opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -pthread
LFLAGS = -Wall -std=c99 -pedantic -pthread
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
$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS1) $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS2) $(HEADS2) $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

	
.PHONY: run6
run6: $(EXEC1) $(EXEC2) 
	./$(EXEC1) $(EXEC2) numer.txt 3 2
	

#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

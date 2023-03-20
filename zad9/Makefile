.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = thread


#program wykonawczy
EXEC1  = $(NAME1).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS1  = 
#pliki naglowkowe
HEADS1 = 


#----------------------------------------------------------------------
#opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic
LDLIBS = -lpthread
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
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)

	
	
.PHONY: run9
run9: $(EXEC1)
	./$(EXEC1) 5 3
	
	
	
#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

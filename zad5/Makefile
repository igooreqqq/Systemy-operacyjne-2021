.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = main
NAME2 = producent
NAME3 = konsument

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

#program wykonawczy
EXEC3  = $(NAME3).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS3  = $(NAME3).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS3  = 
#pliki naglowkowe
HEADS3 = 


#----------------------------------------------------------------------
#opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic
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
all: $(EXEC1) $(EXEC2) $(EXEC3) 
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) $(LIBS3) 
	$(LD) -o $@ $(LFLAGS) $^

	
.PHONY: run5
run5: $(EXEC1) $(EXEC2) $(EXEC3) 
	./$(EXEC1) $(EXEC2) $(EXEC3) fifopipe in.txt out.txt
	diff -s in.txt out.txt
	
	
.PHONY: run5b1
run5b1: $(EXEC2) $(EXEC3) 
	xterm -hold -title PRODUCENT -e ./producent.x fifopipe in.txt &
	
.PHONY: run5b2
run5b2: $(EXEC2) $(EXEC3) 
	xterm -hold -title KONSUMENT -e ./konsument.x fifopipe out.txt
	
	

#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

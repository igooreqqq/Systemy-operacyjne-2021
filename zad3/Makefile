.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = 3a
NAME2 = 3b
NAME3 = 3c
NAME4 = 3c2

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

#program wykonawczy
EXEC4  = $(NAME4).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS4  = $(NAME4).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS4  = 
#pliki naglowkowe
HEADS4 = 

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
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) $(LIBS3) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4) $(LIBS4) 
	$(LD) -o $@ $(LFLAGS) $^
	
.PHONY: run3a
run3a: $(EXEC1)
	./$(EXEC1) $(opcja) $(sygnal)
	
.PHONY: run3b
run3b: $(EXEC2) $(EXEC1)
	./$(EXEC2) $(EXEC1) $(opcja) $(sygnal)
	
.PHONY: run3c
run3c: $(EXEC3) $(EXEC4) $(EXEC1)
	./$(EXEC3) $(EXEC4) $(EXEC1) $(opcja) $(sygnal)
	

#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

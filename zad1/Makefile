.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = a
NAME2 = b
NAME3 = c
NAME4 = d
NAME5 = e

#program wykonawczy
EXEC1  = $(NAME1).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS1  = 
#pliki naglowkowe
HEADS1 = 
#----------------------------------------------------------------------
EXEC2  = $(NAME2).x
OBJS2  = $(NAME2).o
LIBS2  = 
HEADS2 = 
#----------------------------------------------------------------------
EXEC3  = $(NAME3).x
OBJS3  = $(NAME3).o
LIBS3  = 
HEADS3 = 
#----------------------------------------------------------------------
EXEC4  = $(NAME4).x
OBJS4  = $(NAME4).o
LIBS4  = 
HEADS4 = 
#----------------------------------------------------------------------
EXEC5  = $(NAME5).x
OBJS5  = $(NAME5).o
LIBS5  = 
HEADS5 = 
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
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) 
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runA
runA: $(EXEC1)
	./$(EXEC1)
#---------------------------------------------------------------------
$(EXEC2): $(OBJS2) $(LIBS2) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runB
runB: $(EXEC2)
	./$(EXEC2)
#---------------------------------------------------------------------
$(EXEC3): $(OBJS3) $(LIBS3) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runC
runC: $(EXEC3)
	./$(EXEC3)
#----------------------------------------------------------------------
$(EXEC4): $(OBJS4) $(LIBS4) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runD
runD: $(EXEC4)
	./$(EXEC4)
#----------------------------------------------------------------------
$(EXEC5): $(OBJS5) $(LIBS5) 
	$(LD) -o $@ $(LFLAGS) $^
.PHONY: runE
runE: $(EXEC5)
	./$(EXEC5)
#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

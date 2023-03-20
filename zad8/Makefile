.SUFFIXES: .c .cpp .o .x .h
#----------------------------------------------------------------------
DIR = `basename $(CURDIR)`

#nazwy ktorych bedziemy uzywac
NAME1 = serwer
NAME2 = klient
NAME3 = funkcje
NAME4 = nazwa

#program wykonawczy
EXEC1  = $(NAME1).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
OBJS3  = $(NAME3).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS1  = 
#pliki naglowkowe
HEADS1 = $(NAME3).h
HEADS4 = $(NAME3).h

#program wykonawczy
EXEC2  = $(NAME2).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
#dolaczane biblioteki, makra moga byc puste na przyszlosc
LIBS2  = 
#pliki naglowkowe
HEADS2 = $(NAME3).h
HEADS4 = $(NAME4).h


#----------------------------------------------------------------------
#opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic
LDLIBS = -lrt
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
$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS1) $(OBJS3) $(HEADS4)
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)
$(EXEC2): $(OBJS2) $(LIBS2) $(HEADS2) $(OBJS3) $(HEADS4)
	$(LD) -o $@ $(LFLAGS) $^ $(LDLIBS)
	
	
.PHONY: run8serwer
run8serwer: $(EXEC1)
	xterm -hold -title SERWER -bg DARKGREEN -e ./serwer.x &
	
.PHONY: run8klient
run8klient: $(EXEC2)
	xterm -hold -title KLIENT1 -bg DARKRED -e ./klient.x &
	
.PHONY: run8klient2
run8klient2: $(EXEC2)
	xterm -hold -title KLIENT2 -bg DARKBLUE -e ./klient.x &
	
	
#----------------------------------------------------------------------
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

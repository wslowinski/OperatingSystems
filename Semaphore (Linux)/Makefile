.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = main
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o
LIBS1  = 

NAME2  = powielacz
EXEC2  = $(NAME2).x  
OBJS2  = $(NAME2).o
LIBS2  = 

NAME_ERR = error
NAME_CAP = cap
NAME_RAND = random
NAME_LIB = lib

HEADS3 = $(NAME_ERR).h 
HEADS4 = $(NAME_CAP).h
HEADS5 = $(NAME_LIB).h
HEADS6 = $(NAME_RAND).h

IMP3 = $(NAME_ERR).c
IMP4 = $(NAME_CAP).c
IMP5 = $(NAME_LIB).c
IMP6 = $(NAME_RAND).c


CFLAGS = 
CO = gcc -pthread
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC2): $(OBJS2) $(LIBS2) $(HEADS6) $(IMP6) $(HEADS3) $(IMP3) $(HEADS4) $(IMP4) $(HEADS5) $(IMP5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: powielacz
powielacz: $(EXEC2)

$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS3) $(IMP3) $(HEADS6) $(IMP6) $(HEADS4) $(IMP4) $(HEADS5) $(IMP5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: main
main: $(EXEC1)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x numer.txt
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))

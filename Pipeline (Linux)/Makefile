.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = main
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o
LIBS1  = 

NAME_CONS = consumer
NAME_PROD = producer
NAME_ERR = error
NAME_CAP = cap
NAME_MESS = message
NAME_RAND = random

HEADS1 = $(NAME_CONS).h
HEADS2 = $(NAME_PROD).h
HEADS3 = $(NAME_ERR).h 
HEADS4 = $(NAME_CAP).h
HEADS5 = $(NAME_MESS).h
HEADS6 = $(NAME_RAND).h

IMP1 = $(NAME_CONS).c
IMP2 = $(NAME_PROD).c
IMP3 = $(NAME_ERR).c
IMP4 = $(NAME_CAP).c
IMP5 = $(NAME_MESS).c
IMP6 = $(NAME_RAND).c

CFLAGS = 
CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS1) $(IMP1) $(HEADS2) $(IMP2) $(HEADS3) $(IMP3) $(HEADS4) $(IMP4) $(HEADS5) $(IMP5) $(HEADS6) $(IMP6)
	$(LD) -o $@ $(LFLAGS) $^


.PHONY: pipe
pipe: $(EXEC1)

.PHONY: compare
compare:
	diff -s $(in) $(out)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x a.out
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = 3a
NAME2 = 3b
NAME3 = 3c
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o
LIBS1  = 
EXEC2  = $(NAME2).x  
OBJS2  = $(NAME2).o
LIBS2  = 
EXEC3  = $(NAME3).x  
OBJS3  = $(NAME3).o
LIBS3  = 

NAMEid = identifiers
NAMEcap = cap
NAMEfun = my_signal_handler
NAMEmess = message


HEADS1 = $(NAMEid).h
HEADS2 = $(NAMEcap).h
HEADS3 = $(NAMEfun).h 
HEADS4 = $(NAMEmess).h


IMP1 = $(NAMEid).c 
IMP2 = $(NAMEcap).c
IMP3 = $(NAMEfun).c 
IMP4 = $(NAMEmess).c

CFLAGS = 
CO = gcc
LD = $(CO)

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS1) $(IMP1) $(HEADS2) $(IMP2) $(HEADS3) $(IMP3) $(HEADS4) $(IMP4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: 3a
3a: $(EXEC1)

$(EXEC2): $(OBJS2) $(LIBS2) $(HEADS1) $(IMP1) $(HEADS2) $(IMP2) $(HEADS3) $(IMP3) $(HEADS4) $(IMP4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: 3b
3b: $(EXEC2)

$(EXEC3): $(OBJS3) $(LIBS3) $(HEADS1) $(IMP1) $(HEADS2) $(IMP2) $(HEADS3) $(IMP3) $(HEADS4) $(IMP4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: 3c
3c: $(EXEC3)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
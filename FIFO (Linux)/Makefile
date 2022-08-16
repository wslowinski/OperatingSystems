.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = main
EXEC1  = $(NAME1).x  
OBJS1  = $(NAME1).o
LIBS1  = 

NAME2  = producer
EXEC2  = $(NAME2).x  
OBJS2  = $(NAME2).o
LIBS2  = $(NAME2).h

NAME3  = consumer
EXEC3  = $(NAME3).x  
OBJS3  = $(NAME3).o
LIBS3  = $(NAME3).h


NAME_ERR = error
NAME_CAP = cap
NAME_MESS = message
NAME_RAND = random

HEADS3 = $(NAME_ERR).h 
HEADS4 = $(NAME_CAP).h
HEADS5 = $(NAME_MESS).h
HEADS6 = $(NAME_RAND).h

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
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC2): $(OBJS2) $(LIBS2) $(HEADS6) $(IMP6) $(HEADS5) $(IMP5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: producer
producer: $(EXEC2)

$(EXEC3): $(OBJS3) $(LIBS3) $(HEADS6) $(IMP6) $(HEADS5) $(IMP5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: consumer
consumer: $(EXEC3)

$(EXEC1): $(OBJS1) $(LIBS1) $(HEADS3) $(IMP3) $(HEADS5) $(IMP5) $(HEADS4) $(IMP4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: main
main: $(EXEC1)

.PHONY: compare
compare:
	diff -s $(in) $(out)
	
.PHONY: MakeFIFO
MakeFIFO:
	mkfifo -m 0644 $(fifo)

.PHONY: PRODUCER
PRODUCER:
	xterm -hold -title PRODUCENT -e $(prog) $(in) $(fifo) &

.PHONY: CONSUMER
CONSUMER:
	xterm -hold -title KONSUMENT -e $(prog) $(out) $(fifo) 

.PHONY: RemoveFIFO
RemoveFIFO:
	unlink $(fifo)

.PHONY: clean tar

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x a.out
	
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))

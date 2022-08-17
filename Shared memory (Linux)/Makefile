.SUFFIXES: .c .o .x .h

CC			= gcc
CC_FLAGS	= -Wall -std=gnu99 -pedantic -O
STD_LIBS	= -pthread -lrt

AR			= ar
ARFLAGS 	= rsv

DIR			= `basename $(CURDIR)`
MAIN		= main
PRODUCER	= producer
PROD_FILE 	= in.txt
CONSUMER	= consumer
CONS_FILE 	= out.txt
LIB_NAME 	= library
LIB1_NAME	= sem_lib
LIB2_NAME	= sharedmemory
LIB_DIR		= ./lib

LIB_STAT = lib$(LIB_NAME).a

LIB_SHAR = lib$(LIB_NAME).so

.PHONY: all
all: $(MAIN)s.x $(PRODUCER)s.x $(CONSUMER)s.x $(MAIN)d1.x $(PRODUCER)d1.x $(CONSUMER)d1.x $(MAIN)d2.x $(PRODUCER)d2.x $(CONSUMER)d2.x

%.o: %.c
	$(CC) $(CC_FLAGS) -c $<

$(LIB_STAT): $(LIB1_NAME).o $(LIB2_NAME).o
	$(AR) $(ARFLAGS) $@ $^
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB1_NAME).o $(LIB2_NAME).o
	$(CC) -shared -o $@ $(CC_FLAGS) $^
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

%s.x: %.o $(LIB_STAT)
	$(CC) -o $@ $(CC_FLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(STD_LIBS)

%d1.x: %.o $(LIB_SHAR)
	$(CC) -o $@ $(CC_FLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(STD_LIBS) -Wl,-R $(LIB_DIR)

%d2.x: %.o $(LIB_SHAR)
	$(CC) -o $@ $(CC_FLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(STD_LIBS)

.PHONY: clean tar

clean:
	rm -f *.x *.o *.a -r; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR))

static: clean $(MAIN)s.x $(PRODUCER)s.x $(CONSUMER)s.x
	./$(MAIN)s.x $(PRODUCER)s.x $(CONSUMER)s.x $(PROD_FILE) $(CONS_FILE)
	diff -s $(PROD_FILE) $(CONS_FILE)

dynamic1: clean $(MAIN)d1.x $(PRODUCER)d1.x $(CONSUMER)d1.x
	./$(MAIN)d1.x $(PRODUCER)d1.x $(CONSUMER)d1.x $(PROD_FILE) $(CONS_FILE)
	diff -s $(PROD_FILE) $(CONS_FILE)

dynamic2: clean $(MAIN)d2.x $(PRODUCER)d2.x $(CONSUMER)d2.x
	(export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(MAIN)d2.x $(PRODUCER)d2.x $(CONSUMER)d2.x $(PROD_FILE) $(CONS_FILE) )
	diff -s $(PROD_FILE) $(CONS_FILE)
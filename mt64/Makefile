LIB 			= libMT64.so

CC 				= gcc
CFLAGS 		= -O3
LDFLAGS 	= -shared

INC 			= .
SRC 			= mt19937-64.c

all :
	$(CC) $(CFLAGS) -I $(INC) -o $(LIB) $(SRC) $(LDFLAGS)

clean :
	@rm $(LIB)
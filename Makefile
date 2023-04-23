# Main

CC 				= gcc
CFLAGS 		= -O3
LDFLAGS 	= -lm

INC 			= include
SRC 			= $(wildcard src/*.c)
OBJ				= $(patsubst src/%.c, obj/%.o, $(SRC))

MAIN  		= $(wildcard main/*.c)
BIN 			= $(patsubst main/%.c, %, $(MAIN))

# Dependencies

MT64 			= mt64
INC 		 += -I $(MT64)
LDFLAGS  += -Wl,-R $(MT64) -L $(MT64) -lMT64

# Rules

all : objdir $(OBJ) $(BIN)

objdir : 
	@mkdir -p obj

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

% : main/%.c 
	$(CC) $(CFLAGS) -I $(INC) -o $@ $< $(OBJ) $(LDFLAGS)

clean :
	@rm -r $(BIN) $(OBJ) obj

# Link dependencies

obj/Random.o : libmt64

# Build dependencies

libmt64 :
	make -C $(MT64)
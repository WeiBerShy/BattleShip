TARGETS= $(BIN_DIR)/BattleShip
BIN_DIR= ../bin
SRC_DIR= .
INC_DIR= ../inc
OBJ_DIR= ../obj
OBJS   = $(OBJ_DIR)/main.o \
		 $(OBJ_DIR)/sock-lib.o\
		 $(OBJ_DIR)/funciones.o 
CC     = gcc
FLAGS  = -g -Wall -I$(INC_DIR)


$(TARGETS): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGETS)	$(FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $< -o $@ $(FLAGS) -c -MD
	
-include $(OBJ_DIR)/*.d 

.PHONY: clean
clean:
	rm -r $(BIN_DIR) $(OBJ_DIR)
	
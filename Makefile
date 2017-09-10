CC = cc
C_FILES = $(wildcard src/*.c)
H_FILES = $(wildcard include/*.h)
OBJ = $(C_FILES:.c=.o)

OUT_EXE = polymer

build: $(OBJ)
	$(CC) -g -Wall -o $(OUT_EXE) $(C_FILES) main.c -include $(H_FILES)

clean:
	rm -f $(OBJ) core

rebuild: clean build

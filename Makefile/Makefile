CC=g++
OPCOES_COMPILADOR=-I./lib -I/usr/include/SOIL -lglut -lSDL_mixer -lGLU -lSOIL -lGLEW -lSDL -lGL -lm -lstdc++ -w
LIB=../lib/
SRC=../src/

TODOS_ARQUIVOS_PONTOH =
TODOS_ARQUIVOS_OBJ = $(SRC)main.o $(LIB)texto.o $(LIB)config.o $(LIB)texturas.o 

$(LIB)%.o: $(LIB)%.cpp
	@echo "Compilando as bibliotecas.."
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

$(SRC)%.o: $(SRC)%.cpp
	@echo "Compilando componentes do jogo.."
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run: all
	@./main

clean:
	@rm -f main
	@rm -f *.o
	@rm -f ../src/*.o
	@rm -f ../lib/*.o
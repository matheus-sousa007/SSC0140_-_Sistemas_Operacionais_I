#=======================================================
# Bacharelado em Ciências de Computação - Turma 2020
#=======================================================
# Makefile com comandos de compilação, execução e utilidades relacionadas ao programa
# make all: comando principal de compilação, que cria o executável
# make run: executa o programa
# make *.o: cria um dos arquivos objeto a partir da fonte
# make clean: remove todos os arquivos objeto do diretório atual
# make rebuild: como make all, mas recompila todos os arquivos objeto no diretório
# make zip: cria o arquivo zip para a submissão
#=======================================================

objects = main.o input.o output.o game.o player.o bomb.o game.o map.o item.o powerups.o
flags = -g -pthread -lncurses

all: $(objects) 
	g++ *.o -o main $(flags)

run: all
	./main 

.cpp.o: $source/*.cpp
	g++ $*.cpp -c $(flags)

clean:
	rm *.o -f
	rm main -f
	rm zip -fr
	rm *.zip -f

FORCE:
zip: FORCE
	rm code.zip -f
	mkdir zip -p
	rm zip/* -f
	cp *.cpp zip
	cp *.h zip
	cp makefile zip 
	zip code.zip zip/* -j

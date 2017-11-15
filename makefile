CC=gcc
route=

all: main_locality.o
	@$(CC) main_locality.o -o locality -Wall -lm -I.
	@rm main_locality.o
	@echo "Compilación terminada"

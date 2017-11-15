CC=gcc
route=

all: util.o image_reduction.o main_locality.o
	@$(CC) main_locality.o image_reduction.o util.o -o locality -Wall -lm -I.
	@rm main_locality.o util.o image_reduction.o
	@echo "Compilación terminada"

main_locality.o: $(route)main_locality.c
	@$(CC) -c $(route)main_locality.c

image_reduction.o: $(route)image_reduction.c
	@$(CC) -c $(route)image_reduction.c

util.o:	$(route)util.c
	@$(CC) -c $(route)util.c
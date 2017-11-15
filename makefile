CC=gcc
route=

all: util.o pixel.o bitmap_manager.o image_reduction.o main_locality.o
	@$(CC) main_locality.o image_reduction.o bitmap_manager.o pixel.o util.o -o locality -Wall -lm -I.
	@rm main_locality.o util.o image_reduction.o pixel.o bitmap_manager.o
	@echo "Compilación terminada"

main_locality.o: $(route)main_locality.c
	@$(CC) -c $(route)main_locality.c

image_reduction.o: $(route)image_reduction.c
	@$(CC) -c $(route)image_reduction.c

pixel.o: $(route)pixel.c
	@$(CC) -c $(route)pixel.c

bitmap_manager.o: $(route)bitmap_manager.c
	@$(CC) -c $(route)bitmap_manager.c

util.o:	$(route)util.c
	@$(CC) -c $(route)util.c
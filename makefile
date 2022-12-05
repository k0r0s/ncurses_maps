CC = gcc
CFLAGS = -lncurses -I./include
SOURCES = ./src/*.c 
OUTDIR = ./bin



all: map run clean

map: 
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTDIR)/map
run: 
	./bin/map

clean:
	rm bin/*

#if [ -d "${OUTDIR}" ]; then rm -r ${OUTDIR}; fi 

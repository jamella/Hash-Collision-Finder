CC = gcc
CFLAGS = -g -Wall
CRPFLAGS = -lcrypto
PRLFLAGS = -fopenmp

SRCDIR = ./src/
BUILDDIR = ./build/

all: serial_bin parallel_bin modular_serial_bin modular_parallel_bin tmpclean

serial: serial_bin tmpclean

parallel: parallel_bin tmpclean

modular_serial: modular_serial_bin tmpclean

modular_parallel: modular_parallel_bin tmpclean

serial_bin: serial_o md5.o generator.o
	$(CC) $(CFLAGS) $(CRPFLAGS) serial.o generator.o md5.o -o $(BUILDDIR)serial.bin 

parallel_bin: parallel_o md5.o generator.o
	$(CC) $(CFLAGS) $(CRPFLAGS) $(PRLFLAGS) parallel.o generator.o md5.o -o $(BUILDDIR)parallel.bin

modular_serial_bin: modular_serial_o md5.o generator.o
	$(CC) $(CFLAGS) $(CRPFLAGS) modular_serial.o generator.o md5.o -o $(BUILDDIR)modular_serial.bin

modular_parallel_bin: modular_parallel_o md5.o generator.o
	$(CC) $(CFLAGS) $(CRPFLAGS) $(PRLFLAGS) modular_parallel.o generator.o md5.o -o $(BUILDDIR)modular_parallel.bin

serial_o: $(SRCDIR)serial.c
	$(CC) $(CFLAGS) -c $(SRCDIR)serial.c

parallel_o: $(SRCDIR)parallel.c
	$(CC) $(CFLAGS) $(PRLFLAGS) -c $(SRCDIR)parallel.c

modular_serial_o: $(SRCDIR)modular_serial.c
	$(CC) $(CFLAGS) -c $(SRCDIR)modular_serial.c

modular_parallel_o: $(SRCDIR)modular_parallel.c
	$(CC) $(CFLAGS) $(PRLFLAGS) -c $(SRCDIR)modular_parallel.c

generator.o: $(SRCDIR)generator/generator.c $(SRCDIR)generator/generator.h
	$(CC) $(CFLAGS) -c $(SRCDIR)generator/generator.c 

md5.o: $(SRCDIR)md5/md5.c $(SRCDIR)md5/md5.h
	$(CC) $(CFLAGS) -c $(SRCDIR)md5/md5.c

tmpclean:
	rm *.o

clean:
	rm $(BUILDDIR)*.bin

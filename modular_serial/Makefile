output: main.o generator.o md5.o
	gcc main.o generator.o md5.o -o collision_finder -lcrypto -g

main.o: main.c
	gcc -c main.c -g

generator.o: generator.c generator.h
	gcc -c generator.c -g

md5.o: md5.c md5.h
	gcc -c md5.c -g

clean:
	rm *.o collision_finder

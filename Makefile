
$(CC) = gcc
final: main.o rbt.o
		$(CC) main.o rbt.o -o final

main.o: main.c rbt.h
		$(CC) -c main.c

rbt.o: rbt.c rbt.h
		$(CC) -c rbt.c

clean:
	rm *.o final
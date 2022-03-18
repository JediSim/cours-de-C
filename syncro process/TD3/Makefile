
all: main

main: main.o clean
	gcc -lpthread main.c train.c -o train_socket

clean:
	rm -f *.o a.out
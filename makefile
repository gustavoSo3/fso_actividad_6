all: ejer1 ejer2

ejer1: ejer1.c
	gcc -o ejer1 ejer1.c -lpthread -lm

ejer2: ejer2.c
	gcc -o ejer2 ejer2.c -lpthread -lm

clean:
	rm ejer1 ejer2
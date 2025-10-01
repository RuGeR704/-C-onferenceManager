main: data.o orario.o evento.o codaEventi.o agenda.o utils.o main.o
	gcc data.o orario.o evento.o codaEventi.o agenda.o utils.o main.o -o main

test: data.o orario.o evento.o codaEventi.o agenda.o utils.o test.o
	gcc data.o orario.o evento.o codaEventi.o agenda.o utils.o test.o -o test

data.o: data.h
	gcc -c data.c

orario.o: orario.h
	gcc -c orario.c

evento.o: data.h orario.h evento.h
	gcc -c evento.c

codaEventi.o: data.h evento.h codaEventi.h
	gcc -c codaEventi.c

agenda.o: data.h orario.h evento.h agenda.h
	gcc -c agenda.c

utils.o: utils.h
	gcc -c utils.c

main.o: data.h orario.h utils.h evento.h codaEventi.h agenda.h 
	gcc -c main.c

test.o: data.h orario.h utils.h evento.h codaEventi.h agenda.h 
	gcc -c test.c

clean: 
	rm -f *.o
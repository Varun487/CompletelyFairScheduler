test: DS_main.o DS_def.o
	gcc -o test DS_main.o DS_def.o

main.o: DS_main.c DS_dec.h
	gcc -c DS_main.c

def.o: DS_def.c DS_dec.h
	gcc -c DS_def.c
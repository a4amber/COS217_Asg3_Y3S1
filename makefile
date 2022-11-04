all: testsymtablelist testsymtablehash
	gcc217 testsymtablelist testsymtablehash -o all

testsymtablehash:  testsymtablehash.o
	gcc217 testsymtablehash.o testsymtablehash.o -o testsymtablehash

testsymtablehash.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c symtablehash.c

testsymtablelist:  testsymtablelist.o
	gcc217 testsymtablelist.o testsymtablelist.o -o testsymtablelist

testsymtablelist.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c symtablelist.c

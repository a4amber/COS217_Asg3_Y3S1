all: testsymtablelist testsymtablehash
	gcc217 -o all testsymtablelist testsymtablehash

testsymtablehash:  testsymtablehash.o
	gcc217 testsymtablehash.o testsymtablehash.o -o testsymtablehash

testsymtablehash.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c -o testsymtablehash.c

testsymtablelist:  testsymtablelist.o
	gcc217 testsymtablelist.o testsymtablelist.o -o testsymtablelist

testsymtablehash.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c -o testsymtablelist.c

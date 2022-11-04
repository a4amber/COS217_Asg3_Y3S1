all: testsymtablelist testsymtablehash
	gcc217 testsymtablelist testsymtablehash -o all

testsymtablehash:  symtablehash.o
	gcc217 symtablehash.o testsymtable.o -o testsymtablehash

testsymtablehash.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c symtablehash.c

testsymtablelist:  symtablelist.o
	gcc217 symtablelist.o testsymtable.o -o testsymtablelist

testsymtablelist.o: testsymtable.c symtablehash.c symtable.h
	gcc217 -c testsymtable.c symtablelist.c

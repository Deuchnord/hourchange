hourchange: hourchange.c
	gcc -c hourchange.c
	gcc hourchange.o -o hourchange

clear:
	rm *.o hourchange

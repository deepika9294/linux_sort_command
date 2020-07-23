sort : sort.o smain.o
	cc sort.o smain.o -lm -o sort
sort.o : sort.c sort.h
	cc -c sort.c
smain.o : smain.c sort.h
	cc -c smain.c

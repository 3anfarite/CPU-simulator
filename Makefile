output: main.o functions.o
	gcc main.o functions.o -o output

main.o: main.c
	gcc -c main.c

functions.o: functions.c functions.h structures.h
	gcc -c functions.c

clean:
	del *.o output

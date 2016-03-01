all: main.o set1.o encode.o decode.o
	gcc -g main.o set1.o encode.o decode.o -o hw1

main.o: main.c function.h
	gcc  -c -g  main.c

set1.o: set1.c function.h
	gcc  -c -g  set1.c

encode.o: encode.c function.h
	gcc -c -g  encode.c

decode.o: decode.c function.h
	gcc -g -c  decode.c

clean:
	rm *.o
	rm hw1

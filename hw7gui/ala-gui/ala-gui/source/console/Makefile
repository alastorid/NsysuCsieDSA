################################################
########Coded By B003040020@20121127############
################################################
all: main

main: main.o io.o compress.o decompress.o algo.o
	g++ -O3 main.o io.o compress.o decompress.o algo.o -o main
main.o: main.cpp

io.o: io.cpp

compress.o: compress.cpp

decompress.o: decompress.cpp

algo.o: algo.cpp

clean: 
	rm -rf *.[ois] main .depend

dep: g++ -M main.c >.depend

-include ".depend"
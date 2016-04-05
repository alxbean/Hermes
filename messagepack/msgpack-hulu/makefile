test: test.o hulu_define.o packTree.o
	gcc -g -o test packTree.o test.o hulu_define.o
test.o: test.c ./include/packTree.h
	gcc -g -c test.c
packTree.o : packTree.c ./include/packTree.h
	gcc -g -c packTree.c
hulu_define.o: hulu_define.c ./include/hulu_define.h
	gcc -g -c hulu_define.c  

clean:
	rm -f *.o

clear: 
	rm -r Merge
	rm -r Saida

run: 
	gcc -o teste *.c
	valgrind ./teste
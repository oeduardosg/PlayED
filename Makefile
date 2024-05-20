run:
	if [ -d "./Merge" ]; then rm -r Merge; fi
	if [ -d "./Saida" ]; then rm -r Saida; fi
	gcc -o teste *.c
	valgrind ./teste

version=$(shell uname -r)
a : forka.o threada.o
	echo "version : " ${version}
	gcc forka.o threada.o -o a -lpthread 
threada.o: threada.c
	gcc -c threada.c -o threada.o -lpthread 
forka.o: forka.c 
	gcc -c forka.c -o forka.o 

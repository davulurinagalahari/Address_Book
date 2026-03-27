addressbook.exe: main.o file.o contact.o populate.o
	gcc main.o file.o contact.o populate.o -o addressbook.exe

main.o: main.c
	gcc -c main.c

file.o: file.c
	gcc -c file.c

contact.o: contact.c
	gcc -c contact.c

populate.o: populate.c
	gcc -c populate.c

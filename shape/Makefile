
all:	main


main:	testgtk.c
	gcc -g -Wall -Wextra $^ -o main $(shell pkg-config --cflags --libs gtk+-3.0)


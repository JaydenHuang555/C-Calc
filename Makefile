CC=gcc
NAME=eval
ARGS =-g

FILES=$(shell ls *.c)

all:
	$(CC) -o $(NAME) $(ARGS) $(FILES) 
	


# Makefile for executable adjust

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -Wall 

#The option -Wall means to turn on all compiler warnings. 
# ****************************************************

# adjust: adjust.o grades.o
# 	$(CC) $(CFLAGS) -o adjust adjust.o grades.o
	
# adjust.o: adjust.c grades.h
# 	$(CC) $(CFLAGS) -c adjust.c

# grades.o: grades.c grades.h	 
# 	$(CC) $(CFLAGS) -c grades.c

# clean: 
# 	rm -f grades.o adjust.o adjust

# CC = gcc

# LDFLAGS =
# OBJFILES = project1.0
# TARGET = mvote
# all: $(TARGET)

# $(TARGET): $(OBJFILES)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
# clean:
# 	rm -f $(OBJFILES) $(TARGET) *~

OBJECTS: vote.o zip.o project1.o

all:  $(OBJECTS)
default: hi

project1: voterlist.o ziplist.o project1.o
	 gcc -g vote.o zip.o project1.o -o project1

vote.o:voter_info.h voterlist.h voterlist.c 
	gcc -c voterlist.c 

zip.o: vote.o voter_info.h ziplist.h ziplist.c
	gcc -c ziplist.c 

project1.o: vote.o zip.o hash.h project1.c
	gcc -c project1.c 












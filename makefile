OBJS = mainA3.o geometry.o
CC = g++
CFLAGS = -Wall -g
#LIBS =
EXEC = output

output: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

mainA3.o: mainA3.cpp geometry.h
	g++ -c mainA3.cpp

geometry.o: geometry.cpp geometry.h
	g++ -c geometry.cpp
	
clean: 
	rm -f $(EXEC) *.o

# target: dependencies
#	command(s)
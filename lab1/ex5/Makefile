CC = gcc
CCFLAGS = -Wall
ALL_CCFLAGS = -Wall -c
RM = rm
RMFLAGS = -f
OBJS = foo.o bar.o main



main: bar.o foo.o
	$(CC) -o $@ $(CCFLAGS) $^ 

bar.o: bar.c bar.h
	$(CC) -o $@ $(ALL_CCFLAGS) bar.c 

foo.o: foo.c foo.h bar.h
	$(CC) -o $@ $(ALL_CCFLAGS) foo.c

clean:
	$(RM) $(RMFLAGS) $(OBJS) 



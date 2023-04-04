# ----- Compiler & Flags -----
CC = gcc
FLAGS = -g
FLAGS_Error = -Wall -Werror -g
# -Wall: Recommended compiler warnings
# -g: Generate debugging information
# -Werror: Reject potentially unsafe format string arguments

# ----- Object and program files -----
# -o: Output a file

# Create prog
prog: functions.o main.o
	$(CC) functions.o main.o -o prog

# Create functions.o
functions.o: functions.c functions.h
	$(CC) -c functions.c $(FLAGS) -o functions.o

# Create main.o
main.o:	main.c functions.h
	$(CC) -c main.c $(FLAGS) -o main.o

# ----- Build Targets -----
# Build prog
all: prog

# Clean .o files and prog
clean:
	rm -f *.o
	rm -f prog

CC = gcc
CFLAGS = -g -Wno-unused-parameter
PROGRAMS = tests_ecosys ecosys
OBJECTS = ecosys.o main_tests.o main_tests2.o main_ecosys.o

.PHONY: all clean

all: $(PROGRAMS)

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

tests_ecosys2: ecosys.o main_tests2.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $<

make graph:
	gnuplot -e "set terminal png; set output 'evo.png'; plot 'Evol_Pop.txt' using 1:2 with lines title 'proies'; set output 'evo.png'; replot 'Evol_Pop.txt' using 1:3 with lines title 'predateurs'"

clean:
	rm -f *.o *~ $(PROGRAMS) evo.png

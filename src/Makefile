SRCS = $(wildcard experiment_*_*.c)

all: $(SRCS:.c=)

clean:
	rm *.o

.c:
	gcc -lm -O0 $(CPFLAGS) $< -o $@.o


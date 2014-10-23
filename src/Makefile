SRCS = $(wildcard experiment_*.c)

all: $(SRCS:.c=)

clean:
	rm *.o

.c:
	gcc -lm -O0 $(CPFLAGS) $< -o $@.o


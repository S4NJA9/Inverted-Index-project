CC = gcc
CFLAGS = -Wall -Wextra
OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

inverted_search: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) inverted_search
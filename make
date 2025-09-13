CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/Modified_shellex.c src/csapp.c
OUT = shellex

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT) *.o

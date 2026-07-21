CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
LDFLAGS  = -lcjson
TARGET   = parser

# List your source files
SRC      = src/main.c
OBJ      = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re

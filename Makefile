CC		= gcc
CFLAGS	= -Wall -Wextra -std=c99
LDFLAGS	= -lcjson
NAME	= parser

# List your source files
SRC		= src/main.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJ)

re: fclean all

.PHONY: all clean fclean re

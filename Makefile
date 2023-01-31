NAME = lem-in

CC = cc

CFLAGS = -Wall -Werror -Wextra -Wno-unused-variable -g

SD = ./src/
SRC =	main.c \
		graph.c \
		parser.c \
		creek.c \
		flow.c \
		flood.c \
		path.c 
SRF = $(addprefix $(SD),$(SRC))

OD = ./obj/
OBJ = $(SRC:.c=.o)
OBF = $(SRF:$(SD)%.c=$(OD)%.o)

all: $(NAME)

debug: fclean $(OBF)
	make -s -C ./lft
	$(CC) $(OBF) -D READ_INPUT=3 ./lft/libft.a -o $(NAME)


e: re
	cat map/default.map | ./$(NAME)

$(OD)%.o: $(SD)%.c
	@mkdir -p $(OD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBF)
	make -s -C ./lft
	$(CC) $(OBF) ./lft/libft.a -o $(NAME)

clean:
	make -s -C ./lft clean
	rm -rdf $(OD)

fclean: clean
	make -s -C ./lft fclean
	rm -rdf $(NAME)

re: fclean all

phony: all clean fclean re e

NAME = lem-in

CC = cc

CFLAGS = -Wall -Werror -Wextra -Wno-unused-variable -g

SD = ./src/
SRC =	tests.c \
		ft_graph.c
SRF = $(addprefix $(SD),$(SRC))

OD = ./obj/
OBJ = $(SRC:.c=.o)
OBF = $(SRF:$(SD)%.c=$(OD)%.o)

all: $(NAME)

e: all
	./$(NAME)

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

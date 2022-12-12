NAME = lem-in

CC = cc

CFLAGS = #-Wall -Werror -Wextra

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
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBF)
	make -C ./lft
	$(CC) $(OBF) ./lft/libft.a -o $(NAME)

clean:
	make clean -C ./lft
	rm -dfr ./obj/*.o

fclean: clean
	make fclean -C ./lft
	rm -rdf $(NAME)

re: fclean all
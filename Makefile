NAME = lem-in

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -Wno-unused-variable

SD = ./src/
SRC =	main.c \
		graph.c \
		parser.c \
		creek.c \
		flow.c \
		flood.c \
		../bonus/bonus.c

SRF = $(addprefix $(SD),$(SRC))

OD = ./obj/
OBJ = $(SRC:.c=.o)
OBF = $(SRF:$(SD)%.c=$(OD)%.o)

all: $(NAME)

test:
	make e | ./tester/tester.sh

e: re
	cat map/test.map | ./$(NAME)

bonus: gclean re
	cat map/Whyy.map | ./$(NAME) # | ./tester/tester.sh
	open -a /Applications/Obsidian.app bonus/Obsidian_Vault

gclean:
	@mv ./bonus/Obsidian_Vault/.obsidian ./bonus
	@rm -rdf ./bonus/Obsidian_Vault
	@mkdir ./bonus/Obsidian_Vault
	@mv ./bonus/.obsidian ./bonus/Obsidian_Vault/.obsidian

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
	rm -f bonus/*.o


re: fclean all

phony: all clean fclean re e

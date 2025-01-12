#OUTPUT NAME
NAME := lem-in

# Folders:
BUILD	= ./build
SOURCE	= ./src

# Other Variables:
COMPILER:=	cc
COMPFLAGS:=	-g #-Wall -Werror -Wextra -Wno-unused-variable 
DEFINES = -D DEBUG=1
DEFINES += -D BONUS=1

# Source Files:
SRCFILES:=	main.c \
			parsing.c \
			rivers.c \
			sending.c \
			utils.c \
			cleanup.c \
			../bonus/bonus.c

# ------------------------------------------
# Do not change anything beyond this point!
# ------------------------------------------

# Process Variables
CC:=		$(COMPILER)
CFLAGS:=	$(COMPFLAGS)
SRCS:=		$(addprefix $(SOURCE)/,$(SRCFILES))
OBJS:=		$(SRCS:$(SOURCE)/%.c=$(BUILD)/%.o)
NAME:=		./$(NAME)
OS:=		$(shell uname -s)

.PHONY: all clean fclean re e red clear green

LFT = ./ft_libft
LIBRARYS = -lm -I include -lglfw  $(LFT)/libft.a

 ifeq ($(SUBM_STATE),)
 SUBM_FLAG	= submodule
 else 
 SUBM_FLAG	= 
 endif

all: $(SUBM_FLAG) lib
	make -j $(nproc) $(NAME)

submodule: 
	@git submodule init 
	@git submodule update --remote

lib:
	make bonus -C $(LFT)

# Compile .cpp files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(DEFINES) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARYS)

clean:
	@make -s red
	rm -rdf $(BUILD)
	make clean -C $(LFT)
	@make -s clear

fclean: clean
	@make -s red
	rm -rdf $(NAME)
	@make -s clear

re: fclean all

bonus: clean
	rm -f ./bonus/Obsidian_Vault/*.md
	make
	./$(NAME) map/flow-ten_double.map
	open -a /Applications/./Obsidian.app/ bonus/Obsidian_Vault/

ree: re
	./$(NAME) map/flow-ten_double.map
e:
	make
	./$(NAME) map/flow-ten_double.map

red:
	echo $(RED)
green:
	echo $(GRN)
clear:
	echo $(CLEAR)

.PHONY: all clean fclean re e red clear green
.SILENT: red clear green

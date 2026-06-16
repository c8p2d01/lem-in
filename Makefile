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
SRCFILES:=	graph/new_net.c \
			graph/new_link.c \
			graph/new_graph.c \
			graph/node_exist.c \
			graph/link_graphs.c \
			graph/are_linked.c \
			graph/linked_to.c \
			graph/unlink_graphs.c \
			graph/quad_tree.c \
			graph/qt_setup.c \
			graph/qt_debug.c \
			\
			parsing.c \
			loose_ends.c \
			pathing.c \
			visualizer.c \
			force.c \
			utils.c \
			cleanup.c

MAIN:=		$(SOURCE)/main.c

BONUS:=		$(SOURCE)/reposition.c

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

.PHONY: all clean fclean re e

LFT = ./ft_libft
LIBMLX = ./MLX42
LIBRARYS = -lm -I include -lglfw  $(LFT)/libft.a

#ifeq ($(SUBM_STATE),)
#SUBM_FLAG	= submodule
#else 
SUBM_FLAG	= 
#endif

ifeq ($(shell uname),Darwin)
	LIBRARYS += $(LIBMLX)/libmlx42.a -framework OpenGL -framework IOKit -lglfw
else ifeq ($(shell uname),Linux)
	LIBRARYS += $(LIBMLX)/libmlx42.a -pthread -lm -lglfw
endif

all: $(SUBM_FLAG) lib
	make -j $(nproc) $(NAME)

submodule: 
	@git submodule init
	@git submodule update --remote --init --recursive
	@cmake -S $(LIBMLX) -B $(LIBMLX)

lib:
	make bonus -C $(LFT)
	@make -C $(LIBMLX)

# Compile .c files to .o Files
$(OBJS): $(BUILD)%.o : $(SOURCE)%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(DEFINES) $< -o $@

# Main Build Rule
$(NAME): $(OBJS)
	@echo "--> Compiling Executable"
	$(CC) $(CFLAGS) $(MAIN) $(OBJS) -o $(NAME) $(LIBRARYS)

# Bonus Build Rule
bonus: $(OBJS)
	@echo "--> Compiling Executable"
	$(CC) $(CFLAGS) $(BONUS) $(OBJS) -o map_recalculation $(LIBRARYS)

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

ree: re
	./$(NAME) map/flow-ten_double.map
e:
	make
	./$(NAME) map/flow-ten_double.map

.PHONY: all clean fclean re e red clear green
.SILENT: red clear green

GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

NAME	= push_swap

CC		= clang
RM		= rm -f

LIB_NAME = libft
PRINTF = ft_printf

LIB_PATH = ./$(LIB_NAME)
PRINTF_PATH = ./$(PRINTF)
INCLUDE_PATH = ./include

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE_PATH) -I$(LIB_PATH) -I$(PRINTF_PATH)

OS := $(shell uname)

# operating systems
ifeq ($(OS), Linux)
	LDFLAGS = 
else ifeq ($(OS), Darwin)
	LDFLAGS = 
endif

SRCS =  push_swap.c init.c utils.c sort.c sort_utils.c \
		operations_push.c operations_swap.c operations_rotate.c operations_reverse_rotate.c \
		
OBJ := $(SRCS:%.c=%.o)

$(NAME): $(OBJ) $(LIB_PATH)/$(LIB_NAME).a $(PRINTF_PATH)/libftprintf.a
	@echo "$(GREEN)$(NAME) has started running $(RESET)"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) -L$(PRINTF_PATH) -lftprintf -L$(LIB_PATH) -lft
	@echo "$(GREEN)$(NAME) has ran $(RESET)"

$(LIB_PATH)/$(LIB_NAME).a:
	make -C $(LIB_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

$(PRINTF_PATH)/libftprintf.a:
	make -C $(PRINTF_PATH) CC="$(CC)" CFLAGS="$(CFLAGS)"

%.o:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

libft:
		make -C libft

ft_printf:
		make -C ft_printf

clean:
	make clean -C $(LIB_PATH)
	make clean -C $(PRINTF_PATH)
	${RM} ${OBJ}

fclean: clean
	${RM} $(NAME)
	make fclean -C $(LIB_PATH)
	make fclean -C $(PRINTF_PATH)

cln:
	make clean -C $(LIB_PATH)
	make clean -C $(PRINTF_PATH)
	${RM} ${OBJ}
	${RM} $(NAME)
	make fclean -C $(LIB_PATH)
	make fclean -C $(PRINTF_PATH)

re:			fclean all

.PHONY: all clean fclean re libft ft_printf

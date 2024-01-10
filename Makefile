CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=leak,address
LDFLAGS = -pthread

################################################################################

YELLOW = \033[0;33m

GREEN = \033[0;32m

Magenta = \033[0;35m

RED = \033[0;31m

RESET = \033[0m

################################################################################

NAME = cub3D

SRC =	src/main.c
OBJ = $(SRC:.c=.o)

################################################################################

.PHONY: all clean fclean re debug bonus

all: $(NAME)

clean:
	@echo "$(Magenta)Cleaning $(OBJ)!$(RESET)"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)!$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

################################################################################

$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(GREEN)Finished buidling $@!$(RESET)"

$(OBJ): %.o: %.c
	@echo "$(YELLOW)Compiling $@ from $^...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^
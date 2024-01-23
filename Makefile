CC = cc
CFLAGS = -Wall -Wextra -Werror -Isrc -Ilibs/libft -Ilibs/MLX42/include/MLX42 -g -fsanitize=address -O3
LDFLAGS = -ldl -lglfw -pthread -lm #linux
# LDFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit	#naji's mac

################################################################################

YELLOW = \033[0;33m

GREEN = \033[0;32m

Magenta = \033[0;35m

RED = \033[0;31m

RESET = \033[0m

################################################################################

NAME = cub3D

SRC =	src/main.c src/errors.c src/color.c src/map.c \
		src/parser/parser.c \
		src/player.c \
		src/game.c \
 		src/parser/parser_layout.c \
		src/intersections.c \
		src/utils.c \
		src/helper.c \
		src/movements.c \
		src/mouse_movements.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libs/libft
MLX_DIR = libs/MLX42
LIB_MLX = $(MLX_DIR)/build/libmlx42.a
LIBFT = $(LIBFT_DIR)/libft.a 

################################################################################

.PHONY: all clean fclean re

all: $(NAME)

clean:
	@echo "$(Magenta)Cleaning $(OBJ)!$(RESET)"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)!$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

################################################################################

$(NAME):$(OBJ) $(LIBFT) $(LIB_MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIB_MLX) $(LDFLAGS)
	@echo "$(GREEN)Finished buidling $@!$(RESET)"

$(OBJ): %.o: %.c
	@echo "$(YELLOW)Compiling $@ from $^...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LIB_MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4
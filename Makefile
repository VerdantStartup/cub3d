TARGET := cube3D
LIBFT    := lib/libft/libft.a
MLX42    := lib/MLX42/build/libmlx42.a
SRC_DIR := src/
OBJ_DIR := obj/
CC 		:= gcc
CFLAGS := -Wunreachable-code -Ofast # -Wall -Wextra -Werror
LIBPATH  := -lglfw -L/opt/homebrew/opt/glfw/lib 
MLXFLAGS := $(MLX42) -framework Cocoa -framework OpenGL -framework IOKit $(LIBPATH)
INC      := -I inc/ -I lib/MLX42/include

SRC := $(wildcard $(SRC_DIR)*.c)
OBJ := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

## Debugging ##
ifdef DEBUG
		CFLAGS += -g -fsanitize=address
endif

all: $(TARGET)

$(TARGET): $(OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(CFLAGS) $(MLXFLAGS) $^ -o $@
	@echo "$(GREEN)Executable created.$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/cube3D.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft ...$(RESET)"
	@$(MAKE) -C lib/libft

$(MLX42):
	@echo "$(GREEN)Building MLX42 ...$(RESET)"
	@cd lib/MLX42 && cmake -B build && cmake --build build -j4 

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/MLX42/build clean
	@echo "$(RED)Object files removed.$(RESET)"

fclean: clean
	@rm -f $(TARGET)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all

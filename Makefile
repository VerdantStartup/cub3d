TARGET := cube3D
LIBFT    := lib/libft/libft.a
MLX42    := lib/MLX42/build/libmlx42.a
SRC_DIR := src/
OBJ_DIR := obj/
CC      := gcc
CFLAGS  := -Wunreachable-code -Ofast # -Wall -Wextra -Werror
# LIBPATH  := -L/opt/homebrew/opt/glfw/lib 
# LIB_INC := -I /Users/mwilsch/.brew/Cellar/glfw/3.3.8/include
LIBPATH  := -L/Users/mwilsch/.brew/Cellar/glfw/3.3.8/lib -lglfw
MAC_OS  := -framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS := $(MLX42) $(MAC_OS) $(LIBPATH)  -ldl -pthread -lm
INC     := -I inc/ -I lib/MLX42/include

# Include the parser and raycaster directories
SRC := $(wildcard $(SRC_DIR)*.c $(SRC_DIR)parser/*.c $(SRC_DIR)raycaster/*.c)
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

# Update the pattern rule for object files to create necessary directories
$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/*.h
	@mkdir -p $(@D)
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



### COMPILATION ###
CC      = gcc
FLAGS  = -Wall -Wextra -Werror

### EXECUTABLE ###
NAME   = cube
NAME_BONUS = philo_bonus

### INCLUDES ###
OBJ_PATH  = objs
HEADER = includes
SRC_PATH  = src
OBJ_PATH_BONUS  = Philosophers_bonus/objs
HEADER_BONUS = Philosophers_bonus/includes
SRC_PATH_BONUS  = Philosophers_bonus/src

### SOURCE FILES ###
SOURCES =     		0_main.c \
					1_cube.c \
					2_raycasting.c \
					3_hooks.c \
					cube_utils.c \
					hooks_utils.c \
					raycasting_utils.c \
					init/map.c \
					init/map_utils.c \
					init/map_error.c \
					init/player_init.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					bonus/doors_bonus.c \
					bonus/doors_message_bonus.c \
					bonus/drawing_functs_bonus.c \
					bonus/minimap_bonus.c \
					bonus/hooks_bonus.c \


SOURCES_BONUS =    	main.c \
					philo_bonus.c \
					init_bonus.c \
					utils_bonus.c \

MLX = mlx_linux
### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))
SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS)/,$(SOURCES_BONUS))
OBJS_BONUS = $(addprefix $(OBJ_PATH_BONUS)/,$(SOURCES_BONUS:.c=.o))


### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: $(NAME) mlx
	./cube maps/arbesa.cub

$(NAME): $(OBJS)
	$(CC) $(FLAGS)  -L ${MLX} -o $@ $^ -lmlx -lXext -lX11 -lm -lz
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/*.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(OBJ_PATH_BONUS)/*.o

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -rf $(OBJ_PATH)
	@rm -rf $(OBJ_PATH_BONUS)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

bonus: $(NAME_BONUS)
	
$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH_BONUS)/%.o: $(SRC_PATH_BONUS)/%.c $(HEADER_BONUS)/*.h
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

norminette:
	@norminette src/ includes/

mlx:
	@cd $(MLX) && $(MAKE)

re: fclean
	@$(MAKE) all

.PHONY: re fclean clean norminette bonus mlx
NAME	= cub3d_bonus
CFLAGS	= -fsanitize=address -g #-Wextra -Wall -Werror 
LIBMLX	= ~/MLX42
CC		= cc

HEADERS	= -I ./include -I $(LIBMLX)/include/MLX42
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= cub3d_bonus.c raycasting_bonus/player_action_bonus.c raycasting_bonus/init_struct_bonus.c raycasting_bonus/utils_bonus.c raycasting_bonus/draw_map_bonus.c \
		raycasting_bonus/player_movement_bonus.c raycasting_bonus/raycasting_bonus.c raycasting_bonus/player_direction_bonus.c raycasting_bonus/utils2_bonus.c \
		parsing_bonus/parsing_bonus.c parsing_bonus/ft_free_bonus.c parsing_bonus/border_check_bonus.c parsing_bonus/elements_bonus.c parsing_bonus/map_bonus.c parsing_bonus/parsing_error_bonus.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		libft/ft_split.c libft/ft_substr.c libft/ft_mini_strchr.c libft/ft_strlen.c libft/ft_strdup.c
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx: 
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c ./include/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: clean, libmlx
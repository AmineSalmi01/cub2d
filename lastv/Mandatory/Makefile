NAME	= cub3d
CFLAGS	= -fsanitize=address -g #-Wextra -Wall -Werror 
LIBMLX	= ~/MLX42
CC		= cc

HEADERS	= -I ./include -I $(LIBMLX)/include/MLX42
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= cub3d.c raycasting/player_action.c raycasting/init_struct.c raycasting/utils.c raycasting/draw_map.c \
		raycasting/player_movement.c raycasting/raycasting.c raycasting/player_direction.c raycasting/utils2.c raycasting/minimap.c \
		parsing/parsing.c parsing/ft_free.c parsing/border_check.c parsing/elements.c parsing/map.c parsing/parsing_error.c parsing/colors_check.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		libft/ft_split.c libft/ft_substr.c libft/ft_mini_strchr.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_isdigit.c libft/ft_atoi.c
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx: 
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c ./include/cub3d.h
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	#@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: clean, libmlx
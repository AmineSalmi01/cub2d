#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <math.h>
// #include <../../MLX42/include/MLX42/MLX42.h>
#include <MLX42.h>

#define UNIT_SIZE 30
#define FOV 60 * (M_PI / 180)
#define MOVE_SPEED 5
#define WIDTH 900
#define HEIGHT 600

typedef struct s_dda {
	int x0;
	int y0;
	int x1;
	int y1;
	int dx;
	int dy;
	int stepx;
	int stepy;
	int err;
	int e2;
}	t_dda;

typedef struct s_horizontal {
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double horzWallHitX;
	double horzWallHitY;
	bool foundHorzWall;
} t_horizontal;

typedef struct s_vertical {
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double vertWallHitX;
	double vertWallHitY;
	bool foundVertWall;
} t_vertical;

typedef struct s_player {
	double position_x;
	double position_y;
	double angle_rotation;
	double rotate_speed;
	double move_speed;
	int rotate_direction;
	int move_direction;
	mlx_image_t *player_image;
} t_player;

typedef struct s_ray {
	double wallHitX;
	double wallHitY;
	double ray_angle;
	double line_hight;
	double distance;
	bool foundHorz;
	bool foundVert;
} t_ray;

typedef struct s_game {
	int width;
	int height;
	double rays_number;
	char **map;
	char **elements;
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	char *floor_color;
	char *ceiling_color;
	char *trash;
	mlx_t *mlx;
	mlx_image_t *image;
	t_ray *rays;
	t_player player;
	t_vertical vertical;
	t_horizontal horizontal;
} t_game;

// parsing function 

int		ft_strlen(char *s);
int		ft_mini_strchr(char s, char *c);
int     ft_strcmp(char *s1, char *s2);
int	ft_strstr(char *src, char *dst, int i);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, int start, int len);
char	**ft_split(char *s, char *c);
char	*get_next_line(int fd);

size_t 	count_width(char **map);
size_t 	count_height(char **map);
int		elements_counter(char *map_name);
void	ft_free(char **arr);
int		map_finder(char *str);
void    elements(t_game *game, char *line);
void	map(t_game *game, char *line);
int		struct_elements(t_game *game);
int		borders(t_game *game);
int		parsing_error(t_game *game);
int	file_check(char *name);

size_t count_width(char **map);
size_t count_height(char **map);
void parsing(t_game *game, char *line);

// raycast function 
void	init_struct(t_game *game);
void	draw_background(t_game *game);
void	draw_wall(t_game *game);
void	draw_player(t_game *game);
void 	draw_line(t_game *game, t_ray ray);
void 	dda_test(t_game *game, t_ray ray);
void	rebuild_game(t_game *game);

void 	right_move(t_game *game);
void	left_move(t_game *game);
void	backward_move(t_game *game);
void	forward_move(t_game *game);

bool	is_facing_down(double angle);
bool	is_facing_up(double angle);
bool	is_facing_right(double angle);
bool	is_facing_left(double angle);
bool 	is_wall(t_game *game, double x, double y);

void	key_hook(mlx_key_data_t key, void *param);

double	normalize_angle(double angle);
void 	find_distance(t_game *game, t_ray *ray, double ray_angle);
void 	cast_rays(t_game *game);
double 	calculate_distance(double x1, double y1, double x2, double y2);

void 	render_wall(t_game *game, t_ray *ray);
unsigned int		rgbt_color(int t, int r, int g, int b);
int depth_color(double distance, int terp);
void find_player(t_game *game);
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
// #include </Users/asalmi/MLX42/include/MLX42/MLX42.h>
#include <MLX42.h>

#define UNIT_SIZE 30
#define FOV 60 * (M_PI / 180)
#define MOVE_SPEED 5
#define WIDTH 1000
#define HEIGHT 650
#define MINIMAP_SCALE 0.2
#define ZOOM 0.5

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

typedef struct s_doors {
	int x;
	int y;
	bool is_closed;
	bool is_open;
} t_doors;

typedef struct s_horizontal {
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double horzWallHitX;
	double horzWallHitY;
	bool foundHorzWall;
	bool closeHorzDoor;
	bool openHorzDoor;
	int x_open;
	int y_open;
} t_horizontal;

typedef struct s_vertical {
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	double vertWallHitX;
	double vertWallHitY;
	bool foundVertWall;
	bool closeVertDoor;
	bool openVertDoor;
	int x_open;
	int y_open;
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
	bool foundDoor;
	int h_openX;
	int h_openY;
	int v_openX;
	int v_openY;
	bool foundNO;
	bool foundSO;
	bool foundEA;
	bool foundWE;
	double h_distance;
	double v_distance;
	t_horizontal horz;
	t_vertical vert;
} t_ray;


typedef struct s_game {
	int width;
	int height;
	int minimap_width;
	int minimap_height;
	double rays_number;
	bool is_door;
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
	mlx_image_t *minimap_img;
	mlx_image_t *image;
	t_ray *rays;
	t_player player;
	t_vertical vertical;
	t_doors *doors;
	t_horizontal horizontal;
} t_game;

// parsing function 

int		ft_strlen(char *s);
int		ft_isdigit(char c);
int		ft_mini_strchr(char s, char *c);
int     ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
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
int		file_check(char *name);
int 	floor_color_check(t_game *game);
int 	floor_color_check_2(t_game *game);
int		ceiling_color_check(t_game *game);
int		ceiling_color_check_2(t_game *game);

size_t count_width(char **map);
size_t count_height(char **map);
int	doors_counter(t_game *game);
void parsing(t_game *game, char *line);

// raycast function 
void	init_struct(t_game *game);
void	draw_background(t_game *game);
void	draw_wall(t_game *game);
void 	draw_doors(t_game *game);
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
bool 	is_doors(t_game *game, double x, double y);
bool 	is_openDoor(t_game *game, double x, double y);

void	movement_hook(mlx_key_data_t key, void *param);
void 	mouse_hook(double xpos, double ypos, void *param);

double	normalize_angle(double angle);
void 	find_distance(t_game *game, t_ray *ray, double ray_angle);
void 	cast_rays(t_game *game);
double 	calculate_distance(double x1, double y1, double x2, double y2);

void 	render_wall(t_game *game, t_ray *ray);
unsigned int		rgbt_color(int t, int r, int g, int b);
int depth_color(double distance, int terp);
void find_player(t_game *game);
void draw_minimap(t_game *game);
void doors_allocted(t_game *game);
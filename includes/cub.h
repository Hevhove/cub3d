#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "mlx.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_pair {
	double	x;
	double	y;
}				t_pair;

typedef struct s_cub {
	/* minilibx */
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	/* parsing map */
	int		no_fd;
	int		so_fd;
	int		we_fd;
	int		ea_fd;
	int		floor_color;
	int		ceil_color;
	int		**map;
	int		map_height;
	int		map_width;
	t_pair	*pos;
	t_pair	*dir;
	t_pair	*proj_plane;
}				t_cub;

typedef struct s_parse_info {
	char	*buff;
	int		ret;
	int		line_nb;
	char	*line_trimmed;
	char	**line_content;
	char	*prefix;
	int		prefix_len;
	char	**colors;
	int		*colors_rgb;
	int		is_floor_color_set;
	int		is_ceil_color_set;
	char	*file_name;
	int		line_nb_map_start;
	size_t	max_map_width;
	int		is_player_set;
}				t_parse_info;

typedef enum e_map_code {
	IN = 0,
	WALL,
	OUT,
	PLAYER
}			t_map_code;

typedef enum e_error_code {
	ERRNO = 1,
	WRONG_ARGC,
	WRONG_FILE_EXT,
	FILE_INEXISTENT,
	MAP_INCORRECT
}			t_error_code;

/* DEAL with user INPUT */
int		check_args(int ac, char **av);

/* INITIALIZERS */
t_cub			init_cub(void);
t_parse_info	init_parse_info(void);
void			init_mlx(t_cub *cub);

/* PARSER */
void	validate_map(int map_fd, char *map_name, t_cub	*cub);
void	validate_map_info(int map_fd, t_cub *cub, t_parse_info* parse_info);
/* PARSER COLOR and TEXTURE */
int	textures_colors_not_set(t_cub *cub, t_parse_info *parse_info);
int	texture_or_color_is_valid(t_cub *cub, t_parse_info	*parse_info);
/* PARSER MAP */
void	evaluate_map_size(int map_fd, t_cub *cub, t_parse_info* parse_info);
void	validate_map_grid(int map_fd, t_cub *cub, t_parse_info* parse_info);
/* PARSER UTILS */
int		line_is_empty(char *line);
char	*replace_tab_with_spaces(char *line, t_cub *cub);

/* COLOR */
int		get_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

/* DEBUG */
void  print_cub(t_cub *cub);

/* FREE MEMORY */
void	free_cub(t_cub *cub);
void	free_split(char **split);
void	free_parse_info(t_parse_info *parse_info);
void	graceful_exit(t_cub *cub);

/* GAMEOVER - Error management */
void	error_message(t_error_code error_code);
int		error_and_return(t_error_code error_code, int return_value);
void	error_and_exit(t_error_code error_code, t_cub *cub);
void	error_and_exit_from_parsing(t_error_code error_code, t_cub *cub,
			t_parse_info *parse_info, int map_fd);
void	*calloc_or_exit(size_t size, int count, t_cub *cub);

/* UTILS */
int		has_right_file_ext(char *file_name, char *extension);
int		count_appearances(char *str, char c);
int		ft_split_len(char **split);
int		is_number(char *str);

#endif

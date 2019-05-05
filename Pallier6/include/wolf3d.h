#ifndef WOLF3D_H
# define WOLF3D_H

#include "../minilibx_macos/mlx.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>

# define WIN_WIDTH				1260
# define WIN_HEIGHT				720
# define TILE_SIZE				64
# define WALL_HEIGHT			64
# define TEXT_SIZE				32
# define mlx->mid_projectplane		WIN_HEIGHT / 2
# define ANGLE60				WIN_WIDTH
# define ANGLE30				(int)(ANGLE60 / 2)
# define ANGLE15				(int)(ANGLE30 / 2)
# define ANGLE10				(int)(ANGLE30 / 3)
# define ANGLE5					(int)(ANGLE15 / 3)
# define ANGLE0					0
# define ANGLE45				(int)(ANGLE15 * 3)
# define ANGLE90				(int)(ANGLE30 * 3)
# define ANGLE180				(int)(ANGLE90 * 2)
# define ANGLE270				(int)(ANGLE90 * 3)
# define ANGLE360				(int)(ANGLE90 * 4)
# define ABS(x)					(x < 0 ? -x : x)

typedef struct		s_rgba
{	
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_rgba;

typedef union		u_color
{
	int				value;
	t_rgba			rgba;
}					t_color;

typedef struct		s_ipos
{
	int				x;
	int				y;
}					t_ipos;

typedef struct		s_fpos
{
	float			x;
	float			y;
}					t_fpos;

typedef struct		s_user
{
	t_fpos			pos;
	int				distPlane;
	int				distMaxWall;
	uint8_t			up;
	short			down;
	short			left;
	short			right;
	int				moveSpeed;
	int				rotSpeed;
	int				pov;
}					t_user;

typedef struct		s_map
{
	int				height;
	int				width;
	char			**map;
}					t_map;

typedef struct		s_image
{
	void			*img;
	char			*ptr;
	int				bits;
	int				s_line;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct		s_mlx
{
	void			*mlx;
	void			*window;
	t_image			*img;
	t_user			user;
	t_map			*map;
	t_image			*tex[7];
	t_image			*floor;
	t_image			*sky;
	t_ipos			gridInter;
	short			init;
}					t_mlx;

int					error(char *msg);

t_mlx				*init(char *title, int width, int height);

t_map				*get_map(int fd);
int					open_file(t_mlx *mlx, char *str);

int					wallColor(int castDeg, t_fpos distToHitGrid);
void				drawWall(t_mlx *mlx, t_ipos cast, int heightWall, t_fpos distHitGrid);

int					initTextures(t_mlx *mlx);

void				setPixel(t_image *img, int x, int y, int color);
t_color				getPixel(t_image *img, int x, int y);
void				resetImage(t_image *img);
t_image				*delImage(t_mlx *mlx, t_image *img);
t_image				*newImage(t_mlx *mlx, int width, int height);
t_image				*fileToImage(char *xpm, t_mlx *mlx, int width, int height);

float				degToRad(int arcAngle);
int					is_DegRight(int castDeg);
int					is_DegDown(int castDeg);
float				get_Gap(int castDeg, int x_y);
void				get_FishTable(float fishTable[ANGLE60]);

void				rayCasting(t_mlx *mlx);

int					isBlock(t_map *map, int x, int y);
void				checkMoveWall(t_mlx *mlx, t_fpos diff);

int					keyPressed(int key, t_mlx *mlx);
int					keyReleased(int key, t_mlx *mlx);
int					mainEvents(t_mlx *mlx);

#endif

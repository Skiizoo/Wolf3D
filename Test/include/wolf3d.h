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
#include <pthread.h>

# define WIN_WIDTH				1260
# define WIN_HEIGHT				720
# define TILE_SIZE				64
# define WALL_HEIGHT			64
# define TEXT_SIZE				32
# define ANGLE60				WIN_WIDTH
# define ANGLE30				(int)(ANGLE60 >> 1)
# define ANGLE15				(int)(ANGLE30 >> 1)
# define ANGLE10				(int)(ANGLE30 / 3)
# define ANGLE20				(int)(ANGLE10 << 1)
# define ANGLE40				(int)(ANGLE20 << 1)
# define ANGLE50				(int)(ANGLE10 * 5)
# define ANGLE5					(int)(ANGLE15 / 3)
# define ANGLE0					0
# define ANGLE45				(int)(ANGLE15 * 3)
# define ANGLE90				(int)(ANGLE45 << 1)
# define ANGLE180				(int)(ANGLE90 << 1)
# define ANGLE270				(int)(ANGLE90 * 3)
# define ANGLE360				(int)(ANGLE90 << 2)

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
	int				height;
	int				mid_projectplane;
	int				distPlane;
	int				distMaxWall;
	uint8_t			up;
	uint8_t			down;
	uint8_t			left;
	uint8_t			right;
	uint8_t			lookup;
	uint8_t			lookdown;
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
	t_image			*tex[6];
	t_image			*floor;
	t_image			*sky;
	t_ipos			gridInter;
	t_ipos			cast;
	t_fpos			thread1;
	t_fpos			thread2;
	t_fpos			thread3;
	t_fpos			thread4;
	uint8_t			textures;
	uint8_t			shadow;
	float			fishTable[ANGLE60];
	pthread_mutex_t mutex;
}					t_mlx;

typedef	struct		s_params
{
	t_mlx			*mlx;
	pthread_t		thread;
	int				th_colstart;
	int				th_angstart;
	int				th_colend;
}					t_params;

int					error(char *msg);

t_mlx				*init(char *title, int width, int height);

t_map				*get_map(int fd);
int					open_file(t_mlx *mlx, char *str);

void				drawCeil(t_mlx *mlx, int start);
int					drawWall(t_mlx *mlx, int heightWall, float dist, t_fpos distHit);
void				drawFloor(t_mlx *mlx, int wallHeight, int start);

int					initTextures(t_mlx *mlx);

void				setPixel(t_mlx *mlx, int x, int y, int color);
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

void				*rayCasting(void *mlx);
void				dispatch(t_mlx *mlx);

int					isBlock(t_map *map, int x, int y);
void				checkMoveWall(t_mlx *mlx, t_fpos diff);

int					keyPressed(int key, t_mlx *mlx);
int					keyReleased(int key, t_mlx *mlx);
int					mainEvents(t_mlx *mlx);

#endif

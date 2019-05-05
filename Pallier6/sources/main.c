#include "../include/wolf3d.h"


int			error(char *msg)
{
	ft_putendl(msg);
	return (1);
}

void		initUser_Sky(t_mlx *mlx)
{
	mlx->init = 1;
	mlx->user.pov = ANGLE0;
	mlx->user.rotSpeed = ANGLE5 / 2;
	mlx->user.distMaxWall = TILE_SIZE / 2;
	mlx->user.up = 0;
	mlx->user.down = 0;
	mlx->user.left = 0;
	mlx->user.right = 0;
	mlx->user.moveSpeed = ANGLE5 / 30;
	mlx->user.distPlane = (WIN_WIDTH / 2) / tan(degToRad(ANGLE30) + 0.0001);
	mlx->sky = fileToImage("textures/sky.xpm", mlx, WIN_WIDTH, WIN_HEIGHT);
	initTextures(mlx);
}

int			main(int argc, char **argv)
{
	t_mlx	*mlx;
	
	if (argc != 2)
		error("Usage: ");
	if (!(mlx = init("Wolf3d - tbroggi@le-101", WIN_WIDTH, WIN_HEIGHT)))
		error("error: initialization");
	if (open_file(mlx, argv[1]) == 0)
		error("error: map");
	initUser_Sky(mlx);
	mlx_hook(mlx->window, 2, 1L << 0, keyPressed, mlx);
	mlx_hook(mlx->window, 3, 1L << 1, keyReleased, mlx);
	mlx_loop_hook(mlx->mlx, mainEvents, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
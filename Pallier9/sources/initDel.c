#include "../include/wolf3d.h"

t_mlx		*mlxdel(t_mlx *mlx)
{
	if (!mlx)
		return (NULL);
	if (mlx->window)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->img)
		delImage(mlx, mlx->img);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init(char *title, int width, int height)
{
	t_mlx	*mlx;

	if (!(mlx = ft_memalloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->mlx = mlx_init()) ||
		!(mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) ||
		!(mlx->img = newImage(mlx, width, height)))
		return (mlxdel(mlx));
	return (mlx);
}

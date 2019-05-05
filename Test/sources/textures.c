#include "../include/wolf3d.h"

static void		delTextures(t_mlx *mlx)
{
	int			i;

	i = -1;
	while (++i < 20)
		delImage(mlx, mlx->tex[i]);
}

int				initTextures(t_mlx *mlx)
{
	static char	*map[7] = { "brick.xpm", "wood.xpm", "metal.xpm",
		"stone.xpm", "grass.xpm", NULL };
	t_image		*img;
	int			i;
	char		*t;

	i = 0;
	while (++i < 6 && map[i - 1])
	{
		t = ft_strjoin("textures/", map[i - 1]);
		if (!(img = fileToImage(t, mlx, TEXT_SIZE, TEXT_SIZE)))
		{
			ft_strdel(&t);
			delTextures(mlx);
			return (1);
		}
		ft_strdel(&t);
		mlx->tex[i] = img;
	}
	mlx->tex[0] = NULL;
	return (0);
}

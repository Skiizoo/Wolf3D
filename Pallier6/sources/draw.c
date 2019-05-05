#include "../include/wolf3d.h"

int			wallTexture(int castDeg, int side)
{
	if (side && (castDeg < ANGLE90 || castDeg > ANGLE270))
		return (1);
	if (side && castDeg > ANGLE90 && castDeg < ANGLE270)
		return (2);
	if (!side && castDeg < ANGLE180)
		return (3);
	if (!side && castDeg > ANGLE180)
		return (4);
	return (-1);
}

void		drawWall(t_mlx *mlx, t_ipos cast, int heightWall, t_fpos distHit)
{
	int		start;
	int 	side;
	int		texture;
	int		pix_y;
	t_ipos	tmp;

	start = mlx->mid_projectplane - heightWall / 2;
	side = distHit.y < distHit.x ? 1 : 0;
	texture = wallTexture(cast.y, side);
	pix_y = 0;
	while (++pix_y < start)
		setPixel(mlx->img, cast.x, pix_y, 0xC00000BB);
	while ((++pix_y < heightWall + start) && texture > 0)
	{
		tmp.y = ((pix_y - start) * 100 / heightWall) % TEXT_SIZE;
		tmp.x = side ? mlx->gridInter.y % TEXT_SIZE : mlx->gridInter.x % TEXT_SIZE;
		setPixel(mlx->img, cast.x, pix_y, mlx_get_color_value(mlx->window, 
			getPixel(mlx->tex[texture], tmp.x, tmp.y).value));
	}
	while (++pix_y <= WIN_HEIGHT)
		setPixel(mlx->img, cast.x, pix_y, 0xC1CDCD);
}

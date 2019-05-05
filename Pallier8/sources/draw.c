#include "../include/wolf3d.h"

int 		getShadow(t_mlx *mlx, int color, float dist)
{
	float 	intensity;
	t_color newColor;

	if (!mlx->shadow)
		return (color);
	intensity = (150 / dist);
	newColor.value = color;
	newColor.rgba.r *= (intensity / 6);
	newColor.rgba.g *= (intensity / 6);
	newColor.rgba.b *= (intensity / 6);
	return (newColor.value);
}

int 		wallTexture(t_mlx *mlx, int castDeg, float dist, uint8_t side)
{
	if (side && (castDeg < ANGLE90 || castDeg > ANGLE270))
		return (mlx->textures ? 1 : getShadow(mlx, 0x00FF1C, dist));
	if (side && castDeg > ANGLE90 && castDeg < ANGLE270)
		return (mlx->textures ? 2 : getShadow(mlx, 0xFF0000, dist));
	if (!side && castDeg < ANGLE180)
		return (mlx->textures ? 3 : getShadow(mlx, 0x0002E8, dist));
	if (!side && castDeg > ANGLE180)
		return (mlx->textures ? 4 : getShadow(mlx, 0xE8B100, dist));
	return (-1);
}

int			drawWall(t_mlx *mlx, int wallHeight, float start, t_fpos distHit)
{
	uint8_t side;
	int 	texture;
	int 	pix_y;
	t_ipos	tmp;
	float	dist;
	
	side = distHit.y < distHit.x ? 1 : 0;
	dist = (distHit.x < distHit.y ? distHit.x : distHit.y)
			* mlx->fishTable[mlx->cast.x];
	texture = wallTexture(mlx, mlx->cast.y, dist, side);
	pix_y = 0;
	while (pix_y < (WIN_HEIGHT - start))
		setPixel(mlx->img, mlx->cast.x, pix_y++, mlx->shadow ? 0x000000 : 0xC00000AA);
	while ((pix_y < wallHeight + (WIN_HEIGHT - start)) && texture > 0)
	{
		tmp.y = ((int)(pix_y - (WIN_HEIGHT - start)) * 100 / wallHeight) % TEXT_SIZE;
		tmp.x = side ? mlx->gridInter.y % TEXT_SIZE : mlx->gridInter.x % TEXT_SIZE;
		if (mlx->textures)
			setPixel(mlx->img, mlx->cast.x, pix_y++, getShadow(mlx,
				mlx_get_color_value(mlx->window,
					getPixel(mlx->tex[texture], tmp.x, tmp.y).value), dist));
		else
			setPixel(mlx->img, mlx->cast.x, pix_y++, texture);
	}
	return (pix_y);
}

void		drawFloor(t_mlx *mlx, int wallHeight, int end)
{
	float	dist;
	int		start;

	start = end - wallHeight - 1;
	while (end <= WIN_HEIGHT)
	{	
		dist = mlx->user.height / (float)(end - (WIN_HEIGHT / 2)) *
			mlx->user.distPlane;
		dist *= mlx->fishTable[mlx->cast.x];
		setPixel(mlx->img, mlx->cast.x, end++, getShadow(mlx, 0xC1CDCD, dist));
		if (mlx->shadow)
			setPixel(mlx->img, mlx->cast.x, start--, getShadow(mlx, 0xC1CDCD, dist));
	}
}
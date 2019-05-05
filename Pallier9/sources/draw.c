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
	int 	texOrCol;
	int 	pix_y;
	t_ipos	tmp;
	float	dist;
	
	side = distHit.y < distHit.x ? 1 : 0;
	dist = (distHit.x < distHit.y ? distHit.x : distHit.y)
			* mlx->fishTable[mlx->cast.x];
	texOrCol = wallTexture(mlx, mlx->cast.y, dist, side);
	pix_y = WIN_HEIGHT - start;
	while ((pix_y < wallHeight + (WIN_HEIGHT - start)) && texOrCol > 0)
	{
		tmp.y = ((int)(pix_y - (WIN_HEIGHT - start)) * 100 / wallHeight) % TEXT_SIZE;
		tmp.x = side ? mlx->gridInter.y % TEXT_SIZE : mlx->gridInter.x % TEXT_SIZE;
		if (mlx->textures)
			setPixel(mlx->img, mlx->cast.x, pix_y++, getShadow(mlx,
				mlx_get_color_value(mlx->window,
					getPixel(mlx->tex[texOrCol], tmp.x, tmp.y).value), dist));
		else
			setPixel(mlx->img, mlx->cast.x, pix_y++, texOrCol);
	}
	return (pix_y);
}

void		drawFloor(t_mlx *mlx, int wallHeight, int end)
{
	float	dist;
	float	tmp;
	int		start;
	int		color;

	start = end - wallHeight - 1;
	tmp = (64.0 - mlx->user.height) * mlx->user.distPlane * mlx->fishTable[mlx->cast.x];
	while (end <= WIN_HEIGHT)
	{	
		dist = tmp / (end - (WIN_HEIGHT >> 1));
		color = getShadow(mlx, 0xC1CDCD, dist);
		setPixel(mlx->img, mlx->cast.x, end++, color);
		setPixel(mlx->img, mlx->cast.x, start--, mlx->shadow ? color : 0xC00000AA);
	}
}
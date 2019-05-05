#include "../include/wolf3d.h"

static float	getHorizontalDist(t_mlx *mlx, int castDeg)
{
	t_fpos		inter;
	t_fpos		dist;
	float		temp;

	inter.y = is_DegDown(castDeg) ? (((int)mlx->user.pos.y >> 6) << 6) + TILE_SIZE
		: ((int)mlx->user.pos.y >> 6) << 6;
	dist.y = is_DegDown(castDeg) ? TILE_SIZE : -TILE_SIZE;
	temp = (1.0 / tan(degToRad(castDeg) + 0.0001)) * (inter.y - mlx->user.pos.y);
	dist.x = get_Gap(castDeg, 1);
	inter.x = temp + mlx->user.pos.x - dist.x;
	inter.y -= is_DegDown(castDeg) ? 0 : 1;
	if (castDeg != ANGLE0 && castDeg != ANGLE180)
		while (1 && (inter.x += dist.x))
		{
			if (((int)inter.x >> 6 >= mlx->map->width) || ((int)inter.y >> 6 >=
					mlx->map->height) || (int)inter.y >> 6 < 0 || (int)inter.y >> 6 < 0)
				return (FLT_MAX);
			else if (isBlock(mlx->map, (int)inter.x >> 6, (int)inter.y >> 6) &&
						(mlx->gridInter.x = inter.x))
				return ((inter.x - mlx->user.pos.x) * (1.0 /
							cos(degToRad(castDeg) + 0.0001)));
			inter.y += dist.y;
		}
	return (FLT_MAX);
}

static float	getVerticalDist(t_mlx *mlx, int castDeg)
{
	t_fpos		inter;
	t_fpos		dist;
	float		temp;

	inter.x = is_DegRight(castDeg) ? (((int)mlx->user.pos.x >> 6) << 6) + TILE_SIZE
		: ((int)mlx->user.pos.x >> 6) << 6;
	dist.x = is_DegRight(castDeg) ? TILE_SIZE : -TILE_SIZE;
	temp = tan(degToRad(castDeg) + 0.0001) * (inter.x - mlx->user.pos.x);
	dist.y = get_Gap(castDeg, 0);
	inter.y = temp + mlx->user.pos.y - dist.y;
	inter.x -= is_DegRight(castDeg) ? 0 : 1;
	if (!(castDeg == ANGLE90 || castDeg == ANGLE270))
		while (1 && (inter.y += dist.y))
		{
			if (((int)inter.y >> 6 >= mlx->map->height) || ((int)inter.x >> 6 >=
					mlx->map->width) || (int)inter.x >> 6 < 0 || (int)inter.y >> 6 < 0)
				return (FLT_MAX);
			else if (isBlock(mlx->map, (int)inter.x >> 6, (int)inter.y >> 6) &&
						(mlx->gridInter.y = inter.y))
				return ((inter.y - mlx->user.pos.y) * (1.0 /
							sin(degToRad(castDeg) + 0.0001)));
			inter.x += dist.x;
		}
	return (FLT_MAX);
}

void			rayCasting(t_mlx *mlx)
{
	t_fpos		distHitGrid;
	float		dist;
	int			wallHeight;
	int			end;

	get_FishTable(mlx->fishTable);
	if ((mlx->cast.y = mlx->user.pov - ANGLE30) < 0)
		mlx->cast.y = ANGLE360 + mlx->cast.y;
	mlx->cast.x = -1;
	while (++mlx->cast.x < ANGLE60)
	{
		distHitGrid.x = getHorizontalDist(mlx, mlx->cast.y);
		distHitGrid.y = getVerticalDist(mlx, mlx->cast.y);
		dist = (distHitGrid.x < distHitGrid.y ? distHitGrid.x : distHitGrid.y)
			* mlx->fishTable[mlx->cast.x];
		wallHeight = WALL_HEIGHT * mlx->user.distPlane / dist;
		end = (mlx->user.distPlane / dist) * mlx->user.height + mlx->mid_projectplane;
		end = drawWall(mlx, wallHeight, end, distHitGrid);
		drawFloor(mlx, wallHeight, end);
		if ((mlx->cast.y += 1) >= ANGLE360)
			mlx->cast.y -= ANGLE360;
	}
}

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

void			*rayCasting(void *t)
{
	t_fpos		distHitGrid;
	float		dist;
	int			wallHeight;
	int			end;
	t_params	*thread;

	thread = t;
	get_FishTable(thread->mlx->fishTable);
	thread->mlx->cast.y = thread->th_angstart;
	thread->mlx->cast.x = thread->th_colstart - 1;
	while (++thread->mlx->cast.x < thread->th_colend)
	{
		distHitGrid.x = getHorizontalDist(thread->mlx, thread->mlx->cast.y);
		distHitGrid.y = getVerticalDist(thread->mlx, thread->mlx->cast.y);
		dist = (distHitGrid.x < distHitGrid.y ? distHitGrid.x : distHitGrid.y)
			* thread->mlx->fishTable[thread->mlx->cast.x];
		wallHeight = WALL_HEIGHT * thread->mlx->user.distPlane / dist;
		end = (thread->mlx->user.distPlane / dist) * thread->mlx->user.height +
			thread->mlx->user.mid_projectplane;
		end = drawWall(thread->mlx, wallHeight, end, distHitGrid);
		drawFloor(thread->mlx, wallHeight, end);
		if ((thread->mlx->cast.y += 1) >= ANGLE360)
			thread->mlx->cast.y -= ANGLE360;
	}
	return NULL;
}

void			launch_thread(t_mlx *mlx, int colstart, int colend, int angstart)
{
	t_params	*thread;

	thread = ft_memalloc(sizeof(t_params *));
	thread->mlx = mlx;
	thread->th_colstart = colstart;
	thread->th_colend = colend;
	if ((thread->th_angstart = thread->mlx->user.pov - ANGLE30 + angstart) < 0)
		thread->th_angstart = ANGLE360 + thread->th_angstart;
	pthread_create(&thread->thread, NULL, rayCasting, thread);
	pthread_join(thread->thread, NULL);
}

void			dispatch(t_mlx *mlx)
{
	launch_thread(mlx, 0, ANGLE10, ANGLE0);
	launch_thread(mlx, ANGLE10, ANGLE20, ANGLE10);
	launch_thread(mlx, ANGLE20, ANGLE30, ANGLE20);
	launch_thread(mlx, ANGLE30, ANGLE40, ANGLE30);
	launch_thread(mlx, ANGLE40, ANGLE50, ANGLE40);
	launch_thread(mlx, ANGLE50, ANGLE60, ANGLE50);
}

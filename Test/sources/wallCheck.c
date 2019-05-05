#include "../include/wolf3d.h"

int			isBlock(t_map *map, int x, int y)
{
	if ((x >= 0 && x < map->width) && (y >= 0 && y < map->height))
		return (map->map[y][x] == '1');
	return (0);
}

void		checkMoveWall(t_mlx *mlx, t_fpos diff)
{
	t_fpos	userCell;
	t_fpos	cellOffset;
	int		distMaxWall;

	userCell.x = floor(mlx->user.pos.x / TILE_SIZE);
	userCell.y = floor(mlx->user.pos.y / TILE_SIZE);
	cellOffset.x = (int)mlx->user.pos.x % TILE_SIZE;
	cellOffset.y = (int)mlx->user.pos.y % TILE_SIZE;
	distMaxWall = TILE_SIZE / 2;
	if (diff.x > 0)
		if (isBlock(mlx->map, (int)userCell.x + 1, (int)userCell.y)
				&& (cellOffset.x > (TILE_SIZE - distMaxWall)))
			mlx->user.pos.x -= (cellOffset.x - (TILE_SIZE - distMaxWall));
	if (diff.x <= 0)
		if (isBlock(mlx->map, (int)userCell.x - 1, (int)userCell.y)
				&& (cellOffset.x < (distMaxWall)))
			mlx->user.pos.x += (distMaxWall - cellOffset.x);
	if (diff.y < 0)
		if (isBlock(mlx->map, (int)userCell.x, (int)userCell.y - 1)
				&& (cellOffset.y < (distMaxWall)))
			mlx->user.pos.y += (distMaxWall - cellOffset.y);
	if (diff.y >= 0)
		if (isBlock(mlx->map, (int)userCell.x, (int)userCell.y + 1)
				&& (cellOffset.y > (TILE_SIZE - distMaxWall)))
			mlx->user.pos.y -= (cellOffset.y - (TILE_SIZE - distMaxWall));
}

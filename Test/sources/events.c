#include "../include/wolf3d.h"

int		keyPressed(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		mlx->user.up = 1;
	if (keycode == 1)
		mlx->user.down = 1;
	if (keycode == 0)
		mlx->user.left = 1;
	if (keycode == 2)
		mlx->user.right = 1;
	if (keycode == 257)
		if (mlx->user.moveSpeed != ANGLE5 / 15)
			mlx->user.moveSpeed *= 2;
	if (keycode == 83)
		mlx->textures ^= 1;
	if (keycode == 84)
		mlx->shadow ^= 1;
	if (keycode == 53)
		exit(1);
	return (0);
}

int		keyReleased(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		mlx->user.up = 0;
	if (keycode == 1)
		mlx->user.down = 0;
	if (keycode == 0)
		mlx->user.left = 0;
	if (keycode == 2)
		mlx->user.right = 0;
	if (keycode == 257)
		if (mlx->user.moveSpeed != ANGLE5 / 30)
			mlx->user.moveSpeed /= 2;
	return (0);
}

static void	rotate(int leftOrRight, t_mlx *mlx)
{
	if (leftOrRight)
		if ((mlx->user.pov += mlx->user.rotSpeed) >= ANGLE360)
			mlx->user.pov -= ANGLE360;
	if (!leftOrRight)
		if ((mlx->user.pov -= mlx->user.rotSpeed) < ANGLE0)
			mlx->user.pov += ANGLE360;
}

static void	movement(t_mlx *mlx)
{
	int		upOrDown;
	t_fpos	diff;

	if (mlx->user.up || mlx->user.down)
	{
		upOrDown = mlx->user.up ? 1 : -1;
		diff.x = cos(degToRad(mlx->user.pov) + 0.0001) * mlx->user.moveSpeed * upOrDown;
		diff.y = sin(degToRad(mlx->user.pov) + 0.0001) * mlx->user.moveSpeed * upOrDown;
		mlx->user.pos.x += diff.x;
		mlx->user.pos.y += diff.y;
		checkMoveWall(mlx, diff);
	}
	if (mlx->user.left)
		rotate(0, mlx);
	if (mlx->user.right)
		rotate(1, mlx);
}

int			mainEvents(t_mlx *mlx)
{
	movement(mlx);
	dispatch(mlx);
	if (!mlx->shadow)
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->sky->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	return (0);
}

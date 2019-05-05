#include "../include/wolf3d.h"

void			setPixel(t_mlx *mlx, int x, int y, int color)
{

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pthread_mutex_lock(&mlx->mutex);
	*(int *)(mlx->img->ptr + ((x + y * WIN_WIDTH) * mlx->img->bits)) = color;
	pthread_mutex_unlock(&mlx->mutex);
}

t_color			getPixel(t_image *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ((t_color)0x0);
	return ((t_color)*(int *)(image->ptr + ((x + y * image->width) * image->bits)));
}

void			resetImage(t_image *img)
{
	ft_bzero(img->ptr, img->width * img->height * img->bits);
}

t_image			*delImage(t_mlx *mlx, t_image *img)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		ft_memdel((void **)&img);
	}
	return (img);
}

t_image			*newImage(t_mlx *mlx, int width, int height)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_new_image(mlx->mlx, width, height)))
		return (delImage(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bits, &img->s_line,
			&img->endian);
	img->bits /= 8;
	img->height = height;
	img->width = width;
	return (img);
}

t_image			*fileToImage(char *xpm, t_mlx *mlx, int width, int height)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_xpm_file_to_image(mlx->mlx, xpm, &width, &height)))
		return (delImage(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bits, &img->s_line,
		&img->endian);
	img->bits /= 8;
	img->width = img->s_line / img->bits;
	img->height = img->s_line / img->bits;
	return (img);
}

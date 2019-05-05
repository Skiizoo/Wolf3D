#include "../include/wolf3d.h"

static void		read_pos(int fd, t_mlx *mlx)
{
	char	*line;
	char	**line_split;
	int		i;

	i = -1;
	if (get_next_line(fd, &line) < 1)
		error("map error");
	line_split = ft_strsplit(line, ' ');
	while (line_split[++i] != '\0')
		;
	if (i != 4 || !(mlx->map = ft_memalloc(sizeof(t_map))))
		error("map error");
	mlx->map->width = ft_atoi(line_split[0]);
	mlx->map->height = ft_atoi(line_split[1]);
	mlx->user.pos.y = (ft_atoi(line_split[2]) * 64) + 32;
	mlx->user.pos.x = (ft_atoi(line_split[3]) * 64) + 32;
	if (mlx->map->width < 0 || mlx->map->height < 0 || mlx->user.pos.x < 0 ||
			mlx->user.pos.y < 0 || (int)mlx->user.pos.x >> 6 >=
				mlx->map->width || (int)mlx->user.pos.y >> 6 >= mlx->map->width)
		error("map error");
}

static void		read_line(char *line, int y, char **map, t_mlx *mlx)
{
	int		x;
	char	**line_split;

	x = -1;
	if (y >= mlx->map->height)
		error("map error");
	line_split = ft_strsplit(line, ' ');
	map[y] = (char *)malloc(sizeof(char *) * mlx->map->width);
	while (line_split[++x] != '\0')
	{
		if (!(line_split[x][0] >= '0' && line_split[x][0] <= '9'
					&& ft_atoi(line_split[x]) >= 0 && x < mlx->map->width))
			error("map error");
		map[y][x] = ft_atoi(line_split[x]) + '0';
		if ((x == 0 || x == mlx->map->width - 1 || y == 0 || y == mlx->map->height -
					1) && map[y][x] == 0)
			error("map error");
	}
	if (x != mlx->map->width)
		error("map error");
}

static int		read_file(int fd, t_mlx *mlx)
{
	char	*line;
	int		y;
	char	**map;

	y = -1;
	read_pos(fd, mlx);
	map = (char **)malloc(sizeof(char **) * mlx->map->height);
	while (get_next_line(fd, &line) == 1)
		read_line(line, ++y, map, mlx);
	if (map[(int)mlx->user.pos.x >> 6][(int)mlx->user.pos.y >> 6] != '0')
		error("map error");
	mlx->map->map = map;
	return (1);
}

int				open_file(t_mlx *mlx, char *f)
{
	int		fd;

	fd = open(f, O_DIRECTORY);
	if (fd >= 0)
		return (0);
	fd = open(f, O_RDONLY);
	if (fd < 0)
		return (0);
	return (read_file(fd, mlx));
}

#include "../include/wolf3d.h"

float		degToRad(int arcAngle)
{
	return (arcAngle * M_PI / ANGLE180);
}

int			is_DegRight(int castDeg)
{
	return (castDeg < ANGLE90 || castDeg > ANGLE270);
}

int			is_DegDown(int castDeg)
{
	return (castDeg > ANGLE0 && castDeg < ANGLE180);
}

float		get_Gap(int castDeg, int x_y)
{
	float	gap;

	gap = x_y ? TILE_SIZE / tan(degToRad(castDeg) + 0.0001) : TILE_SIZE *
		tan(degToRad(castDeg) + 0.0001);
	if (x_y && castDeg >= ANGLE90 && castDeg < ANGLE270)
		return (gap > 0 ? -gap : gap);
	else if (x_y)
		return (gap < 0 ? -gap : gap);
	if (!x_y && castDeg >= ANGLE0 && castDeg < ANGLE180)
		return (gap < 0 ? -gap : gap);
	else if (!x_y)
		return (gap > 0 ? -gap : gap);
	return (gap);
}

void		get_FishTable(float fishTable[ANGLE60])
{
	int		i;

	i = -ANGLE30 - 1;
	while (++i <= ANGLE30)
		fishTable[i + ANGLE30] = cos(degToRad(i));
}

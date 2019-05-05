/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:56:59 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 12:41:00 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	nb_atoi(int c, int base)
{
	int		i;
	char	*s1;
	char	*s2;

	i = -1;
	s1 = "0123456789abcdef";
	s2 = "0123456789ABCDEF";
	while (++i < base)
		if (c == s1[i] || c == s2[i])
			return (i);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		neg;
	long	nb;
	int		base;

	neg = 1;
	nb = 0;
	base = 10;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
		neg = 44 - *str++;
	if (*str == '0' && (*str++))
	{
		if ((*str == 'x' || *str == 'X') && (*str++))
			base = 16;
		else if (*str == 'b' && (*str++))
			base = 2;
		else if (ft_isocta(*str))
			base = 8;
	}
	while ((base == 10 && ft_isdigit(*str)) || (base == 2 && ft_isbin(*str)) ||
			(base == 8 && ft_isocta(*str)) || (base == 16 && ft_ishexa(*str)))
		nb = nb * base + nb_atoi(*str++, base);
	return (neg * nb);
}

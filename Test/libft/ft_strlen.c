/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 19:55:38 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 22:52:38 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	unsigned long			lg;
	const unsigned long		*ptr;
	const char				*s;

	s = str - 1;
	while ((unsigned long)++s & 7)
		if (!(*s))
			return (s - str);
	ptr = (unsigned long *)s;
	while (1)
	{
		lg = *ptr;
		if (((lg - 0x101010101010101L) & ~lg & 0x8080808080808080L))
		{
			s = (const char *)ptr;
			while (*s)
				s++;
			return (s - str);
		}
		ptr++;
	}
}

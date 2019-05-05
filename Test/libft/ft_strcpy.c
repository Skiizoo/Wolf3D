/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:11 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 22:48:37 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned long		*ld;
	const unsigned long	*ls;
	char				*d;

	d = dst;
	while (((unsigned long)src & 7) && ((*d++ = *src++) || 1))
		if (!(*src) && (!(*d = '\0')))
			return (dst);
	ls = (unsigned long *)src;
	ld = (unsigned long *)d;
	while (1)
	{
		if (((*ls - 0x101010101010101L) & ~(*ls) & 0x8080808080808080L))
		{
			d = (char *)ld;
			src = (const char *)ls;
			while (*src)
				*d++ = *src++;
			*d = '\0';
			return (dst);
		}
		*ld++ = *ls++;
	}
}

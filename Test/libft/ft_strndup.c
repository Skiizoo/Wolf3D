/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/30 15:44:09 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 15:29:47 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	int		i;

	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	ft_memcpy(s2, s1, n);
	return (s2);
}

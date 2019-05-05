/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 16:31:48 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	long			l;
	unsigned char	*str;
	unsigned long	*lg;

	l = ft_mask(c);
	str = (unsigned char *)b;
	while ((len % 8) && len--)
		*str++ = (unsigned char)c;
	len /= 8;
	lg = (unsigned long *)str;
	while (len--)
		*lg++ = l;
	return (b);
}

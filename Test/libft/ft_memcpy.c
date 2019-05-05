/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 18:37:33 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *s1;
	unsigned long *long1;
	unsigned char *s2;
	unsigned long *long2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while ((n % 8) && n--)
		*s1++ = *s2++;
	n /= 8;
	long1 = (unsigned long *)s1;
	long2 = (unsigned long *)s2;
	while (n--)
		*long1++ = *long2++;
	return (dst);
}

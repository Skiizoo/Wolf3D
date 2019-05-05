/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 16:02:54 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, int base)
{
	char	*nbr;
	size_t	len;

	len = ft_intlen_base(n, base);
	if (!(nbr = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		nbr[len] = ABS((long)n % base) + BASE(ABS((long)n % base));
		n = ABS((long)n) < base ? n : (n / base);
	}
	n < 0 ? nbr[len + 1] = '-' : 0;
	return (nbr);
}

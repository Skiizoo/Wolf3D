/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen_base.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 16:00:04 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(int n, int base)
{
	if (n < 0)
		return ((n / base ? 2 : 1) + ft_intlen_base(-(n / base), base));
	return (n < base ? 1 : 1 + ft_intlen_base(n / base, base));
}

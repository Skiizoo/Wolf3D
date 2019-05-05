/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbword.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 16:03:27 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbword(char const *s, char split)
{
	size_t	nb;

	nb = 0;
	while (*s)
	{
		while (*s == split)
			s++;
		nb = *s != split && *s ? nb + 1 : nb;
		while (*s != split && *s)
			s++;
	}
	return (nb);
}

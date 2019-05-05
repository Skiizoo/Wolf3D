/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:15 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 15:59:15 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	l;
	char	*new;

	if (!s)
		return (NULL);
	l = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	while (s[l])
		l++;
	while (l && (s[l - 1] == ' ' || s[l - 1] == '\t' || s[l - 1] == '\n'))
		l--;
	new = ft_strsub(s, 0, l);
	return (new);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:15 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 15:59:15 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	if (!s || !(split = malloc(sizeof(char *) * ft_nbword(s, c) + 1)))
		return (NULL);
	split[ft_nbword(s, c)] = 0;
	i = 0;
	j = 0;
	while (i < ft_nbword(s, c))
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			return (split);
		if (!(split[i] = ft_strsub(&s[j], 0, ft_wordlen(&s[j], c))))
			return (NULL);
		j = j + ft_wordlen(&s[j], c);
		i++;
	}
	return (split);
}

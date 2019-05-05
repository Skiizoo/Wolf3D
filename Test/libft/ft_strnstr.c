/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:15 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 15:59:15 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!(*needle))
		return ((char *)haystack);
	while (*haystack && *needle && len--)
	{
		if ((!ft_strncmp(haystack, needle, ft_strlen(needle))) &&
				(len + 1 >= ft_strlen(needle)))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

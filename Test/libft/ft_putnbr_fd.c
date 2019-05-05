/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/05 15:59:10 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/05 15:59:10 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	n < 0 ? ft_putchar_fd('-', fd) : 0;
	ABS((long)n) > 9 ? ft_putnbr_fd(ABS((long)n / 10), fd) : 0;
	ft_putchar_fd(ABS((long)n % 10) + 48, fd);
}

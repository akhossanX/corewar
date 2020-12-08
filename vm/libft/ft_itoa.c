/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:20:56 by yelazrak          #+#    #+#             */
/*   Updated: 2020/01/27 18:06:37 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			len(long long int n)
{
	int				i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char			*ft_rempli(char *t, int i, long long int r, int x)
{
	long long int	n;

	n = r;
	i--;
	while (i >= x)
	{
		t[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (t);
}

char				*ft_itoa(long long int a)
{
	char			*t;
	int				i;
	long long int	x;
	long long int	n;

	i = 0;
	x = (a < 0) ? 1 : 0;
	if (a == 0)
		return (ft_strdup("0"));
	if (a < 0)
	{
		n = a * -1;
		i = len(n) + 1;
		if (!(t = ft_strnew(i)))
			return (0);
		t[0] = '-';
	}
	else
	{
		n = a;
		i = len(n);
		if (!(t = ft_strnew(i)))
			return (0);
	}
	return (ft_rempli(t, i, n, x));
}

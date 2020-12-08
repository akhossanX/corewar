/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:56:49 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 10:56:25 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_nstrjoin(size_t n, ...)
{
	char		*fresh;
	char		*ptr;
	va_list		ap;

	va_start(ap, n);
	if (!n || !(fresh = ft_strdup(va_arg(ap, char *))))
	{
		va_end(ap);
		return (NULL);
	}
	while (--n)
	{
		ptr = fresh;
		if (!(fresh = ft_strjoin(fresh, va_arg(ap, char *))))
		{
			free(fresh);
			va_end(ap);
			return (NULL);
		}
		free(ptr);
	}
	va_end(ap);
	return (fresh);
}

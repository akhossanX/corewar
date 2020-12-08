/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:24:48 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/10 12:04:35 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_visu					*get_visu(t_visu *visu)
{
	static t_visu		*v;

	if (visu)
		v = visu;
	return (v);
}

void					print_byt(const void *addr)
{
	const char			*str = "0123456789ABCDEF";
	uint8_t				*p;

	p = (uint8_t *)addr;
	ft_putchar(str[(p[0] / 16) % 16]);
	ft_putchar(str[p[0] % 16]);
	ft_putstr(" ");
}

void					print_index_hex(const void *addr)
{
	const char			*str = "0123456789ABCDEF";
	uint8_t				*p;

	p = (uint8_t *)addr;
	ft_putchar(str[(p[0] / 16) % 16]);
	ft_putchar(str[p[0] % 16]);
}

t_corewar				*get_corewar(t_corewar *lst)
{
	static t_corewar	*p;

	if (lst)
		p = lst;
	return (p);
}

uint8_t					*ft_get_arena(void)
{
	uint8_t				*str;

	if (!(str = (uint8_t *)malloc(sizeof(uint8_t) * MEM_SIZE)))
		return (NULL);
	ft_memset((void *)str, 0, sizeof(uint8_t) * MEM_SIZE);
	return (str);
}

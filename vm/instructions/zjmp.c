/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 19:35:13 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int					ft_zjmp(t_process *p)
{
	t_corewar		*war;
	unsigned	int	byt;

	if (p->carry == 0)
	{
		p->pc += 3;
		p->pc %= MEM_SIZE;
		return (0);
	}
	byt = 0;
	war = get_corewar(0);
	ft_memcpy(&byt, &war->arena[p->pc + 1], 2);
	p->pc = overrided_pos(ft_sign(byt, 2), p->pc);
	p->pc %= MEM_SIZE;
	return (0);
}

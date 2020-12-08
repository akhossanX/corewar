/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/12/01 12:24:00 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void		task_fork(t_process *p, t_process *new, t_corewar *war)
{
	int				i;

	i = 0;
	if (new->pc < 0)
	{
		i = MEM_SIZE - ((-1 * new->pc) % MEM_SIZE);
		new->pc = i;
	}
	new->pc += p->pc;
	new->pc %= SIZE_MAX;
	new->cycle_count = 0;
	new->next = war->all_process;
	war->all_process = new;
}

int					ft_lfork(t_process *p)
{
	unsigned	int	byt;
	t_corewar		*war;
	t_process		*new;

	war = get_corewar(0);
	ft_memcpy((void *)&byt, (void *)&war->arena[p->pc + 1], 2);
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (0);
	ft_memset((void *)new, 0, sizeof(t_process));
	ft_memcpy((void *)new, (void *)p, sizeof(t_process));
	war->nbr_process++;
	new->pc = ft_sign(byt, 2);
	new->next = NULL;
	new->cycle_create = war->cycle;
	task_fork(p, new, war);
	p->pc += 3;
	p->pc %= MEM_SIZE;
	return (0);
}

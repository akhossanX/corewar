/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 22:32:08 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void			task_add(t_process *p, unsigned char byt_arg, int cr0)
{
	int					byt;
	int					reg;

	byt = ft_sign(return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 5, cr0), 4) +
ft_sign(return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 5, cr0), 4);
	byt = ft_sign(byt, 4);
	if ((reg = read_regster(p)) != -1 && p->erorr != -1)
	{
		ft_memcpy(&p->regster[reg - 1], &byt, 4);
		p->carry = (!p->regster[reg - 1]) ? 1 : 0;
	}
}

int						ft_add(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	int					cr0;

	war = get_corewar(0);
	cr0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 4)) > 0)
	{
		p->pc++;
		task_add(p, byt_arg, cr0);
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cr0) % MEM_SIZE;
	return (0);
}

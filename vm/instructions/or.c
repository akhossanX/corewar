/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 22:30:57 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int						ft_or(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	unsigned	int		byt;
	int					reg;
	int					cr0;

	war = get_corewar(0);
	cr0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 7)) > 0)
	{
		p->pc++;
		byt = ft_sign(return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 5, cr0),
4) | ft_sign(return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 5, cr0), 4);
		byt = ft_sign(byt, 4);
		if ((reg = read_regster(p)) != -1 && p->erorr != -1)
		{
			ft_memcpy(&p->regster[reg - 1], &byt, 4);
			p->carry = (!p->regster[reg - 1]) ? 1 : 0;
		}
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cr0) % MEM_SIZE;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:08:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void			task_sti(t_process *p,
unsigned char byt_arg, int cursor0, int reg)
{
	unsigned	int		byt;
	long				data;

	byt = return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 11, cursor0);
	if ((((byt_arg >> 4) & 0x03)) == DIR_CODE)
		data = ft_sign(byt, 2);
	else
		data = ft_sign(byt, 4);
	byt = return_data_of_arg(p, ((byt_arg >> 2) & 0x03), 11, cursor0);
	if ((((byt_arg >> 2) & 0x03)) == DIR_CODE)
		data += ft_sign(byt, 2);
	else
		data += ft_sign(byt, 4);
	if (p->erorr != -1)
		cpy_reg_to_arena(p, cursor0, data, reg);
}

int						ft_sti(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	int					reg;
	int					cursor0;

	war = get_corewar(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 11)) > 0)
	{
		p->pc++;
		if ((reg = read_regster(p)) != -1)
		{
			p->pc++;
			task_sti(p, byt_arg, cursor0, reg);
			p->erorr = 0;
		}
	}
	p->pc = (p->size_of_flg + cursor0) % MEM_SIZE;
	return (0);
}

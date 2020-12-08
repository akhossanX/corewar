/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:07:03 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void			task_st(t_process *p,
unsigned char byt_arg, int cursor0, int reg)
{
	t_corewar			*war;
	unsigned	int		data;

	data = 0;
	war = get_corewar(0);
	if ((((byt_arg >> 4) & 0x03) & IND_CODE) == IND_CODE)
	{
		ft_memcpy(&data, &war->arena[++p->pc], 2);
		cpy_reg_to_arena(p, cursor0,
ft_sign(data, 2), hex(addr_to_hex(&reg, 1)));
		p->pc++;
	}
	else if ((((byt_arg >> 4) & 0x03) & REG_CODE) == REG_CODE)
	{
		p->pc++;
		if ((int)(data = read_regster(p)) != -1)
			p->regster[data - 1] = p->regster[reg - 1];
	}
}

int						ft_st(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	int					reg;
	int					cursor0;

	war = get_corewar(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 3)) > 0)
	{
		p->pc++;
		if ((reg = read_regster(p)) != -1)
		{
			task_st(p, byt_arg, cursor0, reg);
		}
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cursor0) % MEM_SIZE;
	return (0);
}

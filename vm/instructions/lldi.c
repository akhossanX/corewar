/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 20:12:51 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void			task_lldi(t_process *p, int cursor0, int byt_arg)
{
	unsigned	int		byt;
	int					data;

	byt = return_data_of_arg(p, ((byt_arg >> 6) & 0x03), 14, cursor0);
	if ((((byt_arg >> 6) & 0x03)) == DIR_CODE)
		data = ft_sign(byt, 2);
	else
		data = ft_sign(byt, 4);
	byt = return_data_of_arg(p, ((byt_arg >> 4) & 0x03), 14, cursor0);
	if ((((byt_arg >> 4) & 0x03)) == DIR_CODE)
		data += ft_sign(byt, 2);
	else
		data += ft_sign(byt, 4);
	if ((int)(byt = read_regster(p)) != -1 && p->erorr != -1)
		cpy_arena_to_reg(p, cursor0, data, byt);
}

int						ft_lldi(t_process *p)
{
	t_corewar			*war;
	unsigned	char	byt_arg;
	int					cursor0;

	war = get_corewar(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 14)) > 0)
	{
		p->pc++;
		task_lldi(p, cursor0, byt_arg);
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cursor0) % MEM_SIZE;
	return (0);
}

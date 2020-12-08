/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/28 14:52:36 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void					print_aff(t_visu *visu, char aff)
{
	t_corewar			*war;

	war = get_corewar(0);
	if (visu && war->a)
	{
		wattron(visu->menu, A_BOLD);
		mvwprintw(visu->menu, 62, 6, "%c", aff);
		wattroff(visu->menu, A_BOLD);
	}
}

int						ft_aff(t_process *p)
{
	t_corewar			*war;
	t_visu				*visu;
	unsigned	char	byt_arg;
	int					cursor0;
	int					reg;

	war = get_corewar(0);
	visu = get_visu(0);
	cursor0 = p->pc;
	ft_memcpy(&byt_arg, &war->arena[++p->pc], 1);
	if ((get_size_beyt_flag(p, byt_arg, 16)) > 0)
	{
		p->pc++;
		if ((reg = read_regster(p)) != -1)
		{
			p->pc++;
			reg = (char)(p->regster[reg - 1] % 256);
			print_aff(visu, (char)reg);
		}
		p->erorr = 0;
	}
	p->pc = (p->size_of_flg + cursor0) % MEM_SIZE;
	return (0);
}

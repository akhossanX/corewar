/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battlefield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:04:41 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 21:50:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int						get_size_arg(uint8_t flg,
int nb_arg, int opcode, int *err)
{
	if ((flg & IND_CODE) == IND_CODE)
	{
		if ((g_op_tab[opcode - 1].args[nb_arg] & T_IND) != T_IND)
			*err = -1;
		return (2);
	}
	else if ((flg & REG_CODE) == REG_CODE)
	{
		if ((g_op_tab[opcode - 1].args[nb_arg] & T_REG) != T_REG)
			*err = -1;
		return (1);
	}
	else if ((flg & DIR_CODE) == DIR_CODE)
	{
		if ((g_op_tab[opcode - 1].args[nb_arg] & T_DIR) != T_DIR)
			*err = -1;
		if (!g_op_tab[opcode - 1].size_dir)
			return (4);
		return (2);
	}
	*err = -1;
	return (0);
}

int						get_size_beyt_flag(t_process *p,
uint8_t flg, int opcode)
{
	int					i;
	int					count;
	int					size_arg;
	uint8_t				oper_args;
	int					err;

	i = -1;
	count = 0;
	err = 0;
	size_arg = 0;
	while (++i < g_op_tab[opcode - 1].nbr_args)
	{
		oper_args = (flg >> (6 - (i * 2))) & 0x3;
		size_arg = get_size_arg(oper_args, i, opcode, &err);
		count += size_arg;
	}
	p->size_of_flg = count + 2;
	if (err == -1)
		return (-1);
	return (count);
}

static	uint32_t		task_return_data(t_process *proc,
int opcode, t_corewar *war)
{
	uint32_t			st;

	if (!g_op_tab[opcode - 1].size_dir)
	{
		ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 4);
		proc->pc += 4;
		return (st);
	}
	ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 2);
	proc->pc += 2;
	return (st);
}

uint32_t				return_data_of_arg(t_process *proc,
						uint8_t flg, int opcode, int cursor0)
{
	t_corewar			*war;
	unsigned	int		st;

	war = get_corewar(NULL);
	if ((flg & IND_CODE) == IND_CODE)
	{
		ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 2);
		st = cpy_arena_to_var(proc,
		(ft_sign(st, 2)), cursor0, opcode);
		proc->pc += 2;
		return (st);
	}
	else if ((flg & REG_CODE) == REG_CODE)
	{
		if ((st = read_regster(proc)) == (uint32_t)-1)
		{
			proc->erorr = -1;
			return (0);
		}
		proc->pc++;
		return (proc->regster[st - 1]);
	}
	else if ((flg & DIR_CODE) == DIR_CODE)
		return (task_return_data(proc, opcode, war));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int				overrided_pos(int size, int cursor0)
{
	if (size >= 0)
	{
		size = cursor0 + (size % IDX_MOD);
	}
	else
	{
		size = MEM_SIZE + (cursor0 +
(((-1 * size) % IDX_MOD) * -1));
	}
	return ((size % MEM_SIZE));
}

void			cpy_reg_to_arena(t_process *p, int cursor0, int size, int reg)
{
	t_corewar	*war;

	war = get_corewar(NULL);
	size = overrided_pos(size, cursor0);
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&war->arena[size], (void *)&p->regster[reg - 1],
(MEM_SIZE - size));
		inedx_color(p->id, size, MEM_SIZE, 1);
		ft_memcpy((void *)&war->arena[0], (void *)&p->regster[reg - 1],
4 - (MEM_SIZE - size));
		inedx_color(p->id, 0, 4 - (MEM_SIZE - size), 1);
	}
	else
	{
		ft_memcpy((void *)&war->arena[size],
(void *)&p->regster[reg - 1], 4);
		inedx_color(p->id, size, size + 4, 1);
	}
}

int				read_regster(t_process *proc)
{
	t_corewar	*war;
	uint8_t		i;

	i = 0;
	war = get_corewar(NULL);
	ft_memcpy((void *)&i, (void *)&war->arena[proc->pc], 1);
	i = hex(addr_to_hex(&i, 1));
	if (i >= 1 && i <= 16)
		return (i);
	proc->erorr = 1;
	return (-1);
}

void			cpy_arena_to_reg(t_process *p,
int cursor0, int size, int reg)
{
	t_corewar	*war;

	war = get_corewar(NULL);
	size = overrided_pos(size, cursor0);
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&p->regster[reg - 1],
(void *)&war->arena[size], (MEM_SIZE - size));
		ft_memcpy((void *)&p->regster[reg - 1] +
(MEM_SIZE - size),
(void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
	{
		ft_memcpy((void *)&p->regster[reg - 1],
(void *)&war->arena[size], 4);
	}
}

uint32_t		cpy_arena_to_var(t_process *p,
int size, int cursor0, int opcode)
{
	uint32_t	stock;
	t_corewar	*war;

	stock = 0;
	(void)p;
	war = get_corewar(0);
	if (opcode == 13)
		size = cursor0 + size;
	else
		size = overrided_pos(size, cursor0);
	size = size % MEM_SIZE;
	if ((size + 4) >= MEM_SIZE)
	{
		ft_memcpy((void *)&stock, (void *)&war->arena[size],
(MEM_SIZE - size));
		ft_memcpy((void *)&stock + (MEM_SIZE - size),
(void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
		ft_memcpy((void *)&stock, (void *)&war->arena[size], 4);
	return (stock);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/12/01 12:33:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static	void		task_init(t_corewar *war, int i)
{
	t_process		*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return ;
	ft_memset((void *)new, 0, sizeof(t_process));
	new->id = i + 1;
	new->regster[0] = ft_sign((war->players[i].value_reg) * -1, 4);
	new->pc = war->players[i].starting_point;
	inedx_color(new->id, new->pc, new->pc +\
ft_sign(war->players[i].data_file->prog_size, 4), 0);
	if (!war->last_process && !war->all_process)
	{
		war->all_process = new;
		war->last_process = new;
	}
	else
	{
		new->next = war->all_process;
		war->all_process = new;
	}
}

void				ft_init_process(t_corewar *war)
{
	int				i;

	i = -1;
	war->nbr_process = war->nbr_fighters;
	war->cycle_to_die = CYCLE_TO_DIE;
	while (++i < war->nbr_fighters)
	{
		task_init(war, i);
	}
}

int					hextodecimal(char val)
{
	const	char	tab[16] = "0123456789abcdef";
	int				i;

	i = -1;
	while (++i < 16)
	{
		if (val == tab[i])
		{
			return (i);
		}
	}
	return (-1);
}

int					is_id_integer(char *arg)
{
	int				i;
	int				n;

	if (!arg)
		return (0);
	n = ft_strlen(arg);
	i = (arg[0] == '-') ? 0 : -1;
	while (++i < n)
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

void				inedx_color(int id, int start, int end, int alpha)
{
	int	i;

	i = start;
	while (i < end)
	{
		g_coords[i].alpha = alpha;
		g_coords[i].id = id;
		i++;
	}
}

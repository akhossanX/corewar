/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/25 10:24:30 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void				free_process(t_process *p)
{
	if (p && p->next)
		free_process(p->next);
	ft_memdel((void **)&p);
}

void				free_corewar(t_corewar *war)
{
	int				i;
	t_visu			*visu;

	i = -1;
	visu = get_visu(0);
	if (war)
	{
		ft_memdel((void *)&war->arena);
		while (++i < war->nbr_fighters)
		{
			ft_memdel((void *)&war->players[i].data_file);
		}
		free_process(war->all_process);
		ft_memdel((void **)&war);
	}
	ft_memdel((void **)&visu);
	endwin();
}

int					usage(t_corewar *war)
{
	ft_printf("\033[0;33m usage:    ./corewar [-v | \
-dump N]  [-n N] <champion1.cor> <...> \033[0m\n");
	ft_printf("\033[0;34m           -v\033[0m       : \
Enables visualization\n");
	ft_printf("\033[0;34m           -dump N\033[0m  \
: Dumps memory after N cycles\n");
	ft_printf("\033[0;34m           -a  \033[0m     \
: Prints output from 'aff' (Default is to hide it)\n");
	ft_printf("\033[0;34m           -n N\033[0m     \
: Assigns id N to the player specified right \
after N \n");
	ft_printf("\033[0;31m Pay attention!\033[0m [-v] \
has higher priority when is used with [-dump]\n");
	free_corewar(war);
	return (1);
}

int					play_visu(t_corewar *war)
{
	t_visu			*visu;

	visu = NULL;
	if (war->v)
	{
		if (!(visu = (t_visu *)ft_memalloc(sizeof(t_visu))))
			return (exit_error("error memoir"));
		init_struct(visu);
		border_maker(visu);
		get_visu(visu);
	}
	else
		print_game();
	return (0);
}

int					main(int argc, char **argv)
{
	t_corewar		*war;

	war = NULL;
	if (argc < 2 || !(war = (t_corewar *)ft_memalloc(sizeof(t_corewar))))
		return (usage(war));
	ft_memset(g_coords, 0, sizeof(g_coords));
	war->arena = ft_get_arena();
	get_id(argv);
	parsing(war, argc, argv);
	ft_init_process(war);
	get_corewar(war);
	play_visu(war);
	ft_loop();
	free_corewar(war);
	return (0);
}

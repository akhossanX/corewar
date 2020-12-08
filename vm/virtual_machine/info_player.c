/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:24:48 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/10 12:04:35 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void				print_winer(void)
{
	t_corewar		*war;
	int				i;
	int				id;
	int				last_live;

	war = get_corewar(0);
	i = -1;
	id = 0;
	last_live = 0;
	while (++i < war->nbr_fighters)
	{
		if (war->players[i].last_cycle_to_live > last_live)
		{
			id = i;
			last_live = war->players[i].last_cycle_to_live;
		}
	}
	ft_printf("Contestant %d, \" %s \", has won !\n",
id + 1, war->players[id].data_file->prog_name);
}

void				ft_print_arena(void)
{
	t_corewar		*war;
	int				i;
	char			count;

	war = get_corewar(0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i != 0 && !(i % 64))
			ft_putchar('\n');
		if (i == 0 || !((i) % 64))
		{
			ft_putstr("0x");
			count = ((i >> 8) & 0xff);
			print_index_hex(&count);
			count = (i & 0xff);
			print_index_hex(&count);
			ft_putstr(" : ");
		}
		print_byt(&war->arena[i]);
	}
	ft_putchar('\n');
}

void				print_game(void)
{
	t_corewar		*war;
	int				i;

	war = get_corewar(0);
	i = -1;
	ft_putendl("Introducting contestants ...");
	while (++i < war->nbr_fighters)
	{
		ft_printf("* Player %d, weighing %d \
bytes, \"%s\" (\"%s\") !\n",
i + 1,
ft_sign(war->players[i].data_file->prog_size, 4),
war->players[i].data_file->prog_name,
war->players[i].data_file->comment);
	}
}

int					exit_error(char *message_error)
{
	t_corewar		*war;

	war = get_corewar(0);
	if (message_error)
		ft_printf("./corewar:\033[0;31m %s\033[0m\n", message_error);
	free_corewar(war);
	exit(1);
	return (1);
}

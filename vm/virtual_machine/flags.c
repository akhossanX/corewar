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

static	int			manage_file(t_corewar *war, int id, char *file_name)
{
	t_header		*lst;
	int				n;

	if (!file_name)
		return (0);
	if (war->status_reg && id > 0 && id < 5)
		war->value_reg = (get_id_player(id - 1, 1));
	else if (!war->status_reg)
		war->value_reg = (get_id_player(id - 1, -1));
	n = ft_strlen(file_name);
	if (n < 5 || ft_strcmp(file_name + (n - 4), ".cor"))
		return (0);
	if (!(lst = ft_cin_file(file_name)))
		return (exit_error("file not valide"));
	war->players[war->nbr_fighters].data_file = lst;
	war->players[war->nbr_fighters].value_reg = war->value_reg;
	war->nbr_fighters++;
	return (1);
}

int					ft_copy_player_arena(t_corewar *war)
{
	t_header		*lst;
	int				i;
	int				position;
	int				pa;

	i = -1;
	if (!war->nbr_fighters)
		return (exit_error("not exist any player"));
	if (war->nbr_fighters > 4)
		return (exit_error("number player not valid"));
	pa = MEM_SIZE / war->nbr_fighters;
	position = 0;
	while (++i < war->nbr_fighters)
	{
		lst = war->players[i].data_file;
		if (lst && war->arena)
			ft_memcpy(&war->arena[position], lst->champ,
hex(addr_to_hex(&lst->prog_size, 4)));
		war->players[i].starting_point = position;
		position += pa;
	}
	return (1);
}

static	int			task_parsing(t_corewar *war, int i, char **argv)
{
	if (argv[i] && !ft_strcmp(argv[i], "-v"))
	{
		war->v = 1;
	}
	else if (argv[i] && !ft_strcmp(argv[i], "-a"))
	{
		war->a = 1;
	}
	else if (!ft_strcmp(argv[i], "-dump"))
	{
		if (!is_int(war, argv[++i]))
			return (exit_error(" not valide arg for dump "));
	}
	return (i);
}

int					parsing(t_corewar *war, int argc, char **argv)
{
	int				i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "-dump") ||
			!ft_strcmp(argv[i], "-a"))
		{
			if ((i = task_parsing(war, i, argv)) == 0)
				return (exit_error(" flag -dump "));
		}
		else if (!ft_strcmp(argv[i], "-n"))
		{
			if (!argv[++i] || !is_id_integer(argv[i]))
				return (exit_error(" flag -n "));
			war->value_reg = ft_atoi(argv[i]);
			war->status_reg = 1;
			if (!manage_file(war, war->value_reg, argv[++i]))
				return (exit_error("file not valide"));
			war->status_reg = 0;
		}
		else if (!manage_file(war, -1, argv[i]))
			return (exit_error("file not valide"));
	}
	return (ft_copy_player_arena(war));
}

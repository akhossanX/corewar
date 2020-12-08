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

static	int			task_get_id(int *array, int id)
{
	if (array[id] == 2)
	{
		array[id] = 1;
		return (id + 1);
	}
	return (exit_error("not valide  id for player"));
}

int					get_id_player(int id, int flg)
{
	static	int		array[] = {0, 0, 0, 0};
	int				i;

	i = -1;
	if (flg != 0)
	{
		if (flg != -1)
			return (task_get_id(array, id));
		while (++i < 4)
		{
			if (!array[i])
			{
				array[i] = 1;
				return (i + 1);
			}
		}
	}
	else
		array[id] = 2;
	return (0);
}

int					is_intger(char *arg)
{
	int i;
	int n;

	if (!arg)
		return (0);
	i = -1;
	n = ft_strlen(arg);
	while (++i < n)
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

int					is_int(t_corewar *war, char *arg)
{
	if (!is_intger(arg))
		return (0);
	war->dump = ft_atoi(arg);
	return (1);
}

int					get_id(char **argv)
{
	int				i;
	int				index;

	i = 0;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			index = 1;
			if (!argv[i + 1] || !is_id_integer(argv[i + 1]))
				return (exit_error(" flag -n "));
			index = ft_atoi(argv[i + 1]);
			if ((index < 5 && index > 0))
				get_id_player(index - 1, 0);
			else
				return (exit_error(" flag -n  id not valid "));
		}
		i++;
	}
	return (-1);
}

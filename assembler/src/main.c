/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:51:46 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:22:54 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
**	Checks the validity of command line arguments
**	Return value:
**		0: invalid option
**		1: valids option and input file
**		2: option -a is active
*/

static int	check_cmd_args(t_data *data, char *av[])
{
	int		i;
	int		ret;
	char	*dot;

	ret = 1;
	i = -1;
	while (av[++i])
	{
		if (*av[i] == '-')
		{
			if (ft_strcmp(av[i], "-a") == 0)
				ret = 2;
			else
				return (0);
		}
		else
		{
			if (!(dot = ft_strrchr(av[i], '.')))
				return (0);
			if (!ft_strstr(dot, ".s") && !ft_strstr(dot, ".cor"))
				return (0);
			data->filepath = av[i];
		}
	}
	return (ret);
}

int			main(int argc, char *argv[])
{
	t_data	data;
	int		cmd;

	data.filepath = NULL;
	if (argc < 2 || argc > 3)
		disp_usage(*argv);
	cmd = check_cmd_args(&data, argv + 1);
	cmd == 0 || data.filepath == NULL ? disp_usage(*argv) : 0;
	data.program_name = argv[0];
	if (ft_strstr(data.filepath, ".s"))
	{
		asm_init(&data, (const char **)argv);
		asm_assemble(&data, cmd);
	}
	else
		asm_disassemble(&data, cmd);
	return (0);
}

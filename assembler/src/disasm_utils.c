/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:55:40 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:22:25 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

t_op	*disasm_get_op(t_disasm *dis)
{
	unsigned char	opcode;

	read_bytes(dis, &opcode, 1);
	if (opcode > 16)
	{
		ft_dprintf(STDERR, "Invalid opcode at byte %d\n", dis->r - 1);
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
	return (&g_op_tab[opcode - 1]);
}

void	read_bytes(t_disasm *dis, unsigned char *buff, size_t b)
{
	int	ret;

	errno = 0;
	ret = read(dis->exec_fd, buff, b);
	if (ret == -1)
	{
		perror(dis->prog);
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
	if (ret < (int)b)
	{
		ft_printf("Error: Unexpected EOF at byte %d\n", dis->r + ret);
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
	dis->r += ret;
}

void	check_argtype(t_disasm *dis, short np, char *types)
{
	unsigned char	argtype;
	int				i;

	read_bytes(dis, &argtype, 1);
	i = -1;
	while (++i < np)
	{
		if (((argtype >> (6 - i * 2)) & 0b00000011) == REG_CODE)
			types[i] = T_REG;
		else if (((argtype >> (6 - i * 2)) & 0b00000011) == DIR_CODE)
			types[i] = T_DIR;
		else if (((argtype >> (6 - i * 2)) & 0b00000011) == IND_CODE)
			types[i] = T_IND;
		else
		{
			ft_dprintf(STDERR, "Unknown argtype code #%d at byte %d\n", i + 1\
				, dis->r - 1);
			clear_data(dis);
			exit(EXIT_FAILURE);
		}
	}
}

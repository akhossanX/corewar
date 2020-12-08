/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:55:31 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:20:48 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int		check_magic(t_disasm *dis)
{
	unsigned char	s[4];
	unsigned int	magic;
	int				i;

	read_bytes(dis, s, 4);
	i = 0;
	magic = 0;
	while (i < 4)
	{
		magic += s[i] * ft_pow(256, 3 - i);
		i++;
	}
	return (magic == COREWAR_EXEC_MAGIC);
}

void	get_champ_name(t_disasm *dis)
{
	static unsigned char	cmp[PROG_NAME_LENGTH];
	int						i;
	int						j;

	read_bytes(dis, dis->champ, PROG_NAME_LENGTH);
	i = 0;
	j = 0;
	while (i < PROG_NAME_LENGTH)
	{
		if (dis->champ[i])
			cmp[j++] = dis->champ[i];
		i++;
	}
	if (ft_memcmp((void *)cmp, (void *)dis->champ, ft_strlen((char *)cmp)))
	{
		ft_dprintf(STDERR, "{magneta}Warning:{eoc} champ name is not a string");
		ft_dprintf(STDERR, ": %s is perhaps modified\n", dis->filepath);
	}
}

void	get_size(t_disasm *dis)
{
	unsigned char	buff[4];
	int				i;
	unsigned int	size;

	read_bytes(dis, buff, 4);
	size = 0;
	i = 0;
	while (i < 4)
	{
		size += ft_pow(256, 3 - i) * buff[i];
		i++;
	}
	dis->size = size;
}

void	get_description(t_disasm *dis)
{
	static unsigned char	cmp[COMMENT_LENGTH];
	int						i;
	int						j;

	read_bytes(dis, dis->comment, COMMENT_LENGTH);
	i = 0;
	j = 0;
	while (i < COMMENT_LENGTH)
	{
		if (dis->comment[i])
			cmp[j++] = dis->comment[i];
		i++;
	}
	if (ft_memcmp((void *)cmp, (void *)dis->comment, ft_strlen((char *)cmp)))
	{
		ft_dprintf(STDERR, "{magneta}Warning:{eoc} comment is not a string:");
		ft_dprintf(STDERR, "%s is perhaps modified\n", dis->filepath);
	}
}

void	get_code(t_disasm *dis)
{
	unsigned int	i;

	i = 0;
	while (i < dis->size)
		i += get_statement(dis);
}

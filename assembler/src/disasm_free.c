/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:08 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 16:52:10 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

static void	free_statements(t_statement *lst)
{
	t_statement	*tmp;

	while (lst)
	{
		ft_strdel(&lst->opname);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void		clear_data(t_disasm *dis)
{
	if (dis->champ_fd != -1)
		close(dis->champ_fd);
	if (dis->exec_fd != -1)
		close(dis->exec_fd);
	free(dis->file);
	free_statements(dis->sts);
}

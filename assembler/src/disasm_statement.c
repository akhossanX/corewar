/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_statement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:55:36 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:21:54 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

static t_statement	*statement_new(t_disasm *dis, char *opname)
{
	t_statement	*st;

	errno = 0;
	if (!(st = (t_statement *)ft_memalloc(sizeof(t_statement))) || \
		!(st->opname = ft_strdup(opname)))
	{
		ft_dprintf(STDERR, "%s: %s\n", dis->prog, strerror(errno));
		if (st)
			free(st->opname);
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
	return (st);
}

static void			add_statement(t_disasm *dis, t_statement *new)
{
	t_statement	*lst;

	lst = dis->sts;
	if (!lst)
		dis->sts = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

static int			get_pvalue(t_disasm *dis, t_op *op, char tp, int *size)
{
	size_t			sz;
	unsigned char	buff[4];
	size_t			i;
	int				val;
	int				sign;

	sz = 1;
	tp == T_DIR ? sz = (4 >> op->sztdir) : 0;
	tp == T_IND ? sz = 2 : 0;
	read_bytes(dis, buff, sz);
	i = -1;
	val = 0;
	sign = buff[0] & 0x80;
	while (++i < sz)
	{
		if (sign)
			val |= (buff[i] ^ 0xff) << ((sz - i - 1) * 8);
		else
			val |= buff[i] << ((sz - i - 1) * 8);
	}
	sign ? val = ~val : 0;
	(*size) += sz;
	return (val);
}

int					get_statement(t_disasm *dis)
{
	char		types[3];
	int			values[3];
	t_statement	*st;
	int			size;
	int			i;

	dis->op = disasm_get_op(dis);
	if (dis->op->argtype)
		check_argtype(dis, dis->op->nbparams, types);
	else
		types[0] = T_DIR;
	i = 0;
	size = 1 + dis->op->argtype;
	while (i < dis->op->nbparams)
	{
		values[i] = get_pvalue(dis, dis->op, types[i], &size);
		i++;
	}
	st = statement_new(dis, dis->op->opname);
	st->nbparams = dis->op->nbparams;
	ft_strncpy(st->types, types, dis->op->nbparams);
	ft_memcpy(st->params, values, dis->op->nbparams * sizeof(int));
	add_statement(dis, st);
	return (size);
}

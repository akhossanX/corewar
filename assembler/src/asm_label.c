/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:53:34 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:05:25 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_label		*new_label(t_data *d, t_token *tk)
{
	t_label	*label;

	if (!(label = ft_memalloc(sizeof(t_label))))
		free_all_data(d, FAILURE);
	label->name = tk->content;
	label->line = tk->number;
	label->pos = tk->pos;
	label->ins = NULL;
	label->next = NULL;
	return (label);
}

void		add_label(t_label *lst, t_label *new)
{
	t_label	*ptr;

	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

/*
**	Returns the total size of a given assembly instruction
*/

short int	get_ins_size(t_ins *ins)
{
	short int	size;
	int			i;

	size = 1 + ins->argtype;
	i = 0;
	while (i < ins->nbparams)
	{
		if (ins->ptypes[i] == T_DIR)
			ins->psizes[i] = 4 >> ins->sztdir;
		else if (ins->ptypes[i] == T_IND)
			ins->psizes[i] = 2;
		else if (ins->ptypes[i] == T_REG)
			ins->psizes[i] = 1;
		size += ins->psizes[i];
		i++;
	}
	ins->size = size;
	return (size);
}

/*
**	Stores at which byte position a given label is.
*/

void		get_labels_offset(t_data *data)
{
	t_label	*ptr;
	t_ins	*ins;
	int		off;
	int		sz;

	off = 0;
	ptr = data->labels;
	while (ptr)
	{
		ptr->offset = off;
		ins = ptr->ins;
		sz = 0;
		while (ins)
		{
			ins->offset = off + sz;
			sz += get_ins_size(ins);
			ins = ins->next;
		}
		data->header.prog_size += sz;
		off += sz;
		ptr = ptr->next;
	}
}

/*
**	Substitutes direct and indirect labels params with
**	the relative position to the current instruction.
*/

int			preprocess_label(t_data *data, t_ins *ins, const char *name, int n)
{
	t_label	*lb;

	lb = data->labels;
	while (lb)
	{
		if (ft_strcmp(lb->name, name) == 0)
			return (lb->offset - ins->offset);
		lb = lb->next;
	}
	ft_dprintf(STDERR, "Undeclared label `%s` at [%03d][%03d]\n", \
		name, ins->ppos[n].line, ins->ppos[n].pos);
	free_all_data(data, FAILURE);
	return (0);
}

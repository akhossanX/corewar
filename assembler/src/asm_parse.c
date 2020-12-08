/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:53:43 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:06:29 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_ins	*new_ins(t_data *data, t_op *op)
{
	t_ins	*ins;

	ins = NULL;
	if (!(ins = (t_ins *)ft_memalloc(sizeof(t_ins))))
		free_all_data(data, FAILURE);
	ins->opname = op->opname;
	ins->opcode = op->opcode;
	ins->nbparams = op->nbparams;
	ins->argtype = op->argtype;
	ins->sztdir = op->sztdir;
	ins->next = NULL;
	return (ins);
}

t_ins	*get_instruction(t_data *data, t_token **tk)
{
	t_token		*ptr;
	t_parser	parser;

	ptr = *tk;
	if ((parser.op = get_op(ptr->content)))
	{
		parser.ins = new_ins(data, parser.op);
		ptr = ptr->next;
		parser.colones = parser.op->nbparams - 1;
		parser.n = 0;
		while (parser.n < parser.op->nbparams)
		{
			if (is_param(ptr))
				get_param(data, &parser, &ptr);
			else
				syntax_error(data, &parser, ptr, ERR_UNEXPECTED_TOKEN);
		}
	}
	else
		syntax_error(data, NULL, ptr, ERR_UNKNOWN_OPERATOR);
	*tk = ptr;
	return (parser.ins);
}

void	add_instruction(t_label *curr, t_ins *ins)
{
	t_ins	*ptr;

	ptr = curr->ins;
	if (ptr == NULL)
		curr->ins = ins;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = ins;
	}
}

void	asm_parse(t_data *data)
{
	t_token	*ptr;
	t_label	*curr;
	t_ins	*ins;

	curr = data->labels;
	ptr = data->tokens;
	while (ptr->type != EOFILE)
	{
		if (ptr->type == LABEL)
		{
			curr = new_label(data, ptr);
			add_label(data->labels, curr);
			if ((ptr = ptr->next) && ptr->type == EOFILE)
				syntax_error(data, NULL, ptr, ERR_UNEXPECTED_EOF);
		}
		else if (ptr->type == OPERATOR)
		{
			ins = get_instruction(data, &ptr);
			add_instruction(curr, ins);
		}
		else if (ptr->type == NEW_LINE)
			ptr = ptr->next;
		else
			syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_getparam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:02:54 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:02:26 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
**	Wrapps up a token type in either one of
**	those three main types:
**			T_IND: indirect type
**			T_DIR: direct type
**			T_REG: registry type
*/

static short	get_param_type(t_token *tk)
{
	if (tk->type == INDIRECT || tk->type == INDIRECT_LABEL)
		return (T_IND);
	else if (tk->type == DIRECT || tk->type == DIRECT_LABEL)
		return (T_DIR);
	else if (tk->type == REGISTRY)
		return (T_REG);
	return (0);
}

/*
**	Parses one single assembly instruction parameter
**	if its type doesn't match the required type
**	it reports a syntax error and exits properly.
*/

void			get_param(t_data *data, t_parser *parser, t_token **tk)
{
	t_token	*ptr;

	ptr = *tk;
	if ((parser->type = get_param_type(ptr)) & parser->op->params[parser->n])
	{
		if (parser->colones && ptr->next->type != SEPARATOR)
			syntax_error(data, parser, ptr->next, ERR_UNEXPECTED_TOKEN);
		parser->ins->params[parser->n] = ptr->content;
		parser->ins->ptypes[parser->n] = parser->type;
		parser->ins->ppos[parser->n].line = ptr->number;
		parser->ins->ppos[parser->n].pos = ptr->pos;
		ptr = parser->colones ? ptr->next->next : ptr->next;
		if (!parser->colones && ptr->type != NEW_LINE)
			syntax_error(data, parser, ptr, ERR_UNEXPECTED_TOKEN);
		parser->colones--;
		parser->n++;
	}
	else
		syntax_error(data, parser, ptr, ERR_INVALID_PARAMETER);
	*tk = ptr;
}

/*
**	Parses a numeric literal and gets its corresponding value
**	if it's a negative value it is stored as a 2 complement
**	since the cast is made from signed to unsigned.
*/

unsigned int	get_value(t_data *data, t_ins *ins, int n)
{
	int		i;
	char	*s;
	int		value;

	i = 0;
	s = ins->params[n];
	s[i] == 'r' ? i++ : 0;
	while (s[i] && ft_contains("%:", s[i]))
		i++;
	if (ft_isnumeric(&s[i]))
		value = ft_atoll(&s[i]);
	else
		value = preprocess_label(data, ins, &s[i], n);
	return (value);
}

/*
**	Gets all parameter values for all assembly instructions
*/

void			get_params_values(t_data *data)
{
	t_label	*lb;
	t_ins	*ins;
	int		i;

	lb = data->labels;
	while (lb)
	{
		ins = lb->ins;
		while (ins)
		{
			i = 0;
			while (i < ins->nbparams)
			{
				ins->pvalues[i] = get_value(data, ins, i);
				i++;
			}
			ins = ins->next;
		}
		lb = lb->next;
	}
}

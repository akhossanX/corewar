/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokens3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:54:50 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:16:25 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		token_direct(t_data *d)
{
	char	*line;
	int		i;
	int		hold;
	t_token	*tk;

	line = d->ptr->line;
	i = d->i;
	if (line[i] == DIRECT_CHAR && ++i)
	{
		if (line[i] == '-')
			i++;
		hold = i;
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (hold == i)
			return (0);
		if (!(tk = token_new(d, i - d->i, DIRECT)))
			free_all_data(d, FAILURE);
		lstappend_(&d->tokens, tk);
		d->i = i;
		return (1);
	}
	return (0);
}

int		token_operator(t_data *d)
{
	char	*line;
	int		i;
	t_token	*tk;

	line = d->ptr->line;
	i = d->i;
	while (ft_contains(LABEL_CHARS, line[i]))
		i++;
	if (i > d->i)
	{
		if (!(tk = token_new(d, i - d->i, OPERATOR)))
			free_all_data(d, FAILURE);
		lstappend_(&d->tokens, tk);
		d->i = i;
		return (1);
	}
	return (0);
}

int		token_newline(t_data *d)
{
	char	*line;
	int		i;
	t_token	*tk;

	line = d->ptr->line;
	i = d->i;
	if (line[i] == '\n')
	{
		tk = token_init(d);
		tk->content = NULL;
		tk->number = d->ptr->number;
		tk->pos = i + 1;
		tk->type = NEW_LINE;
		lstappend_(&d->tokens, tk);
		d->i = i + 1;
		return (1);
	}
	return (0);
}

int		token_whitespace(t_data *d)
{
	char	*line;
	int		i;

	line = d->ptr->line;
	i = d->i;
	if (ft_contains("\t ", line[i]))
	{
		while (line[i] && ft_contains("\t ", line[i]))
			i++;
		d->i = i;
		return (1);
	}
	return (0);
}

int		token_label(t_data *d)
{
	int		i;
	char	*line;
	t_token	*tk;

	i = d->i;
	line = d->ptr->line;
	if (ft_contains(LABEL_CHARS, line[i]))
	{
		while (line[i] && ft_contains(LABEL_CHARS, line[i]))
			i++;
		if (line[i] == LABEL_CHAR)
		{
			if (!(tk = token_new(d, i - d->i, LABEL)))
				free_all_data(d, FAILURE);
			lstappend_(&d->tokens, tk);
			d->i = i + 1;
			return (1);
		}
	}
	return (0);
}

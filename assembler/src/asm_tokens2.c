/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokens2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:54:45 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 16:54:46 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		token_indirect_label(t_data *d)
{
	char	*line;
	t_token	*tk;
	int		i;

	line = d->ptr->line;
	i = d->i;
	if (line[i] == LABEL_CHAR && ++i)
	{
		if (ft_contains(LABEL_CHARS, line[i]))
		{
			while (line[i] && ft_contains(LABEL_CHARS, line[i]))
				i++;
			if (!(tk = token_new(d, i - d->i, INDIRECT_LABEL)))
				free_all_data(d, FAILURE);
			lstappend_(&d->tokens, tk);
			d->i = i;
			return (1);
		}
	}
	return (0);
}

int		token_indirect(t_data *d)
{
	char	*line;
	int		i;
	t_token	*tk;
	int		offset;

	line = d->ptr->line;
	i = d->i;
	line[i] == '-' ? i++ : 0;
	if ((offset = is_numeric(&line[i])))
	{
		i += offset;
		if (!(tk = token_new(d, i - d->i, INDIRECT)))
			free_all_data(d, FAILURE);
		lstappend_(&d->tokens, tk);
		d->i = i;
		return (1);
	}
	return (0);
}

int		token_direct_label(t_data *d)
{
	char	*line;
	int		i;
	t_token	*tk;

	line = d->ptr->line;
	i = d->i;
	if (ft_strncmp(&line[i], "%:", 2) == 0)
	{
		i += 2;
		if (ft_contains(LABEL_CHARS, line[i]))
		{
			while (line[i] && ft_contains(LABEL_CHARS, line[i]))
				i++;
			if (!(tk = token_new(d, i - d->i, DIRECT_LABEL)))
				free_all_data(d, FAILURE);
			lstappend_(&d->tokens, tk);
			d->i = i;
			return (1);
		}
	}
	return (0);
}

int		token_separator(t_data *d)
{
	char	*line;
	t_token	*tk;

	line = d->ptr->line;
	if (line[d->i] == SEPARATOR_CHAR)
	{
		tk = token_init(d);
		if (!(tk->content = ft_strdup(",")))
		{
			free(tk);
			free_all_data(d, FAILURE);
		}
		tk->number = d->ptr->number;
		tk->pos = d->i + 1;
		tk->type = SEPARATOR;
		tk->next = NULL;
		lstappend_(&d->tokens, tk);
		d->i += 1;
		return (1);
	}
	return (0);
}

int		token_registry(t_data *d)
{
	char	*line;
	int		i;
	t_token	*tk;

	line = d->ptr->line;
	i = d->i;
	if (line[i] == REGISTRY_CHAR && ++i)
	{
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (i - d->i == 3 || i - d->i == 2)
		{
			if (!(tk = token_new(d, i - d->i, REGISTRY)))
				free_all_data(d, FAILURE);
			lstappend_(&d->tokens, tk);
			d->i = i;
			return (1);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:30:25 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:15:13 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		token_string_literal(t_data *d)
{
	t_token	*tk;
	char	*line;
	char	*s;
	char	*ap;
	int		nb;

	line = d->ptr->line;
	nb = d->ptr->number;
	if (line[d->i] == '"' && ++d->i)
	{
		ap = ft_strchr(line + d->i, '"');
		s = ap ? ft_strsub(line, d->i, \
			ap - line - d->i) : ft_strdup(line + d->i);
		tk = token_init(d);
		tk->type = STRING_LITERAL;
		tk->pos = d->i;
		tk->number = nb;
		d->i = !ap ? get_string_literal(d, &s, nb) : \
			d->i + (int)ft_strlen(s) + 1;
		tk->content = s;
		tk->next = NULL;
		lstappend_(&d->tokens, tk);
		return (1);
	}
	return (0);
}

int		token_name_cmd(t_data *d)
{
	char	*line;
	t_token	*tk;

	line = d->ptr->line;
	if (ft_strncmp(NAME_CMD_STRING, line + d->i, 5) == 0)
	{
		tk = token_init(d);
		if (!(tk->content = ft_strdup(".name")))
			free_all_data(d, FAILURE);
		tk->type = CMD_NAME;
		tk->next = NULL;
		tk->number = d->ptr->number;
		tk->pos = d->i + 1;
		d->i += 5;
		lstappend_(&d->tokens, tk);
		return (1);
	}
	return (0);
}

int		token_comment_cmd(t_data *d)
{
	char	*line;
	t_token	*tk;

	line = d->ptr->line;
	if (ft_strncmp(COMMENT_CMD_STRING, line + d->i, 8) == 0)
	{
		tk = token_init(d);
		if (!(tk->content = ft_strdup(".comment")))
			free_all_data(d, FAILURE);
		tk->type = CMD_COMMENT;
		tk->next = NULL;
		tk->number = d->ptr->number;
		tk->pos = d->i + 1;
		d->i += 8;
		lstappend_(&d->tokens, tk);
		return (1);
	}
	return (0);
}

int		token_comment(t_data *d)
{
	char	*line;

	line = d->ptr->line;
	if (line[d->i] == COMMENT_CHAR || line[d->i] == ALT_COMMENT_CHAR)
	{
		while (line[d->i] && line[d->i] != '\n')
			d->i++;
		return (1);
	}
	return (0);
}

int		token_eol(t_data *d)
{
	t_token	*tk;
	t_line	*tmp;

	if (!d->ptr->line[d->i])
	{
		tmp = d->ptr;
		if ((d->ptr = d->ptr->next) == NULL)
		{
			tk = token_init(d);
			tk->type = EOFILE;
			tk->number = tmp->number;
			tk->pos = d->i + 1;
			lstappend_(&d->tokens, tk);
		}
		d->i = 0;
		return (1);
	}
	return (0);
}

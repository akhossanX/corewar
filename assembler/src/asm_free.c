/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:52 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:01:01 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	free_all_data(t_data *d, int state)
{
	if (errno)
		perror(d->program_name);
	ft_strdel(&d->buff);
	free_lines(d->lst);
	free_tokens(d->tokens);
	free_labels(d->labels);
	free(d->exec_file);
	if (state == FAILURE)
		exit(EXIT_FAILURE);
}

void	free_lines(t_line *lst)
{
	t_line	*tmp;

	while (lst)
	{
		tmp = lst;
		free(tmp->line);
		lst = lst->next;
		free(tmp);
	}
}

void	free_tokens(t_token *lst)
{
	t_token *tk;

	while (lst)
	{
		tk = lst;
		lst = lst->next;
		free(tk->content);
		tk->content = NULL;
		free(tk);
	}
}

void	free_labels(t_label *labels)
{
	t_label	*ptr;
	t_ins	*ins;
	t_ins	*tmp;

	while (labels)
	{
		ins = labels->ins;
		while (ins)
		{
			tmp = ins;
			ins = ins->next;
			free(tmp);
		}
		ptr = labels;
		labels = labels->next;
		free(ptr);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:53:26 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:03:32 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	asm_init(t_data *dat, const char **argv)
{
	dat->fd_assm = open(dat->filepath, O_RDONLY);
	if (dat->fd_assm == -1)
	{
		ft_dprintf(STDERR, "%s: ", argv[0]);
		perror(dat->filepath);
		exit(EXIT_FAILURE);
	}
	errno = 0;
	dat->i = 0;
	dat->fd_exec = -1;
	dat->exec_file = NULL;
	dat->lst = NULL;
	dat->ptr = NULL;
	dat->buff = NULL;
	dat->tokens = NULL;
	dat->header.magic = COREWAR_EXEC_MAGIC;
	dat->header.prog_size = 0;
	ft_bzero((void *)dat->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero((void *)dat->header.comment, COMMENT_LENGTH + 1);
	if (!(dat->labels = (t_label *)ft_memalloc(sizeof(t_label))))
		free_all_data(dat, FAILURE);
	dat->labels->name = "_default";
}

t_token	*token_new(t_data *dat, int size, t_type code)
{
	t_token	*token;

	if (!(token = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (!(token->content = ft_strsub(dat->ptr->line, dat->i, size)))
	{
		free(token);
		return (NULL);
	}
	token->type = code;
	token->number = dat->ptr->number;
	token->pos = dat->i + 1;
	token->next = NULL;
	return (token);
}

t_token	*token_init(t_data *d)
{
	t_token	*tk;

	if (!(tk = (t_token *)ft_memalloc(sizeof(t_token))))
	{
		perror(d->program_name);
		free_lines(d->lst);
		free_tokens(d->tokens);
		free_labels(d->labels);
		exit(EXIT_FAILURE);
	}
	return (tk);
}

void	lstappend_(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		if (new->type == ptr->type && new->type == NEW_LINE)
		{
			free(new);
			return ;
		}
		ptr->next = new;
		new->next = NULL;
	}
}

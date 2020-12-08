/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:59:32 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:07:34 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_line	*new_line(t_data *d, char **line, int *n)
{
	t_line	*node;

	if (!(node = (t_line *)malloc(sizeof(t_line))))
		free_all_data(d, FAILURE);
	node->line = *line;
	node->number = ++(*n);
	node->next = NULL;
	return (node);
}

void	add_line(t_line **lines, t_line *new)
{
	t_line	*tmp;

	if (*lines == NULL)
		*lines = new;
	else
	{
		tmp = *lines;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	asm_read(t_data *d)
{
	t_line	*node;
	char	*line;
	int		n;
	int		ret;

	line = NULL;
	n = 0;
	while ((ret = get_next_line(d->fd_assm, &line)) > 0)
	{
		node = new_line(d, &line, &n);
		add_line(&d->lst, node);
	}
	if (ret < 0)
	{
		close(d->fd_assm);
		free_labels(d->labels);
		free_lines(d->lst);
		ft_dprintf(STDERR, "%s: ", d->program_name);
		perror(d->filepath);
		exit(EXIT_FAILURE);
	}
	close(d->fd_assm);
}

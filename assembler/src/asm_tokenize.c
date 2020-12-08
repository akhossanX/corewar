/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:54:29 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:08:49 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	asm_tokenize(t_data *d)
{
	int		flg;
	int		j;

	if (!(d->ptr = d->lst))
	{
		ft_dprintf(STDERR, "Unexpected token EOF at [001:001]\n");
		free_all_data(d, FAILURE);
	}
	while (d->ptr)
	{
		flg = 0;
		j = -1;
		while (++j < TOKENIZERS)
		{
			if (g_tokenizers[j](d) == 1)
			{
				flg = 1;
				break ;
			}
		}
		if (!flg)
			lexic_error(d);
	}
}

int		get_string_literal(t_data *d, char **s, int nb)
{
	char	*tmp;
	char	*ap;

	d->ptr = d->ptr->next;
	while (d->ptr && !(ap = ft_strchr(d->ptr->line, '"')))
	{
		tmp = *s;
		*s = ft_strjoin(*s, d->ptr->line);
		free(tmp);
		d->ptr = d->ptr->next;
	}
	if (!d->ptr)
	{
		free(*s);
		ft_dprintf(STDERR, "No closing match for `\"` at [%03d:%03d]\n", \
			nb, d->i + 1);
		free_all_data(d, FAILURE);
	}
	tmp = *s;
	*s = ft_strnjoin(*s, d->ptr->line, ap - d->ptr->line + 1);
	free(tmp);
	d->i = ap - d->ptr->line + 1;
	return (d->i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:29:33 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:17:55 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		is_param(t_token *tk)
{
	int	t;

	t = tk->type;
	return (t == DIRECT || t == INDIRECT || t == DIRECT_LABEL \
			|| t == INDIRECT_LABEL || t == REGISTRY);
}

void	skip_spaces(char *s, t_data *d)
{
	d->i = 0;
	while (s[d->i] && ft_isspace(s[d->i]))
		d->i++;
}

void	skip_comment(char *s, t_data *d)
{
	if (s[d->i] == COMMENT_CHAR)
		while (s[d->i] && s[d->i] != '\n')
			d->i++;
}

int		is_numeric(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_contains(" ,\t\n#", s[i]))
			break ;
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (i);
}

void	open_exec_file(t_data *data)
{
	char	*base_name;
	char	*dot;

	dot = ft_strrchr(data->filepath, '.') - 1;
	errno = 0;
	base_name = ft_strsub(data->filepath, 0, dot - data->filepath + 1);
	if (!base_name || !(data->exec_file = ft_strjoin(base_name, ".cor")))
	{
		free(base_name);
		free_all_data(data, FAILURE);
	}
	free(base_name);
	data->fd_exec = open(data->exec_file, O_WRONLY | O_CREAT, S_IRWXU);
	if (data->fd_exec == -1)
		free_all_data(data, FAILURE);
}

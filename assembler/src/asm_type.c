/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:54:59 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 16:55:00 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*get_token_content(t_token *tk)
{
	if (tk->type == NEW_LINE)
		return ("\\n");
	else if (tk->type == EOFILE)
		return ("EOFILE");
	return (tk->content);
}

t_op	*get_op(char *opname)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(opname, g_op_tab[i].opname) == 0)
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

char	*get_type(t_type type)
{
	return ((char *)g_type[(int)type]);
}

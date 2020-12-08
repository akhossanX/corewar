/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:53:16 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 16:53:17 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			get_assm_name(t_data *data, t_token **tk)
{
	t_token	*ptr;

	ptr = (*tk)->next;
	if (ptr->type == STRING_LITERAL)
	{
		if (ft_strlen(ptr->content) > PROG_NAME_LENGTH)
			syntax_error(data, NULL, ptr, ERR_CHAMP_NAME_LENGTH);
		ft_strcpy(data->header.prog_name, ptr->content);
		if ((ptr = ptr->next) && ptr->type != NEW_LINE)
			syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
		*tk = ptr;
		return (1);
	}
	syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
	return (0);
}

int			get_assm_comment(t_data *data, t_token **tk)
{
	t_token	*ptr;

	ptr = (*tk)->next;
	if (!ptr)
		return (0);
	if (ptr->type == STRING_LITERAL)
	{
		if (ft_strlen(ptr->content) > COMMENT_LENGTH)
			syntax_error(data, NULL, ptr, ERR_CHAMP_COMMENT_LENGTH);
		ft_strcpy(data->header.comment, ptr->content);
		if ((ptr = ptr->next) && ptr->type != NEW_LINE)
			syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
		*tk = ptr;
		return (1);
	}
	syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
	return (0);
}

void		get_assm_header(t_data *data)
{
	t_token	*ptr;
	t_token	*tmp;
	int		done;

	ptr = data->tokens;
	done = 0;
	while (ptr && done < 2)
	{
		if (ptr->type == CMD_NAME)
			done += get_assm_name(data, &ptr);
		else if (ptr->type == CMD_COMMENT)
			done += get_assm_comment(data, &ptr);
		else if (ptr->type != NEW_LINE)
			syntax_error(data, NULL, ptr, ERR_UNKNOWN_COMMAND);
		else
			ptr = ptr->next;
	}
	if (!ptr || ptr->type != NEW_LINE)
		syntax_error(data, NULL, ptr, ERR_UNEXPECTED_TOKEN);
	tmp = data->tokens;
	data->tokens = ptr->next;
	ptr->next = NULL;
	free_tokens(tmp);
}

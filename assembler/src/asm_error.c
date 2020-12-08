/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:46 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:00:25 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
**	Report lexical errors whenever it encounters a token
**	that is not defined by the pseudo-assembly grammar
*/

void	lexic_error(t_data *data)
{
	ft_dprintf(STDERR, "Lexic error:Unknown token at [%03d:%03d]\n", \
		data->ptr->number, data->i + 1);
	free_all_data(data, FAILURE);
}

/*
**	Report Syntax errors
*/

void	syntax_error(t_data *data, t_parser *parser, t_token *tk, int err)
{
	if (err == ERR_UNKNOWN_OPERATOR)
		ft_dprintf(2, "Syntax Error: Unknown OPERATOR `%s` at [%03d:%03d]\n", \
			get_token_content(tk), tk->number, tk->pos);
	else if (err == ERR_UNEXPECTED_TOKEN)
		ft_dprintf(2, "Syntax Error: Unexpected token `%s` %s at [%03d:%03d]\n"\
			, get_token_content(tk), get_type(tk->type), tk->number, tk->pos);
	else if (err == ERR_UNEXPECTED_EOF)
		ft_dprintf(2, "Syntax Error: Unexpected token %s at [%03d:%03d]\n",\
			get_type(tk->type), tk->number, tk->pos);
	else if (err == ERR_UNKNOWN_COMMAND)
		ft_dprintf(2, "Unknown command `%s` at token [%03d:%03d]\n", \
			tk->content, tk->number, tk->pos);
	else if (err == ERR_CHAMP_NAME_LENGTH)
		ft_dprintf(2, "Champion name too long (Max %d)\n", PROG_NAME_LENGTH);
	else if (err == ERR_CHAMP_COMMENT_LENGTH)
		ft_dprintf(2, "Champion comment too long (Max %d)\n",\
			COMMENT_LENGTH);
	else if (err == ERR_INVALID_PARAMETER)
	{
		ft_dprintf(2, "Syntax Error: Invalid type of parameter ");
		ft_dprintf(2, "#%d %s at [%03d:%03d]\n", parser->n + 1, \
			get_type(tk->type), tk->number, tk->pos);
	}
	parser ? free(parser->ins) : 0;
	free_all_data(data, FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_symbol_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:53:54 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 18:08:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
**	Do not mess with the order in which
**	the function pointers are stored,
**	the order complies with the
**	"longest token" match rule.
*/

t_tokenizer	g_tokenizers[TOKENIZERS] =
{
	token_comment,
	token_string_literal,
	token_eol,
	token_name_cmd,
	token_comment_cmd,
	token_label,
	token_newline,
	token_direct,
	token_registry,
	token_separator,
	token_direct_label,
	token_indirect,
	token_indirect_label,
	token_whitespace,
	token_operator,
};

const char	*g_type[] =
{
	"LABEL",
	"OPERATOR",
	"REGISTRY",
	"SEPARATOR",
	"DIRECT_LABEL",
	"DIRECT",
	"INDIRECT",
	"INDIRECT_LABEL",
	"WHITESPACE",
	"STRING_LITERAL",
	"CMD_NAME",
	"CMD_COMMENT",
	"NEW_LINE",
	"EOFILE",
	NULL,
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:51:15 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/30 16:33:07 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLER_H
# define DISASSEMBLER_H

# include "assembler.h"

typedef struct	s_statement
{
	char				*opname;
	int					nbparams;
	int					params[MAX_OP_PARAMS];
	char				types[MAX_OP_PARAMS];
	struct s_statement	*next;
}				t_statement;

typedef struct	s_disasm
{
	unsigned char	champ[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	const char		*filepath;
	int				exec_fd;
	int				champ_fd;
	unsigned int	size;
	int				r;
	char			*file;
	const char		*prog;
	t_op			*op;
	t_statement		*sts;
}				t_disasm;

void			get_size(t_disasm *dis);
void			get_code(t_disasm *dis);
int				check_magic(t_disasm *dis);
int				get_statement(t_disasm *dis);
void			get_champ_name(t_disasm *dis);
void			get_description(t_disasm *dis);

void			clear_data(t_disasm *dis);
t_op			*disasm_get_op(t_disasm *dis);
void			check_argtype(t_disasm *dis, short np, char *types);
void			read_bytes(t_disasm *dis, unsigned char *buff, size_t b);

#endif

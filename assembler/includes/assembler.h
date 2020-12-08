/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:34:57 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 17:23:16 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define TOKENIZERS			15
# define SUCCESS			0
# define FAILURE			1

/*
**	User-defined codes for syntax errors
*/

# define ERR_UNKNOWN_OPERATOR		1
# define ERR_UNEXPECTED_TOKEN		2
# define ERR_UNEXPECTED_EOF			3
# define ERR_INVALID_PARAMETER		4
# define ERR_UNKNOWN_COMMAND		5
# define ERR_CHAMP_NAME_LENGTH		6
# define ERR_CHAMP_COMMENT_LENGTH	7

/*
**	Enum Codes for all possible types of tokens
**
**	LABEL: `label:`
**	OPERATOR: `live|ld|...`
**	REGISTRY: `r[unsigned numeric literal]`
**	SEPARATOR: `,`
**	DIRECT_LABEL: `%:label`
**	DIRECT: `%[numeric literal]`
**	INDIRECT: `numeric literal`
**	INDIRECT_LABEL: `:label`
**	WHITESPAEC: `Whitespaces`
**	STRING_LITERTAL: `String literal`
**	CMD_NAME: `.name`
**	CMD_COMMENT: `.name`
**	NEW_LINE: `\n` marks the end of an instruction
*/

typedef enum	e_type
{
	LABEL,
	OPERATOR,
	REGISTRY,
	SEPARATOR,
	DIRECT_LABEL,
	DIRECT,
	INDIRECT,
	INDIRECT_LABEL,
	WHITESPACE,
	STRING_LITERAL,
	CMD_NAME,
	CMD_COMMENT,
	NEW_LINE,
	EOFILE
}				t_type;

typedef struct	s_token
{
	t_type			type;
	char			*content;
	unsigned long	number;
	unsigned int	pos;
	struct s_token	*next;
}				t_token;

typedef struct	s_line
{
	char			*line;
	int				number;
	struct s_line	*next;
}				t_line;

typedef struct	s_pos
{
	int			line;
	int			pos;
}				t_pos;

typedef struct	s_ins
{
	char			*opname;
	short			nbparams;
	char			*params[MAX_OP_PARAMS];
	unsigned char	ptypes[MAX_OP_PARAMS];
	unsigned int	pvalues[MAX_OP_PARAMS];
	unsigned int	psizes[MAX_OP_PARAMS];
	t_pos			ppos[MAX_OP_PARAMS];
	unsigned char	opcode;
	char			argtype;
	char			sztdir;
	unsigned short	size;
	unsigned int	offset;
	struct s_ins	*next;
}				t_ins;

typedef struct	s_parser
{
	int				colones;
	int				n;
	short			type;
	t_ins			*ins;
	t_op			*op;
}				t_parser;

typedef struct	s_label
{
	char			*name;
	int				line;
	int				pos;
	size_t			offset;
	t_ins			*ins;
	struct s_label	*next;
}				t_label;

typedef struct	s_data
{
	const char		*program_name;
	const char		*filepath;
	char			*exec_file;
	char			*buff;
	t_arg_type		argt;
	int				fd_assm;
	int				fd_exec;
	int				i;
	t_header		header;
	t_line			*lst;
	t_line			*ptr;
	t_token			*tokens;
	t_label			*labels;
}				t_data;

typedef int		(*t_tokenizer)(t_data *);

extern t_tokenizer	g_tokenizers[];
extern const char	*g_type[];
extern t_op		g_op_tab[];

void			free_lines(t_line *lst);
void			free_tokens(t_token *tk);
void			free_labels(t_label *labels);
void			free_all_data(t_data *d, int state);

int				is_numeric(const char *s);
int				is_param(t_token *tk);
void			skip_comment(char *s, t_data *data);
void			skip_spaces(char *s, t_data *data);
void			open_exec_file(t_data *data);
int				preprocess_label(t_data *data, t_ins *ins, const char *name, \
				int n);

void			disp_usage(const char *prg);
void			disp_lines(t_data *data);
void			disp_ins(t_data *data);
void			disp_tokens(t_data *data);
void			disp_header(t_data *data);

void			asm_init(t_data *data, const char **argv);
void			asm_tokenize(t_data *data);
void			asm_read(t_data *data);
void			asm_parse(t_data *data);
void			asm_code(t_data *data, int cmd);

char			*get_type(t_type type);
void			get_param(t_data *data, t_parser *parser, t_token **tk);
char			*get_token_content(t_token *tk);
int				get_string_literal(t_data *d, char **s, int nb);
void			get_assm_header(t_data *data);
void			get_labels_offset(t_data *data);
void			get_params_values(t_data *data);
t_op			*get_op(char *content);

void			syntax_error(t_data *data, t_parser *parser, t_token *tk, \
				int err);
void			lexic_error(t_data *data);

void			lstappend_(t_token **lst, t_token *new);
t_token			*token_new(t_data *d, int size, t_type code);
t_token			*token_init(t_data *d);
t_label			*new_label(t_data *data, t_token *tk);
void			add_label(t_label *lb, t_label *new);

int				token_label(t_data *d);
int				token_whitespace(t_data *d);
int				token_newline(t_data *d);
int				token_operator(t_data *d);
int				token_direct(t_data *d);
int				token_registry(t_data *d);
int				token_separator(t_data *d);
int				token_direct_label(t_data *d);
int				token_indirect(t_data *d);
int				token_indirect_label(t_data *d);
int				token_comment_cmd(t_data *d);
int				token_name_cmd(t_data *d);
int				token_string_literal(t_data *d);
int				token_comment(t_data *d);
int				token_eol(t_data *d);

void			asm_assemble(t_data *data, int option);
void			asm_disassemble(t_data *data, int option);

#endif

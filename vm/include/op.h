/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define MAX_CYCLE	3666
# define IND_SIZE	2
# define REG_SIZE	4
# define DIR_SIZE REG_SIZE

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE 4096
# define IDX_MOD 512
# define CHAMP_MAX_SIZE 682

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER 16

# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define PROG_NAME_LENGTH 128
# define COMMENT_LENGTH 2048
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef	struct			s_header
{
	unsigned	int		magic;
	char				prog_name[PROG_NAME_LENGTH + 5];
	unsigned	int		prog_size;
	char				comment[COMMENT_LENGTH + 5];
	unsigned	char	champ[CHAMP_MAX_SIZE + 1];
}						t_header;

typedef	struct			s_op
{
	char				*name;
	int					nbr_args;
	int					args[3];
	int					id;
	int					nbr_cycler;
	char				*name_actoin;
	int					beyt_arg;
	int					size_dir;
}						t_op;
#endif

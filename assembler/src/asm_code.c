/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:26 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 17:51:31 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
**	Reads, in Big-endian order, n bytes from an unsigned value
**	and stores each of those bytes into a string representation
*/

static char	*to_big_endian(unsigned int val, int n)
{
	char	*str;
	int		i;

	errno = 0;
	if (!(str = (char *)ft_memalloc(n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = (val >> ((n - i - 1) * 8)) & 0xff;
		i++;
	}
	return (str);
}

/*
**	Writes the assembly header to the bytecode buffer
*/

size_t		write_header_to_buffer(t_data *data)
{
	size_t	pos;
	char	*ptr;

	pos = 0;
	if (!(ptr = to_big_endian(data->header.magic, 4)))
		return (0);
	ft_memcpy((void *)data->buff, (void *)ptr, 4);
	free(ptr);
	pos += 4;
	ft_memcpy((void *)(data->buff + pos), (void *)data->header.prog_name, \
		PROG_NAME_LENGTH);
	pos += PROG_NAME_LENGTH;
	ft_memcpy((void *)(data->buff + pos), "\0\0\0\0", 4);
	pos += 4;
	if (!(ptr = to_big_endian(data->header.prog_size, 4)))
		return (0);
	ft_memcpy((void *)(data->buff + pos), (void *)ptr, 4);
	free(ptr);
	pos += 4;
	ft_memcpy((void *)(data->buff + pos), (void *)data->header.comment, \
		COMMENT_LENGTH);
	pos += COMMENT_LENGTH;
	ft_memcpy((void *)(data->buff + pos), "\0\0\0\0", 4);
	pos += 4;
	return (pos);
}

/*
**	Writes assembly instruction bytecode to bytecode buffer
*/

void		write_ins_bytes(t_data *data, t_ins *ins, size_t *pos)
{
	int		i;
	char	*ptr;

	ft_memcpy((void *)(data->buff + *pos), (char *)&ins->opcode, 1);
	(*pos)++;
	data->argt = 0b0;
	i = 0;
	while (ins->argtype && i < ins->nbparams)
	{
		ins->ptypes[i] == T_DIR ? data->argt |= DIR_CODE << (6 - i * 2) : 0;
		ins->ptypes[i] == T_IND ? data->argt |= IND_CODE << (6 - i * 2) : 0;
		ins->ptypes[i] == T_REG ? data->argt |= REG_CODE << (6 - i * 2) : 0;
		i++;
	}
	ins->argtype ? ft_memcpy(data->buff + *pos, &data->argt, 1) : 0;
	ins->argtype ? (*pos)++ : 0;
	i = -1;
	while (++i < ins->nbparams)
	{
		if (!(ptr = to_big_endian(ins->pvalues[i], ins->psizes[i])))
			free_all_data(data, FAILURE);
		ft_memcpy((void *)(data->buff + *pos), (void *)ptr, ins->psizes[i]);
		*pos += ins->psizes[i];
		ft_strdel(&ptr);
	}
}

/*
**	Loops through all assembly instructions and writes their
**	bytecode to the bytecode buffer
*/

void		write_code_to_buffer(t_data *data, size_t pos)
{
	t_label	*lb;
	t_ins	*ins;

	lb = data->labels;
	while (lb)
	{
		ins = lb->ins;
		while (ins)
		{
			write_ins_bytes(data, ins, &pos);
			ins = ins->next;
		}
		lb = lb->next;
	}
}

/*
**	Dumps the bytecode into a .cor file
**	if "-m" switch is enabled, it only dumps
**	a detailed representation of the assembly file
**	without writing it to a .cor file
*/

void		asm_code(t_data *data, int cmd)
{
	size_t	pos;
	size_t	size;

	get_labels_offset(data);
	get_params_values(data);
	if (cmd == 2)
	{
		disp_header(data);
		disp_ins(data);
	}
	else
	{
		size = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
		size += data->header.prog_size;
		if (!(data->buff = (char *)ft_memalloc(size)))
			free_all_data(data, FAILURE);
		open_exec_file(data);
		pos = 0;
		if (!(pos += write_header_to_buffer(data)))
			free_all_data(data, FAILURE);
		write_code_to_buffer(data, pos);
		ft_printf("Writing output to %s\n", data->exec_file);
		write(data->fd_exec, data->buff, size);
		close(data->fd_exec);
	}
}

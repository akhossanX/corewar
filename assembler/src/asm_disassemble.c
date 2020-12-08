/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_disassemble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:35 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/26 10:35:36 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

static void	disasm_init(t_disasm *disasm, t_data *d)
{
	ft_bzero((void *)disasm, sizeof(t_disasm));
	disasm->exec_fd = open(d->filepath, O_RDONLY);
	if (disasm->exec_fd == -1)
	{
		ft_dprintf(STDERR, "%s: %s:", d->program_name, d->filepath);
		ft_dprintf(STDERR, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	disasm->champ_fd = -1;
	disasm->prog = d->program_name;
	disasm->filepath = d->filepath;
	disasm->r = 1;
}

static void	open_champ_file(t_disasm *dis)
{
	char	*dot;

	dot = ft_strrchr(dis->filepath, '.');
	if (!(dis->file = ft_strsub(dis->filepath, 0, dot - dis->filepath)))
	{
		ft_dprintf(STDERR, "%s: %s\n", dis->prog, strerror(errno));
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
	dis->file = ft_strjoin_free(dis->file, ft_strdup(".s"));
	dis->champ_fd = open(dis->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (dis->champ_fd == -1)
	{
		ft_dprintf(STDERR, "%s: %s\n", dis->prog, strerror(errno));
		clear_data(dis);
		exit(EXIT_FAILURE);
	}
}

static void	write_src_code(t_disasm *dis, int fd)
{
	t_statement	*ptr;
	int			i;
	int			colons;

	ft_dprintf(fd, ".name \"%s\"\n", dis->champ);
	ft_dprintf(fd, ".comment \"%s\"\n\n", dis->comment);
	ptr = dis->sts;
	while (ptr)
	{
		ft_dprintf(fd, "\t%s\t", ptr->opname);
		colons = ptr->nbparams - 1;
		i = -1;
		while (++i < ptr->nbparams)
		{
			if (ptr->types[i] == T_DIR)
				ft_dprintf(fd, "%%%d", ptr->params[i]);
			else if (ptr->types[i] == T_REG)
				ft_dprintf(fd, "r%d", ptr->params[i]);
			else
				ft_dprintf(fd, "%d", ptr->params[i]);
			colons-- ? ft_dprintf(fd, ",\t") : 0;
		}
		ft_dprintf(fd, "\n");
		ptr = ptr->next;
	}
}

void		asm_disassemble(t_data *d, int cmd)
{
	t_disasm		dis;
	unsigned char	null[4];

	disasm_init(&dis, d);
	if (check_magic(&dis) == 0)
	{
		ft_dprintf(STDERR, "Invalid magic header\n");
		exit(EXIT_FAILURE);
	}
	get_champ_name(&dis);
	read_bytes(&dis, null, 4);
	get_size(&dis);
	get_description(&dis);
	read_bytes(&dis, null, 4);
	get_code(&dis);
	cmd != 2 ? open_champ_file(&dis) : 0;
	cmd == 2 ? ft_printf("Dumping source code to standard output\n\n") : 0;
	cmd != 2 ? ft_dprintf(STDOUT, "Writing output to %s\n", dis.file) : 0;
	write_src_code(&dis, cmd == 2 ? STDOUT : dis.champ_fd);
	clear_data(&dis);
}

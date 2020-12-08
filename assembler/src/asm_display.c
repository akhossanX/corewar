/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:41 by akhossan          #+#    #+#             */
/*   Updated: 2020/11/30 16:47:37 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	disp_lines(t_data *d)
{
	t_line	*tmp;

	tmp = d->lst;
	while (tmp)
	{
		ft_printf("{magneta}%2d|{eoc}%s", tmp->number, tmp->line);
		tmp = tmp->next;
	}
}

void	disp_usage(const char *program_name)
{
	ft_dprintf(STDERR, "{yellow}Usage:\n");
	ft_dprintf(STDERR, "\t%s [-a] <champion.s|bytecode.cor>\n", \
		program_name);
	ft_dprintf(STDERR,
"{blue}\t-a{eoc}: Do not create a .cor|.s file, output instead a ");
	ft_dprintf(STDERR, "stripped version of the code to the standard output");
	ft_dprintf(STDERR, "\n");
	exit(EXIT_FAILURE);
}

void	disp_ins(t_data *data)
{
	t_label	*lb;
	t_ins	*ins;
	int		i;

	lb = data->labels;
	while (lb)
	{
		i = !(ft_strcmp(lb->name, "_default") == 0);
		i == 1 ? ft_printf("(%02d) %-10s:\n", lb->offset, lb->name) : 0;
		ins = lb->ins;
		while (ins)
		{
			ft_printf("\t\t(%d) %5s\t", ins->size, ins->opname);
			i = -1;
			while (++i < ins->nbparams)
			{
				ins->ptypes[i] == T_DIR ? ft_printf("%%") : 0;
				ins->ptypes[i] == T_REG ? ft_printf("r") : 0;
				ft_printf("%d\t", ins->pvalues[i]);
			}
			ft_printf("\n");
			ins = ins->next;
		}
		lb = lb->next;
	}
}

void	disp_header(t_data *data)
{
	ft_printf("Dumping annotated program on standart output\n");
	ft_printf("Program size : %d bytes\n", data->header.prog_size);
	ft_printf("Name : \"%s\"\n", data->header.prog_name);
	ft_printf("Comment : \"%s\"\n\n", data->header.comment);
}

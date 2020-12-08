/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_assemble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:21 by akhossan          #+#    #+#             */
/*   Updated: 2020/10/14 16:52:23 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void		asm_assemble(t_data *data, int cmd)
{
	asm_read(data);
	asm_tokenize(data);
	get_assm_header(data);
	asm_parse(data);
	asm_code(data, cmd);
	free_all_data(data, SUCCESS);
}

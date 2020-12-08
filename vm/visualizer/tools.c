/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:06:05 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 17:38:59 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int		event_listenner(void)
{
	int	key;

	if ((key = getch()) == -1)
		return (0);
	return (key);
}

void	init_colors(void)
{
	start_color();
	init_pair(PLAYER1, COLOR_RED, 0);
	init_pair(5, 0, COLOR_RED);
	init_pair(PLAYER2, COLOR_GREEN, 0);
	init_pair(6, 0, COLOR_GREEN);
	init_pair(PLAYER3, COLOR_BLUE, 0);
	init_pair(7, 0, COLOR_BLUE);
	init_pair(PLAYER4, COLOR_MAGENTA, 0);
	init_pair(8, 0, COLOR_MAGENTA);
	init_pair(9, 8, 0);
	init_pair(OUT_PROCE, 8, 8);
	init_pair(10, COLOR_WHITE, COLOR_WHITE);
}

void	print_byte(const void *addr, t_visu *visu, int i, int j)
{
	const char	*str = "0123456789abcdef";
	uint8_t		*p;

	p = (uint8_t *)addr;
	mvwprintw(visu->arena, i, j, "%c", str[(p[0] / 16) % 16]);
	mvwprintw(visu->arena, i, j + 1, "%c", str[p[0] % 16]);
}

void	say_winner(t_corewar *war, t_visu *visu)
{
	char	*msg;

	msg = NULL;
	if (!visu->close)
	{
		msg = ft_nstrjoin(3, "gtts-cli 'congratulations ",\
		war->players[visu->win].data_file->prog_name,\
		"' -l 'en' -o vm/visualizer/assets/winner.mp3");
		system(msg);
		system("afplay vm/visualizer/assets/winner.mp3 &");
		ft_strdel(&msg);
	}
}

void	print_winner(t_corewar *war, t_visu *visu)
{
	if (!visu)
	{
		print_winer();
		return ;
	}
	if (visu->win >= 0 && visu->win < 4)
	{
		wattron(visu->menu, A_BOLD);
		wattron(visu->menu, COLOR_PAIR(visu->win_color - 4));
		mvwprintw(visu->menu, 40, 20, "%s",\
			war->players[visu->win].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(visu->win_color - 4));
		mvwprintw(visu->menu, 42, 4,\
			"********* Press q to finish. *********");
		wattroff(visu->menu, A_BOLD);
		wrefresh(visu->menu);
		say_winner(war, visu);
	}
	if (!visu->close)
		while (1)
			if (event_listenner() == 'q')
			{
				system("rm visualizer/assets/winner.mp3");
				break ;
			}
}

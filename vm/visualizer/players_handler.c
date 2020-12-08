/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:00:31 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 18:03:26 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	player1_handler(t_visu *visu, t_corewar *war)
{
	if (war->nbr_fighters >= 1)
	{
		mvwprintw(visu->menu, 20, 4, "Playser -1 : ");
		wattron(visu->menu, COLOR_PAIR(PLAYER1));
		mvwprintw(visu->menu, 20, 17, "%s",\
			war->players[0].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(PLAYER1));
		mvwprintw(visu->menu, 21, 6, "Last live");
		mvwprintw(visu->menu, 21, 30, ": %d      ",\
			war->players[0].last_cycle_to_live);
		mvwprintw(visu->menu, 22, 6, "Lives in current period : %d      ",\
			war->players[0].count_live);
	}
}

void	player2_handler(t_visu *visu, t_corewar *war)
{
	if (war->nbr_fighters >= 2)
	{
		mvwprintw(visu->menu, 24, 4, "Playser -2 : ");
		wattron(visu->menu, COLOR_PAIR(PLAYER2));
		mvwprintw(visu->menu, 24, 17, "%s",\
			war->players[1].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(PLAYER2));
		mvwprintw(visu->menu, 25, 6, "Last live");
		mvwprintw(visu->menu, 25, 30, ": %d       ",\
			war->players[1].last_cycle_to_live);
		mvwprintw(visu->menu, 26, 6, "Lives in current period : %d       ",\
			war->players[1].count_live);
	}
}

void	player3_handler(t_visu *visu, t_corewar *war)
{
	if (war->nbr_fighters >= 3)
	{
		mvwprintw(visu->menu, 28, 4, "Playser -3 : ");
		wattron(visu->menu, COLOR_PAIR(PLAYER3));
		mvwprintw(visu->menu, 28, 17, "%s",\
			war->players[2].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(PLAYER3));
		mvwprintw(visu->menu, 29, 6, "Last live");
		mvwprintw(visu->menu, 29, 30, ": %d       ",\
			war->players[2].last_cycle_to_live);
		mvwprintw(visu->menu, 30, 6, "Lives in current period : %d        ",\
			war->players[2].count_live);
	}
}

void	player4_handler(t_visu *visu, t_corewar *war)
{
	if (war->nbr_fighters == 4)
	{
		mvwprintw(visu->menu, 32, 4, "Playser -4 : ");
		wattron(visu->menu, COLOR_PAIR(PLAYER4));
		mvwprintw(visu->menu, 32, 17, "%s",\
			war->players[3].data_file->prog_name);
		wattroff(visu->menu, COLOR_PAIR(PLAYER4));
		mvwprintw(visu->menu, 33, 6, "Last live");
		mvwprintw(visu->menu, 33, 30, ": %d       ",\
			war->players[3].last_cycle_to_live);
		mvwprintw(visu->menu, 34, 6, "Lives in current period : %d        ",\
			war->players[3].count_live);
	}
}

void	get_winner_color(t_corewar *war, t_visu *visu)
{
	int	last_live;
	int	i;

	i = 0;
	last_live = 0;
	visu->win_color = BORDER_COLOR;
	while (i < 4)
	{
		if (last_live < war->players[i].last_cycle_to_live)
		{
			last_live = war->players[i].last_cycle_to_live;
			visu->win = i;
		}
		visu->win_color = visu->win + 5;
		i++;
	}
	border_maker(visu);
}

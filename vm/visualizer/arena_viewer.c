/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_viewer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:23:19 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 12:42:04 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include <stdio.h>

void	init_struct(t_visu *visu)
{
	dup2(open("/dev/null", O_WRONLY), 2);
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	noecho();
	init_colors();
	visu->arena = subwin(stdscr, 68, 197, 0, 0);
	visu->menu = subwin(stdscr, 68, 55, 0, 196);
	visu->winner = subwin(stdscr, 10, 55, 36, 196);
	visu->pause = 1;
	visu->key = 32;
	visu->win_color = BORDER_COLOR;
	visu->cycle_speed = 100000;
	visu->speed = 50;
}

void	move_process(t_visu *visu, unsigned char *arena, t_process *p)
{
	int	color;

	color = 0;
	while (p)
	{
		if (g_coords[p->pc].id)
			color = g_coords[p->pc].id + 4;
		else
			color = OUT_PROCE;
		wattron(visu->arena, COLOR_PAIR(color));
		print_byte(&arena[p->pc], visu, g_coords[p->pc].y, g_coords[p->pc].x);
		wattroff(visu->arena, COLOR_PAIR(color));
		p = p->next;
	}
}

void	print_arena(t_corewar *war, t_visu *visu, int i, int j)
{
	int	index;
	int	bold;

	bold = 0;
	index = -1;
	while (++index < 4096)
	{
		if (index != 0 && !(index % 64) && (j = 3))
			i += 1;
		g_coords[index].y = i;
		g_coords[index].x = j;
		bold = 0;
		visu->color = 9;
		if (g_coords[index].id)
			visu->color = g_coords[index].id;
		if (g_coords[index].alpha)
			bold = A_BOLD;
		wattron(visu->arena, bold);
		wattron(visu->arena, COLOR_PAIR(visu->color));
		print_byte(&war->arena[index], visu, i, j);
		wattroff(visu->arena, COLOR_PAIR(visu->color));
		wattroff(visu->arena, bold);
		j += 3;
	}
	move_process(visu, war->arena, war->all_process);
}

void	border_maker(t_visu *visu)
{
	wattron(visu->arena, COLOR_PAIR(visu->win_color));
	box(visu->arena, ACS_VLINE, ACS_HLINE);
	wborder(visu->arena, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->arena, COLOR_PAIR(visu->win_color));
	wattron(visu->menu, COLOR_PAIR(visu->win_color));
	box(visu->menu, ACS_VLINE, ACS_HLINE);
	wborder(visu->menu, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->menu, COLOR_PAIR(visu->win_color));
	wattron(visu->winner, COLOR_PAIR(visu->win_color));
	box(visu->winner, ACS_VLINE, ACS_HLINE);
	wborder(visu->winner, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wattroff(visu->winner, COLOR_PAIR(visu->win_color));
}

void	board(t_corewar *war, t_visu *visu)
{
	if (!visu || !war)
		return ;
	get_winner_color(war, visu);
	print_arena(war, visu, 2, 3);
	wrefresh(visu->arena);
	menu_handler(war, visu);
	pause_handler(visu);
	event_handler(visu);
	usleep(visu->cycle_speed);
}

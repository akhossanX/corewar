/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_viewer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 11:22:18 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 18:02:33 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void		pause_handler(t_visu *visu)
{
	wattron(visu->menu, A_BOLD);
	if (visu->pause == 1)
	{
		mvwprintw(visu->menu, 2, 4, "*** PAUSED ***");
		wrefresh(visu->menu);
		while (1)
		{
			visu->key = event_listenner();
			if (visu->key == 's')
				break ;
			if (visu->key == 'q' && (visu->close = 1))
				break ;
			if (visu->key == 32 || visu->close == 1 || visu->key == 's')
			{
				visu->pause = 0;
				break ;
			}
		}
		mvwprintw(visu->menu, 2, 4, "*** RUNNING ***");
	}
	wattroff(visu->menu, A_BOLD);
}

void		speed_handler(t_visu *visu)
{
	if (!visu)
		return ;
	if (visu->key == 43 && visu->speed == 100)
		system("afplay vm/visualizer/assets/bip.mp3 &");
	else if (visu->key == 45 && visu->speed == 0)
		system("afplay vm/visualizer/assets/bip.mp3 &");
	if (visu->key == 43 && visu->cycle_speed > 0 && visu->speed < 100)
	{
		visu->cycle_speed -= 20000;
		visu->speed += 10;
	}
	else if (visu->key == 45 &&\
		visu->cycle_speed < 5000000 && visu->speed > 0)
	{
		visu->cycle_speed += 20000;
		visu->speed -= 10;
	}
}

void		event_handler(t_visu *visu)
{
	if (visu && (visu->key = event_listenner()) > 0)
	{
		if (visu->key == 32 && (visu->pause = 1))
		{
			nodelay(stdscr, TRUE);
			pause_handler(visu);
		}
		else if (visu->key == 'q')
			visu->close = 1;
		else if (visu->key == 43 || visu->key == 45)
			speed_handler(visu);
		else if (visu->key == 's' && (visu->step = 1))
			visu->pause = 1;
	}
}

static void	print_menu(t_visu *visu)
{
	mvwprintw(visu->menu, 46, 19, "EVENT's MENU");
	mvwprintw(visu->menu, 48, 4, "PLAY/PAUSE   : SPACE");
	mvwprintw(visu->menu, 50, 4, "SPEED        : +/-");
	mvwprintw(visu->menu, 52, 4, "STEP BY STEP : s");
	mvwprintw(visu->menu, 54, 4, "QUIT         : q");
	mvwprintw(visu->menu, 58, 1,\
	"------------------------ aff ------------------------");
}

void		menu_handler(t_corewar *war, t_visu *visu)
{
	wattron(visu->menu, A_BOLD);
	mvwprintw(visu->menu, 4, 4, "Cycles/second limit : ");
	mvwprintw(visu->menu, 4, 26, "%d  ", visu->speed);
	mvwprintw(visu->menu, 7, 4, "Cycle : %d", war->cycle);
	mvwprintw(visu->menu, 9, 4, "Processes : %d    ", war->nbr_process);
	mvwprintw(visu->menu, 11, 4, "CYCLE_TO_DIE : %d       ", war->cycle_to_die);
	mvwprintw(visu->menu, 13, 4, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(visu->menu, 15, 4, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(visu->menu, 17, 4, "MAX_CHECKS : %d", MAX_CHECKS);
	player1_handler(visu, war);
	player2_handler(visu, war);
	player3_handler(visu, war);
	player4_handler(visu, war);
	mvwprintw(visu->menu, 37, 18, "THE WINNER's BOX");
	mvwprintw(visu->menu, 40, 4, "The winner is: ");
	print_menu(visu);
	wattroff(visu->menu, A_BOLD);
	wrefresh(visu->menu);
}

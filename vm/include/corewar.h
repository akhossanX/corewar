/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/30 17:18:03 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"
# include <unistd.h>
# include "../libft/libft.h"
# include <errno.h>
# include "../include/visualizer.h"
# include <fcntl.h>

extern	t_op			g_op_tab[17];

typedef	struct			s_process
{
	struct s_process	*next;
	uint32_t			regster[16];
	int					pc;
	int					carry;
	int					id;
	int					cycle_create;
	int					erorr;
	int					size_of_flg;
	int					is_live_more;
	int					cycle_count;
}						t_process;

typedef	struct			s_player
{
	size_t				size_prog;
	t_header			*data_file;
	char				*name;
	char				*comment;
	int					starting_point;
	int					count_live;
	int					id;
	int					value_reg;
	int					status_reg;
	int					last_cycle_to_live;
}						t_player;

typedef	struct			s_corewar
{
	t_process			*last_process;
	t_process			*all_process;
	t_player			players[4];
	uint8_t				*arena;
	int					value_reg;
	int					status_reg;
	int					cycle;
	int					combat;
	int					cycle_to_die;
	int					nbr_live;
	int					dump;
	int					v;
	int					a;
	int					nbr_checks;
	int					nbr_process;
	int					nbr_fighters;
	int					cycle_last_check;
}						t_corewar;

t_header				*ft_cin_file(char *file);
char					*addr_to_hex(void *addr, size_t size);
uint32_t				cpy_arena_to_var(t_process *p,
int size, int cursor0, int opcode);
uint32_t				return_data_of_arg(t_process *proc,
uint8_t flg, int opcode, int cursor0);
uint32_t				binary_rev(uint32_t s);
uint8_t					*ft_get_arena(void);
t_corewar				*get_corewar(t_corewar *lst);
t_visu					*get_visu(t_visu *visu);
void					task_die_cursor(t_process **list_process,
t_process *tmp, t_process **head);
t_process				*die_cursor(t_corewar *war,
t_process *list_process);
void					ft_init_process(t_corewar *war);
void					ft_print_arena();
void					cpy_reg_to_arena(t_process *p,
int cursor0, int size, int reg);
void					ft_loop(void);
void					ft_exec(t_process *p, t_corewar *war);
void					print_game(void);
void					print_byt(const void *addr);
void					print_index_hex(const void *addr);
void					print_winer(void);
void					free_corewar(t_corewar *war);
void					cpy_reg_to_arena(t_process *p,
int cursor0, int size, int reg);
void					cpy_arena_to_reg(t_process *p,
int cursor0, int size, int reg);

int						read_regster(t_process *proc);
int						ft_sign(uint32_t s, int size);
int						hex(char *value);
int						hextodecimal(char val);
int						hextodecimal(char val);
int						is_id_integer(char *arg);
int						ft_live(t_process *p);
int						ft_ld(t_process *p);
int						ft_st(t_process *p);
int						ft_add(t_process *p);
int						ft_sub(t_process *p);
int						ft_and(t_process *p);
int						ft_or(t_process *p);
int						ft_xor(t_process *p);
int						ft_zjmp(t_process *p);
int						ft_ldi(t_process *p);
int						ft_sti(t_process *p);
int						ft_fork(t_process *p);
int						ft_lld(t_process *p);
int						ft_lfork(t_process *p);
int						ft_aff(t_process *p);
int						ft_lldi(t_process *p);
int						get_size_arg(uint8_t flg,
int nb_arg, int opcode, int *err);
int						get_size_beyt_flag(t_process *p,
uint8_t flg, int opcode);
int						overrided_pos(int pos, int cur0);
int						read_regster(t_process *proc);

int						parsing(t_corewar *war, int argc, char **argv);
int						get_id_player(int id, int flg);
int						is_int(t_corewar *war, char *arg);
int						get_id(char **argv);
int						is_intger(char *arg);
int						exit_error(char *message_error);
int						get_winner(t_corewar *war);
int						event_listenner(void);

void					inedx_color(int id, int start, int end, int alpha);
void					board(t_corewar *war, t_visu *visu);
void					menu_handler(t_corewar *war, t_visu *visu);
void					event_handler(t_visu *visu);
void					border_maker(t_visu *visu);
void					init_struct(t_visu *visu);
void					pause_handler(t_visu *visu);

void					print_winner(t_corewar *war, t_visu *visu);
void					get_winner_color(t_corewar *war, t_visu *visu);
void					print_byte(const void *addr,
t_visu *visu, int i, int j);
void					print_reg_in_arena(int cursor0, int size);
void					print_arena(t_corewar *war, t_visu *visu, int i, int j);
void					init_colors();

void					player1_handler(t_visu *visu, t_corewar *war);
void					player2_handler(t_visu *visu, t_corewar *war);
void					player3_handler(t_visu *visu, t_corewar *war);
void					player4_handler(t_visu *visu, t_corewar *war);

#endif

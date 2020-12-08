# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 18:43:13 by yelazrak          #+#    #+#              #
#    Updated: 2020/12/01 11:36:20 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../corewar

VM_SRCS =   main.c \
			calcul.c \
			arena.c \
			init.c \
			read_file.c \
			exec.c \
			tool.c \
			tool_flg.c \
			op.c \
			info_player.c \
			flags.c \
			tool_arena.c

INS_SRCS = 	ld.c \
		  	st.c \
		  	ldi.c \
		  	and.c \
		  	sti.c\
		  	live.c\
		  	add.c \
		  	aff.c \
		  	fork.c  \
		  	lfork.c \
		  	lld.c  \
		  	lldi.c\
		  	or.c \
		  	sub.c \
		  	xor.c \
		  	zjmp.c

VIS_SRCS  = arena_viewer.c \
			menu_viewer.c \
			tools.c \
			players_handler.c \

VIS_DIR = visualizer/
VM_DIR = virtual_machine/
INS_DIR = instructions/

OBJDIR = objs/

VM_OBJS = $(addprefix $(OBJDIR), $(VM_SRCS:.c=.o))
INS_OBJS = $(addprefix $(OBJDIR), $(INS_SRCS:.c=.o))
VIS_OBJS = $(addprefix $(OBJDIR), $(VIS_SRCS:.c=.o))

OBJS = $(VM_OBJS) $(INS_OBJS) $(VIS_OBJS)

LIBFT = libft/libft.a
	
INCLUDES = ./include/

HEADERS =  include/op.h include/corewar.h include/visualizer.h

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: libft_ $(OBJDIR) $(NAME)

libft_: $(LIBFT)

$(LIBFT):
	@make -C libft

$(OJBS): $(VM_OBJS) $(INS_OBJS) $(VIS_OBJS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $^ -lncurses -L./libft -lft -o $@ 

$(VM_OBJS): $(OBJDIR)%.o: $(VM_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -I $(INCLUDES) $< -o $@

$(VIS_OBJS): $(OBJDIR)%.o: $(VIS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -I $(INCLUDES) $< -o $@

$(INS_OBJS): $(OBJDIR)%.o: $(INS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c -I $(INCLUDES) $< -o $@

$(OBJDIR):
	@mkdir -p $@

install:
	@pip3 install gtts

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

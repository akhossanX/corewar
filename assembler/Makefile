# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhossan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 16:50:17 by akhossan          #+#    #+#              #
#    Updated: 2020/12/01 11:39:56 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../asm

CC		=	gcc

SRC		=	asm_assemble.c\
			asm_code.c\
			asm_display.c\
			asm_error.c\
			asm_free.c\
			asm_getparam.c\
			asm_header.c\
			asm_init.c\
			asm_label.c\
			asm_op.c\
			asm_parse.c\
			asm_read.c\
			asm_symbol_table.c\
			asm_tokenize.c\
			asm_tokens1.c\
			asm_tokens2.c\
			asm_tokens3.c\
			asm_type.c\
			asm_utils.c\
			asm_disassemble.c\
			disasm_free.c\
			disasm_parse.c\
			disasm_statement.c\
			disasm_utils.c\
			main.c

SRCDIR = src/

OBJDIR = objs/

CFLAGS	=	-Werror -Wall -Wextra

LIBS	=	-lft -L./libs/libft

INC		=	-I./includes

HFILES	=	assembler.h disassembler.h libft.h

HEADERS	=	$(addprefix ./includes/, $(HFILES))

LIBFT = ./libs/libft/libft.a

OBJS	=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR):
	@mkdir -p $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INC) $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBS) -o $@	

$(LIBFT):
	@make -C libs/libft

clean:
	@make clean -C libs/libft
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@make fclean -C libs/libft
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re


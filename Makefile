# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 13:22:29 by yelazrak          #+#    #+#              #
#    Updated: 2020/11/30 17:09:54 by akhossan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm vm

ASSEMBLER_DIR = assembler
VM_DIR = vm

all: $(NAME)

asm: 
	@make -C $(ASSEMBLER_DIR)

vm: 
	@make -C $(VM_DIR)

clean: 
	@make clean -C $(ASSEMBLER_DIR)
	@make clean -C $(VM_DIR)

fclean:
	@make fclean -C $(ASSEMBLER_DIR)
	@make fclean -C $(VM_DIR)

re:
	@make -C $(ASSEMBLER_DIR) re
	@make -C $(VM_DIR) re

.PHONY: re all asm vm clean fclean

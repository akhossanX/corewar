# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 11:31:32 by yelazrak          #+#    #+#              #
#    Updated: 2020/11/30 14:12:12 by yelazrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	ft_atoi.c\
		ft_bzero.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_lstadd.c\
		ft_lstdel.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_memalloc.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memdel.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putnbr.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_putstr.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strclr.c\
		ft_strcmp.c\
		ft_strcpy.c\
		ft_strdel.c\
		ft_strdup.c\
		ft_strequ.c\
		ft_striter.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strnequ.c\
		ft_strnew.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strsplit.c\
		ft_strstr.c\
		ft_strsub.c\
		ft_strtrim.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_lstsearch.c\
		ft_lstcount.c\
		ft_spacetab.c\
		ft_tabfree.c\
		ft_tab1.c\
		get_next_line.c\
		ft_safe.c \
		ft_strnew_00.c \
		ft_strjoin_free.c\
		ft_strjoin_00.c\
		ft_float.c \
		ft_float2.c \
		ft_get_flag.c \
		ft_operation.c \
		ft_padding.c  \
		ft_print_base.c \
		ft_print_char.c \
		ft_print_d.c\
		ft_print_f.c\
		ft_printf.c \
		helper.c\
		ft_str_toupper.c\
		ft_str_nbr.c\
		ft_itoa_base.c\
		ft_char_nbr.c\
		ft_abs.c\
		ft_nstrjoin.c

OBJS = $(SRCS:.c=.o)

INCLUDES = .

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)   $(INCLUDE)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJS): %.o : %.c $(INCLUDES)/libft.h
	gcc -c $(FLAGS) $< -o $@ -I $(INCLUDES)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

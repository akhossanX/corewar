/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:59:08 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 11:11:03 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include <limits.h>
# include <float.h>
# include <math.h>
# include <stdio.h>

# define ZERO 1
# define HASH 2
# define SPACE 4
# define PLUS 8
# define MINUS 16
# define LONG 32
# define LL 64
# define H 128
# define HH 256
# define L_D 512

typedef struct			s_init
{
	short				flag;
	char				specifier;
	int					precision;
	int					width;
}						t_init;

typedef struct			s_var
{
	int					s_a;
	int					s_b;
	int					i;
	int					k;
	int					rest;
	int					len;
	int					csnt;
	char				*result;
	char				*str;
	char				*tmp;
	char				*tmp_2;
	char				aa;
	char				bb;
}						t_var;

typedef struct			s_data
{
	unsigned long long	mantissa :	63;
	unsigned long long	as :		1;
	long long			exp :		15;
	unsigned long long	sign :		1;
}						t_data;

typedef union			u_float
{
	long double			f;
	t_data				list;
}						t_float;

int						ft_print_d(va_list list, t_init *lst);
int						ft_print_base(va_list list, t_init *lst);
int						ft_print_s(va_list list, t_init *lst);
int						ft_print_c(va_list list, t_init *lst);
int						ft_print_f(va_list list, t_init *lst);
int						ft_print_persent(t_init *lst);
void					ft_init(t_init *lst);

char					*ft_sum(char *a, char *b);
char					*ft_produit(char *a, char *b);
char					*ft_power(char *str, long n);
char					*ft_putstr_float(char *src, char *dst, char *tmp,
						t_init *lst);
char					*ft_check(t_init *lst, char *str, char **tmp);
char					*ft_strjoin_00(char *dst, int i);

char					*ft_exponent(t_data *lst, int prs, t_init *list);
char					*ft_rounding(char *srcs, char *dst, t_init *lst,
						int prs);

int						ft_printf(const char *format, ...);
int						ft_print_format(va_list list, const char *format,
						t_init *f);
char					*ft_push_c(char *str, int i, char *c, int ps);

char					*ft_manage_width(t_init *lst, char *str);
int						ft_get_flag_of_format(t_init *lst, const char *format);
int						ft_char_nbr(char c);
int						ft_str_nbr(char *str);
char					ft_itoc(int c);
int						ft_ctoi(char c);

#endif

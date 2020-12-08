/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 09:18:54 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/30 11:10:08 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_sum(char *a, char *b)
{
	t_var	var;
	int		i;

	i = -1;
	var.rest = 0;
	var.s_a = ft_strlen(a) - 1;
	var.s_b = ft_strlen(b) - 1;
	var.len = (var.s_a > var.s_b) ? var.s_a + 1 : var.s_b + 1;
	var.result = ft_strnew_00(var.len + 1);
	var.csnt = var.len;
	while (++i < var.csnt)
	{
		var.aa = (-1 < var.s_a) ? a[var.s_a--] : '0';
		var.bb = (-1 < var.s_b) ? b[var.s_b--] : '0';
		var.result[var.len] = ft_itoc(((ft_ctoi(var.aa) +\
		ft_ctoi(var.bb) + var.rest) % 10));
		var.len--;
		var.rest = (ft_ctoi(var.aa) + ft_ctoi(var.bb) + var.rest) / 10;
	}
	var.result[var.len] = ft_itoc(var.rest);
	var.tmp = var.result;
	if (*(var.result) == '0')
		(var.result)++;
	var.result = ft_safe(var.tmp, ft_strdup(var.result));
	return (var.result);
}

static void		ft_produit_helper(t_var *lst, char *a, char *b)
{
	t_var	*var;

	var = lst;
	var->s_a = ft_strlen(a);
	var->s_b = ft_strlen(b);
	var->len = var->s_a + var->s_b;
	var->result = ft_strnew_00(var->len);
}

char			*ft_produit(char *a, char *b)
{
	t_var	var;
	int		prd;

	ft_produit_helper(&var, a, b);
	while (--var.s_b >= 0)
	{
		var.i = var.s_a;
		var.k = --var.len;
		var.rest = 0;
		while (--var.i >= 0)
		{
			var.aa = var.result[var.k];
			prd = ft_ctoi(b[var.s_b]) * ft_ctoi(a[var.i]);
			var.result[var.k] = ft_itoc((prd +\
			ft_ctoi(var.result[var.k]) + var.rest) % 10);
			var.rest = (prd + ft_ctoi(var.aa) + var.rest) / 10;
			var.k--;
		}
		var.result[var.k] = ft_itoc(var.rest);
	}
	var.tmp = var.result;
	while (*(var.result) == '0' && *(var.result + 1) != '\0')
		(var.result)++;
	var.result = ft_safe(var.tmp, ft_strdup(var.result));
	return (var.result);
}

char			*ft_power(char *str, long n)
{
	char	*dst;
	char	*tmp;

	tmp = NULL;
	if (n == 0)
		return (ft_strdup("1"));
	dst = ft_strdup(str);
	while (--n > 0)
	{
		tmp = dst;
		dst = ft_produit(dst, str);
		ft_strdel(&tmp);
	}
	return (dst);
}

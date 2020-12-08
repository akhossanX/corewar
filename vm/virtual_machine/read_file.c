/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/30 17:18:15 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_header			*ft_free_head(t_header **new, char *message)
{
	ft_memdel((void **)new);
	exit_error(message);
	return (NULL);
}

t_header			*ft_valid_file(t_header *new, int fd)
{
	unsigned int	data;
	int				s;

	data = 0;
	if (!new)
		return (NULL);
	if ((s = read(fd, (void *)&data, 4)) != 4 || (int)data != 0)
		return (ft_free_head(&new, "Champion name not preceded by null bytes"));
	if ((s = read(fd, (void *)&new->prog_size, 4)) != 4)
		return (ft_free_head(&new, "size programme"));
	if ((s = read(fd, (void *)new->comment,
				COMMENT_LENGTH)) != COMMENT_LENGTH)
		return (ft_free_head(&new, "not valid COMMENT_LENGTH"));
	if ((s = read(fd, (void *)&data, 4)) != 4 || (int)data != 0)
		return (ft_free_head(&new, "Comment not preceded by null bytes"));
	if ((s = read(fd, (void *)new->champ,
				CHAMP_MAX_SIZE)) != ft_sign(new->prog_size, 4))
		return (ft_free_head(&new, " size champ > CHAMP_MAX_SIZE"));
	return (new);
}

t_header			*ft_cin_file(char *file)
{
	t_header		*new;
	unsigned int	data;
	int				fd;
	int				s;

	data = 0;
	if (!(new = (t_header *)malloc(sizeof(t_header))))
		return (NULL);
	ft_memset((void *)new, 0, sizeof(t_header));
	errno = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_free_head(&new, strerror(errno)));
	if ((s = read(fd, (void *)&new->magic, 4)) != 4 ||
		(int)new->magic != -209458688)
		return (ft_free_head(&new, "not valid header magic"));
	if ((s = read(fd, (void *)new->prog_name,
				(PROG_NAME_LENGTH))) != (PROG_NAME_LENGTH))
		return (ft_free_head(&new, "not valid PROG_NAME_LENGTH"));
	return (ft_valid_file(new, fd));
}

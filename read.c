/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:56:37 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/15 12:38:28 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		error(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	return (0);
}

int		read_rt(t_data *data, char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (error("Can not open file"));
	


	close(fd);
	return (1);
}
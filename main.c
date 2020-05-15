/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:05:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/15 12:12:40 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		main(int argc, char **argv)
{
	t_data data;

	if (argc == 2)
	{
		if (!(read_rt(&data, argv[1])))
			return (0);

	}
	else
		ft_printf("usage: %s [file]\n", argv[0]);
	return (0);
}
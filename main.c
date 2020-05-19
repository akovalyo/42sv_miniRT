/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:05:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/18 17:15:42 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void init_data(t_scene *scn)
{
	scn->res.processed = 0;
}

int		start_wind(t_scene *scn)
{
	scn->mlx = mlx_init();
	scn->img = mlx_new_image(scn->mlx, scn->res.x, scn->res.y);
	scn->img_addr = mlx_get_data_addr(scn->img, &(scn->bits_per_pixel),
					&(scn->line_length), &(scn->endian));
	scn->win = mlx_new_window(scn->mlx, scn->res.x, scn->res.y, "miniRT");
	
}

int close_win(int key, t_scene *scn)
{
    ft_printf("%d\n", key);
    if (key == 65307)
	{
		
        mlx_destroy_window(scn->mlx, scn->win);
		exit(EXIT_SUCCESS);
	}
    return (0);
}

int		main(int argc, char **argv)
{
	t_scene scn;

	init_data(&scn);
	if (argc == 2)
	{
		if (read_rt(&scn, argv[1]) == -1)
			return (-1);
		start_wind(&scn);
		mlx_hook(scn.win, 2, 1L<<0, close_win, &scn);
		mlx_loop(scn.mlx);
	}
	else
		ft_printf("usage: %s [file]\n", argv[0]);
	return (0);
}
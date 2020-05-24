/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:05:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/24 12:29:18 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void init_data(t_scene *scn)
{
	scn->res.processed = 0;
	scn->amb.processed = 0;
	scn->cams = NULL;
	scn->cam_count = 0;
	scn->light_count = 0;
	scn->lights = NULL;
	scn->pl_count = 0;
	scn->shapes = NULL;
}

int		start_wind(t_scene *scn)
{
	int	x;
	int y;

	y = scn->res.y + 1;
	scn->mlx = mlx_init();
	if (!(scn->img = mlx_new_image(scn->mlx, scn->res.x, scn->res.y)))
		error("Cannot create image");
	scn->img_addr = mlx_get_data_addr(scn->img, &(scn->bits_per_pixel),
					&(scn->line_length), &(scn->endian));
	scn->win = mlx_new_window(scn->mlx, scn->res.x, scn->res.y, "miniRT");
	scn->curr_cam = scn->cams->prev;
	
	

	return (0);
}

int close_win(int key, t_scene *scn)
{
    if (key == ESCAPE)
	{
        mlx_destroy_window(scn->mlx, scn->win);
		exit(EXIT_SUCCESS);
	}
    return (0);
}

void test_cam(t_scene *scn)
{

	printf("CAM NUM: %d\n", scn->curr_cam->cam_num);
	printf("CAM FOV: %f\n", scn->curr_cam->fov);
	printf("CAM POS x: %f, y: %f, z: %f\n", scn->curr_cam->pos.x, scn->curr_cam->pos.y, scn->curr_cam->pos.z);
	printf("CAM OR x: %f, y: %f, z: %f\n", scn->curr_cam->orient.x, scn->curr_cam->orient.y, scn->curr_cam->orient.z);
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

		test_cam(&scn);

		mlx_loop(scn.mlx);
		mlx_destroy_window(scn.mlx, scn.win);
	}
	else
		ft_printf("usage: %s [file]\n", argv[0]);
	return (0);
}
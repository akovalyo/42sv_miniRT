/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:05:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/05 22:07:50 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		intersections(t_shape *shape, t_cam cam, double *dist)
{
	double		tmp;
	int			index;
	int			pos;
	static int	(*inters_f[])(t_shape*, t_cam, double*) = {inters_pl,
		inters_sp, inters_sq, inters_cy, inters_tr};

	pos = -1;
	index = 0;
	tmp = *dist;
	while (shape)
	{
		if ((*inters_f[shape->type])(shape, cam, &tmp))
			pos = index;
		index++;
		shape = (t_shape *)shape->next;
	}
	*dist = tmp;
	return (pos);
}

void	reflect(t_scene scn, t_shape *shape, t_color *color, double dist)
{
	set_reflamb(&scn, shape);
	color->r += scn.refl.amb.r;
	color->g += scn.refl.amb.g;
	color->b += scn.refl.amb.b;
	while (scn.lights)
	{
		refl_shape(scn, shape, dist);
		set_diff(&scn, shape);
		set_spec(&scn);
		if (!shadow(scn, shape))
		{
			color->r += scn.refl.s.r + scn.refl.d.r;
			color->g += scn.refl.s.g + scn.refl.d.g;
			color->b += scn.refl.s.b + scn.refl.d.b;
		}
		scn.lights = scn.lights->next;
	}
}

void	render(t_scene scn, t_cam cam, t_color *color)
{
	int			pos;
	double		dist;
	t_shape		*shape;

	*color = (t_color){0, 0, 0, 0};
	dist = 1000;
	if ((pos = intersections(scn.shapes, cam, &dist)) >= 0)
	{
		shape = scn.shapes;
		while (pos--)
			shape = (t_shape *)shape->next;
		reflect(scn, shape, color, dist);
	}
}

void	render_main(t_scene *scn)
{
	int		y;
	int		x;
	t_color color;
	int		*img;

	y = scn->res.y + 1;
	init_img(scn);
	init_cam(*scn, scn->curr_cam);
	img = scn->img;
	while (--y > 0)
	{
		x = -1;
		while (++x < scn->res.x)
		{
			scn->curr_cam->view_ray = get_ray(scn, x, y);
			render(*scn, *(scn)->curr_cam, &color);
			*img = create_trgb(color);
			img++;
		}
	}
	if (scn->save == 1)
		save_bmp(scn);
	else
		mlx_put_image_to_window(scn->mlx, scn->win, scn->img_ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_scene scn;

	init_data(&scn);
	if (argc >= 2 && argc <= 4)
	{
		if ((argc == 3 || argc == 4) && ft_strncmp(argv[2], "--save", 7) == 0)
		{
			if (argc == 4)
				scn.img_name = argv[3];
			scn.save = 1;
		}
		read_rt(&scn, argv[1]);
		start_wind(&scn);
		render_main(&scn);
		mlx_hook(scn.win, 17, 131072, close_program, 0);
		mlx_hook(scn.win, 2, 1, key_hooks, &scn);
		mlx_loop(scn.mlx);
	}
	else
		ft_printf("usage: %s FILE.RT [--save] [name]\n", argv[0]);
	return (0);
}

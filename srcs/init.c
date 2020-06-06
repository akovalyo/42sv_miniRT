/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 08:52:03 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:22:07 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_data(t_scene *scn)
{
	scn->res.processed = 0;
	scn->refl.processed = 0;
	scn->cams = NULL;
	scn->cam_count = 0;
	scn->light_count = 0;
	scn->lights = NULL;
	scn->pl_count = 0;
	scn->shapes = NULL;
	scn->sp_count = 0;
	scn->sq_count = 0;
	scn->cy_count = 0;
	scn->tr_count = 0;
	scn->save = 0;
	scn->img_name = NULL;
	scn->save = 0;
}

void	init_img(t_scene *scn)
{
	if (!(scn->img_ptr = mlx_new_image(scn->mlx, scn->res.x, scn->res.y)))
		close_minirt("Cannot create image", scn);
	scn->img = (int *)mlx_get_data_addr(scn->img_ptr, &(scn->bits_per_pixel),
					&(scn->line_length), &(scn->endian));
}

void	init_cam(t_scene scn, t_cam *cam)
{
	t_vect	middle;
	t_vect	view_ray;
	double	width_unit;
	double	height_unit;
	t_vect	bot_left;

	cam->res_x = scn.res.x;
	cam->res_y = scn.res.y;
	middle = v_add(cam->pos, cam->orient);
	view_ray = v_sub(middle, cam->pos);
	cam->right = v_norm(cross_prod(new_vect(0, 1, 0), view_ray));
	cam->up = v_norm(cross_prod(view_ray, cam->right));
	width_unit = tan(deg_to_rad(cam->fov) / 2);
	height_unit = ((double)cam->res_y / cam->res_x) * width_unit;
	bot_left = v_add(middle, v_mult(cam->up, -height_unit));
	bot_left = v_add(bot_left, v_mult(cam->right, -width_unit));
	cam->inc_x = v_div(v_mult(cam->right, 2 * width_unit)
	, cam->res_x);
	cam->inc_y = v_div(v_mult(cam->up, 2 * height_unit)
	, cam->res_y);
	cam->bot = bot_left;
}

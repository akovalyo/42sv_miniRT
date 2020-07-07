/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 16:06:35 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/07 16:10:47 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	close_minirt(char *message, t_scene *scn)
{
	if (message)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", message);
	}
	if (scn->gnl > 0)
		free(scn->line);
	ft_printf("Closing minirt...\n");
	free_scene(scn);
	ft_printf("Minirt is closed\n");
	exit(0);
}

double	norm_color(double col)
{
	if (col > 1)
		return (1);
	else if (col < 0)
		return (0);
	else
		return (col);
}

int		cy_activate(t_shape *sh, t_cam cam, t_intercy *cy)
{
	t_vect v_cam;

	cy->dist_a = INFINITY;
	cy->dist_b = INFINITY;
	v_cam = v_sub(cam.pos, sh->pos);
	sh->cy_a = v_prod(cam.view_ray, cam.view_ray) -
		(v_prod(cam.view_ray, sh->orient) * v_prod(cam.view_ray, sh->orient));
	sh->cy_b = (v_prod(cam.view_ray, v_cam) - (v_prod(cam.view_ray,
		sh->orient) * v_prod(v_cam, sh->orient))) * 2;
	sh->cy_c = v_prod(v_cam, v_cam) - (v_prod(v_cam, sh->orient) *
		v_prod(v_cam, sh->orient)) - ((sh->d / 2) * (sh->d / 2));
	sh->delta = (sh->cy_b * sh->cy_b) - (4 * sh->cy_a * sh->cy_c);
	sh->delta = sqrt(sh->delta);
	if (sh->delta > 0)
		return (1);
	return (0);
}

void	tr_vectors(t_intertr *tr, t_shape *sh, t_cam cam)
{
	tr->v_a = v_sub(sh->pos_2, sh->pos);
	tr->v_b = v_sub(sh->pos_3, sh->pos);
	tr->rb_cross = cross_prod(cam.view_ray, tr->v_b);
	tr->crosspnt = v_prod(tr->v_a, tr->rb_cross);
	tr->point = 1;
	if (tr->crosspnt > -INFINITY && tr->crosspnt < 0.0001)
		tr->point = 0;
}

int		close_program(void *prm)
{
	prm = (void *)prm;
	exit(0);
	return (0);
}

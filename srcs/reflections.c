/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:44:47 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:45:07 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	refl_pl(t_scene scn, t_shape *sh, double dist)
{
	int	side;

	side = v_prod(sh->orient_n, v_norm(scn.curr_cam->view_ray)) > 0 ? -1 : 1;
	scn.curr_cam->p_inter = v_add(scn.curr_cam->pos,
		v_mult(scn.curr_cam->view_ray, dist));
	scn.lights->vec = v_norm(v_sub(scn.lights->pos, scn.curr_cam->p_inter));
	sh->orient_n = v_mult(sh->orient_n, side);
	scn.lights->refl = v_norm(v_refl(v_mult(scn.lights->vec, -1),
		v_norm(sh->orient_n)));
}

void	refl_sp(t_scene scn, t_shape *sh, double dist)
{
	int	side;

	scn.curr_cam->p_inter = v_add(scn.curr_cam->pos,
		v_mult(scn.curr_cam->view_ray, dist));
	scn.lights->vec = v_norm(v_sub(scn.lights->pos, scn.curr_cam->p_inter));
	sh->orient_n = v_norm(v_sub(scn.curr_cam->p_inter, sh->pos));
	side = v_prod(sh->orient_n, v_norm(scn.curr_cam->view_ray)) > 0 ? -1 : 1;
	sh->orient_n = v_mult(sh->orient_n, side);
	scn.lights->refl = v_norm(v_refl(v_mult(scn.lights->vec, -1),
		sh->orient_n));
}

void	refl_cy(t_scene scn, t_shape *sh, double dist)
{
	int		side;
	double	cy;

	cy = (v_prod(scn.curr_cam->view_ray, sh->orient) * dist) +
		v_prod(v_sub(scn.curr_cam->pos, sh->pos), sh->orient);
	scn.curr_cam->p_inter = v_add(scn.curr_cam->pos,
		v_mult(scn.curr_cam->view_ray, dist));
	scn.lights->vec = v_norm(v_sub(scn.lights->pos, scn.curr_cam->p_inter));
	sh->orient_n = v_norm(v_sub(scn.curr_cam->p_inter,
		v_add(sh->pos, v_mult(sh->orient, cy))));
	side = v_prod(sh->orient_n, v_norm(scn.curr_cam->view_ray)) > 0 ? -1 : 1;
	sh->orient_n = v_norm(v_mult(sh->orient_n, side));
	scn.lights->refl = v_norm(v_refl(v_mult(scn.lights->vec, -1),
		sh->orient_n));
}

void	refl_tr(t_scene scn, t_shape *sh, double dist)
{
	int		side;
	t_vect	v_1;
	t_vect	v_2;

	v_1 = v_sub(sh->pos_2, sh->pos);
	v_2 = v_sub(sh->pos_3, sh->pos);
	scn.curr_cam->p_inter = v_add(scn.curr_cam->pos,
		v_mult(scn.curr_cam->view_ray, dist));
	scn.lights->vec = v_norm(v_sub(scn.lights->pos, scn.curr_cam->p_inter));
	sh->orient_n = v_norm(v_sub(scn.curr_cam->p_inter, sh->pos));
	sh->orient_n = v_norm(cross_prod(v_2, v_1));
	side = v_prod(sh->orient_n, v_norm(scn.curr_cam->view_ray)) > 0 ? -1 : 1;
	sh->orient_n = v_norm(v_mult(sh->orient_n, side));
	scn.lights->refl = v_norm(v_refl(v_mult(scn.lights->vec, -1),
		sh->orient_n));
}

void	refl_shape(t_scene scn, t_shape *sh, double dist)
{
	if (sh->type == PLANE || sh->type == SQUARE)
		refl_pl(scn, sh, dist);
	else if (sh->type == SPHERE)
		refl_sp(scn, sh, dist);
	else if (sh->type == CYL)
		refl_cy(scn, sh, dist);
	else if (sh->type == TRNG)
		refl_tr(scn, sh, dist);
}

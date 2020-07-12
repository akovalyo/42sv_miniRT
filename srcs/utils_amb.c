/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:25:50 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/12 14:30:54 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_reflamb(t_scene *scn, t_shape *sh)
{
	double coeff;

	scn->refl.amb = (t_color){0, 0, 0, 0};
	coeff = scn->refl.coeff;
	scn->refl.amb.t = 0;
	scn->refl.amb.r = coeff * (scn->refl.amb_col.r / 255) *
		(sh->rgb.r / 255);
	scn->refl.amb.g = coeff * (scn->refl.amb_col.g / 255) *
		(sh->rgb.g / 255);
	scn->refl.amb.b = coeff * (scn->refl.amb_col.b / 255) *
		(sh->rgb.b / 255);
}

void	set_diff(t_scene *scn, t_shape *sh)
{
	double	dot;

	scn->refl.d = (t_color){0, 0, 0, 0};
	dot = v_prod(scn->lights->vec, sh->orient_n);
	dot = dot < 0 ? 0 : dot;
	scn->refl.d.r = scn->lights->ratio * (sh->rgb.r / 255) *
		(scn->lights->rgb.r / 255) * dot;
	scn->refl.d.g = scn->lights->ratio * (sh->rgb.g / 255) *
		(scn->lights->rgb.g / 255) * dot;
	scn->refl.d.b = scn->lights->ratio * (sh->rgb.b / 255) *
		(scn->lights->rgb.b / 255) * dot;
}

void	set_spec(t_scene *scn)
{
	double	factor;

	scn->refl.s = (t_color){0, 0, 0, 0};
	factor = pow(fmax(v_prod(scn->lights->refl,
		v_mult(scn->curr_cam->view_ray, -1)), 0.0), 60);
	scn->refl.s.r = scn->lights->ratio * (scn->lights->rgb.r / 255) * factor;
	scn->refl.s.g = scn->lights->ratio * (scn->lights->rgb.g / 255) * factor;
	scn->refl.s.b = scn->lights->ratio * (scn->lights->rgb.b / 255) * factor;
}

int		shadow(t_scene scn, t_shape *sh)
{
	t_cam	cam;
	double	dist;
	int		inter;

	inter = 0;
	cam = *scn.curr_cam;
	cam.pos = v_add(cam.p_inter, v_mult(sh->orient_n, 0.00001));
	cam.view_ray = v_norm(v_sub(scn.lights->pos, cam.pos));
	dist = p_dist(scn.lights->pos, cam.pos);
	if (intersections(scn.shapes, cam, &dist) >= 0)
		inter = 1;
	return (inter);
}

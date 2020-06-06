/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:48:33 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:26:10 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		inters_pl(t_shape *shape, t_cam cam, double *dist)
{
	double	new_d;

	if (v_prod(cam.view_ray, shape->orient_n) != 0)
	{
		new_d = (-v_prod(v_sub(cam.pos, shape->pos), shape->orient_n)) /
			v_prod(cam.view_ray, shape->orient_n);
		if (new_d > 0 && new_d < *dist && new_d > 0.1)
		{
			*dist = new_d;
			return (1);
		}
	}
	return (0);
}

int		inters_sp(t_shape *sh, t_cam cam, double *dist)
{
	double	dist_a;
	double	dist_b;
	t_shv	shv;
	t_vect	v_cam;

	v_cam = v_sub(cam.pos, sh->pos);
	if (!(shv.a = v_prod(cam.view_ray, cam.view_ray)))
		return (0);
	shv.b = 2 * v_prod(cam.view_ray, v_cam);
	shv.c = v_prod(v_cam, v_cam) - (sh->d * sh->d);
	shv.delta = shv.b * shv.b - 4 * shv.a * shv.c;
	if (shv.delta > 0)
	{
		shv.delta = sqrt(shv.delta);
		dist_a = (shv.delta - shv.b) / (2 * shv.a);
		dist_b = (-shv.delta - shv.b) / (2 * shv.a);
		min_value(&dist_a, &dist_b);
		if (dist_a > 0 && dist_a < *dist && dist_a > 0.1)
		{
			*dist = dist_a;
			return (1);
		}
	}
	return (0);
}

int		inters_sq(t_shape *sh, t_cam cam, double *dist)
{
	double		new_d;
	t_intersq	isq;

	new_d = *dist;
	if (inters_pl(sh, cam, &new_d))
	{
		isq.dir = v_sub(v_add(cam.pos, v_mult(cam.view_ray, new_d)), sh->pos);
		isq.r = v_norm(cross_prod(new_vect(0, 1, 0.1), sh->orient_n));
		isq.up = v_norm(cross_prod(sh->orient_n, isq.r));
		isq.r = v_mult(isq.r, sh->d / 2);
		isq.up = v_mult(isq.up, sh->d / 2);
		isq.up = (v_prod(isq.up, isq.dir) <= 0) ? v_mult(isq.up, -1) : isq.up;
		isq.r = (v_prod(isq.r, isq.dir) <= 0) ? v_mult(isq.r, -1) : isq.r;
		isq.a_up = acos(v_prod(isq.up, isq.dir) / (v_size(isq.up) *
			v_size(isq.dir)));
		isq.a_r = acos(v_prod(isq.r, isq.dir) / (v_size(isq.r) *
			v_size(isq.dir)));
		if ((v_size(isq.dir) * cos(isq.a_up) < v_size(isq.up)) &&
		(v_size(isq.dir) * cos(isq.a_r) < v_size(isq.r)))
		{
			*dist = new_d;
			return (1);
		}
	}
	return (0);
}

int		inters_cy(t_shape *sh, t_cam cam, double *dist)
{
	t_intercy		cy;
	double			new_d;

	new_d = *dist;
	if (cy_activate(sh, cam, &cy))
	{
		cy.v_cam = v_sub(cam.pos, sh->pos);
		cy.dist_a = (sh->delta - sh->cy_b) / (2 * sh->cy_a);
		cy.dist_b = (-sh->delta - sh->cy_b) / (2 * sh->cy_a);
		min_value(&cy.dist_a, &cy.dist_b);
		cy.a = (v_prod(cam.view_ray, sh->orient) * cy.dist_a) +
			v_prod(cy.v_cam, sh->orient);
		cy.b = (v_prod(cam.view_ray, sh->orient) * cy.dist_b) +
			v_prod(cy.v_cam, sh->orient);
		if (cy.a > (-sh->h) / 2 && cy.a < sh->h / 2)
			new_d = cy.dist_a;
		else if (cy.b > (-sh->h) / 2 && cy.b < sh->h / 2)
			new_d = cy.dist_b;
		if (new_d > 0 && new_d < *dist && new_d > 0.1)
		{
			*dist = new_d;
			return (1);
		}
	}
	return (0);
}

int		inters_tr(t_shape *sh, t_cam cam, double *dist)
{
	t_intertr	tr;
	double		n_dist;

	tr_vectors(&tr, sh, cam);
	if (!tr.point)
		return (0);
	tr.r_pos2 = v_sub(cam.pos, sh->pos);
	tr.p1 = (1.0 / tr.crosspnt) * v_prod(tr.r_pos2, tr.rb_cross);
	if (tr.p1 < 0.0 || tr.p1 > 1.0)
		return (0);
	tr.ra_cross = cross_prod(tr.r_pos2, tr.v_a);
	tr.p2 = (1.0 / tr.crosspnt) * v_prod(cam.view_ray, tr.ra_cross);
	if (tr.p2 < 0.0 || tr.p1 + tr.p2 > 1.0)
		return (0);
	n_dist = (1.0 / tr.crosspnt) * v_prod(tr.ra_cross, tr.v_b);
	if (n_dist > 0.0001 && n_dist < *dist)
	{
		*dist = n_dist;
		return (1);
	}
	return (0);
}

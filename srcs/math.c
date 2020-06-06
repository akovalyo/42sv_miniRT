/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:13:26 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:30:26 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_ray(t_scene *scn, double x, double y)
{
	t_vect		curr;
	t_vect		ray;

	curr = v_add(scn->curr_cam->bot, v_mult(scn->curr_cam->inc_x, x));
	curr = v_add(curr, v_mult(scn->curr_cam->inc_y, y));
	ray = v_sub(curr, scn->curr_cam->pos);
	return (v_norm(ray));
}

double	p_dist(t_vect a, t_vect b)
{
	double result;

	result = sqrt(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) *
		(b.y - a.y)) + ((b.z - a.z) * (b.z - a.z)));
	return (result);
}

void	min_value(double *a, double *b)
{
	double tmp;

	if (*a < 0)
		*a = 1000;
	if (*b < 0)
		*b = 1000;
	if (*b < *a)
	{
		tmp = *b;
		*b = *a;
		*a = tmp;
	}
}

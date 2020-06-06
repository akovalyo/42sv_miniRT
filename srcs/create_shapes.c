/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shapes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 16:09:22 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:19:59 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape		*new_plane(t_vect pos, t_vect orient, t_color rgb)
{
	t_shape	*pl;

	if (!(pl = malloc(sizeof(t_shape))))
		return (NULL);
	pl->type = PLANE;
	pl->pos.x = pos.x;
	pl->pos.y = pos.y;
	pl->pos.z = pos.z;
	pl->orient_n.x = orient.x;
	pl->orient_n.y = orient.y;
	pl->orient_n.z = orient.z;
	pl->rgb.t = rgb.t;
	pl->rgb.r = rgb.r;
	pl->rgb.g = rgb.g;
	pl->rgb.b = rgb.b;
	pl->next = NULL;
	return (pl);
}

t_shape		*new_sphere(t_vect pos, double d, t_color rgb)
{
	t_shape	*sp;

	if (!(sp = malloc(sizeof(t_shape))))
		return (NULL);
	sp->type = SPHERE;
	sp->pos.x = pos.x;
	sp->pos.y = pos.y;
	sp->pos.z = pos.z;
	sp->d = d;
	sp->rgb.t = rgb.t;
	sp->rgb.r = rgb.r;
	sp->rgb.g = rgb.g;
	sp->rgb.b = rgb.b;
	sp->next = NULL;
	return (sp);
}

t_shape		*new_square(t_vect pos, double d, t_vect or, t_color rgb)
{
	t_shape	*sq;

	if (!(sq = malloc(sizeof(t_shape))))
		return (NULL);
	sq->type = SQUARE;
	sq->pos.x = pos.x;
	sq->pos.y = pos.y;
	sq->pos.z = pos.z;
	sq->d = d;
	sq->orient_n.x = or.x;
	sq->orient_n.y = or.y;
	sq->orient_n.z = or.z;
	sq->rgb.t = rgb.t;
	sq->rgb.r = rgb.r;
	sq->rgb.g = rgb.g;
	sq->rgb.b = rgb.b;
	sq->next = NULL;
	return (sq);
}

t_shape		*new_cylinder(t_parsecy data)
{
	t_shape	*cy;

	if (!(cy = malloc(sizeof(t_shape))))
		return (NULL);
	cy->type = CYL;
	cy->pos.x = data.pos.x;
	cy->pos.y = data.pos.y;
	cy->pos.z = data.pos.z;
	cy->orient.x = data.orient.x;
	cy->orient.y = data.orient.y;
	cy->orient.z = data.orient.z;
	cy->d = data.d;
	cy->h = data.h;
	cy->rgb.t = data.rgb.t;
	cy->rgb.r = data.rgb.r;
	cy->rgb.g = data.rgb.g;
	cy->rgb.b = data.rgb.b;
	cy->next = NULL;
	return (cy);
}

t_shape		*new_triangle(t_vect p_1, t_vect p_2, t_vect p_3, t_color rgb)
{
	t_shape	*tr;

	if (!(tr = malloc(sizeof(t_shape))))
		return (NULL);
	tr->type = TRNG;
	tr->pos.x = p_1.x;
	tr->pos.y = p_1.y;
	tr->pos.z = p_1.z;
	tr->pos_2.x = p_2.x;
	tr->pos_2.y = p_2.y;
	tr->pos_2.z = p_2.z;
	tr->pos_3.x = p_3.x;
	tr->pos_3.y = p_3.y;
	tr->pos_3.z = p_3.z;
	tr->rgb.t = rgb.t;
	tr->rgb.r = rgb.r;
	tr->rgb.g = rgb.g;
	tr->rgb.b = rgb.b;
	tr->next = NULL;
	return (tr);
}

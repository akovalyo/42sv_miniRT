/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 13:59:19 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:46:37 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	v_size(t_vect vect)
{
	return (sqrt(vect.x * vect.x + vect.y
	* vect.y + vect.z * vect.z));
}

t_vect	v_norm(t_vect vect)
{
	double	len;
	t_vect	new;

	len = v_size(vect);
	new = v_div(vect, len);
	return (new);
}

t_vect	cross_prod(t_vect a, t_vect b)
{
	t_vect new;

	new.x = (a.y * b.z) - (a.z * b.y);
	new.y = (a.z * b.x) - (a.x * b.z);
	new.z = (a.x * b.y) - (a.y * b.x);
	return (new);
}

t_vect	new_vect(double x, double y, double z)
{
	t_vect	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vect	v_refl(t_vect vect, t_vect norm)
{
	t_vect	refl;

	refl = v_sub(vect, v_mult(norm, 2.0 * v_prod(vect, norm)));
	return (refl);
}

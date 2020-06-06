/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:09:54 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:28:51 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	v_div(t_vect vect, double num)
{
	t_vect	new;

	new.x = vect.x / num;
	new.y = vect.y / num;
	new.z = vect.z / num;
	return (new);
}

t_vect	v_add(t_vect vec_1, t_vect vec_2)
{
	t_vect	new;

	new.x = vec_1.x + vec_2.x;
	new.y = vec_1.y + vec_2.y;
	new.z = vec_1.z + vec_2.z;
	return (new);
}

t_vect	v_sub(t_vect vect_1, t_vect vect_2)
{
	t_vect	new;

	new.x = vect_1.x - vect_2.x;
	new.y = vect_1.y - vect_2.y;
	new.z = vect_1.z - vect_2.z;
	return (new);
}

t_vect	v_mult(t_vect vect, double num)
{
	t_vect	new;

	new.x = num * vect.x;
	new.y = num * vect.y;
	new.z = num * vect.z;
	return (new);
}

double	v_prod(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

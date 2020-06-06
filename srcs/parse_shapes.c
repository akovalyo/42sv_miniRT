/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 16:02:32 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/05 22:04:46 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(t_scene *scn, char **tab)
{
	t_shape	*pl;
	t_vect	pos;
	t_vect	orient;
	t_color	rgb;

	scn->pl_count++;
	if (ft_strarraylen(tab) != 4)
		close_minirt("Invalid plane data", scn);
	if (!atocoord(tab[1], &pos))
		close_minirt("Invalid coordinates of the plane center", scn);
	if (!atocoord(tab[2], &orient))
		close_minirt("Invalid coord. of the plane orinetation vector", scn);
	if (orient.x > 1 || orient.x < -1 || orient.y > 1 || orient.y < -1 ||
		orient.z > 1 || orient.z < -1)
		close_minirt("Plane orient. vectors are not in range -1 and 1", scn);
	orient = v_norm(orient);
	if (atorgb(tab[3], &rgb))
		close_minirt("Invalid RGB for plane, should be in range 0-255", scn);
	if (!(pl = new_plane(pos, orient, rgb)))
		close_minirt(NULL, scn);
	add_shape(&(scn)->shapes, pl);
	ft_printf("Plane #%d: OK\n", scn->pl_count);
}

void	parse_sphere(t_scene *scn, char **tab)
{
	t_shape	*sp;
	t_vect	pos;
	double	d;
	t_color	rgb;

	scn->sp_count++;
	if (ft_strarraylen(tab) != 4)
		close_minirt("Invalid sphere data", scn);
	if (!atocoord(tab[1], &pos))
		close_minirt("Invalid coordinates of the sphere center", scn);
	d = ft_atof(tab[2]);
	if (d < 0 || d > 180)
		close_minirt("Diameter of the sphere is incorrect", scn);
	if (atorgb(tab[3], &rgb))
		close_minirt("Invalid RGB for sphere, should be in range 0-255", scn);
	if (!(sp = new_sphere(pos, d, rgb)))
		close_minirt(NULL, scn);
	add_shape(&(scn)->shapes, sp);
	ft_printf("Sphere #%d: OK\n", scn->sp_count);
}

void	parse_square(t_scene *scn, char **tab)
{
	t_shape	*sq;
	t_vect	pos;
	t_vect	orient;
	double	d;
	t_color	rgb;

	scn->sq_count++;
	if (ft_strarraylen(tab) != 5)
		close_minirt("Invalid square data", scn);
	if (!atocoord(tab[1], &pos))
		close_minirt("Invalid coordinates of the square center", scn);
	if (!atocoord(tab[2], &orient))
		close_minirt("Invalid coord. of the square orinet. vector", scn);
	if (orient.x > 1 || orient.x < -1 || orient.y > 1 || orient.y < -1 ||
		orient.z > 1 || orient.z < -1)
		close_minirt("Square orient. vectors are not in range -1 and 1", scn);
	orient = v_norm(orient);
	d = ft_atof(tab[3]);
	if (atorgb(tab[4], &rgb))
		close_minirt("Invalid RGB for square, should be in range 0-255", scn);
	if (!(sq = new_square(pos, d, orient, rgb)))
		close_minirt(NULL, scn);
	add_shape(&(scn)->shapes, sq);
	ft_printf("Square #%d: OK\n", scn->sq_count);
}

void	parse_cylinder(t_scene *scn, char **tab)
{
	t_shape		*cy;
	t_parsecy	data;

	scn->cy_count++;
	if (ft_strarraylen(tab) != 6)
		close_minirt("Invalid cylinder data", scn);
	if (!atocoord(tab[1], &data.pos))
		close_minirt("Invalid coordinates of the cylinder center", scn);
	if (!atocoord(tab[2], &data.orient))
		close_minirt("Invalid coord. of the cylinder orinet. vect", scn);
	if (data.orient.x > 1 || data.orient.x < -1 || data.orient.y > 1 ||
		data.orient.y < -1 || data.orient.z > 1 || data.orient.z < -1)
		close_minirt("Cylinder orient. vectors are not in range -1 and 1", scn);
	data.orient = v_norm(data.orient);
	data.d = ft_atof(tab[3]);
	data.h = ft_atof(tab[4]);
	if (atorgb(tab[5], &data.rgb))
		close_minirt("Invalid RGB for cylinder, should be in range 0-255", scn);
	if (!(cy = new_cylinder(data)))
		close_minirt(NULL, scn);
	add_shape(&(scn)->shapes, cy);
	ft_printf("Cylinder #%d: OK\n", scn->cy_count);
}

void	parse_triangle(t_scene *scn, char **tab)
{
	t_shape	*tr;
	t_vect	pos;
	t_vect	pos_2;
	t_vect	pos_3;
	t_color	rgb;

	scn->tr_count++;
	if (ft_strarraylen(tab) != 5)
		close_minirt("Invalid triangle data", scn);
	if (!atocoord(tab[1], &pos))
		close_minirt("Invalid coordinates of the first point in triangle", scn);
	if (!atocoord(tab[2], &pos_2))
		close_minirt("Invalid coord. of the second point in triangle", scn);
	if (!atocoord(tab[3], &pos_3))
		close_minirt("Invalid coordinates of the third point in triangle", scn);
	if (atorgb(tab[4], &rgb))
		close_minirt("Invalid RGB for triangle, should be in range 0-255", scn);
	if (!(tr = new_triangle(pos, pos_2, pos_3, rgb)))
		close_minirt(NULL, scn);
	add_shape(&(scn)->shapes, tr);
	ft_printf("Triangle #%d: OK\n", scn->sq_count);
}

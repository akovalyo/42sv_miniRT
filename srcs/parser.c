/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 12:54:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:40:34 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_res(t_scene *scn, char **tab)
{
	if (ft_strarraylen(tab) != 3)
		close_minirt("Invalid resolution data", scn);
	if (scn->res.processed)
		close_minirt("Resolution has already loaded", scn);
	scn->res.processed = 1;
	scn->res.x = ft_atoi(tab[1]);
	scn->res.y = ft_atoi(tab[2]);
	if (scn->res.x <= 0 || scn->res.y <= 0)
		close_minirt("Resolution is set to 0 or negative", scn);
	scn->res.x = scn->res.x > 2560 ? 2560 : scn->res.x;
	scn->res.y = scn->res.y > 1395 ? 1395 : scn->res.y;
	ft_printf("Resolution: OK\n");
}

void		parse_amb(t_scene *scn, char **tab)
{
	if (ft_strarraylen(tab) != 3)
		close_minirt("Invalid ambient lightning data", scn);
	if (scn->refl.processed)
		close_minirt("Ambinet lightning has already loaded", scn);
	scn->refl.processed = 1;
	scn->refl.coeff = ft_atof(tab[1]);
	if (scn->refl.coeff < 0 || scn->refl.coeff > 1)
		close_minirt("Ambient lightning ratio is not in range 0 and 1", scn);
	if (atorgb(tab[2], &(scn->refl.amb_col)))
		close_minirt("Invalid RGB for amb l., should be in range 0-255", scn);
	ft_printf("Ambient lightning: OK\n");
}

void		parse_cam(t_scene *scn, char **tab)
{
	t_vect	view;
	t_vect	vector;
	double	fov;
	t_cam	*camera;

	scn->cam_count++;
	if (ft_strarraylen(tab) != 4)
		close_minirt("Invalid camera data", scn);
	if (!atocoord(tab[1], &view))
		close_minirt("Invalid coord. of the view point of the camera", scn);
	if (!atocoord(tab[2], &vector))
		close_minirt("Invalid orientation vector of the camera", scn);
	if (vector.x > 1 || vector.x < -1 || vector.y > 1 || vector.y < -1 ||
		vector.z > 1 || vector.z < -1)
		close_minirt("Camera orientation vector is not in range -1 and 1", scn);
	fov = ft_atof(tab[3]);
	if (fov < 0 || fov > 180)
		close_minirt("Horizontal field of view is not in range 0 and 180", scn);
	if (!(camera = new_camera(view, vector, fov, scn->cam_count)))
		close_minirt(NULL, scn);
	add_cam(&(scn)->cams, camera);
	ft_printf("Camera #%d: OK\n", scn->cam_count);
}

void		parse_light(t_scene *scn, char **tab)
{
	t_light	*light;
	t_vect	pos;
	double	ratio;
	t_color	rgb;

	scn->light_count++;
	if (ft_strarraylen(tab) != 4)
		close_minirt("Invalid light data", scn);
	if (!atocoord(tab[1], &pos))
		close_minirt("Invalid coordinates of the light point", scn);
	ratio = ft_atof(tab[2]);
	if (ratio < 0 || ratio > 1)
		close_minirt("Light brightness ratio is not in range 0 and 1", scn);
	if (atorgb(tab[3], &rgb))
		close_minirt("Invalid RGBfor light, should be in range 0-255", scn);
	if (!(light = new_light(pos, ratio, rgb, scn->light_count)))
		close_minirt(NULL, scn);
	add_light(&(scn)->lights, light);
	ft_printf("Light #%d: OK\n", scn->light_count);
}

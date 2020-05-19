/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 12:54:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/18 16:37:21 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_res(t_scene *scn, char **tab)
{
	if (ft_strarraylen(tab) != 3)
		return (error("Invalid resolution data"));
	else if (scn->res.processed)
		return (error("Resolution already loaded"));
	scn->res.x = ft_atoi(tab[1]);
	scn->res.y = ft_atoi(tab[2]);
	if (scn->res.x <= 0 || scn->res.y <= 0)
		return (error("Resolution is set to 0 or negative"));
	ft_printf("Resolution: OK\n");
	return (0);
}

int		parse_amb(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_cam(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_light(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_plane(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_sphere(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_square(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_cylinder(t_scene *scn, char **tab)
{
	return (0);
}

int		parse_triangle(t_scene *scn, char **tab)
{
	return (0);
}
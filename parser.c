/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 12:54:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 17:47:10 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int			ft_atoi_rgb(const char *nptr)
{
	int		sign;
	int		collector;

	sign = 1;
	collector = 0;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	if (!(ft_isdigit(*nptr)))
		return (-1000);
	if (*nptr == '0' && ft_isdigit(*(nptr + 1)))
		return (-1000);
	while (ft_isdigit(*nptr))
		collector = collector * 10 + *(nptr++) - '0';
	return (collector * sign);
}

int		atorgb(char *ptr)
{
	int rgb[3];
	int i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi_rgb(ptr);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
		while (ft_isdigit(*ptr))
			ptr++;
		if (*ptr != ',' && *ptr != '\0')
			return (-1);
		i++;
		ptr++;
	}
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

int		atocoord(char *ptr, t_vect *vect)
{
	if (ft_isdigit(*ptr) || *ptr == '-')
		vect->x = ft_atof(ptr);
	else
		return (0);
	while (ft_isdigit(*ptr) || *ptr == '.')
			ptr++;
	if (*(ptr++) != ',')
		return (0);
	if (ft_isdigit(*ptr) || *ptr == '-')
		vect->y = ft_atof(ptr);
	else
		return (0);
	while (ft_isdigit(*ptr) || *ptr == '.')
			ptr++;
	if (*(ptr++) != ',')
		return (0);
	if (ft_isdigit(*ptr) || *ptr == '-')
		vect->z = ft_atof(ptr);
	else
		return (0);
	while (ft_isdigit(*ptr) || *ptr == '.')
			ptr++;
	return ((*ptr != '\0') ? 0 : 1);
}

int		parse_res(t_scene *scn, char **tab)
{
	if (ft_strarraylen(tab) != 3)
		return (error("Invalid resolution data"));
	if (scn->res.processed)
		return (error("Resolution has already loaded"));
	scn->res.processed = 1;
	scn->res.x = ft_atoi(tab[1]);
	scn->res.y = ft_atoi(tab[2]);
	if (scn->res.x <= 0 || scn->res.y <= 0)
		return (error("Resolution is set to 0 or negative"));
	ft_printf("Resolution: OK\n");
	return (0);
}

int		parse_amb(t_scene *scn, char **tab)
{
	if (ft_strarraylen(tab) != 3)
		return (error("Invalid ambient lightning data"));
	if (scn->amb.processed)
		return (error("Ambinet lightning has already loaded"));
	scn->amb.processed = 1;
	scn->amb.ratio = ft_atof(tab[1]);
	if (scn->amb.ratio < 0 || scn->amb.ratio > 1)
		return (error("Ambient lightning ratio is not in range 0 and 1"));
	if ((scn->amb.rgb = atorgb(tab[2]) == -1))
		return (error("Invalid RGB values for ambient lightning, should be in range 0-255"));
	ft_printf("Ambient lightning: OK\n");
	return (0);
}

t_cam	*new_camera(t_vect view, t_vect vector, double fov, int num)
{
	t_cam	*cam;

	if(!(cam = malloc(sizeof(t_cam))))
		return (NULL);
	cam->pos.x = view.x;
	cam->pos.y = view.y;
	cam->pos.z = view.z;
	cam->orient.x = vector.x;
	cam->orient.y = vector.y;
	cam->orient.z = vector.z;
	cam->fov = fov;
	cam->cam_num = num;
	return (cam);
}

int		parse_cam(t_scene *scn, char **tab)
{
	t_vect	view;
	t_vect	vector;
	double	fov;
	t_list	*camera;
	
	scn->cam_count++;
	if (ft_strarraylen(tab) != 4)
		return (error("Invalid camera data"));
	if (!atocoord(tab[1], &view))
		return (error("Invalid coordinates of the view point"));
	if (!atocoord(tab[2], &vector))
		return (error("Invalid orientation vector of the camera"));
	if (vector.x > 1 || vector.x < -1 || vector.y > 1 || vector.y < -1 ||
		vector.z > 1 || vector.z < -1)
		return (error("Camera orientation vector is not in range -1 and 1"));
	fov = ft_atof(tab[3]);
	if (fov < 0 || fov > 180)
		return (error("Horizontal field of view is not in range 0 and 180"));
	
	//printf("FOV: %f\n", tmp->fov);
	
	if (!(camera = ft_lstnew(new_camera(view, vector, fov, scn->cam_count))))
		return (-1);
	ft_lstadd_back(&(scn->cams), camera);
	ft_printf("Camera #%d: OK\n", scn->cam_count);
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
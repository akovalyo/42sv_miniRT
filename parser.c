/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 12:54:52 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/24 12:17:10 by akovalyo         ###   ########.fr       */
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
	while (ft_isdigit(*ptr) || *ptr == '.' || *ptr == '-')
			ptr++;
	if (*(ptr++) != ',')
		return (0);
	if (ft_isdigit(*ptr) || *ptr == '-')
		vect->y = ft_atof(ptr);
	else
		return (0);
	while (ft_isdigit(*ptr) || *ptr == '.' || *ptr == '-')
			ptr++;
	if (*(ptr++) != ',')
		return (0);
	if (ft_isdigit(*ptr) || *ptr == '-')
		vect->z = ft_atof(ptr);
	else
		return (0);
	while (ft_isdigit(*ptr) || *ptr == '.' || *ptr == '-')
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
	scn->res.x = scn->res.x > 2560 ? 2560 : scn->res.x;
	scn->res.y = scn->res.y > 1395 ? 1395 : scn->res.y;
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

float		vect_size(t_vect vect)
{
	return (sqrt(vect.x * vect.x + vect.y
	* vect.y + vect.z * vect.z));
}

t_vect		vect_div(t_vect vect, float num)
{
	t_vect	new;

	new.x = vect.x / num;
	new.y = vect.y / num;
	new.z = vect.z / num;
	return (new);
}

t_vect		vect_norm(t_vect vect)
{
	float	len;
	t_vect	new;

	len = vect_size(vect);
	new = vect_div(vect, len);
	return (new);
}



t_cam	*new_camera(t_vect view, t_vect vector, float fov, int num)
{
	t_cam	*cam;

	if(!(cam = malloc(sizeof(t_cam))))
		return (NULL);
	cam->next = NULL;
	cam->pos.x = view.x;
	cam->pos.y = view.y;
	cam->pos.z = view.z;

	cam->orient = vect_norm(vector);

	cam->orient.x += 0.0001;
	// cam->orient.x = vector.x;
	// cam->orient.y = vector.y;
	// cam->orient.z = vector.z;
	cam->fov = fov;
	cam->cam_num = num;
	return (cam);
}

void	add_cam(t_cam **lst, t_cam *new)
{
	t_cam *tmp;

	if (!(*lst))
	{
		(*lst) = new;
		new->next = new;
		new->prev = new;
		(*lst) = new;
	}
	else
	{
		tmp = (*lst)->next;
		(*lst)->next = new;
		new->prev = *lst;
		new->next = tmp;
		tmp->prev = new;
		(*lst) = new;
	}
}


int		parse_cam(t_scene *scn, char **tab)
{
	t_vect	view;
	t_vect	vector;
	float	fov;
	t_cam	*camera;
	
	scn->cam_count++;
	if (ft_strarraylen(tab) != 4)
		return (error("Invalid camera data"));
	if (!atocoord(tab[1], &view))
		return (error("Invalid coordinates of the view point of the camera"));
	if (!atocoord(tab[2], &vector))
		return (error("Invalid orientation vector of the camera"));
	if (vector.x > 1 || vector.x < -1 || vector.y > 1 || vector.y < -1 ||
		vector.z > 1 || vector.z < -1)
		return (error("Camera orientation vector is not in range -1 and 1"));
	fov = ft_atof(tab[3]);
	if (fov < 0 || fov > 180)
		return (error("Horizontal field of view is not in range 0 and 180"));
	
	//printf("FOV: %f\n", tmp->fov);
	
	if (!(camera = new_camera(view, vector, fov, scn->cam_count)))
		return (-1);
	add_cam(&(scn)->cams, camera);
	ft_printf("Camera #%d: OK\n", scn->cam_count);
	return (0);
}

t_light		*new_light(t_vect pos, float ratio, int rgb, int num)
{
	t_light	*light;

	if(!(light = malloc(sizeof(t_light))))
		return (NULL);
	light->pos.x = pos.x;
	light->pos.y = pos.y;
	light->pos.z = pos.z;
	light->ratio = ratio;
	light->rgb = rgb;
	light->light_num = num;
	return (light);
}

int		parse_light(t_scene *scn, char **tab)
{

	t_list	*light;
	t_vect	pos;
	float	ratio;
	int		rgb;

	scn->light_count++;
	if (ft_strarraylen(tab) != 4)
		return (error("Invalid light data"));
	if (!atocoord(tab[1], &pos))
		return (error("Invalid coordinates of the light point"));
	ratio = ft_atof(tab[2]);
	if (scn->amb.ratio < 0 || scn->amb.ratio > 1)
		return (error("Light brightness ratio is not in range 0 and 1"));
	if ((rgb = atorgb(tab[3]) == -1))
		return (error("Invalid RGB values for light, should be in range 0-255"));
	if (!(light = ft_lstnew(new_light(pos, ratio, rgb, scn->light_count))))
		return (-1);
	ft_lstadd_back(&(scn->lights), light);
	ft_printf("Light #%d: OK\n", scn->light_count);
	return (0);
}

t_plane		*new_plane(t_vect pos, t_vect orient, int rgb, int num)
{
	t_plane	*pl;

	if(!(pl = malloc(sizeof(t_plane))))
		return (NULL);
	pl->pos.x = pos.x;
	pl->pos.y = pos.y;
	pl->pos.z = pos.z;
	pl->orient.x = orient.x;
	pl->orient.y = orient.y;
	pl->orient.z = orient.z;
	pl->rgb = rgb;
	pl->pl_num = num;
	return (pl);
}

int		parse_plane(t_scene *scn, char **tab)
{
	t_list	*pl;
	t_vect	pos;
	t_vect	orient;
	int		rgb;

	scn->pl_count++;
	if (ft_strarraylen(tab) != 4)
		return (error("Invalid plane data"));
	if (!atocoord(tab[1], &pos))
		return (error("Invalid coordinates of the plane center"));
	if (!atocoord(tab[2], &orient))
		return (error("Invalid coordinates of the plane orinetation vector"));	
	if (orient.x > 1 || orient.x < -1 || orient.y > 1 || orient.y < -1 ||
		orient.z > 1 || orient.z < -1)
		return (error("Plane's orientation vector values are not in range -1 and 1"));
	if ((rgb = atorgb(tab[3]) == -1))
		return (error("Invalid RGB values for plane, should be in range 0-255"));
	
	if (!(pl = ft_lstnew(new_plane(pos, orient, rgb, scn->pl_count))))
		return (-1);
	ft_lstadd_back(&(scn->shapes), pl);
	ft_printf("Light #%d: OK\n", scn->light_count);
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
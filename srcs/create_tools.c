/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 12:19:02 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:21:42 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*new_camera(t_vect view, t_vect vector, double fov, int num)
{
	t_cam	*cam;

	if (!(cam = malloc(sizeof(t_cam))))
		return (NULL);
	cam->next = NULL;
	cam->pos.x = view.x;
	cam->pos.y = view.y;
	cam->pos.z = view.z;
	cam->orient = v_norm(vector);
	cam->fov = fov;
	cam->cam_num = num;
	return (cam);
}

t_light	*new_light(t_vect pos, double ratio, t_color rgb, int num)
{
	t_light	*light;

	if (!(light = malloc(sizeof(t_light))))
		return (NULL);
	light->pos.x = pos.x;
	light->pos.y = pos.y;
	light->pos.z = pos.z;
	light->ratio = ratio;
	light->rgb.t = rgb.t;
	light->rgb.r = rgb.r;
	light->rgb.g = rgb.g;
	light->rgb.b = rgb.b;
	light->light_num = num;
	light->next = NULL;
	return (light);
}

void	add_shape(t_shape **lst, t_shape *new)
{
	t_shape *shape;

	if (!(*lst))
	{
		(*lst) = new;
		new->next = NULL;
	}
	else
	{
		shape = *lst;
		while (shape->next)
			shape = (t_shape *)shape->next;
		shape->next = (struct s_shape *)new;
		new->next = NULL;
		shape = *lst;
	}
}

void	add_light(t_light **lst, t_light *new)
{
	t_light *light;

	if (!(*lst))
	{
		(*lst) = new;
		new->next = NULL;
	}
	else
	{
		light = *lst;
		while (light->next)
			light = light->next;
		light->next = new;
		new->next = NULL;
		light = *lst;
	}
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

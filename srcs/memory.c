/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:32:31 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:28:20 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scn)
{
	free_cam(scn);
	free_light(scn);
	free_shape(scn);
}

void	free_cam(t_scene *scn)
{
	t_cam *tmp;

	while (scn->cam_count > 0)
	{
		ft_printf("Free cam #%d\n", scn->cams->cam_num);
		tmp = scn->cams;
		scn->cams = scn->cams->next;
		free(tmp);
		scn->cam_count--;
	}
}

void	free_light(t_scene *scn)
{
	t_light *tmp;

	while (scn->light_count > 0)
	{
		ft_printf("Free light #%d\n", scn->lights->light_num);
		tmp = scn->lights;
		scn->lights = scn->lights->next;
		free(tmp);
		scn->light_count--;
	}
}

void	free_shape(t_scene *scn)
{
	t_shape	*tmp;
	int		num_sh;

	num_sh = scn->pl_count + scn->sp_count + scn->sq_count +
		scn->cy_count + scn->tr_count;
	while (num_sh > 0)
	{
		ft_printf("Free shape #%d\n", num_sh);
		tmp = scn->shapes;
		scn->shapes = (t_shape *)scn->shapes->next;
		free(tmp);
		num_sh--;
	}
}

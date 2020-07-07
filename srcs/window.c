/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 09:06:41 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/06 23:11:36 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		start_wind(t_scene *scn)
{
	scn->mlx = mlx_init();
	if (scn->save == 0)
		scn->win = mlx_new_window(scn->mlx, scn->res.x, scn->res.y, "miniRT");
	scn->curr_cam = scn->cams;
	return (0);
}

int		key_hooks(int key, t_scene *scn)
{
	if (key == ESCAPE)
	{
		mlx_destroy_window(scn->mlx, scn->win);
		close_minirt(NULL, scn);
	}
	else if (key == RIGHT && scn->cam_count > 1)
	{
		mlx_destroy_image(scn->mlx, scn->img_ptr);
		scn->curr_cam = scn->curr_cam->next;
		render_main(scn);
	}
	else if (key == LEFT && scn->cam_count > 1)
	{
		mlx_destroy_image(scn->mlx, scn->img_ptr);
		scn->curr_cam = scn->curr_cam->prev;
		render_main(scn);
	}
	return (0);
}

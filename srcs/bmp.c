/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 10:46:07 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/05 22:07:49 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bm_fileheader(t_bmp *bmp, t_bmfileheader *bmfh)
{
	bmfh->type[0] = 'B';
	bmfh->type[1] = 'M';
	bmfh->size = bmp->f_size;
	bmfh->reserved1 = 0;
	bmfh->reserved2 = 0;
	bmfh->offbits = 0;
}

void	bm_infoheader(t_scene *scn, t_bmp *bmp, t_bminfoheader *bmih)
{
	bmih->size = 40;
	bmih->width = scn->res.x;
	bmih->height = scn->res.y;
	bmih->planes = 1;
	bmih->bitcount = 32;
	bmih->compression = 0;
	bmih->size_image = bmp->f_size;
	bmih->x_ppm = 0;
	bmih->y_ppm = 0;
	bmih->clr_used = 0;
	bmih->clr_important = 0;
}

void	create_name(t_scene *scn, t_bmp *bmp)
{
	char *tmp;

	if (scn->img_name)
		bmp->name = ft_strdup(scn->img_name);
	else
		bmp->name = ft_strdup("image");
	tmp = bmp->name;
	bmp->name = ft_strjoin(bmp->name, ".bmp");
	free(tmp);
}

void	save_bmp(t_scene *scn)
{
	t_bmfileheader	bmfh;
	t_bminfoheader	bmih;
	t_bmp			bmp;

	bmp.img_size = scn->res.x * scn->res.y;
	bmp.f_size = 54 + 4 * bmp.img_size;
	bm_fileheader(&bmp, &bmfh);
	bm_infoheader(scn, &bmp, &bmih);
	create_name(scn, &bmp);
	if ((bmp.fd = open(bmp.name, O_CREAT | O_WRONLY | O_TRUNC)) == -1)
	{
		free(scn->img_name);
		close_minirt("Cannot save image", scn);
	}
	write(bmp.fd, &bmfh, 14);
	write(bmp.fd, &bmih, 40);
	write(bmp.fd, scn->img, 4 * bmp.img_size);
	ft_printf("\nImage %s saved\n", bmp.name);
	free(bmp.name);
	close(bmp.fd);
	mlx_destroy_image(scn->mlx, scn->img_ptr);
	close_minirt(NULL, scn);
}
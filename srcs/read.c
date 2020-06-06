/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:56:37 by akovalyo          #+#    #+#             */
/*   Updated: 2020/06/04 13:41:35 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	line_parse(t_scene *scn, char **tab)
{
	if (ft_strncmp(tab[0], "R", 2) == 0)
		parse_res(scn, tab);
	else if (ft_strncmp(tab[0], "A", 2) == 0)
		parse_amb(scn, tab);
	else if (ft_strncmp(tab[0], "c", 2) == 0)
		parse_cam(scn, tab);
	else if (ft_strncmp(tab[0], "l", 2) == 0)
		parse_light(scn, tab);
	else if (ft_strncmp(tab[0], "pl", 3) == 0)
		parse_plane(scn, tab);
	else if (ft_strncmp(tab[0], "sp", 3) == 0)
		parse_sphere(scn, tab);
	else if (ft_strncmp(tab[0], "sq", 3) == 0)
		parse_square(scn, tab);
	else if (ft_strncmp(tab[0], "cy", 3) == 0)
		parse_cylinder(scn, tab);
	else if (ft_strncmp(tab[0], "tr", 3) == 0)
		parse_triangle(scn, tab);
	else
		close_minirt("Invalid data in rt file", scn);
}

void	tab_free(char **tab, int len)
{
	len--;
	while (len >= 0)
		free(tab[len--]);
	free(tab);
}

void	line_process(t_scene *scn)
{
	char	**tab;

	tab = ft_strsplit(scn->line, ' ');
	if (ft_strarraylen(tab) > 0)
		line_parse(scn, tab);
	tab_free(tab, ft_strarraylen(tab));
}

void	read_rt(t_scene *scn, char *file)
{
	if ((scn->fd = open(file, O_RDONLY)) < 0)
		close_minirt("Can not open file", scn);
	while ((scn->gnl = get_next_line(scn->fd, &(scn)->line)) > 0)
	{
		line_process(scn);
		free(scn->line);
	}
	if (scn->gnl == -1)
	{
		free(scn->line);
		close_minirt("Can not read file", scn);
	}
	close(scn->fd);
}

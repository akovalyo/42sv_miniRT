/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:56:37 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/18 17:15:39 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		error(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	return (-1);
}

int		line_parse(t_scene *scn, char **tab)
{
	if (ft_strncmp(tab[0], "R", 2) == 0)
		return (parse_res(scn, tab));
	else if (ft_strncmp(tab[0], "A", 2) == 0)
		return (parse_amb(scn, tab));
	else if (ft_strncmp(tab[0], "c", 2) == 0)
		return (parse_cam(scn, tab));
	else if (ft_strncmp(tab[0], "l", 2) == 0)
		return (parse_light(scn, tab));
	else if (ft_strncmp(tab[0], "pl", 3) == 0)
		return (parse_plane(scn, tab));
	else if (ft_strncmp(tab[0], "sp", 3) == 0)
		return (parse_sphere(scn, tab));
	else if (ft_strncmp(tab[0], "sq", 3) == 0)
		return (parse_square(scn, tab));
	else if (ft_strncmp(tab[0], "cy", 3) == 0)
		return (parse_cylinder(scn, tab));
	else if (ft_strncmp(tab[0], "tr", 3) == 0)
		return (parse_triangle(scn, tab));
	else
		return (error("Invalid data in rt file"));
}

void	tab_free(char **tab, int len)
{
	len--;
	while (len >= 0)
		free(tab[len--]);
	free(tab);
}

int		line_process(t_scene *scn)
{
	char	**tab;
	int		ret;

	int i = 0;

	ret = 0;
	tab = ft_strsplit(scn->line, ' ');


	while (tab[i])
	{
		ft_printf("|%s|\n", tab[i]);
		i++;
	}

	if (ft_strarraylen(tab) > 0)
		ret = line_parse(scn, tab);	
	tab_free(tab, ft_strarraylen(tab));
	return (ret);
}

int		read_rt(t_scene *scn, char *file)
{
	if ((scn->fd = open(file, O_RDONLY)) < 0)
		return (error("Can not open file"));
	while ((scn->gnl = get_next_line(scn->fd, &(scn)->line)) > 0)
	{
		if(line_process(scn) == -1)
		{
			//error("Incorrect data");
			free(scn->line);
			close(scn->fd);
			return (-1);
		}
		free(scn->line);
	}
	if (scn->gnl == -1)
	{
		free(scn->line);
		return (error("Can not read file"));
	}
	close(scn->fd);
	return (0);
}
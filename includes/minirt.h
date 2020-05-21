/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:38:18 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 17:11:59 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "libft.h"
# include "mlx.h"

typedef struct		s_res
{
	unsigned int 	processed : 1;
	int				x;
	int				y;

}					t_res;

typedef struct		s_amb
{
	unsigned int 	processed : 1;
	double			ratio;
	int				rgb;

}					t_amb;

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			orient;
	double			fov;
	int				cam_num;
}					t_cam;

typedef struct		s_scene
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_addr;
	int         	bits_per_pixel;
    int         	line_length;
    int         	endian;
	int				fd;
	int				gnl;
	char			*line;
	t_res			res;
	t_amb			amb;
	t_list			*cams;
	int				cam_count;


}					t_scene;


int		start_wind(t_scene *scn);
void init_data(t_scene *scn);
int close_win(int key, t_scene *scn);


int		error(char *message);
int		line_parse(t_scene *scn, char **tab);
int		start_wind(t_scene *scn);
void	tab_free(char **tab, int len);
int		line_process(t_scene *scn);
int		read_rt(t_scene *scn, char *file);

int		parse_res(t_scene *scn, char **tab);
int		parse_amb(t_scene *scn, char **tab);
int		parse_cam(t_scene *scn, char **tab);
int		parse_light(t_scene *scn, char **tab);
int		parse_plane(t_scene *scn, char **tab);
int		parse_sphere(t_scene *scn, char **tab);
int		parse_square(t_scene *scn, char **tab);
int		parse_cylinder(t_scene *scn, char **tab);
int		parse_triangle(t_scene *scn, char **tab);

#endif
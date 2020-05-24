/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:38:18 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/24 12:11:13 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ESCAPE 65307
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
	float			ratio;
	int				rgb;

}					t_amb;

typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
}					t_vect;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			orient;
	float			fov;
	int				cam_num;
	struct s_cam	*next;
	struct s_cam	*prev;
}					t_cam;

typedef struct		s_light
{
	t_vect			pos;
	float			ratio;
	int				rgb;
	int				light_num;
}					t_light;



typedef struct		s_plane
{
	t_vect			pos;
	t_vect			orient;
	int				rgb;
	int				pl_num;
}					t_plane;

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
	t_cam			*cams;
	int				cam_count;
	t_cam			*curr_cam;
	int				light_count;
	t_list			*lights;
	int				pl_count;
	t_list			*shapes;

	int				*workable;
	int				start;
	int				end;


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
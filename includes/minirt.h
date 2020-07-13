/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:38:18 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/12 23:02:08 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define PLANE 0
# define SPHERE 1
# define SQUARE 2
# define CYL 3
# define TRNG 4
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "keys.h"
# include <float.h>

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_shv
{
	double			a;
	double			b;
	double			c;
	double			delta;
}					t_shv;

typedef struct		s_intersq
{
	t_vect			up;
	t_vect			r;
	t_vect			dir;
	double			a_up;
	double			a_r;
}					t_intersq;

typedef struct		s_intercy
{
	double			dist_a;
	double			dist_b;
	double			a;
	double			b;
	t_vect			v_cam;

}					t_intercy;

typedef struct		s_intertr
{
	t_vect			v_a;
	t_vect			v_b;
	t_vect			ra_cross;
	t_vect			rb_cross;
	t_vect			r_pos2;
	double			crosspnt;
	double			p1;
	double			p2;
	int				point;

}					t_intertr;

typedef struct		s_color
{
	double			t;
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_res
{
	unsigned int	processed : 1;
	int				x;
	int				y;

}					t_res;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			orient;
	double			fov;
	int				cam_num;
	int				res_x;
	int				res_y;
	struct s_cam	*next;
	struct s_cam	*prev;
	t_vect			right;
	t_vect			up;
	t_vect			down;
	t_vect			inc_x;
	t_vect			inc_y;
	t_vect			bot;
	t_vect			view_ray;
	t_vect			p_inter;
}					t_cam;

typedef struct		s_shape
{
	int				type;
	t_vect			pos;
	t_vect			pos_2;
	t_vect			pos_3;
	t_vect			orient;
	t_vect			orient_n;
	t_color			rgb;
	double			d;
	double			h;
	double			cy_a;
	double			cy_b;
	double			cy_c;
	double			delta;
	struct s_shape	*next;
}					t_shape;

typedef struct		s_parsecy
{
	t_shape			*cy;
	t_vect			pos;
	t_vect			orient;
	double			d;
	double			h;
	t_color			rgb;
}					t_parsecy;

typedef struct		s_light
{
	t_vect			pos;
	double			ratio;
	t_color			rgb;
	int				light_num;
	t_vect			vec;
	t_vect			refl;
	struct s_light	*next;
}					t_light;

typedef struct		s_refl
{
	unsigned int	processed : 1;
	t_color			d;
	t_color			s;
	t_color			amb;
	t_color			amb_col;
	double			coeff;
}					t_refl;

typedef struct		s_scene
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*img;
	char			*img_name;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				fd;
	int				gnl;
	int				save;
	char			*line;
	t_res			res;
	t_cam			*cams;
	int				cam_count;
	t_cam			*curr_cam;
	int				light_count;
	t_light			*lights;
	int				pl_count;
	t_shape			*shapes;
	t_color			color;
	t_refl			refl;
	int				sp_count;
	int				sq_count;
	int				cy_count;
	int				tr_count;

}					t_scene;

typedef struct		s_bmfileh
{
	unsigned char	type[2];
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offbits;

}					t_bmfileh;

typedef struct		s_bminfoh
{
	unsigned int	size;
	int				width;
	int				height;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	img_size;
	int				x_ppm;
	int				y_ppm;
	unsigned int	clr_used;
	unsigned int	clr_important;

}					t_bminfoh;

typedef struct		s_bmp
{
	int				fd;
	int				img_size;
	int				f_size;
	char			*name;
}					t_bmp;

/*
** main.c
*/

int					intersections(t_shape *shape, t_cam cam, double *dist);
void				reflect(t_scene scn, t_shape *shape, t_color *color,
						double dist);
void				render(t_scene scn, t_cam cam, t_color *color);
void				render_main(t_scene *scn);

/*
** bmp.c
*/

void				save_bmp(t_scene *scn);
void				create_name(t_scene *scn, t_bmp *bmp);
void				bm_infoheader(t_scene *scn, t_bmp *bmp, t_bminfoh *bmih);
void				bm_fileheader(t_bmp *bmp, t_bmfileh *bmfh);
void				write_headers(t_bmp bmp, t_bmfileh bmfh, t_bminfoh bmih);

/*
** init.c
*/

void				init_data(t_scene *scn);
void				init_img(t_scene *scn);
void				init_cam(t_scene scn, t_cam *cam);

/*
** window.c
*/

int					start_wind(t_scene *scn);
int					key_hooks(int key, t_scene *scn);

/*
** reflections.c
*/

void				refl_pl(t_scene scn, t_shape *shape, double dist);
void				refl_sp(t_scene scn, t_shape *shape, double dist);
void				refl_shape(t_scene scn, t_shape *shape, double dist);
void				refl_cy(t_scene scn, t_shape *shape, double dist);
void				refl_tr(t_scene scn, t_shape *sh, double dist);

/*
** intersections.c
*/

int					inters_pl(t_shape *shape, t_cam cam, double *dist);
int					inters_sp(t_shape *sh, t_cam cam, double *dist);
int					inters_sq(t_shape *sh, t_cam cam, double *dist);
int					inters_cy(t_shape *sh, t_cam cam, double *dist);
int					inters_tr(t_shape *sh, t_cam cam, double *dist);

/*
** utils.c
*/

double				norm_color(double col);
void				close_minirt(char *message, t_scene *scn);
int					cy_activate(t_shape *sh, t_cam cam, t_intercy *cy);
void				tr_vectors(t_intertr *tr, t_shape *sh, t_cam cam);
int					close_program(void *prm);

/*
** read.c
*/

void				line_parse(t_scene *scn, char **tab);
void				tab_free(char **tab, int len);
void				line_process(t_scene *scn);
void				read_rt(t_scene *scn, char *file);

/*
** parser.c
*/

void				parse_res(t_scene *scn, char **tab);
void				parse_amb(t_scene *scn, char **tab);
void				parse_cam(t_scene *scn, char **tab);
void				parse_light(t_scene *scn, char **tab);

/*
** parse_shapes.c
*/

void				parse_plane(t_scene *scn, char **tab);
void				parse_sphere(t_scene *scn, char **tab);
void				parse_square(t_scene *scn, char **tab);
void				parse_cylinder(t_scene *scn, char **tab);
void				parse_triangle(t_scene *scn, char **tab);

/*
** create_tools.c
*/

t_cam				*new_camera(t_vect view, t_vect vector,
						double fov, int num);
t_light				*new_light(t_vect pos, double ratio, t_color rgb, int num);
void				add_shape(t_shape **lst, t_shape *new);
void				add_light(t_light **lst, t_light *new);
void				add_cam(t_cam **lst, t_cam *new);

/*
** create_shapes.c
*/

t_shape				*new_plane(t_vect pos, t_vect orient, t_color rgb);
t_shape				*new_sphere(t_vect pos, double d, t_color rgb);
t_shape				*new_square(t_vect pos, double d, t_vect orient,
						t_color rgb);
t_shape				*new_cylinder(t_parsecy cy);
t_shape				*new_triangle(t_vect p_1, t_vect p_2, t_vect p_3,
						t_color rgb);

/*
** conversions.c
*/

int					atorgb(char *ptr, t_color *rgb);
int					atocoord(char *ptr, t_vect *vect);
double				deg_to_rad(double deg);
int					atoi_rgb(const char *nptr);
int					create_trgb(t_color rgb);

/*
** vectors.c
*/

double				v_length(t_vect vect);
t_vect				v_norm(t_vect vect);
t_vect				v_refl(t_vect vect, t_vect norm);
t_vect				cross_prod(t_vect u, t_vect v);
t_vect				new_vect(double x, double y, double z);

/*
** math_vect.c
*/

t_vect				v_div(t_vect vect, double num);
t_vect				v_add(t_vect vec_1, t_vect vec_2);
t_vect				v_sub(t_vect vec_1, t_vect vec_2);
t_vect				v_mult(t_vect vect, double num);
double				v_prod(t_vect a, t_vect b);

/*
** math.c
*/

t_vect				get_ray(t_scene *scn, double x, double y);
double				p_dist(t_vect a, t_vect b);
void				min_value(double *a, double *b);

/*
** memory.c
*/
void				free_scene(t_scene *scn);
void				free_cam(t_scene *scn);
void				free_light(t_scene *scn);
int					shape_size(t_shape *lst);
void				free_shape(t_scene *scn);

/*
** utils_amb.c
*/

void				set_reflamb(t_scene *scn, t_shape *shape);
void				set_diff(t_scene *scn, t_shape *shape);
void				set_spec(t_scene *scn);
int					shadow(t_scene scn, t_shape *shape);

#endif

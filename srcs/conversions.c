/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:57:45 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/07 16:08:20 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		atorgb(char *ptr, t_color *color)
{
	int rgb[3];
	int i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = atoi_rgb(ptr);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (1);
		while (ft_isdigit(*ptr))
			ptr++;
		if (*ptr != ',' && *ptr != '\0')
			return (1);
		i++;
		ptr++;
	}
	color->t = 0;
	color->r = rgb[0];
	color->g = rgb[1];
	color->b = rgb[2];
	return (0);
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

double	deg_to_rad(double deg)
{
	return ((deg * M_PI) / 180);
}

int		atoi_rgb(const char *nptr)
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

int		create_trgb(t_color rgb)
{
	int r;
	int g;
	int b;

	r = norm_color(rgb.r) * 255;
	g = norm_color(rgb.g) * 255;
	b = norm_color(rgb.b) * 255;
	return ((int)rgb.t << 24 | r << 16 | g << 8 | b);
}

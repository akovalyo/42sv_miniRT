/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 10:53:47 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/20 13:58:47 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int			ft_atoi_mini(const char *nptr)
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

int		atorgb(char *ptr)
{
	int rgb[3];
	int i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi_mini(ptr);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
		while (ft_isdigit(*ptr))
			ptr++;
		if (*ptr != ',' && *ptr != '\0')
			return (-1);
		i++;
		ptr++;
	}
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

int		main(void)
{
	ft_printf("%d\n", create_trgb(0, 0, 0, 255));
	ft_printf("%d\n", atorgb("0,0,0"));
	return (0);
}

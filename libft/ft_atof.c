/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 09:24:46 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/26 12:06:50 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *nptr)
{
	double	val;
	double	signif;
	int		sign;

	val = 0;
	sign = 1;
	signif = 0.1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		val = 10 * val + *(nptr++) - '0';
	if (*nptr == '.')
	{
		nptr++;
		while (ft_isdigit(*nptr))
		{
			val += (*(nptr++) - '0') * signif;
			signif *= 0.1;
		}
	}
	return (val * sign);
}

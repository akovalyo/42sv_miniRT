/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:38:18 by akovalyo          #+#    #+#             */
/*   Updated: 2020/05/15 12:21:27 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "libft.h"
# include "mlx.h"

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
}					t_data;


int		error(char *message);
int		read_rt(t_data *data, char *file);

#endif
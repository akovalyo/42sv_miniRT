/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalyo <al.kovalyov@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:20:02 by akovalyo          #+#    #+#             */
/*   Updated: 2020/07/07 12:09:19 by akovalyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef MAC
#  define ESCAPE 53
#  define LEFT 123
#  define RIGHT 124
# endif

# ifdef LIN
#  define ESCAPE 65307
#  define LEFT 65361
#  define RIGHT 65363
# endif

#endif

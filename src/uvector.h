/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:27:33 by lkaser            #+#    #+#             */
/*   Updated: 2018/08/31 09:42:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVECTOR_H
# define UVECTOR_H
# include <stdint.h>

typedef struct		s_uvector
{
	uint8_t			*data;
	unsigned		capacity;
	unsigned		length;
	unsigned		width;
}					t_uvector;

void				ft_uvector_init(t_uvector *v, unsigned size);
void				ft_uvector_resize(t_uvector *v, unsigned size);
void				ft_uvector_push(t_uvector *v, void *d);
void				*ft_uvector_pop(t_uvector *v, void *item);
void				*ft_uvector_get(t_uvector *v, unsigned i, char copy);

#endif

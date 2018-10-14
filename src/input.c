/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:33:17 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/13 19:33:18 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <emscripten.h>
#include <emscripten/html5.h>
#include "scop.h"

EM_BOOL	key_down(int type, const EmscriptenKeyboardEvent *key, void *data)
{
	t_scop *scop;

	(void)type;
	scop = data;
	scop->key[(uint8_t)key->key[0]] = 1;
	return (0);
}

EM_BOOL	key_up(int type, const EmscriptenKeyboardEvent *key, void *data)
{
	t_scop *scop;

	(void)type;
	scop = data;
	scop->key[(uint8_t)key->key[0]] = 0;
	return (0);
}

void	handle_input(t_scop *scop)
{
	if (scop->key['w'])
		scop->rot.x += 0.5;
	if (scop->key['s'])
		scop->rot.x -= 0.5;
	if (scop->key['a'])
		scop->rot.y += 0.5;
	if (scop->key['d'])
		scop->rot.y -= 0.5;
	if (scop->key['q'])
		scop->rot.z -= 0.5;
	if (scop->key['e'])
		scop->rot.z += 0.5;
	if (scop->key['j'])
		scop->pos.x -= 0.01;
	if (scop->key['l'])
		scop->pos.x += 0.01;
	if (scop->key['i'])
		scop->pos.y += 0.01;
	if (scop->key['k'])
		scop->pos.y -= 0.01;
	if (scop->key['='])
		scop->pos.z += 0.01;
	if (scop->key['-'])
		scop->pos.z -= 0.01;
}

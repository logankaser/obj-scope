/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:41:32 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/14 13:41:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "scop.h"

EMSCRIPTEN_KEEPALIVE
void	load_obj_from_js(const uint8_t *buff, size_t size)
{
	FILE *tmp;

	tmp = tmpfile();
	fwrite(buff, 1, size, tmp);
	fseek(tmp, 0, SEEK_SET);
	obj_open(tmp);
	fclose(tmp);
}

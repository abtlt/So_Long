/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:19:17 by abertolo          #+#    #+#             */
/*   Updated: 2025/08/28 14:19:19 by abertolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ends_with(const char *s, const char *suf)
{
	size_t	ls;
	size_t	lr;
	size_t	i;

	ls = ft_strlen(s);
	lr = ft_strlen(suf);
	if (lr > ls)
		return (0);
	i = 0;
	while (i < lr && s[ls - lr + i] == suf[i])
		i++;
	if (i == lr)
		return (1);
	return (0);
}

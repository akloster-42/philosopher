/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:53:00 by akloster          #+#    #+#             */
/*   Updated: 2024/11/05 16:07:50 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (true);
	if (!s1 || !s2)
		return (false);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	if (s1[i] == s2[i])
		return (true);
	return (false);
}
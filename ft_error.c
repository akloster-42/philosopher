/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:20:08 by akloster          #+#    #+#             */
/*   Updated: 2024/11/02 22:13:46 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_str(char *str, int fd)
{
	int i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
	write(fd, "\n", 1);
}

int	ft_error(char *msg)
{		
	put_str(msg, STDERR_FILENO);
	return (EXIT_FAILURE);
}
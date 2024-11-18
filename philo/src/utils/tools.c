/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:50:00 by akloster          #+#    #+#             */
/*   Updated: 2024/11/18 22:49:15 by akloster         ###   ########.fr       */
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

int	ft_mod_calloc(t_data *data)
{
	int	i;

	i = -1;
	data->elapsed = malloc(sizeof(long) * data->n_philo);
	if (!data->elapsed)
		return (ft_error("Error: malloc failed"));
	while (++i < data->n_philo)
		data->elapsed[i] = 0;
	return (EXIT_SUCCESS);
}

int	ft_error(char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		write(STDERR_FILENO, &msg[i], 1);
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

static int	overflow(long sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_mod_atoi(char *str)
{
	int		i;
	long	sign;
	long	nb;
	long	temp;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = nb;
		nb = nb * 10 + str[i++] - '0';
		if (temp > nb)
			return (overflow(sign));
	}
	nb = (nb * sign);
	return ((int) nb);
}

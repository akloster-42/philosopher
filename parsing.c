/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:28:12 by akloster          #+#    #+#             */
/*   Updated: 2024/11/08 14:41:23 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_num(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (false);
		}
	}
	return (true);
}

static bool is_overflow(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_mod_atoi(av[i]) == -1)
			return (true);
	}
	return (false);
}

int	parsing(char **av, t_data *data)
{
	int	i;

	i = -1;
	if (!is_num(av))
		return (ft_error("Error: only positive integers accepted"));
	if (is_overflow(av))
		return (ft_error("Error: integer is too large"));
	data->n_philo = ft_mod_atoi(av[1]);
	data->ids = (int *)malloc(sizeof(int) * (data->n_philo + 1));
	if (!data->ids)
		return (ft_error("Error: malloc failed"));
	while (++i < data->n_philo)
		data->ids[i] = 1;
	data->stop = false;
	data->ids[data->n_philo] = 0;
	data->time_die = ft_mod_atoi(av[2]);
	data->time_eat = ft_mod_atoi(av[3]);
	data->time_sleep = ft_mod_atoi(av[4]);
	if (av[5])
		data->n_orbits = ft_mod_atoi(av[5]);
	else
		data->n_orbits = -1;
	return (EXIT_SUCCESS);
}

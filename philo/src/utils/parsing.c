/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:28:12 by akloster          #+#    #+#             */
/*   Updated: 2024/11/19 15:14:24 by akloster         ###   ########.fr       */
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

static bool	is_overflow(char **av)
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

static int	set_constants(char **av, t_data *data)
{
	data->n_philo = ft_mod_atoi(av[1]);
	if (data->n_philo > MAX_PHILO || data->n_philo <= 0)
		return (ft_error("Error: invalid number_of_philosophers"));
	data->time_die = (long) ft_mod_atoi(av[2]);
	if (data->time_die == 0)
		return (ft_error("Error: invalid time_to_die"));
	data->time_eat = (long) ft_mod_atoi(av[3]);
	if (data->time_die == 0)
		return (ft_error("Error: invalid time_to_eat"));
	data->time_sleep = (long) ft_mod_atoi(av[4]);
	if (data->time_die == 0)
		return (ft_error("Error: invalid time_to_sleep"));
	if (av[5])
		data->n_orbit = (long) ft_mod_atoi(av[5]);
	else
		data->n_orbit = -1;
	if (data->n_orbit == 0)
		return (ft_error(
				"Error: invalid number_of_times_each_philosopher_must_eat"));
	return (EXIT_SUCCESS);
}

int	parsing(char **av, t_data *data)
{
	if (!is_num(av))
		return (ft_error("Error: only positive integers accepted"));
	if (is_overflow(av))
		return (ft_error("Error: integer is too large"));
	data->stop = false;
	data->ready = false;
	return (set_constants(av, data));
}

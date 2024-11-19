/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:44:36 by akloster          #+#    #+#             */
/*   Updated: 2024/11/19 16:27:45 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&((data->fork)[i]), NULL))
			return (ft_error("Error: mutex init. failed"));
		++data->n_init_forks;
	}
	if (pthread_mutex_init(data->meal_lock, NULL))
		return (ft_error("Error: mutex init. failed"));
	++data->n_init_locks;
	if (pthread_mutex_init(data->print_lock, NULL))
		return (ft_error("Error: mutex init. failed"));
	++data->n_init_locks;
	if (pthread_mutex_init(data->stop_lock, NULL))
		return (ft_error("Error: mutex init. failed"));
	++data->n_init_locks;
	if (pthread_mutex_init(data->ready_lock, NULL))
		return (ft_error("Error: mutex init. failed"));
	++data->n_init_locks;
	return (EXIT_SUCCESS);
}

static void	thread_cleanup(t_data *data, int n_philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(data->stop_lock);
	data->stop = true;
	pthread_mutex_unlock(data->stop_lock);
	pthread_mutex_lock(data->ready_lock);
	data->ready = true;
	pthread_mutex_unlock(data->ready_lock);
	while (++i < n_philo)
	{
		if (pthread_join((data->philo)[i], NULL))
			ft_error("Error: pthread_join failed");
	}
}

static int	ft_pthread_create(t_data *data, t_table **table)
{
	int		i;

	i = -1;
	init_table(data, *table);
	while (++i < data->n_philo)
	{
		if (pthread_create(&((data->philo)[i])
			, NULL, &philo_routine, (void *) &(*table)[i]))
		{
			thread_cleanup(data, i);
			return (ft_error("Error: pthread_create failed"));
		}
	}
	data->time_start = ft_gettime();
	pthread_mutex_lock(data->ready_lock);
	data->ready = true;
	pthread_mutex_unlock(data->ready_lock);
	if (pthread_create(&data->check_routine
			, NULL, &check_routine, (void *) data))
	{
		pthread_detach(data->check_routine);
		thread_cleanup(data, data->n_philo);
		return (ft_error("Error: pthread_create failed"));
	}
	return (EXIT_SUCCESS);
}

static int	ft_pthread_join(t_data *data)
{
	int		i;

	i = -1;
	if (pthread_join(data->check_routine, NULL))
		return (ft_error("Error: pthread_join failed"));
	while (++i < data->n_philo)
	{
		if (pthread_join((data->philo)[i], NULL))
		{
			return (ft_error("Error: pthread_join failed"));
		}
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data)
{
	t_table	*table;

	table = NULL;
	if (ft_mutex_init(data))
		return (EXIT_FAILURE);
	table = malloc(sizeof(t_table) * data->n_philo);
	if (!table)
		return (ft_error("Error: malloc failed"));
	if (ft_pthread_create(data, &table) || ft_pthread_join(data))
		return (table_free(&table), EXIT_FAILURE);
	return (table_free(&table), EXIT_SUCCESS);
}

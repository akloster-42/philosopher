/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:55 by akloster          #+#    #+#             */
/*   Updated: 2024/11/10 20:48:40 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(t_data *data)
{
	data->philo = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->philo)
		return (ft_error("Error: malloc failed"));
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (ft_error("Error: malloc failed"));
	return (EXIT_SUCCESS);
}

void kill_threads_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&(data->mutex)[STP]);
	pthread_mutex_destroy(&(data->mutex)[PRINT]);
	pthread_mutex_destroy(&(data->mutex)[DL]);
	pthread_mutex_destroy(&(data->mutex)[RW]);
	while (++i < data->n_philo)
	{
		printf("before\n");
		// pthread_detach((data->philo)[i]);
		pthread_mutex_destroy(&(data->fork)[i]);
		printf("after	\n");
	}
}

void    my_free(t_data *data)
{
	if (!data)
		return ;
	kill_threads_mutex(data);
	if (data->ids)
	{
		free(data->ids);
		data->ids = NULL;
	}
	if (data->fork)
	{
		free(data->fork);
		data->fork = NULL;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
}

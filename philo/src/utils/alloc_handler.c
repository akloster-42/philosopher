/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:55 by akloster          #+#    #+#             */
/*   Updated: 2024/11/18 01:30:19 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(t_data *data)
{
	int	i;

	i = -1;
	data->meal_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->meal_lock)
		return (ft_error("Error: malloc failed"));
	data->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->print_lock)
		return (ft_error("Error: malloc failed"));
	data->ready_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->ready_lock)
		return (ft_error("Error: malloc failed"));
	data->stop_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->stop_lock)
		return (ft_error("Error: malloc failed"));
	data->philo = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->philo)
		return (ft_error("Error: malloc failed"));
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (ft_error("Error: malloc failed"));
	data->elapsed = malloc(sizeof(long) * data->n_philo);
	while (++i < data->n_philo)
		data->elapsed[i] = 0;
	if (!data->elapsed)
		return (ft_error("Error: malloc failed"));
	return (EXIT_SUCCESS);
}

void	kill_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(data->meal_lock);
	pthread_mutex_destroy(data->print_lock);
	pthread_mutex_destroy(data->ready_lock);
	pthread_mutex_destroy(data->stop_lock);
	free(data->meal_lock);
	data->meal_lock = NULL;
	free(data->print_lock);
	data->print_lock = NULL;
	free(data->ready_lock);
	data->ready_lock = NULL;
	free(data->stop_lock);
	data->stop_lock = NULL;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->fork)[i]);
}

void	ft_free(t_table **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	my_free(t_data *data)
{
	if (!data)
		return ;
	kill_mutex(data);
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
	if (data->elapsed)
	{
		free(data->elapsed);
		data->elapsed = NULL;
	}
}

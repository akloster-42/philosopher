/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:55 by akloster          #+#    #+#             */
/*   Updated: 2024/11/19 16:46:23 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(t_data *data)
{
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
	return (ft_mod_calloc(data));
}

static void	free_mutex_ptr(pthread_mutex_t **ptr, int *n_locks)
{
	if (!(*ptr))
		return ;
	if (*n_locks)
	{
		pthread_mutex_destroy(*ptr);
		--(*n_locks);
	}
	free(*ptr);
	*ptr = NULL;
}

static void	kill_mutex(t_data *data)
{
	int	i;

	i = -1;
	free_mutex_ptr(&data->meal_lock, &data->n_init_locks);
	free_mutex_ptr(&data->print_lock, &data->n_init_locks);
	free_mutex_ptr(&data->ready_lock, &data->n_init_locks);
	free_mutex_ptr(&data->stop_lock, &data->n_init_locks);
	if (data->fork)
	{
		while (++i < data->n_philo && (data->n_init_forks)-- > 0)
			pthread_mutex_destroy(&(data->fork)[i]);
	}
}

void	table_free(t_table **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	my_free(t_data *data)
{
	kill_mutex(data);
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

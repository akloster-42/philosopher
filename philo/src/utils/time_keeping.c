/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_keeping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:10:09 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 23:28:43 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_stop_bool(t_table *table)
{
	pthread_mutex_lock(table->stop_lock);
	if (table->data->stop == true)
	{
		pthread_mutex_unlock(table->stop_lock);
		return (true);
	}
	pthread_mutex_unlock(table->stop_lock);
	return (false);
}

static bool	end_philo(t_data *data, char *msg, int i)
{
	if (msg)
	{
		pthread_mutex_lock(data->print_lock);
		pthread_mutex_lock(data->stop_lock);
		if (data->stop == false)
			printf(msg, ft_gettime() - data->time_start, i);
		pthread_mutex_unlock(data->stop_lock);
		pthread_mutex_unlock(data->print_lock);
	}
	pthread_mutex_lock(data->stop_lock);
	data->stop = true;
	pthread_mutex_unlock(data->stop_lock);
	return (true);
}

static bool	full_check(t_data *data)
{
	int	i;
	int	full_cnt;

	i = -1;
	full_cnt = 0;
	pthread_mutex_lock(data->stop_lock);
	if (data->stop == true)
	{
		pthread_mutex_unlock(data->stop_lock);
		return (end_philo(data, DIE, i + 1));
	}
	pthread_mutex_unlock(data->stop_lock);
	pthread_mutex_lock(data->meal_lock);
	while (++i < data->n_philo)
	{
		if ((data->elapsed)[i] == -1)
			++full_cnt;
	}
	pthread_mutex_unlock(data->meal_lock);
	if (full_cnt == data->n_philo)
		return (end_philo(data, NULL, 0));
	return (false);
}

static bool	death_check(t_data *data, int i)
{
	long	val;

	pthread_mutex_lock(data->stop_lock);
	if (data->stop == true)
	{
		pthread_mutex_unlock(data->stop_lock);
		return (end_philo(data, DIE, i + 1));
	}
	pthread_mutex_unlock(data->stop_lock);
	pthread_mutex_lock(data->meal_lock);
	val = (data->elapsed)[i];
	if (val == 0 && ft_gettime() - data->time_start > data->time_die)
	{
		pthread_mutex_unlock(data->meal_lock);
		return (end_philo(data, DIE, i + 1));
	}
	else if (val != -1 && val && ft_gettime() - val > data->time_die)
	{
		pthread_mutex_unlock(data->meal_lock);
		return (end_philo(data, DIE, i + 1));
	}
	pthread_mutex_unlock(data->meal_lock);
	return (false);
}

void	*check_routine(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *) ptr;
	while (1)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			if (death_check(data, i) || full_check(data))
				return (NULL);
			ft_usleep(1);
		}
	}
	return (NULL);
}

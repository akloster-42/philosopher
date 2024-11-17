/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:49:57 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 20:58:52 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_data *data, t_table *table)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		
		table[i].data = data;
		table[i].id = i + 1;	
		table[i].meal_lock = data->meal_lock;
		table[i].print_lock = data->print_lock;
		table[i].ready_lock = data->ready_lock;
		table[i].stop_lock = data->stop_lock;
		set_forks(&table[i], data->n_philo);
	}
	while (++i < MAX_PHILO)
		memset(&table[i], 0, sizeof(t_table));
}

void	print_msg(t_data *data, char *msg, int id)
{
	pthread_mutex_lock(data->print_lock);
	if (!get_stop_bool(data))
		printf(msg, ft_gettime() - data->time_start, id);
	pthread_mutex_unlock(data->print_lock);
}

static bool	get_ready_bool(t_data *data)
{
	pthread_mutex_lock(data->ready_lock);
	if (data->ready == true)
	{
		pthread_mutex_unlock(data->ready_lock);
		return (true);
	}
	pthread_mutex_unlock(data->ready_lock);
	return (false);
}

static void	*lone_philo(t_data *data)
{
	print_msg(data, TAKE_FORK, 1);
	ft_usleep(data->time_die);
	print_msg(data, DIE, 1);
	pthread_mutex_lock(data->stop_lock);
	data->stop = true;
	pthread_mutex_unlock(data->stop_lock);
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_table	*table;
	int		n_cycles;

	table = (t_table *) ptr;
	n_cycles = 0;
	while (!get_ready_bool(table->data))
		;
	if (table->data->n_philo == 1)
		return (lone_philo(table->data));
	while (!get_stop_bool(table->data))
	{
		if (n_cycles++ == table->data->n_orbit)
			break ;
		philo_eat(table);
		philo_sleep(table);
		print_msg(table->data, THINK, table->id);
	}
	pthread_mutex_lock(table->meal_lock);
	(table->data->elapsed)[table->id - 1] = -1;
	pthread_mutex_unlock(table->meal_lock);
	return (NULL);
}

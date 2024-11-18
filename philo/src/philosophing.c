/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:49:57 by akloster          #+#    #+#             */
/*   Updated: 2024/11/18 22:38:31 by akloster         ###   ########.fr       */
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
}

void	print_msg(t_table *table, char *msg, int id)
{
	pthread_mutex_lock(table->print_lock);
	if (!get_stop_bool(table))
		printf(msg, ft_gettime() - table->data->time_start, id);
	pthread_mutex_unlock(table->print_lock);
}

static bool	get_ready_bool(t_table *table)
{
	pthread_mutex_lock(table->ready_lock);
	if (table->data->ready == true)
	{
		pthread_mutex_unlock(table->ready_lock);
		return (true);
	}
	pthread_mutex_unlock(table->ready_lock);
	return (false);
}

static void	*lone_philo(t_table *table)
{
	print_msg(table, TAKE_FORK, 1);
	ft_usleep(table->data->time_die);
	print_msg(table, DIE, 1);
	pthread_mutex_lock(table->stop_lock);
	table->data->stop = true;
	pthread_mutex_unlock(table->stop_lock);
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_table	*table;
	int		n_cycles;

	table = (t_table *) ptr;
	n_cycles = 0;
	while (!get_ready_bool(table))
		;
	if (table->data->n_philo == 1)
		return (lone_philo(table));
	while (!get_stop_bool(table))
	{
		if (n_cycles++ == table->data->n_orbit)
			break ;
		philo_eat(table);
		philo_sleep(table);
		print_msg(table, THINK, table->id);
	}
	pthread_mutex_lock(table->meal_lock);
	(table->data->elapsed)[table->id - 1] = -1;
	pthread_mutex_unlock(table->meal_lock);
	return (NULL);
}

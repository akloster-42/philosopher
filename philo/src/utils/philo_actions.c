/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:50:58 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 23:16:00 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_table *table)
{
	pthread_mutex_lock(table->l_fork);
	print_msg(table, TAKE_FORK, table->id);
	pthread_mutex_lock(table->r_fork);
	print_msg(table, TAKE_FORK, table->id);
	print_msg(table, EAT, table->id);
	pthread_mutex_lock(table->meal_lock);
	(table->data->elapsed)[table->id - 1] = ft_gettime();
	pthread_mutex_unlock(table->meal_lock);
	ft_usleep(table->data->time_eat);
}

void	philo_sleep(t_table *table)
{
	pthread_mutex_unlock(table->l_fork);
	pthread_mutex_unlock(table->r_fork);
	print_msg(table, SLEEP, table->id);
	ft_usleep(table->data->time_sleep);
}

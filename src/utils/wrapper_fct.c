/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:26:33 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 21:12:43 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_table *table, int n_philo)
{
	if (table->id % 2 == 0)
	{
		table->l_fork = &(table->data->fork)[table->id - 2];
		table->r_fork = &(table->data->fork)[table->id - 1];
	}
	else if (table->id == 1)
	{
		table->l_fork = &(table->data->fork)[table->id - 1];
		table->r_fork = &(table->data->fork)[n_philo - 1];
	}
	else
	{
		table->l_fork = &(table->data->fork)[table->id - 1];
		table->r_fork = &(table->data->fork)[table->id - 2];
	}
}

long	ft_gettime(void)
{
	struct timeval	tt;

	gettimeofday(&tt, NULL);
	return (tt.tv_sec * 1000 + tt.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = ft_gettime();
	if (start == -1)
		return ;
	while (ft_gettime() - start < time)
		usleep(500);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:49:57 by akloster          #+#    #+#             */
/*   Updated: 2024/11/10 21:24:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	proper_death(t_time *t, t_data *data, bool sleep_death)
{
	(void) sleep_death;
	ft_lock(data, STP);
	if (*t->stop)
		return (ft_unlock(data, STP), true);
	*t->stop = true;
	ft_unlock(data, STP);
	ft_lock(data, PRINT);
	printf(DIE, t->tv.tv_usec, t->id);
	ft_unlock(data, PRINT);
/* 	if (sleep_death)
		usleep(t->die - t->life); */
	// printf("life = %ld\n die = %ld\n prev = %ld\n t = %ld\n\n", t->life, t->die, t->tv_prev.tv_usec, t->tv.tv_usec);
	return (true);
}

static bool	has_died(t_time *t, char *action, t_data *data)
{
	ft_lock(data, STP);
	if (*t->stop)
		return (ft_unlock(data, STP), true);
	ft_unlock(data, STP);
	t->tv_prev = t->tv;
	gettimeofday(&t->tv, NULL);
	if (t->tv.tv_usec < t->tv_prev.tv_usec)
	{
		t->life = t->life + MAX_USEC - t->tv_prev.tv_usec + t->tv.tv_usec + 1;
	}
	else
	{
		t->life = t->life + t->tv.tv_usec - t->tv_prev.tv_usec;
	}
	if (ft_compare(action, SLEEP))
	{
		if (t->life + t->sleep > t->die)
			return (proper_death(t, data, NEED_SLEEP));
		usleep(t->sleep);
		t->life = 0;
	}
	else if (ft_compare(action, EAT))
	{
		if (t->life + t->eat > t->die)
			return (proper_death(t, data, NEED_SLEEP));
		usleep(t->eat);
	}
	else if (t->life > t->die)
		return (proper_death(t, data, NO_SLEEP));
	return (false);
}

static void	print_msg(t_time *t, char *msg, t_data *data)
{
	ft_lock(data, STP);
	if (*t->stop)
	{
		ft_unlock(data, STP);
		return ;
	}
	printf(msg, t->tv.tv_usec, t->id);	
	ft_unlock(data, STP);
}

static void	eat_sleep_die(t_data *data, t_time *t)
{
	while (42)
	{
		ft_lock(data, DL);
		if (has_died(t, "check", data))
			return ;
		pthread_mutex_lock(&(data->fork)[(t->id - 1) % data->n_philo]);
		print_msg(t, TAKE_FORK, data);
		print_msg(t, THINK, data);
		if (has_died(t, THINK, data))
		{
			ft_unlock(data, DL);
			pthread_mutex_lock(&(data->fork)[(t->id - 1) % data->n_philo]);
			return ;
		}
		pthread_mutex_lock(&(data->fork)[(t->id) % data->n_philo]);
		ft_unlock(data, DL);
		print_msg(t, TAKE_FORK, data);
		print_msg(t, EAT, data);
		if (has_died(t, EAT, data))
		{
			pthread_mutex_unlock(&(data->fork)[(t->id - 1) % data->n_philo]);
			pthread_mutex_unlock(&(data->fork)[(t->id) % data->n_philo]);
			return ;
		}
		pthread_mutex_unlock(&(data->fork)[(t->id - 1) % data->n_philo]);
		pthread_mutex_unlock(&(data->fork)[(t->id) % data->n_philo]);
		print_msg(t, SLEEP, data);
		if (has_died(t, SLEEP, data))
		{
			return ;
		}
	}
}

void	*philo_routine(void *ptr)
{
	t_data		*data;
	t_time		t;
	int			i;

	i = -1;
	data = (t_data *)ptr;
	memset(&t, 0, sizeof(t_time));
	t.sleep = (long) data->time_sleep * 1000;
	t.eat = (long) data->time_eat * 1000;
	t.die = (long) data->time_die * 1000;
	t.stop = &data->stop;
	gettimeofday(&t.tv, NULL);
	ft_lock(data, RW);
	while((data->ids)[++i] == 2)
		;
	t.id = i + 1;
	(data->ids)[i] = 2;
	ft_unlock(data, RW);
	eat_sleep_die(data, &t);
	printf("id = %d ------END-----\n", t.id);
	return (NULL);
}


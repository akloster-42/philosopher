/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:44:36 by akloster          #+#    #+#             */
/*   Updated: 2024/11/10 19:30:53 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static int	ft_mutex_destroy(t_data *data, int last)
{
	int	i;

	i - -1;
	while (i < last)
	{
		
	}
} */

/* static int	ft_pthread_detach(t_data *data, int	last)
{
	int	i;

	i = -1;
	while (++i < last)
	{
		if (pthread_detach((data->philo)[i]) != 0)
			return (ft_error("Error: pthread_detach failed"));
	}
	return (EXIT_SUCCESS);
} */

static int	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&((data->fork)[i]), NULL))
			return (ft_error("Error: mutex init. failed"));
	}
	pthread_mutex_init(&(data->mutex)[STP], NULL);
	pthread_mutex_init(&(data->mutex)[PRINT], NULL);
	pthread_mutex_init(&(data->mutex)[DL], NULL);
	pthread_mutex_init(&(data->mutex)[RW], NULL);
	return (EXIT_SUCCESS);
}

static int	ft_pthread_create(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&((data->philo)[i]), NULL, &philo_routine, (void *) data) != 0)
			return (ft_error("Error: pthread_create failed"));
	}
	return (EXIT_SUCCESS);
}

static int	ft_pthread_join(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_join((data->philo)[i], NULL) != 0)
		{
			return (ft_error("Error: pthread_join failed"));
		}
	}
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data)
{
	return (ft_mutex_init(data)
		|| ft_pthread_create(data)
		|| ft_pthread_join(data));
}


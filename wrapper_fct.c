/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:26:33 by akloster          #+#    #+#             */
/*   Updated: 2024/11/10 19:17:51 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock(t_data *data, e_mtx mtx)
{
	pthread_mutex_lock(&(data->mutex)[mtx]);
}

void	ft_unlock(t_data *data, e_mtx mtx)
{
	pthread_mutex_unlock(&(data->mutex)[mtx]);
}

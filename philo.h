/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:11:25 by akloster          #+#    #+#             */
/*   Updated: 2024/11/10 20:29:24 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

#        include <stdio.h> //  <-------------- DELETE
#        include <errno.h>

# ifdef __linux__
#  define TAKE_FORK "%ld %d has taken a fork\n"
#  define EAT "%ld %d is eating\n"
#  define SLEEP "%ld %d is sleeping\n"
#  define THINK "%ld %d is thinking\n"
#  define DIE "%ld %d died\n"
# elif __APPLE__
#  define TAKE_FORK "%d %d has taken a fork\n"
#  define EAT "%d %d is eating\n"
#  define SLEEP "%d %d is sleeping\n"
#  define THINK "%d %d is thinking\n"
#  define DIE "%d %d died\n"
# endif
# define MAX_USEC (long) 999999
# define NEED_SLEEP true
# define NO_SLEEP false

typedef enum e_mtx
{
	STP,
	PRINT,	
	DL,
	RW
}	e_mtx;

typedef struct s_data
{
	int		*ids;
	int		n_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		n_orbits;
	bool		stop;
	pthread_t	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex[4];
}	t_data;

typedef struct s_time
{
	struct timeval	tv;
	struct timeval	tv_prev;
	long		life;
	long		sleep;
	long		eat;
	long		die;
	int		id;
	bool		*stop;
}	t_time;

void	put_str(char *str, int fd);
int	ft_error(char *msg);
int	parsing(char **av, t_data *data);
int	ft_mod_atoi(char *str);
bool	ft_compare(char *s1, char *s2);
void	my_free(t_data *data);
int	alloc_threads(t_data *data);
int	init_philo(t_data *data);
void	*philo_routine(void *data);
void	kill_threads_mutex(t_data *data);
void	ft_lock(t_data *data, e_mtx);
void	ft_unlock(t_data *data, e_mtx);

#endif

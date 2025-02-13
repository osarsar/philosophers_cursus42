/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:57:56 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/29 21:39:54 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_data
{
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	int				nbr_philo;
	int				nbr_must_eat;
	int				count;
	int				death;
	pthread_mutex_t	mx_start;
	pthread_mutex_t	mx_print;
	pthread_mutex_t	mx_death;
	pthread_mutex_t	mx_start_eat;
	struct s_philo	*p;
}	t_data;

typedef struct s_philo
{
	int				tid;
	pthread_t		th;
	pthread_mutex_t	fork;
	long long		start_eat;
	long long		start;
	int				time_ate;
	t_data			*data;
}	t_philo;

void		init_argument(t_data *data, char **av);
int			init_philosopher(t_data *data);
void		*action(void *philo);
void		mx_destroy(t_data *data);
void		merror(t_data *data);
long long	time_now(void);
void		printf_action(t_philo *philosopher, char *str);
int			check_error(char **av);
void		ft_usleep(long long ms);
long int	ft_atoi(const char *str);
void		check_death(t_data *data);
void		init_argument(t_data *data, char **av);
void		init_action(t_philo *philosopher);
int			check_nbr_ate(t_philo *philosopher);
int			action_utils(t_philo *ph);

#endif
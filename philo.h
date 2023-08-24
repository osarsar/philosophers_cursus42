/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:57:56 by osarsar           #+#    #+#             */
/*   Updated: 2023/06/26 23:51:23 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
//--------------------------------struct--------------------------------//

typedef	struct s_data
{
	int				time_to_eat;
	int				time_to_sleep;
	long long		time_to_die;
	int				nbr_philo;
	int				nbr_must_eat;
	int				count;
	int				death;
	pthread_mutex_t mx_start;
	pthread_mutex_t mx_print;
	pthread_mutex_t mx_death;
	struct s_philo	*philosopher;
	
}t_data;

typedef struct s_philo
{
	int				tid;
	pthread_t		thread;
	pthread_mutex_t fork_left;
	pthread_mutex_t fork_right;
	long long		start_eat;
	long long		start;
	int				time_ate;
	t_data			*data;
}t_philo;




//--------------------------------philo.c--------------------------------//

void		init_argument(t_data *data, char **av);
int			init_philosopher(t_data *data);
void		*action(void *philo);

//-----------------------------philo_utils1.c----------------------------//

long int	ft_atoi(const char *str);
void		merror(t_data *data);
long long	time_now(void);
void		printf_action(t_philo *philosopher, char *str);
int			check_error(char **av);

#endif
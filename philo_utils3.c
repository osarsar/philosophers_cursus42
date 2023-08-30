/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 05:13:56 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/29 21:22:21 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death_print(long long time, t_data *data, int i)
{
	time = time_now() - data->p[i].start;
	printf("%lld\t%d %s\n", time, data->p[i].tid, "died");
}

void	check_death(t_data *data)
{
	int			i;
	long long	time;

	time = 0;
	while (1)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->mx_death);
			pthread_mutex_lock(&data->mx_start_eat);
			if ((time_now() - data->p[i].start_eat) > data->time_to_die) 
			{
				pthread_mutex_unlock(&data->mx_start_eat);
				pthread_mutex_lock(&data->mx_print);
				if (data->death != 2)
					check_death_print(time, data, i);
				return ;
				pthread_mutex_unlock(&data->mx_print);
			}
			pthread_mutex_unlock(&data->mx_start_eat);
			pthread_mutex_unlock(&data->mx_death);
			i++;
		}
	}
}

void	init_argument(t_data *data, char **av)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mx_start, NULL);
	pthread_mutex_init(&data->mx_print, NULL);
	pthread_mutex_init(&data->mx_death, NULL);
	pthread_mutex_init(&data->mx_start_eat, NULL);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nbr_must_eat = ft_atoi(av[5]);
	while (i < data->nbr_philo)
	{
		data->p[i].data = data;
		i++;
	}
}

void	init_action(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->data->mx_death);
	philosopher->data->death = 0;
	pthread_mutex_unlock(&philosopher->data->mx_death);
	philosopher->time_ate = 0;
	if ((philosopher->tid % 2) == 0)
		usleep(100);
}

int	check_nbr_ate(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->data->mx_start_eat);
	if (philosopher->data->nbr_must_eat != 0)
	{
		if (philosopher->time_ate >= philosopher->data->nbr_must_eat)
		{
			philosopher->data->death = 2;
			pthread_mutex_unlock(&philosopher->data->mx_start_eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&philosopher->data->mx_start_eat);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:58:12 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/25 04:51:42 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_argument(t_data *data, char **av)
{
	int i;

	i = 0;
	pthread_mutex_init(&data->mx_start, NULL);
	pthread_mutex_init(&data->mx_print, NULL);
	pthread_mutex_init(&data->mx_death, NULL);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nbr_must_eat = ft_atoi(av[5]);
	while (i < data->nbr_philo)
	{
		data->philosopher[i].data = data;
		i++;
	}
}

void	*action(void *philo)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philo;
	philosopher->data->death = 0;
	philosopher->time_ate = 0;
	if ((philosopher->tid % 2) == 0)
		usleep(100);
	while (1)
	{
			pthread_mutex_lock(&philosopher[philosopher->tid - 1].fork);
			printf_action(philosopher, "has taken a fork");
			if(philosopher->data->nbr_philo == 1)
				ft_usleep((philosopher->data->time_to_die * 1000) + 1000);
			pthread_mutex_lock(&philosopher[philosopher->tid % philosopher->data->nbr_philo].fork);
			printf_action(philosopher, "has taken a fork");
			printf_action(philosopher, "is eating");	
			philosopher->start_eat = time_now(); 
			philosopher->time_ate++;
			ft_usleep(philosopher->data->time_to_eat);
			pthread_mutex_unlock(&philosopher[philosopher->tid - 1].fork);
			printf_action(philosopher, "has taken a unlocked fork");
			pthread_mutex_unlock(&philosopher[philosopher->tid % philosopher->data->nbr_philo].fork);
			printf_action(philosopher, "has taken a unlocked fork");
			printf_action(philosopher, "is sleeping");	
			ft_usleep(philosopher->data->time_to_sleep );
			printf_action(philosopher, "is thinking");
			if (philosopher->data->nbr_must_eat != 0)
			{
				if (philosopher->time_ate >= philosopher->data->nbr_must_eat)
				{
					philosopher->data->death = 2;
					return(0);
				}
			}
	}
	return (0);
}

int init_philosopher(t_data *data)
{
	int i;

	i = -1;

	while (++i < data->nbr_philo)
	{
		data->philosopher[i].start_eat = time_now();
		data->philosopher[i].start = time_now();
		data->philosopher[i].tid = i + 1;
		pthread_mutex_init(&(data->philosopher[i].fork), NULL);
		if (pthread_create(&data->philosopher[i].thread, NULL, action, &(data->philosopher[i]))!= 0)
			return (-1);
		pthread_detach(data->philosopher[i].thread);
	}
	
	while (1)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->mx_death);
			if ((time_now() - data->philosopher[i].start_eat) > data->time_to_die) 
			{
				pthread_mutex_lock(&data->mx_print);
				if (data->death != 2)
					printf("%lld\t%d %s\n",  time_now() - data->philosopher[i].start, data->philosopher[i].tid, "died");
				return(0);
				pthread_mutex_unlock(&data->mx_print);	
			}
			pthread_mutex_unlock(&data->mx_death);
			i++;
		}
	}
	return (0);
}

// void mx_destroy(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	pthread_mutex_destroy(&data->mx_death);
// 	pthread_mutex_destroy(&data->mx_print);
// 	pthread_mutex_destroy(&data->mx_print);
// 	while (i < data->nbr_philo)
// 	{
// 		pthread_mutex_destroy(&data->philosopher[i].fork_right);
// 		i++;
// 	}
// }

int main (int ac,  char **av)
{
	(void)ac;
	t_philo	*philosopher;
	t_data	*data;

	if (ac > 6 || ac < 5)
	{		
		printf("ERROR!\n");
		return(1);
	}
	data = malloc(sizeof(t_data)); //free(data)
	if (!data)
		return (0);
	data->count = 0;
	data->death = 0;
	if (check_error(av) == 0)
		merror(data);
	data->nbr_philo = ft_atoi(av[1]);
	data->philosopher = malloc(sizeof(t_philo) * data->nbr_philo); //free(data->philosopher)
	if (!data->philosopher)
	 	return (0);
	init_argument(data, av);
	init_philosopher(data);
	//mx_destroy(data);
}

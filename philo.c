/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:58:12 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/29 21:39:34 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action_utils(t_philo *ph)
{
	printf_action(ph, "is sleeping");
	ft_usleep(ph->data->time_to_sleep);
	printf_action(ph, "is thinking");
	if (!check_nbr_ate(ph))
		return (0);
	return (1);
}

void	*action(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	init_action(ph);
	while (1)
	{
		pthread_mutex_lock(&ph[ph->tid - 1].fork);
		printf_action(ph, "has taken a fork");
		if (ph->data->nbr_philo == 1)
			ft_usleep((ph->data->time_to_die * 1000) + 1000);
		pthread_mutex_lock(&ph[ph->tid % ph->data->nbr_philo].fork);
		printf_action(ph, "has taken a fork");
		printf_action(ph, "is eating");
		pthread_mutex_lock(&ph->data->mx_start_eat);
		ph->start_eat = time_now(); 
		ph->time_ate++;
		pthread_mutex_unlock(&ph->data->mx_start_eat);
		ft_usleep(ph->data->time_to_eat);
		pthread_mutex_unlock(&ph[ph->tid - 1].fork);
		pthread_mutex_unlock(&ph[ph->tid % ph->data->nbr_philo].fork);
		if (action_utils(ph) == 0)
			return (0);
	}
	return (0);
}

int	init_philosopher(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		data->p[i].start_eat = time_now();
		data->p[i].start = time_now();
		data->p[i].tid = i + 1;
		pthread_mutex_init(&(data->p[i].fork), NULL);
		if (pthread_create(&data->p[i].th, NULL, action, &(data->p[i])) != 0)
			return (-1);
		pthread_detach(data->p[i].th);
	}
	check_death(data);
	return (0);
}

void	mx_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mx_death);
	pthread_mutex_destroy(&data->mx_print);
	pthread_mutex_destroy(&data->mx_start);
	pthread_mutex_destroy(&data->mx_start_eat);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->p[i].fork);
		i++;
	}
	if (data->p)
		free(data->p);
	if (data)
		free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac > 6 || ac < 5)
	{
		printf("ERROR!\n");
		return (1);
	}
	if (check_error(av) == 0)
		return (merror(data), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->count = 0;
	data->death = 0;
	data->nbr_philo = ft_atoi(av[1]);
	data->p = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->p)
		return (0);
	init_argument(data, av);
	init_philosopher(data);
	mx_destroy(data);
}

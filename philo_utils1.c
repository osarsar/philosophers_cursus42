/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:56:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/06/25 17:26:10 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *str)
{
	int	i;
	long int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		if (res > 2147483647 || res < -2147483648)
			return(0);
		i++;
	}
	return (res * sign);
}

int check_error(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 0)
			return(0);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = time_now();
	while (time_now() - time < ms)
		usleep(ms / 10);
}

void merror(t_data *data)
{
	printf("ERROR!\n");
	free(data);
	exit(1);
}

long long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void printf_action(t_philo *philosopher, char *str)
{
	pthread_mutex_lock(&philosopher->data->mx_print);
	printf("%lld\t%d %s\n",  time_now() - (long long)philosopher->start, philosopher->tid, str);
	pthread_mutex_unlock(&philosopher->data->mx_print);
}

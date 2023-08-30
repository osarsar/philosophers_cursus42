/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:56:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/29 21:35:29 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 0)
			return (0);
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

void	ft_usleep(long long ms)
{
	long long	time;

	time = time_now();
	while (time_now() <= time + ms)
		usleep(10);
}

void	merror(t_data *data)
{
	printf("ERROR!\n");
	if (data)
		free(data);
	return ;
}

long long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	printf_action(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->data->mx_print);
	printf("%lld\t%d %s\n", time_now() - p->start, p->tid, str);
	pthread_mutex_unlock(&p->data->mx_print);
}

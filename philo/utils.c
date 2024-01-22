/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:00:47 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/22 07:03:38 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	curr_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		return (-1);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	free_all(t_info **args, t_stats ***philos, t_meals **meals)
{
	int	i;

	i = -1;
	if (*philos)
	{
	while (*philos[++i])
		free(philos[i]);
	free(*philos);
	}
	if (*meals)
		free(*meals);
	if (*args)
	i = (*args)->philos_number;
	{
		while (--i)
			pthread_mutex_destroy(&(*args)->forks[i]);
		free(*args);
	}
}

int	error_status(char *err, t_info **args, t_stats ***philos, t_meals **meals)
{
	free_all(args, philos, meals);
	printf("%s\n", err);
	return (0);
}

int	ft_isdigit(char *c)
{
	int	i;

	i = 0;
	if (c[0] == '+')
		i++;
	while (c[i])
	{
		if (c[i] >= '0' && c[i] <= '9')
			i++;
	}
	if (!c[i])
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res);
}

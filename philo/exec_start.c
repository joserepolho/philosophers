/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:47:43 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/04 19:31:21 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action1(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->wrt_eat[1]);
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (philo->args->end || philo->args->eaten
		|| philo->args->philos_number == 1)
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[1]);
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		return (0);
	}
	pthread_mutex_unlock(&philo->args->wrt_eat[1]);
	pthread_mutex_unlock(&philo->args->wrt_eat[3]);
	pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	return (1);
}

int	action2(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (!philo->args->end && !philo->args->eaten)
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		pthread_mutex_lock(&philo->args->wrt_eat[4]);
		if (philo->args->eaten)
		{
			pthread_mutex_unlock(&philo->args->wrt_eat[4]);
			return (0);
		}
		pthread_mutex_unlock(&philo->args->wrt_eat[4]);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("%d %d is sleeping\n",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	}
	ft_wait(philo->args->time_to_sleep, philo);
	return (1);
}

int	action3(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (!philo->args->end && !philo->args->eaten)
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		pthread_mutex_lock(&philo->args->wrt_eat[4]);
		if (philo->args->eaten)
		{
			pthread_mutex_unlock(&philo->args->wrt_eat[4]);
			return (0);
		}
		pthread_mutex_unlock(&philo->args->wrt_eat[4]);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("%d %d is thinking\n",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	}
	return (1);
}

void	action(void *philos)
{
	t_stats	*philo;

	philo = (t_stats *)philos;
	while (1)
	{
		if (!action1(philo))
			return ;
		eat_meal(philo);
		if (!action2(philo))
			return ;
		if (!action3(philo))
			return ;
		usleep(800);
	}
}

int	exec_start(t_info **args, t_stats ***philos)
{
	int	i;

	i = -1;
	while (++i < (*args)->philos_number)
	{
		if (pthread_create(&(*philos)[i]->philo, NULL, (void *)action,
			(*philos)[i]))
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:47:43 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/25 22:54:37 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_meals(void *philos)
{
	int		i;
	t_stats	*philo;

	i = -1;
	philo = (t_stats *)philos;
	while (++i < philo->args->philos_number)
	{
		if (philo->meal->meal_number >= philo->args->meals_to_survive)
		{
			if (i == philo->args->philos_number)
				philo->args->end = 1;
		}
	}
	return (NULL);
}

void	*check_life(void *philos)
{
	t_stats	*philo;

	philo = (t_stats *)philos;
	while (!philo->args->end)
	{
		if (curr_time() - philo->last_meal_time >= philo->args->time_to_die)
		{
			pthread_mutex_lock(&philo->args->wrt_eat[0]);
			printf("\n[%d] %d died",
					curr_time() - philo->args->start_time,
					philo->philo_number + 1);
			philo->args->end = 1;
		}
	}
	return (NULL);
}

void	*action(void *philos)
{
	t_stats	*philo;

	philo = (t_stats *)philos;
	while (!philo->args->end)
	{
		eat_meal(philo);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("\n[%d] %d is sleeping",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		ft_wait(philo->args->time_to_sleep);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("\n[%d] %d is thinking",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	}
	return (NULL);
}

int	exec_start(t_info **args, t_stats ***philos)
{
	int	i;

	i = -1;
	while (++i < (*args)->philos_number)
	{
		(*philos)[i]->last_meal_time = curr_time();
		if (pthread_create(&(*philos)[i]->philo, NULL, action, (*philos)[i]))
			return (0);
		if (pthread_create(&(*philos)[i]->check_life, NULL, check_life,
			(*philos)[i]))
			return (0);
		if ((*args)->meals_to_survive)
		{
			if (pthread_create(&(*philos)[i]->meal->check_meals, NULL,
				check_meals, (*philos)[i]))
				return (0);
		}
	}
	return (1);
}

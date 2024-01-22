/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:47:43 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/22 03:44:34 by joaoribe         ###   ########.fr       */
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
			printf("[%d]\tPhilosopher %d died",
					curr_time() - philo->args->start_time, philo->philo_number);
			philo->args->end = 1;
		}
	}
	return (NULL);
}

void	*action(void *philos)
{
	t_stats	*philo;

	philo = (t_stats *)philos;
	philo->last_meal_time = curr_time();
	while (!philo->args->end)
	{
		eat_meal(philo);
		printf("[%d]\tPhilosopher %d is sleeping",
				curr_time() - philo->args->start_time, philo->philo_number);
		ft_wait(philo->args->time_to_sleep);
		printf("[%d]\tPhilosopher %d is thinking",
				curr_time() - philo->args->start_time, philo->philo_number);
	}
	return (NULL);
}

int	exec_start(t_info **args, t_stats ***philos)
{
	int	i;

	i = -1;
	while (++i < (*args)->philos_number)
	{
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
			if (pthread_detach((*philos)[i]->meal->check_meals))
				return (0);
		}
		if (pthread_detach((*philos)[i]->philo))
			return (0);
		if (pthread_detach((*philos)[i]->check_life))
			return (0);
	}
	return (1);
}

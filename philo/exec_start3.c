/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:58:40 by ametta            #+#    #+#             */
/*   Updated: 2024/01/22 21:07:25 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checking_meal(t_stats	*ph)
{
	int	i;

	i = 0;
	while (i < ph->args->philos_number)
	{
		if (ph->meal->meal_number >= ph->args->meals_to_survive)
		{
			if (i == ph->args->philos_number - 1)
			{
				ph->args->end = 0;
			}
			i++;
		}
		else
			break ;
	}
}

void	*monitor(void *arg)
{
	t_stats	*ph;

	ph = ((t_stats *)arg);
	while (ph->args->end)
	{
		if (curr_time() - ph->last_meal_time >= ph->args->time_to_die)
		{
			printf("[%d]\tPhilosopher %d died",
					curr_time() - ph->args->start_time, ph->philo_number);
			ph->args->end = 0;
		}
		if (ph->args->meals_to_survive
			&& ph->meal->meal_number >= ph->args->meals_to_survive)
			checking_meal(ph);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_stats	*ph;

	ph = ((t_stats *)arg);
	while (ph->args->end)
	{
		eat_meal(ph);
		pthread_mutex_unlock(&ph->args->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->args->forks[ph->right_fork]);
		printf("[%d]\tPhilosopher %d is sleeping",
				curr_time() - ph->args->start_time, ph->philo_number);
		ft_wait(ph->args->time_to_sleep);
		printf("[%d]\tPhilosopher %d is thinking",
				curr_time() - ph->args->start_time, ph->philo_number);
	}
	return (NULL);
}

void	exec_start(t_info **args, t_stats ***philo)
{
	int	i;

	i = 0;
	while (i < (*args)->philos_number)
	{
		(*philo)[i]->last_meal_time = curr_time();
		pthread_create(&(*philo)[i]->philo, NULL, routine,
		(void *)(*philo)[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < (*args)->philos_number)
	{
		pthread_create(&(*philo)[i]->check_life, NULL, monitor,
			(void *)(*philo)[i]);
		i++;
		usleep(100);
	}
}


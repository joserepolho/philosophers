/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:06:34 by dinunes-          #+#    #+#             */
/*   Updated: 2024/01/26 23:31:07 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philo == 1)
	{
		wait_or_die(philo, philo->data->time_to_die);
		printf("%d %d %s", philo->data->time_to_die, philo->philo_id, DIE);
		return ;
	}
	else
	{
			lifecycle(philo);
	}
}

void	lifecycle(t_philo *philo)
{
	while (1)
	{
		if (philo->data->dead || philo->data->full)
		{
			return ;
		}
		forks(philo, 1);
		actions(philo, 1);
		forks(philo, 2);
		actions(philo, 2);
	}
}

void	forks(t_philo *philo, int action)
{
	t_philo	*next_philo;

	if (philo->philo_id < philo->data->number_of_philo)
		next_philo = &philo[1];
	else
		next_philo = &philo[-1 * (philo->data->number_of_philo - 1)];
	if (action == 1)
	{
		if (philo->philo_id < next_philo->philo_id)
		{
			pthread_mutex_lock(philo->fork);
			pthread_mutex_lock(next_philo->fork);
			return ;
		}
		pthread_mutex_lock(next_philo->fork);
		pthread_mutex_lock(philo->fork);
	}
	else if (action == 2)
	{
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(next_philo->fork);
	}
}

void	actions(t_philo *philo, int action)
{
	if (action == 1)
	{
		print_status(philo, FORK);
		print_status(philo, FORK);
		print_status(philo, EAT);
		pthread_mutex_lock(philo->data->food);
		philo->last_meal = get_time() - philo->data->start_time;
		philo->eat_count++;
		pthread_mutex_unlock(philo->data->food);
		wait_or_die(philo, philo->data->time_to_eat);
	}
	else if (action == 2)
	{
		print_status(philo, SLEEP);
		wait_or_die(philo, philo->data->time_to_sleep);
		print_status(philo, THINK);
	}
}

void	wait_or_die(t_philo *philo, time_t time)
{
	time_t	start;
	time_t	now;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(philo->data->life);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(philo->data->life);
			return ;
		}
		pthread_mutex_unlock(philo->data->life);
		now = get_time();
		if (now - start >= time)
			break ;
	}
}

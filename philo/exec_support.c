/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:07:02 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/25 22:48:56 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(int wait_time)
{
	int	start_time;
	int	elapsed_time;

	start_time = curr_time();
	elapsed_time = 0;
	while (elapsed_time < wait_time)
	{
		usleep(500);
		elapsed_time = curr_time() - start_time;
	}
}

void	eat_meal(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	printf("\n[%d] %d has taken a fork",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	printf("\n[%d] %d has taken a fork",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	philo->last_meal_time = curr_time();
	philo->args->eat = 1;
	printf("\n[%d] %d is eating",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
	ft_wait(philo->args->time_to_eat);
	philo->args->eat = 0;
	if (philo->meal)
		philo->meal->meal_number++;
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
}

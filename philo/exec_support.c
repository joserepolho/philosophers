/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:07:02 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/22 04:04:43 by joaoribe         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->forks_mutex[philo->left_fork]);
	printf("[%d]\tPhilosopher %d has taken the left fork",
			curr_time() - philo->args->start_time, philo->philo_number);
	pthread_mutex_lock(&philo->forks_mutex[philo->right_fork]);
	printf("[%d]\tPhilosopher %d has taken the right fork",
			curr_time() - philo->args->start_time, philo->philo_number);
	philo->last_meal_time = curr_time();
	printf("[%d]\tPhilosopher %d is eating",
			curr_time() - philo->args->start_time, philo->philo_number);
	ft_wait(philo->args->time_to_eat);
	philo->meal->meal_number++;
	pthread_mutex_unlock(&philo->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks_mutex[philo->right_fork]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:07:02 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/02 03:23:53 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(int wait_time, t_stats *philo)
{
	int	start_time;
	int	elapsed_time;

	start_time = curr_time();
	elapsed_time = 0;
	while (elapsed_time < wait_time)
	{
		if (philo->args->end)
			return ;
		usleep(500);
		elapsed_time = curr_time() - start_time;
	}
}

void	take_left_fork(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	if (philo->args->end)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		return ;
	}
		printf("%d %d has taken a fork\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);

}

void	take_right_fork(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	if (philo->args->end)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		return ;
	}
	printf("%d %d has taken a fork\n",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
}

int	eat_meal(t_stats *philo)
{
	if (philo->philo_number % 2)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	philo->eating = 1;
	philo->last_meal_time = curr_time();
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	if (!philo->args->end)
	{
		printf("%d %d is eating\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
	}
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	if (!philo->args->end)
		ft_wait(philo->args->time_to_eat, philo);
	if (philo->args->meals_to_survive)
		philo->meal->meal_number++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	return (0);
}

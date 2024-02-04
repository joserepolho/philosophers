/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 00:07:02 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/04 18:55:46 by joaoribe         ###   ########.fr       */
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
		pthread_mutex_lock(&philo->args->wrt_eat[3]);
		pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
		if (philo->args->end || philo->args->eaten)
		{
			pthread_mutex_unlock(&philo->args->wrt_eat[3]);
			pthread_mutex_unlock(&philo->args->wrt_eat[4]);
			return ;
		}
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		usleep(500);
		elapsed_time = curr_time() - start_time;
	}
}

int	take_left_fork(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (philo->args->end || philo->args->eaten)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		return (0);
	}
		printf("%d %d has taken a fork\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	pthread_mutex_unlock(&philo->args->wrt_eat[3]);
	pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	return (1);
}

int	take_right_fork(t_stats *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (philo->args->end || philo->args->eaten)
	{
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		return (0);
	}
	printf("%d %d has taken a fork\n",
			curr_time() - philo->args->start_time, philo->philo_number + 1);
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	pthread_mutex_unlock(&philo->args->wrt_eat[3]);
	pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	return (1);
}

int	eat_meal(t_stats *philo)
{
	int	i;
	int	j;
	
	if (philo->philo_number % 2)
	{
		i = take_left_fork(philo);
		j = take_right_fork(philo);
	}
	else
	{
		j = take_right_fork(philo);
		i = take_left_fork(philo);
	}
	pthread_mutex_lock(&philo->args->wrt_eat[1]);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->args->wrt_eat[1]);
	pthread_mutex_lock(&philo->args->wrt_eat[2]);
	philo->last_meal_time = curr_time();
	pthread_mutex_unlock(&philo->args->wrt_eat[2]);
	pthread_mutex_lock(&philo->args->wrt_eat[0]);
	pthread_mutex_lock(&philo->args->wrt_eat[3]);
	pthread_mutex_lock(&(philo)->args->wrt_eat[4]);
	if (!philo->args->end && !philo->args->eaten)
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
		printf("%d %d is eating\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		pthread_mutex_unlock(&(philo)->args->wrt_eat[4]);
	}
	pthread_mutex_unlock(&philo->args->wrt_eat[0]);
		pthread_mutex_lock(&philo->args->wrt_eat[3]);
	if (!philo->args->end)
	{
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
		ft_wait(philo->args->time_to_eat, philo);
	}
	else
		pthread_mutex_unlock(&philo->args->wrt_eat[3]);
	if (philo->args->meals_to_survive)
	{
		pthread_mutex_lock(&philo->args->wrt_eat[2]);
		philo->meals++;
		pthread_mutex_unlock(&philo->args->wrt_eat[2]);
	}
	philo->eating = 0;
	if (i)
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
	if (j)
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	return (0);
}

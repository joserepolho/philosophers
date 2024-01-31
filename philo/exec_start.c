/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 23:47:43 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/28 04:09:03 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(void *philos)
{
	t_stats	*philo;

	philo = (t_stats *)philos;
	while (1)
	{
		if (philo->args->end)
			return ;
		eat_meal(philo);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("%d %d is sleeping\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
			ft_wait(philo->args->time_to_sleep, philo);
		pthread_mutex_lock(&philo->args->wrt_eat[0]);
		printf("%d %d is thinking\n",
				curr_time() - philo->args->start_time, philo->philo_number + 1);
		pthread_mutex_unlock(&philo->args->wrt_eat[0]);
	}
}

int	exec_start(t_info **args, t_stats ***philos)
{
	int	i;

	i = -1;
	while (++i < (*args)->philos_number)
	{
		(*philos)[i]->last_meal_time = curr_time();
		if (pthread_create(&(*philos)[i]->philo, NULL, (void *)action, (*philos)[i]))
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:26:29 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/04 19:36:13 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fed(t_info **args, t_stats ***philo)
{
	int	i;

	i = 0;
	if ((*args)->meals_to_survive)
	{
		while (i < (*args)->philos_number)
		{
			pthread_mutex_lock(&(*philo)[i]->args->wrt_eat[2]);
			if ((*philo)[i]->meals < (*args)->meals_to_survive)
			{
				pthread_mutex_unlock(&(*philo)[i]->args->wrt_eat[2]);
				return ;
			}
			pthread_mutex_unlock(&(*philo)[i]->args->wrt_eat[2]);
			i++;
		}
		pthread_mutex_lock(&(**philo)->args->wrt_eat[4]);
		(*args)->eaten = 1;
		pthread_mutex_unlock(&(**philo)->args->wrt_eat[4]);
	}
}

void	ft_ded(t_info **args, t_stats ***philo, int i)
{
	pthread_mutex_lock(&(*philo)[i]->args->wrt_eat[1]);
	if ((*args)->end || (*philo)[i]->eating)
	{
		pthread_mutex_unlock(&(*philo)[i]->args->wrt_eat[1]);
		return ;
	}
	else
		pthread_mutex_unlock(&(*philo)[i]->args->wrt_eat[1]);
	pthread_mutex_lock(&(*philo)[i]->args->wrt_eat[3]);
	(*args)->end = 1;
	pthread_mutex_unlock(&(*philo)[i]->args->wrt_eat[3]);
	printf("%d %d died\n",
		curr_time() - (*philo)[i]->args->start_time,
		(*philo)[i]->philo_number + 1);
}

void	if_ded_or_fed(t_info *args, t_stats **philo)
{
	int		i;

	while (!(args->end) && !(args->eaten))
	{
		i = -1;
		while (++i < args->philos_number)
		{
			pthread_mutex_lock(&philo[i]->args->wrt_eat[2]);
			if (curr_time() - philo[i]->last_meal_time >= args->time_to_die)
			{
				pthread_mutex_unlock(&philo[i]->args->wrt_eat[2]);
				pthread_mutex_lock(&philo[i]->args->wrt_eat[1]);
				if (!args->end && !philo[i]->eating)
				{
					pthread_mutex_unlock(&philo[i]->args->wrt_eat[1]);
					ft_ded(&args, &philo, i);
				}
				else
					pthread_mutex_unlock(&philo[i]->args->wrt_eat[1]);
			}
			else
				pthread_mutex_unlock(&philo[i]->args->wrt_eat[2]);
		}
		ft_fed(&args, &philo);
	}
}

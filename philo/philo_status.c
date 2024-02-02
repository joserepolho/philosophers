/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:26:29 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/02 03:32:49 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_ded(t_info **args, t_stats ***philo, int i)
{
    if ((*args)->end || (*args)->eaten || (*philo)[i]->eating)
	{
        return ;
	}
    (*args)->end = 1;
    printf("%d %d died\n",
			curr_time() - (*philo)[i]->args->start_time, (*philo)[i]->philo_number + 1);
}

void	if_ded(t_info *args, t_stats **philo)
{
	int		i;

	while (!(args->end))
	{
		i = -1;
		while (++i < args->philos_number)
		{
			if (curr_time() - philo[i]->last_meal_time >= args->time_to_die)
			{
                if (!args->end && !philo[i]->eating)
                    ft_ded(&args, &philo, i);
            }
		}
	}
}

void	if_full(t_info **args, t_stats ***philo)
{
	int	i;

	while (!((*args)->end))
	{
		i = -1;
		while (++i < (*args)->philos_number)
		{
			if ((*philo)[i]->meal->meal_number >= (*args)->meals_to_survive)
					(*args)->eaten++;
		}
					pthread_mutex_lock(&(*philo)[i]->args->wrt_eat[0]);
		if ((*args)->eaten == (*args)->philos_number)
			(*args)->end = 1;
	}
}

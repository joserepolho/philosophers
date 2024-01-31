/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 21:26:29 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/28 04:03:05 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_ded(t_info **args, t_stats ***philo, int i)
{
    if ((*args)->end || (*args)->eaten || (*philo)[i]->eating)
        return ;
    (*args)->end = 1;
    printf("%d %d died\n",
			curr_time() - (*philo)[i]->args->start_time, (*philo)[i]->philo_number + 1);
}

void	philo_status(t_info *args, t_stats **philo)
{
	int		i;

	while (!(args->end))
	{
		i = 0;
		while (i < args->philos_number)
		{
			if (curr_time() - philo[i]->last_meal_time >= args->time_to_die)
			{
                if (args->end || philo[i]->eating)
                    ft_ded(&args, &philo, i);
            }
			i++;
		}
	}
}
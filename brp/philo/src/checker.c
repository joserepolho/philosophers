/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 05:53:36 by dinunes-          #+#    #+#             */
/*   Updated: 2024/01/27 04:55:46 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	checker(t_table *f)
{
	int		i;

	while (!(f->data->dead) && !(f->data->full))
	{
		i = 0;
		while (i < f->data->number_of_philo)
		{
			if (get_time() - f->data->start_time >= f->philo[i].last_meal + f->data->time_to_die)
				philo_kill(f, i);
			i++;
		}
		if (f->data->times_must_eat != -1)
			philo_full(f);
	}
}

void	philo_kill(t_table *f, int index)
{
	if (f->data->dead || f->data->full)
		return ;
	f->data->dead = 1;
	printf("\033[0;90m%ld	\033[0;91m%d \033[0;0m%s",
		get_time() - f->philo->data->start_time, index + 1, DIE);
}

void	philo_full(t_table *f)
{
	int	i;

	i = 0;
	while (i < f->data->number_of_philo)
	{
		pthread_mutex_lock(f->data->food);
		if (f->philo[i].eat_count < f->data->times_must_eat)
		{
			pthread_mutex_unlock(f->data->food);
			return ;
		}
		pthread_mutex_unlock(f->data->food);
		i++;
	}
	pthread_mutex_lock(f->data->food);
	f->data->full = 1;
	pthread_mutex_unlock(f->data->food);
}

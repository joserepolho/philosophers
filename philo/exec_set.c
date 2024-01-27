/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:27:09 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/19 21:32:22 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(int ac, char **av, t_info **args)
{	
	int	i;

	(*args)->start_time = curr_time();
	if (!(*args)->start_time)
		return (0);
	(*args)->philos_number = ft_atoi(av[1]);
	(*args)->time_to_die = ft_atoi(av[2]);
	(*args)->time_to_eat = ft_atoi(av[3]);
	(*args)->time_to_sleep = ft_atoi(av[4]);
	(*args)->meals_to_survive = 0;
	if (ac == 6)
		(*args)->meals_to_survive = ft_atoi(av[5]);
	(*args)->eat = 0;
	i = 3;
	(*args)->wrt_eat = malloc(i * sizeof(pthread_mutex_t));
	if (!(*args)->wrt_eat)
		return (0);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(*args)->wrt_eat[i], NULL))
			return (0);
	}
	(*args)->end = 0;
	(*args)->forks = malloc((*args)->philos_number * sizeof(pthread_mutex_t));
	if (!(*args)->forks)
		return (0);
	i = -1;
	while (++i < (*args)->philos_number)
	{
		if (pthread_mutex_init(&(*args)->forks[i], NULL))
			return (0);
	}
	return (1);
}

int	exec_set(t_stats ***philos, t_info **args, t_meals **meals)
{
	int	i;

	i = -1;
	while (++i < (*args)->philos_number)
	{
		(*philos)[i] = malloc(sizeof(t_stats));
		(*philos)[i]->meal = (*meals);
		(*philos)[i]->last_meal_time = 0;
		(*philos)[i]->philo_number = i;
		(*philos)[i]->args = (*args);
		(*philos)[i]->left_fork = i;
		if (i + 1 == (*args)->philos_number)
			(*philos)[i]->right_fork = 0;
		else
			(*philos)[i]->right_fork = i + 1;
	}
	return (1);
}

int	curr_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
		return (-1);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}
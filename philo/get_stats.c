/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 02:27:09 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/18 14:07:36 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_m(t_info *stats)
{
	int	i;

	stats->forks_mutex = malloc(stats->philos_number * sizeof(pthread_mutex_t));
	
}

void	get_stats(int ac, char **av, t_info *stats)
{
	int						i;
	static struct timeval	curr_time;
	
	stats->philos_number = ft_atoi(av[1]);
	stats->time_to_die = ft_atoi(av[2]);
	stats->time_to_die = ft_atoi(av[3]);
	stats->time_to_sleep = ft_atoi(av[4]);
	stats->meals_to_survive = 0;
	if (ac == 6)
		stats->meals_to_survive = ft_atoi(av[5]);
	gettimeofday(&curr_time, NULL);
	stats->start_time = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
	stats->forks_mutex = malloc(stats->philos_number * sizeof(pthread_mutex_t));
	if (!stats->forks_mutex)
		return (0);
	i = -1;
	while (++i < stats->philos_number)
		pthread_mutex_init(&stats->forks_mutex[i], NULL);
	
}

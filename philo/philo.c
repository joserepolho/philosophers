/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:58:37 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/18 13:43:25 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_info	*stats;

	if (ac < 5 || ac > 6)
	{
		printf("Error\nOnly 4 or 5 arguments!\n");
		return (0);
	}
	i = 0;
	while (++i < ac)
	{
		if (av[1][0] == '-' || av[1][0] == '0' || !ft_isdigit(av[i]))
		{
			printf("Error\nOnly positive numbers as arguments!");
			return (0);
		}
	}
	stats = malloc(sizeof(t_info));
	if (!stats)
		return (0);
	if (!get_stats(ac, av, &stats))
		return (0);
	return (0);
}

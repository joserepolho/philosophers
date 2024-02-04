/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:58:37 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/04 19:54:48 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_info	*args;
	t_stats	**philos;

	if (ac < 5 || ac > 6)
		return (error_status("Error\n5 or 6 arguments required!\n", 0, 0));
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' || av[i][0] == '0' || !ft_isdigit(av[i]))
			return (error_status("Error\nOnly positive numbers!\n", 0, 0));
	}
	args = malloc(sizeof(t_info));
	if (!args || !get_args(ac, av, &args))
		return (error_status("Error\nFailure getting args!\n", &args, 0));
	philos = malloc(args->philos_number * sizeof(t_stats *));
	if (!philos || !exec_set(&philos, &args))
		return (error_status("Error\nExec initiation failed!\n", &args,
				&philos));
	if (!exec_start(&args, &philos))
		return (error_status("Error\nThread exec failed!\n", &args, &philos));
	if_ded_or_fed(args, philos);
	if (!free_all(&args, &philos))
		return (error_status("Error\nThread join failed!\n", &args, &philos));
	return (0);
}

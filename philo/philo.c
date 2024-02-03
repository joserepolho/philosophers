/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:58:37 by joaoribe          #+#    #+#             */
/*   Updated: 2024/02/03 03:55:52 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(int ac, char **av)
{
	int	i;
	
	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' || av[i][0] == '0' || !ft_isdigit(av[i]))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_info	*args;
	t_stats	**philos;
	t_meals	*meals;

	if (!arg_check(ac, av))
		return (error_status("Error\nArguments failure!\n", 0, 0, 0));
	args = malloc(sizeof(t_info));
	if (!args || !get_args(ac, av, &args))
		return (error_status("Error\nFailure getting args!\n", &args, 0, 0));
	philos = malloc(args->philos_number * sizeof(t_stats *));
	meals = malloc(sizeof(t_meals));
	meals->meal_number = 0;
	if (!philos || !meals || !exec_set(&philos, &args, &meals))
		return (error_status("Error\nExec initiation failed!\n", &args,
				&philos, &meals));
	if (!exec_start(&args, &philos))
		return (error_status("Error\nThread exec failed!\n", &args, &philos,
				&meals));
	if_ded_or_fed(args, philos);
	if (!free_all(&args, &philos, &meals))
		return (error_status("Error\nThread join failed!\n", &args, &philos,
				&meals));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:58:37 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/26 23:04:39 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_info	*args;
	t_stats	**philos;
	t_meals	*meals;

	if (ac < 5 || ac > 6)
		return (error_status("Error\nOnly 4 or 5 arguments!\n", 0, 0, 0));
	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' || av[i][0] == '0' || !ft_isdigit(av[i]))
			return (error_status("Error\nOnly positive numbers as arguments!\n",
					0, 0, 0));
	}
	args = malloc(sizeof(t_info));
	if (!args)
		return (error_status("Error\nMemory allocation failed!\n", &args, 0, 0));
	if (!get_args(ac, av, &args))
		return (error_status("Error\nFailure getting args!\n", &args, 0, 0));
	philos = malloc(args->philos_number * sizeof(t_stats *));
	if (!philos)
		return (error_status("Error\nMemory allocation failed!\n", &args, &philos, 0));
	if (args->meals_to_survive)
	{
		meals = malloc(sizeof(t_meals));
		if (!meals)
			return (error_status("Error\nMemory allocation failed!\n",
					&args, &philos, &meals));
		meals->meal_number = 0;
	}
	else
		meals = 0;
	if (!exec_set(&philos, &args, &meals))
		return (error_status("Error\nExec initiation failed!\n", &args, &philos, &meals));
	exec_start(&args, &philos);
	while (args->end)
		continue ;
	free_all(&args, &philos, &meals);
	return (0);
}

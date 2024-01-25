/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoribe <joaoribe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:44:47 by joaoribe          #+#    #+#             */
/*   Updated: 2024/01/25 22:47:34 by joaoribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_start(t_info **args, t_stats ***philos)
{
	int	i;

	i = 0;
	while (i < (*args)->philos_number)
	{
		if (pthread_create(&(*philos)[i]->))
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:51:32 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 16:40:09 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_proces	**init_proces(t_philo *philo)
{
	t_proces	**proces_for_philo;
	int			i;

	proces_for_philo = malloc(sizeof(t_proces *) * philo->number_of_philo);
	if (!proces_for_philo)
		return (NULL);
	i = 0;
	while (i < philo->number_of_philo)
	{
		proces_for_philo[i] = malloc(sizeof(t_proces));
		if (!proces_for_philo[i])
			return (NULL);
		proces_for_philo[i]->id_of_philo = i;
		proces_for_philo[i]->id_fork = i;
		proces_for_philo[i]->count_eat = 0;
		proces_for_philo[i]->philo = philo;
		proces_for_philo[i]->threead_id = 0;
		proces_for_philo[i]->last_meal = 0;
		proces_for_philo[i]->time_without_food = 0;
		i++;
	}
	return (proces_for_philo);
}

t_philo	*init_philo(char *argv[])
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->number_of_philo = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->eat = -1;
	if (argv[5])
		philo->eat = ft_atoi(argv[5]);
	philo->exit = 0;
	philo->simulatian_run = true;
	return (philo);
}

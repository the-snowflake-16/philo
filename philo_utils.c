/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:47:02 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 16:47:18 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_mtx(t_philo *philo, bool simulatin)
{
	pthread_mutex_lock(&philo->mtx_simulation);
	philo->simulatian_run = simulatin;
	pthread_mutex_unlock(&philo->mtx_simulation);
}

bool	get_simulation_mtx(t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->mtx_simulation);
	if (philo->simulatian_run == true)
		result = true;
	pthread_mutex_unlock(&philo->mtx_simulation);
	pthread_mutex_lock(&philo->mtx_simulation);
	if (philo->simulatian_run == false)
		result = false;
	pthread_mutex_unlock(&philo->mtx_simulation);
	return (result);
}

void	init_table(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_mutex_init(&philo->proceses[i]->fork, NULL);
		i++;
	}
	pthread_mutex_init(&philo->mtx_monitor, NULL);
	pthread_mutex_init(&philo->mtx_write, NULL);
	pthread_mutex_init(&philo->mtx_time, NULL);
	pthread_mutex_init(&philo->mtx_simulation, NULL);
}

void	finish_dinner(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_join(philo->monitor, NULL);
	while (i < philo->number_of_philo)
	{
		pthread_mutex_destroy(&philo->proceses[i]->fork);
		free(philo->proceses[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->mtx_monitor);
	pthread_mutex_destroy(&philo->mtx_write);
	pthread_mutex_destroy(&philo->mtx_time);
	pthread_mutex_destroy(&philo->mtx_simulation);
	free(philo->proceses);
	free(philo);
}

void	init_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		if (i == philo->number_of_philo - 1)
			philo->proceses[i]->next_for = philo->proceses[0];
		else
			philo->proceses[i]->next_for = philo->proceses[i + 1];
		i++;
	}
}

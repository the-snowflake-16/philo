/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:46:49 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 16:47:57 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_philo *philo, int i)
{
	long	current_time;
	long	time_since_meal;

	current_time = get_time_of_day();
	pthread_mutex_lock(&philo->mtx_time);
	time_since_meal = current_time - philo->proceses[i]->last_meal;
	pthread_mutex_unlock(&philo->mtx_time);
	if (time_since_meal > philo->time_die)
	{
		pthread_mutex_lock(&philo->mtx_write);
		printf("%ld %d died\n", current_time - philo->start_time,
			philo->proceses[i]->id_of_philo + 1);
		pthread_mutex_unlock(&philo->mtx_write);
		pthread_mutex_lock(&philo->mtx_monitor);
		philo->exit = 1;
		pthread_mutex_unlock(&philo->mtx_monitor);
		set_simulation_mtx(philo, false);
		return (1);
	}
	return (0);
}

void	*monitor(void *argv)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)argv;
	delay_for_philo(philo->start_time);
	while (get_simulation_mtx(philo))
	{
		i = 0;
		while (i < philo->number_of_philo)
		{
			if (check_philo_death(philo, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

static void	create_and_join_threads(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_create(&philo->proceses[i]->threead_id, NULL, &philo_routine,
			philo->proceses[i]);
		i++;
	}
	j = 0;
	while (j < philo->number_of_philo)
	{
		pthread_join(philo->proceses[j]->threead_id, NULL);
		j++;
	}
}

void	start_dinner(t_philo *philo)
{
	int	i;

	philo->start_time = get_time_of_day() + 100;
	philo->proceses = init_proces(philo);
	i = 0;
	while (i < philo->number_of_philo)
	{
		philo->proceses[i]->last_meal = philo->start_time;
		i++;
	}
	init_table(philo);
	init_fork(philo);
	pthread_create(&philo->monitor, NULL, &monitor, philo);
	create_and_join_threads(philo);
	finish_dinner(philo);
}

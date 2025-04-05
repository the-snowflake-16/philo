/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:11:10 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 16:40:31 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping_thinking(t_proces *proces)
{
	output_message(proces, SLEEPING);
	time_to_sleep(proces->philo->time_sleep);
	output_message(proces, THINKING);
}

void	is_philo_full(t_proces *proces)
{
	int	i;
	int	all_full;

	if (proces->count_eat >= proces->philo->eat)
	{
		pthread_mutex_lock(&proces->philo->mtx_monitor);
		all_full = 1;
		i = 0;
		while (i < proces->philo->number_of_philo)
		{
			if (proces->philo->proceses[i]->count_eat < proces->philo->eat)
			{
				all_full = 0;
				break ;
			}
			i++;
		}
		if (all_full)
		{
			proces->philo->exit = 1;
			set_simulation_mtx(proces->philo, false);
		}
		pthread_mutex_unlock(&proces->philo->mtx_monitor);
	}
}

static void	take_and_release_forks(t_proces *proces)
{
	if (proces->id_of_philo % 2 == 0)
	{
		pthread_mutex_lock(&proces->fork);
		output_message(proces, GET_RIGHT_FORK);
		pthread_mutex_lock(&proces->next_for->fork);
		output_message(proces, GET_LEFT_FORK);
	}
	else
	{
		pthread_mutex_lock(&proces->next_for->fork);
		output_message(proces, GET_LEFT_FORK);
		pthread_mutex_lock(&proces->fork);
		output_message(proces, GET_RIGHT_FORK);
	}
}

void	eating(t_proces *proces)
{
	take_and_release_forks(proces);
	pthread_mutex_lock(&proces->philo->mtx_time);
	proces->last_meal = get_time_of_day();
	proces->count_eat++;
	pthread_mutex_unlock(&proces->philo->mtx_time);
	output_message(proces, EATING);
	if (proces->philo->eat != -1)
		is_philo_full(proces);
	time_to_sleep(proces->philo->time_eat);
	pthread_mutex_unlock(&proces->fork);
	pthread_mutex_unlock(&proces->next_for->fork);
}

void	*philo_routine(void *argv)
{
	t_proces	*proces;

	proces = (t_proces *)argv;
	delay_for_philo(proces->philo->start_time);
	if (proces->id_of_philo % 2 != 0)
		usleep(proces->philo->time_eat / 2 * 1000);
	while (1)
	{
		pthread_mutex_lock(&proces->philo->mtx_monitor);
		if (proces->philo->exit)
		{
			pthread_mutex_unlock(&proces->philo->mtx_monitor);
			break ;
		}
		pthread_mutex_unlock(&proces->philo->mtx_monitor);
		eating(proces);
		sleeping_thinking(proces);
	}
	return (NULL);
}

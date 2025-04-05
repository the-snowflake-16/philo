/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:24:11 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 14:35:01 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_proces *proces, const char *msg)
{
	time_t	time_now;

	if (!proces || !proces->philo || !get_simulation_mtx(proces->philo))
		return ;
	time_now = get_time_of_day() - proces->philo->start_time;
	printf("%ld %d %s\n", time_now, proces->id_of_philo + 1, msg);
}

void	output_message(t_proces *proces, t_status status)
{
	pthread_mutex_lock(&(proces->philo->mtx_write));
	if (!get_simulation_mtx(proces->philo))
	{
		pthread_mutex_unlock(&(proces->philo->mtx_write));
		return ;
	}
	if (status == GET_RIGHT_FORK)
		print_message(proces, "has taken a right fork");
	else if (status == GET_LEFT_FORK)
		print_message(proces, "has taken a left fork");
	else if (status == EATING)
		print_message(proces, "is eating");
	else if (status == SLEEPING)
		print_message(proces, "is sleeping");
	else if (status == THINKING)
		print_message(proces, "is thinking");
	else if (status == RELAXING)
		print_message(proces, "is relaxing");
	pthread_mutex_unlock(&(proces->philo->mtx_write));
}

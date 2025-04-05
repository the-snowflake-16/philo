/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:50:37 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 17:33:12 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	*philo;

	philo = NULL;
	if (parser_input(argc, argv))
		return (EXIT_FAILURE);
	philo = init_philo(argv);
	if (!philo)
		return (EXIT_FAILURE);
	if (philo->number_of_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(philo->time_die * 1000);
		printf("%ld 1 died\n", philo->time_die);
		free(philo);
		return (EXIT_SUCCESS);
	}
	start_dinner(philo);
	return (EXIT_SUCCESS);
}

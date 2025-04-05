/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:42 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 14:43:20 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_count(int num)
{
	if (num <= 0)
	{
		printf("Number of philosophers can't be 0 or negative\n");
		return (1);
	}
	if (num >= 250)
	{
		printf("Number of philosophers can't be more than 250\n");
		return (1);
	}
	return (0);
}

int	invalid_input(char *argv[])
{
	return (check_philo_count(ft_atoi(argv[1])));
}

static void	print_usage(void)
{
	printf("%stry:\n", KMAG);
	printf("./philo <num_of_philo> <time_to_eat> ");
	printf("<time_to_sleep> <time_to_think> ");
	printf("<optional_count_eat>\n");
}

static int	validate_number(char *arg)
{
	if (!is_digit(arg))
	{
		printf("Wrong input: %s is not a valid number\n", arg);
		print_usage();
		return (EXIT_FAILURE);
	}
	if (ft_atoi(arg) == -1)
	{
		printf("%sWrong input: %s too big number ", KRED, arg);
		printf("(should be less than 2147483647)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong input\n");
		print_usage();
		return (EXIT_FAILURE);
	}
	while (i < argc)
	{
		if (validate_number(argv[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (invalid_input(argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

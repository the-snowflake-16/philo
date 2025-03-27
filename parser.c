#include "philo.h"

int invalid_input(char *argv[])
{
    int num_of_philo = ft_atoi(argv[1]);
    if (num_of_philo <= 0)
    {
        printf("Number of philosophers can't be 0 or negative\n");
        return (1);
    }
    else if (num_of_philo >= 250)
    {
        printf("Number of philosophers can't be more than 250\n");
        return (1);
    }
    else
        return (0);
}

int wrong_input(int argc)
{
    if (argc == 5 || argc == 6)
    {
        return (EXIT_SUCCESS);
    }
    printf("Wrong input\n %stry:\n", KMAG);
    printf("./philo <num_of_philo> <time_to_eat> <time_to_sleep> <time_to_think> <optional_count_eat>\n");
    return (EXIT_FAILURE);
}

int parser_input(int argc, char *argv[])
{
    int i = 1;
    if (wrong_input(argc) == EXIT_FAILURE)
    {
        return (EXIT_FAILURE);
    }

    // Проверка всех аргументов на числовое значение
    while (i < argc)
    {
        if (!is_digit(argv[i])) // Убедитесь, что is_digit работает корректно
        {
            printf("Wrong input: %s is not a valid number\n", argv[i]);
            printf("%stry:\n", KMAG);
            printf("./philo <num_of_philo> <time_to_eat> <time_to_sleep> <time_to_think> <optional_count_eat>\n");
            return (EXIT_FAILURE);
        }
        else if (ft_atoi(argv[i]) == -1)
        {
            printf("%sWrong input: %s too big number (should be less than 2147483647)\n", KRED, argv[i]);
            return (EXIT_FAILURE);
        }
        i++;
    }

    // Проверка входных данных по количеству философов
    if (invalid_input(argv))
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}



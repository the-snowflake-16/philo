#include "philo.h"
 
proces_t **init_proces(philo_t *philo)
{
    proces_t **proces_for_philo;
    int i;

    proces_for_philo = malloc(sizeof(proces_t *) * philo->number_of_philo);
    if (!proces_for_philo)
        return NULL;

    for (i = 0; i < philo->number_of_philo; i++) {
        proces_for_philo[i] = malloc(sizeof(proces_t));
        if (!proces_for_philo[i]) 
            return NULL;
    
        proces_for_philo[i]->id_of_philo = i;
        proces_for_philo[i]->id_fork = i;
        proces_for_philo[i]->count_eat = 0;
        proces_for_philo[i]->philo = philo;
        proces_for_philo[i]->threead_id = 0;
        proces_for_philo[i]->last_meal = 0;
        proces_for_philo[i]->time_without_food = 0;
            // if(proces_for_philo[philo->number_of_philo])
            //     proces_for_philo[i] = philo->proceses[0];
            // proces_for_philo[i]->next_for = philo->proceses[i+1];
        // pthread_mutex_init(&philo->proceses[i]->fork, NULL);

    }
    return proces_for_philo;
}

philo_t *init_philo(char *argv[])
{
    philo_t *philo = malloc(sizeof(philo_t));
    if(!philo)
        return NULL;
    philo->number_of_philo = ft_atoi(argv[1]);
    philo->time_die = ft_atoi(argv[2]);
    philo->time_eat = ft_atoi(argv[3]);
    philo->time_sleep = ft_atoi(argv[4]);
    philo->input_count_eat = -1;
    if(argv[5])
        philo->input_count_eat = ft_atoi(argv[5]);
    // philo->start_time = get_time_of_day();
    philo->exit = 0;
    philo->simulatian_run = true;
    return philo;
}

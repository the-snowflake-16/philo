#include "philo.h"


void init_table(philo_t *philo)
{
    int i = 0;

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

void finish_dinner(philo_t *philo)
{
    int i = 0;
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
void init_fork(philo_t *philo)
{
    int i = 0;

    while (i < philo->number_of_philo)
    {
        if (i == philo->number_of_philo - 1)
            philo->proceses[i]->next_for = philo->proceses[0];
        else
            philo->proceses[i]->next_for = philo->proceses[i + 1];
        i++;
    }
}

void sleeping_thinking(proces_t *proces)
{

    int monitor;
    pthread_mutex_lock(&proces->philo->mtx_monitor);
    monitor = proces->philo->exit;
    pthread_mutex_unlock(&proces->philo->mtx_monitor);

    output_message(proces, SLEEPING, monitor);
    time_to_sleep(proces->philo->time_sleep);
    output_message(proces, THINKING, monitor);
    // printf("thinking");
}

void eating(proces_t *proces)
{
    int monitor;
    pthread_mutex_lock(&proces->philo->mtx_monitor);
    monitor = proces->philo->exit;
    pthread_mutex_unlock(&proces->philo->mtx_monitor);
    if(proces->id_of_philo % 2 == 0)
    {
        pthread_mutex_lock(&proces->fork);
        output_message(proces, GET_RIGHT_FORK, monitor);
        pthread_mutex_lock(&proces->next_for->fork);
        output_message(proces, GET_LEFT_FORK, monitor);

    }
    else
    {
        pthread_mutex_lock(&proces->next_for->fork);
        output_message(proces, GET_LEFT_FORK, monitor);
        pthread_mutex_lock(&proces->fork);
        output_message(proces, GET_RIGHT_FORK, monitor);

    }
    pthread_mutex_lock(&proces->philo->mtx_time);
    proces->last_meal = get_time_of_day();
    pthread_mutex_unlock(&proces->philo->mtx_time);
    output_message(proces, EATING, monitor);

    time_to_sleep(proces->philo->time_eat);

    pthread_mutex_unlock(&proces->fork);
    pthread_mutex_unlock(&proces->next_for->fork);
}

void *monitor(void *argv)
{
    bool check;
    philo_t *philo = (philo_t *) argv;
    delay_for_philo(philo->start_time + (philo->time_eat * 3));
    pthread_mutex_lock(&philo->mtx_simulation);
    check = philo->simulatian_run;
    pthread_mutex_unlock(&philo->mtx_simulation);
    int i;
    while (check)
    {
        time_t time_now;
        i = 0;
        while (i < philo->number_of_philo)
        {
            pthread_mutex_lock(&philo->mtx_time);
            time_now = (get_time_of_day() - philo->proceses[i]->last_meal);
            pthread_mutex_unlock(&philo->mtx_time);
            if(time_now >= philo->time_die)
            {
                pthread_mutex_lock(&philo->mtx_monitor);
                philo->exit = 1;
                pthread_mutex_unlock(&philo->mtx_monitor);
                usleep(200);
            }
            i++;
        }
        pthread_mutex_lock(&philo->mtx_simulation);
        check = philo->simulatian_run;
        pthread_mutex_unlock(&philo->mtx_simulation);
    }
    if(!check)
    {
        pthread_mutex_lock(&philo->mtx_write);
        printf("[%ld] philo relaxed\n", get_time_of_day()-philo->start_time);
        pthread_mutex_unlock(&philo->mtx_write);
    }

    return NULL;
}

void *philo_routine(void *argv)
{
    int checker;
    proces_t *proces = (proces_t *)argv;
    delay_for_philo(proces->philo->start_time);
    pthread_mutex_lock(&proces->philo->mtx_monitor);
    checker = proces->philo->exit;
    pthread_mutex_unlock(&proces->philo->mtx_monitor);
    while (!checker)
    {
        if(proces->id_of_philo % 2 == 0)
            usleep(200);
        eating(proces);
        sleeping_thinking(proces);

        pthread_mutex_lock(&proces->philo->mtx_monitor);
        checker = proces->philo->exit;
        pthread_mutex_unlock(&proces->philo->mtx_monitor);
    }
    pthread_mutex_lock(&proces->philo->mtx_simulation);
    proces->philo->simulatian_run = false;
    pthread_mutex_unlock(&proces->philo->mtx_simulation);
    return NULL;
}
void start_dinner(philo_t *philo)
{
    int i = 0;
    int j = 0;
    philo->start_time = get_time_of_day() + (20 * philo->number_of_philo);
    philo->proceses = init_proces(philo);

    init_table(philo);
    init_fork(philo);
    while (i < philo->number_of_philo)
    {
        pthread_create(&philo->proceses[i]->threead_id, NULL, &philo_routine, philo->proceses[i]);
        i++;
    }
    pthread_create(&philo->monitor, NULL, &monitor, philo);

    while (j < philo->number_of_philo)
    {
        pthread_join(philo->proceses[j]->threead_id, NULL);
        j++;
    }
    pthread_join(philo->monitor, NULL); 
    finish_dinner(philo);
}
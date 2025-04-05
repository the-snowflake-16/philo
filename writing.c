#include "philo.h"

#include "philo.h"

void print_message(proces_t *proces, const char *msg)
{
    if (!proces || !proces->philo || !get_simulation_mtx(proces->philo))
        return;

    time_t time_now = get_time_of_day() - proces->philo->start_time;
    printf("%ld %d %s\n", time_now, proces->id_of_philo + 1, msg);
}

void output_message(proces_t *proces, status_t status)
{
    pthread_mutex_lock(&(proces->philo->mtx_write));
    
    if (!get_simulation_mtx(proces->philo)) {
        pthread_mutex_unlock(&(proces->philo->mtx_write));
        return;
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
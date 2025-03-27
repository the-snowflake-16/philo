#include "philo.h"

void print_message(proces_t *proces, char *msg1, char *msg2, status_t status)
{
    if (!proces || !proces->philo)
        return;

    time_t time_now = get_time_of_day() - proces->philo->start_time;
    
    if(status == GET_RIGHT_FORK)
        printf("[%ld] %s %d %s %d\n", time_now, msg1, proces->id_of_philo, msg2, proces->id_of_right_fork);
    else if(status == GET_LEFT_FORK)
        printf("[%ld] %s %d %s %d\n", time_now, msg1, proces->id_of_philo, msg2, proces->id_of_left_fork);
    else if(status == EATING || status == SLEEPING || status == THINKING)
        printf("[%ld] %s %d %s\n", time_now, msg1, proces->id_of_philo, msg2);
}

void output_message(proces_t *proces, status_t status)
{
    // printf("%d", proces->id_of_philo);
    if(status == GET_RIGHT_FORK)
        print_message(proces, "Philo", "takes right fork with id", status);
    if(status == GET_LEFT_FORK)
        print_message(proces, "Philo", "takes left fork with id", status);
    if(status == EATING)
        print_message(proces, "Philo", "is eating", status);
    if(status == SLEEPING)
        print_message(proces, "Philo", "is sleeping", status);
    if(status == THINKING)
        print_message(proces, "Philo", "is thinking", status);
}
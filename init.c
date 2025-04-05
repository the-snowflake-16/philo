#include "philo.h"

void set_simulation_mtx(philo_t *philo, bool simulatin)
{
    pthread_mutex_lock(&philo->mtx_simulation);
    philo->simulatian_run = simulatin;
    pthread_mutex_unlock(&philo->mtx_simulation);
}

bool get_simulation_mtx(philo_t *philo)
{
    bool result;
    pthread_mutex_lock(&philo->mtx_simulation);
    if (philo->simulatian_run == true)
        result = true;
    pthread_mutex_unlock(&philo->mtx_simulation);
    pthread_mutex_lock(&philo->mtx_simulation);
    if (philo->simulatian_run == false)
        result = false;
    pthread_mutex_unlock(&philo->mtx_simulation);
    return result;
}
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

    output_message(proces, SLEEPING);
    time_to_sleep(proces->philo->time_sleep);
    output_message(proces, THINKING);
    // printf("thinking");
}

void eating(proces_t *proces) {
    // Take forks
    if (proces->id_of_philo % 2 == 0) {
        pthread_mutex_lock(&proces->fork);
        output_message(proces, GET_RIGHT_FORK);
        pthread_mutex_lock(&proces->next_for->fork);
        output_message(proces, GET_LEFT_FORK);
    } else {
        pthread_mutex_lock(&proces->next_for->fork);
        output_message(proces, GET_LEFT_FORK);
        pthread_mutex_lock(&proces->fork);
        output_message(proces, GET_RIGHT_FORK);
    }

    // Update meal time
    pthread_mutex_lock(&proces->philo->mtx_time);
    proces->last_meal = get_time_of_day();
    pthread_mutex_unlock(&proces->philo->mtx_time);
    
    output_message(proces, EATING);
    time_to_sleep(proces->philo->time_eat);

    // Release forks
    pthread_mutex_unlock(&proces->fork);
    pthread_mutex_unlock(&proces->next_for->fork);
}

void *monitor(void *argv) {
    philo_t *philo = (philo_t *)argv;
    long current_time;
    long time_since_meal;
    
    // Wait until start time
    delay_for_philo(philo->start_time);
    
    while (get_simulation_mtx(philo)) {
        for (int i = 0; i < philo->number_of_philo; i++) {
            current_time = get_time_of_day();
            
            pthread_mutex_lock(&philo->mtx_time);
            time_since_meal = current_time - philo->proceses[i]->last_meal;
            pthread_mutex_unlock(&philo->mtx_time);
            
            if (time_since_meal > philo->time_die) {
                pthread_mutex_lock(&philo->mtx_write);
                printf("[%ld] philo %d died\n", 
                      current_time - philo->start_time, 
                      philo->proceses[i]->id_of_philo);
                pthread_mutex_unlock(&philo->mtx_write);
                
                pthread_mutex_lock(&philo->mtx_monitor);
                philo->exit = 1;
                pthread_mutex_unlock(&philo->mtx_monitor);
                
                set_simulation_mtx(philo, false);
                return NULL;
            }
        }
        usleep(500); // More frequent checks
    }
    return NULL;
}

void *philo_routine(void *argv) {
    proces_t *proces = (proces_t *)argv;
    
    // Wait until start time
    delay_for_philo(proces->philo->start_time);
    
    // Even philosophers start immediately, odd ones wait half an eat cycle
    if (proces->id_of_philo % 2 != 0)
        usleep(proces->philo->time_eat / 2 * 1000);
    
    while (1) {
        pthread_mutex_lock(&proces->philo->mtx_monitor);
        if (proces->philo->exit) {
            pthread_mutex_unlock(&proces->philo->mtx_monitor);
            break;
        }
        pthread_mutex_unlock(&proces->philo->mtx_monitor);
        
        eating(proces);
        sleeping_thinking(proces);
    }
    return NULL;
}
void start_dinner(philo_t *philo) {
    philo->start_time = get_time_of_day() + 100; // Fixed 100ms startup buffer
    philo->proceses = init_proces(philo);
    
    // Initialize all philosophers first
    for (int i = 0; i < philo->number_of_philo; i++) {
        philo->proceses[i]->last_meal = philo->start_time; // Set initial meal time
    }
    
    init_table(philo);
    init_fork(philo);
    
    // Create monitor FIRST
    pthread_create(&philo->monitor, NULL, &monitor, philo);
    
    // Then create philosophers
    for (int i = 0; i < philo->number_of_philo; i++) {
        pthread_create(&philo->proceses[i]->threead_id, NULL, &philo_routine, philo->proceses[i]);
    }
    
    // Join threads
    for (int j = 0; j < philo->number_of_philo; j++) {
        pthread_join(philo->proceses[j]->threead_id, NULL);
    }
    pthread_join(philo->monitor, NULL);
    finish_dinner(philo);
}
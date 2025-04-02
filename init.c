#include "philo.h"

void stop_dinner(philo_t *philo)
{
    pthread_mutex_t forks[philo->number_of_philo];

    // Destroy mutexes for forks
    for (int i = 0; i < philo->number_of_philo; i++)
        pthread_join(philo->proceses[i]->threead_id, NULL);
    for (int i = 0; i < philo->number_of_philo; i++) {
        pthread_mutex_destroy(&philo->proceses[i]->right_fork);
        pthread_mutex_destroy(&philo->proceses[i]->left_fork);
    }
}
// void time_for_living(proces_t *proces)
// {
//     printf("philo id  last meal %ld\n",proces->philo->proceses[proces->id_of_philo-1]->last_meal - get_time_of_day());
// }
void *monitor(void *varg)
{

    philo_t *philo = (philo_t *)varg;
    if(philo->exit == 1)
    {
        printf("Philo died");
        return NULL;
    }
    
}
void *mytread(void *varg)
{
    proces_t *proces = (proces_t *)varg;

    // printf("OK");

    delay_for_philo(proces->philo->start_time);


        // printf("Philo %d takes fork %d\n", proces->id_of_philo, proces->id_of_left_fork);
        // printf("Philo %d takes fork %d\n", proces->id_of_philo, proces->id_of_left_fork);
    // if (proces->last_meal == 0) proces->last_meal = get_time_of_day() - proces->philo->start_time;

    proces->time_without_food = get_time_of_day() - proces->philo->start_time - proces->last_meal;
    printf("%d time without meal %ld\n",proces->id_of_philo, proces->time_without_food);

    pthread_mutex_lock(&proces->left_fork);
    output_message(proces, GET_LEFT_FORK);
    pthread_mutex_lock(&proces->right_fork);
    output_message(proces, GET_RIGHT_FORK);

    // pthread_mutex_lock(proces->write);
   
    
    // printf("Philo %d is eating\n", proces->id_of_philo);
    output_message(proces, EATING);

    proces->count_eat++;
    time_to_sleep(proces->philo->time_eat);
    proces->last_meal = get_time_of_day();
    // usleep(proces->philo->time_eat);


    printf("%d last meal %ld\n", proces->id_of_philo, proces->last_meal);
    // printf("Philo %d finished eating (%d times)\n", proces->id_of_philo, proces->count_eat);

    pthread_mutex_unlock(&proces->left_fork);
    pthread_mutex_unlock(&proces->right_fork);
    // pthread_mutex_unlock(proces->write);
    output_message(proces, SLEEPING);
    time_to_sleep(proces->philo->time_sleep);

    output_message(proces, THINKING);

    // time_for_living(proces);
    return NULL;
}



void begin_dinner(philo_t *philo)
{
    philo->proceses = init_proces(philo);
    for(int i = 0; i < philo->number_of_philo; i++)
    {
        pthread_mutex_init(&philo->proceses[i]->right_fork, NULL);
        pthread_mutex_init(&philo->proceses[i]->left_fork, NULL);
    }


    // while (!philo->exit)
    // {
    //     if (philo->input_count_eat != -1)
    //     {
            
        //     for (int i = 0; i < philo->input_count_eat; i++) {
        //         for (int i = 0; i < philo->number_of_philo; i++) {
        //             // printf("OK\n");
        //             if (pthread_create(&philo->proceses[i]->threead_id, NULL, &mytread, (void *)philo->proceses[i]) != 0)
        //             {
        //                 perror("Error");
        //                 exit(1);
        //             }
        //         }
        //         for (int i = 0; i < philo->number_of_philo; i++)
        //             pthread_join(philo->proceses[i]->threead_id, NULL);
        //     }
        // }
        // else
        // {
            pthread_create(&philo->monitor, NULL, &monitor, (void *)philo->proceses);
            for (int i = 0; i < philo->number_of_philo; i++) {
                

                pthread_create(&philo->proceses[i]->threead_id, NULL, &mytread, (void *)philo->proceses[i]);
                // pthread_join(philo->monitor, NULL);
            }

            for (int i = 0; i < philo->number_of_philo; i++)
                pthread_join(philo->proceses[i]->threead_id, NULL);
            pthread_join(philo->monitor, NULL);
        // }
        
    // }
            
    stop_dinner(philo);
}



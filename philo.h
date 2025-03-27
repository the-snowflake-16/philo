#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
# include <sys/time.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[45m"
#define KGRN  "\x1B[40m"
#define KYEL  "\x1B[40m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define INT_MAX 2147483647

typedef struct proces proces_t;

typedef struct philo {
    int number_of_philo;
    long int time_die;
    long int time_eat;
    long int time_sleep;
    int input_count_eat;
    bool shoul_eat;
    time_t start_time;
    proces_t **proceses;
    // pthread_mutex_t *fork_mutexes;
} philo_t;

typedef struct proces {
    int id_of_philo;
    int id_of_right_fork;
    int id_of_left_fork;
    int count_eat;
    // bool		simulation_running;
    time_t last_meal;
    pthread_t threead_id;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    // pthread_mutex_t *write;
    philo_t *philo;
} proces_t;

typedef enum status {
    GET_RIGHT_FORK = 1,
    GET_LEFT_FORK = 2,
    EATING = 3,
    SLEEPING = 4,
    THINKING = 5,
    RELAXING = 0,
} status_t;

// typedef struct philos {
//     proces_t *proces;
    
// } philos_t;
void *mytread(void *varg);
// parcer.c
int parser_input(int argc, char *argv[]);

// utils.c
int	ft_atoi(const char *str);
int is_digit(char *s);

// init_philo.c
philo_t *init_philo(char *argv[]);

// // start_tread.c
void create_thread(philo_t *philo);
void begin_dinner(philo_t *philo)
;

// time 
void time_to_sleep(time_t time);
time_t get_time_of_day(void);
void delay_for_philo(time_t time_for_delay);

void	philo_sleep(time_t sleep_time);


proces_t **init_proces(philo_t *philo, pthread_mutex_t *fork_mutexes);
// //writing.c
void output_message(proces_t *proces, status_t status);
// int print_message(long int time, char *msg);
void finish_dinner(proces_t **proces_for_philo, philo_t *philo);
#endif
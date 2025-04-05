/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrychka <thrychka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:27:42 by thrychka          #+#    #+#             */
/*   Updated: 2025/04/05 16:46:02 by thrychka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define KNRM "\x1B[0m"
# define KRED "\x1B[45m"
# define KGRN "\x1B[40m"
# define KYEL "\x1B[40m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define INT_MAX 2147483647

typedef struct s_proces	t_proces;

typedef struct s_philo
{
	int					number_of_philo;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	int					eat;
	time_t				start_time;
	t_proces			**proceses;
	int					exit;
	bool				simulatian_run;
	pthread_mutex_t		mtx_monitor;
	pthread_mutex_t		mtx_time;
	pthread_mutex_t		mtx_write;
	pthread_mutex_t		mtx_relax;
	pthread_mutex_t		mtx_simulation;
	pthread_t			monitor;
}						t_philo;

typedef struct s_proces
{
	int					id_of_philo;
	int					id_fork;
	int					count_eat;
	time_t				last_meal;
	pthread_t			threead_id;
	time_t				time_without_food;
	pthread_mutex_t		fork;
	struct s_proces		*next_for;
	t_philo				*philo;
}						t_proces;

typedef enum e_status
{
	GET_RIGHT_FORK = 1,
	GET_LEFT_FORK = 2,
	EATING = 3,
	SLEEPING = 4,
	THINKING = 5,
	RELAXING = 0,
}						t_status;

// parcer.c
int						parser_input(int argc, char *argv[]);

// utils.c
int						ft_atoi(const char *str);
int						is_digit(char *s);

// init_philo.c
t_philo					*init_philo(char *argv[]);

// time.c
void					time_to_sleep(time_t time);
time_t					get_time_of_day(void);
void					delay_for_philo(time_t time_for_delay);

// init_proces.c
t_proces				**init_proces(t_philo *philo);

// writing.c
void					output_message(t_proces *proces, t_status status);

// init.c
void					start_dinner(t_philo *philo);
bool					get_simulation_mtx(t_philo *philo);
void					set_simulation_mtx(t_philo *philo, bool simulatin);

// action.c
void					*philo_routine(void *argv);

// philo_utils.c
void					init_fork(t_philo *philo);
void					finish_dinner(t_philo *philo);
void					init_table(t_philo *philo);
bool					get_simulation_mtx(t_philo *philo);
void					set_simulation_mtx(t_philo *philo, bool simulatin);

#endif
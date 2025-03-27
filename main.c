#include "philo.h"

int main(int argc, char *argv[])
{
	philo_t *philo;
	philo = NULL;
	if(parser_input(argc, argv))
        return(EXIT_FAILURE);
    philo = init_philo(argv);
    if(!philo)
        return(EXIT_FAILURE);
    begin_dinner(philo);
    finish_dinner(philo->proceses, philo);
    return(EXIT_SUCCESS);
}
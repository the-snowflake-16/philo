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
    start_dinner(philo);
    // // finish_dinner(philo->proceses, philo);
    // free(philo);
    return(EXIT_SUCCESS);
}
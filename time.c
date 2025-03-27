#include "philo.h"

time_t get_time_of_day(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void time_to_sleep(time_t time)
{
    time_t time_stop = get_time_of_day() + time;
    while(get_time_of_day() < time_stop)
        usleep(100);

}
void delay_for_philo(time_t time_for_delay)
{
    while (get_time_of_day() < time_for_delay)
        continue;
}
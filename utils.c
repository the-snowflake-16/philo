#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned  long long int	res;

	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
    if(res >= INT_MAX)
        return(-1);
    else
	    return ((int)res);
}

int is_digit(char *s)
{
    int i = 0;
    while(s[i])
    {
        if(s[i] < '0' || s[i] > '9')
			return(0);
        i++;
    }
	return(1);   
}
     
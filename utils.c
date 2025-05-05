#include "philo.h"

int ft_atoi(char *s)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t get_microtime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
		write(2, "Error getting time\n", 20);
	tv.tv_sec = tv.tv_sec * 1000 + tv.tv_usec / 1000; // convert to milliseconds
	return (tv.tv_sec);
}
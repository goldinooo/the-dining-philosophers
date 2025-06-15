#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	size_t	time;

	pthread_mutex_lock(philo->out_lock);
	time = get_microtime() - philo->start_time;
	if (!is_sim_over(philo))
	{
		printf("%zu %d %s\n", time, philo->id, message);
		fflush(stdout);
	}
	pthread_mutex_unlock(philo->out_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	if (philo->num_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_microtime();
	philo->meals_eaten++;
	philo->is_eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

int	is_sim_over(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(philo->dead_lock);
	result = (*philo->dead == 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (result);
}
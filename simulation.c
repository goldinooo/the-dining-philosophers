#include "philo.h"

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_microtime() - philo->last_meal >= (size_t)philo->time_to_die
		&& philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	check_meals_completed(t_philo_data *program)
{
	int	i;
	int	finished_eating;

	if (program->philos[0].num_to_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < program->philos[0].num_philos)
	{
		pthread_mutex_lock(program->philos[i].meal_lock);
		if (program->philos[i].meals_eaten >= program->philos[i].num_to_eat)
			finished_eating++;
		pthread_mutex_unlock(program->philos[i].meal_lock);
		i++;
	}
	return (finished_eating == program->philos[0].num_philos);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!is_sim_over(philo))
	{
		eat(philo);
		if (is_sim_over(philo))
			break ;
		philo_sleep(philo);
		if (is_sim_over(philo))
			break ;
		think(philo);
	}
	return (NULL);
}

int	create_threads(t_philo_data *program)
{
	int		i;
	pthread_t	monitor;

	i = 0;
	while (i < program->philos[0].num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				routine, &program->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, 
			monitor_death, program) != 0)
		return (1);
	pthread_join(monitor, NULL);
	return (0);
}

void	*monitor_death(void *ptr)
{
	t_philo_data	*program;
	int				i;

	program = (t_philo_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < program->philos[0].num_philos)
		{
			if (check_death(&program->philos[i]))
			{
				print_message(&program->philos[i], "died");
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				return (NULL);
			}
			i++;
		}
		if (check_meals_completed(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_lock);
			return (NULL);
		}
		if (program->dead_flag)
			break ;
		usleep(1000);
	}
	return (NULL);
}
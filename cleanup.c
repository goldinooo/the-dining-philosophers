#include "philo.h"

void	destroy_all(t_philo_data *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < program->philos[0].num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < program->philos[0].num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->out_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
}

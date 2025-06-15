#include "philo.h"

void	init_control_data(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_to_eat = ft_atoi(argv[5]);
	else
		philo->num_to_eat = -1;
}
void init_philos(t_philo *philo, t_philo_data *program, pthread_mutex_t *forks, char **argv)
{
	int i;
	int num_philos;
	size_t start_time;

	num_philos = ft_atoi(argv[1]);
	start_time = get_microtime();
	i = 0;
	while (i < num_philos)
	{
		philo[i].id = i + 1;
		philo[i].is_eating = 0;
		philo[i].meals_eaten = 0;
		init_control_data(&philo[i], argv);
		philo[i].start_time = start_time;
		philo[i].last_meal = start_time;
		philo[i].out_lock = &program->out_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].l_fork = &forks[i];
		if (i == 0) // first philosopher
			philo[i].r_fork = &forks[num_philos - 1];
		else
			philo[i].r_fork = &forks[i - 1];  // left philosopher
		i++;
	}
}
void init_forks(pthread_mutex_t *forks, int num_philos)
{
	int i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
void init_program(t_philo_data *program, t_philo *philos)
{
	program->dead_flag = 0;
	pthread_mutex_init(&program->out_lock, NULL); //pthread_mutex_init will initialize the mutex that is passed to it setting it to a default state
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	program->philos = philos;
}
#include "philo.h"

static int check_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
		return (1);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int validation(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0 || check_arg(argv[1]) == 1)
		return (write(2, "Invalid number of philosophers\n", 31), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 20), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 20), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 22), 1);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_arg(argv[5]) == 1))
		return (write(2, "Invalid number of meals\n", 24), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_data		program;
	t_philo			philos[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (validation(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	if (create_threads(&program) != 0)
		return (destroy_all(&program, forks), 1);
	destroy_all(&program, forks);
	return (0);
}
#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_PHILOS 300

typedef struct s_philo
{
	pthread_t thread;
	int id; // philosopher id AKA number
	int is_eating; // 1 if eating, 0 if not
	int meals_eaten; // number of meals eaten
	int last_meal; // time of last meal
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int start_time;
	int num_philos;
	int num_to_eat; // number of times each philosopher must eat
	int *dead;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *out_lock; // for printing output
	pthread_mutex_t *dead_lock; // for checking if dead
	pthread_mutex_t *meal_lock; // for checking if eating

} t_philo;

typedef struct s_philo_data
{
	int dead_flag; // flag to indicate if any philosopher is dead
	pthread_mutex_t out_lock; // for printing output
	pthread_mutex_t dead_lock; // for checking if dead
	pthread_mutex_t meal_lock; // for checking if eating
	t_philo *philos; // array of philosophers
} t_philo_data;

int ft_atoi(char *s);
int validation(char **argv);
void init_philo(t_philo *philo, int argc, char **argv);
size_t get_microtime(void);

void init_program(t_philo_data *program, t_philo *philos);
void init_forks(pthread_mutex_t *forks, int num_philos);
void init_philos(t_philo *philo, t_philo_data *program, pthread_mutex_t *forks, char **argv);
void init_control_data(t_philo *philo, char **argv); 
#endif
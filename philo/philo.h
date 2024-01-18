#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct 
{

};

typedef struct s_info
{
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_survive;
	int				start_time;
	pthread_mutex_t	*forks_mutex;
}				t_info;

#endif
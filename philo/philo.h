#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_meals
{
	pthread_t		check_meals;
	int				meal_number;
}				t_meals;

typedef struct	s_stats
{
	pthread_t		philo;
	pthread_t		check_life;
	int				philo_number;
	int				last_meal_time;
	int				left_fork;
	int				right_fork;
	struct s_meals	*meal;
	struct s_info	*args;
}				t_stats;

typedef struct	s_info
{
	int				start_time;
	int				end;
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_survive;
	int				eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*wrt_eat;
}				t_info;

int		check_args(int ac, char **av);
int		get_stats(int ac, char **av, t_info *stats);
int		ft_atoi(const char *nptr);
int		ft_isdigit(char *c);
int		get_args(int ac, char **av, t_info **args);
int		curr_time(void);
int		error_status(char *err, t_info **args, t_stats ***philos, t_meals **meals);
int		exec_set(t_stats ***philos, t_info **args, t_meals **meals);
int		exec_start(t_info **args, t_stats ***philos);
void	ft_wait(int wait_time, t_stats *philo);
int		eat_meal(t_stats *philo);
void	free_all(t_info **args, t_stats ***philos, t_meals **meals);
int		check_meals(t_stats *philo);
int		check_life(t_stats *philo);

#endif
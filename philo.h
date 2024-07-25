#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define INPUT_ERR "Correct usage : ./philo nb_philo death_time eat_time sleep_time [nb_meal]"
#define INPUT_ERR2 "Program accepts only numbers"
#define INPUT_ERR3 "0 < nb_philo < 200 | 0 < death_time | 0 < eat_time | 0 < sleep_time"
#define MALLOC_ERR "Malloc error"
#define THREAD_ERR "Thread error"

typedef struct s_mutex
{
	pthread_mutex_t	utensil;
	unsigned int nb_utensil;
}	t_mutex;


typedef struct s_philo
{
	int	total_philo;
	size_t			start;
	pthread_t		thread;
	size_t	nb_philo;
	bool			*death_status;
	int	*meals_eat;
	pthread_mutex_t	*l_utensil;
	pthread_mutex_t	*r_utensil;
	size_t	death_time;
	size_t	eat_time;
	size_t	sleep_time;
	size_t	time_since_eaten;
	pthread_mutex_t *writing;
	pthread_mutex_t *meal;
	int	meals_to_eat;
	int	meals_eaten;
	int eaten_enough;
	bool	ready;
	bool	*start_flag;
	bool	eating;
}	t_philo;

typedef struct s_data
{
	struct timeval	start;
	int	total_philo;
	size_t	death_time;
	size_t	eat_time;
	size_t	sleep_time;
	int	nb_meal;
	size_t	nb_philo;
	t_philo			*philo;
	pthread_t		monitoring;
	pthread_t		monitoring2;
	pthread_mutex_t	writing;
	pthread_mutex_t meal;
	bool			death_status;
	bool	start_flag;
	size_t	start_timing;
	size_t	start_eating;
	bool	full_stomach;
}	t_data;

//fill structs
void	fill_info(t_data *data, char **argv);

//threads functions
void	*function(void *philo);
void	*monit_function(void *data);
void	*monit_function2(void *data);

//Time gestion
int	ft_usleep(size_t milliseconds); //!!ch
void	ft_death(t_philo *philo);
size_t	get_time(t_philo *philo);
size_t	get_time_now(void);

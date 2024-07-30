/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:11:19 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 18:30:32 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INPUT_ERR "Correct usage : ./philo nb_philo \
death_time eat_time sleep_time [nb_meal]"
# define INPUT_ERR2 "Program accepts only positive numbers"
# define INPUT_ERR3 "0 < nb_philo < 200 | 0 < death_time < INT_MAX | \
0 < eat_time < INT_MAX | 0 < sleep_time < INT_MAX [| 0 < nb_meal < INT_MAX]"
# define MALLOC_ERR "Malloc error"
# define MUTEX_ERR "Mutex error"
# define THREAD_ERR "Thread error"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	pthread_t		thread;
	int				total_philo;
	size_t			start;
	size_t			nb_philo;
	bool			*death_status;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			time_since_eaten;
	int				meals_to_eat;
	int				meals_eaten;
	int				eaten_enough;
	bool			ready;
	bool			*start_flag;
	pthread_mutex_t	*l_utensil;
	pthread_mutex_t	*r_utensil;
	pthread_mutex_t	*writing;
	pthread_mutex_t	*meal;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		monitoring;
	pthread_t		monitoring2;
	int				total_philo;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	int				nb_meal;
	bool			death_status;
	bool			start_flag;
	size_t			start_timing;
	size_t			start_eating;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal;
}	t_data;

//check args
int		ft_atoi(const char *str);
bool	check_args(int argc, char **argv);
bool	last_check(t_data *data);

//structs
void	fill_info(t_data *data, char **argv);
void	fill_the_philos(t_data *data, pthread_mutex_t *utensils);
int		destroy_all(t_data *data, pthread_mutex_t *utensils, int condition);
void	destroy_utens(t_data *data, pthread_mutex_t *ut, int num, int con);

//threads functions
void	*philo_function(void *philo);
void	*monit_function(void *data);
void	*monit_function2(void *data);
bool	one_philo(t_philo *philo);
bool	death_and_write(t_philo *philo, int condition);

//Time gestion
int		sleeping_beauty(size_t time);
void	ft_death(t_philo *philo);
size_t	get_time(t_philo *philo);
size_t	get_time_now(void);

#endif
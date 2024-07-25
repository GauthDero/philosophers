#include "philo.h"

size_t	get_time_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

size_t	get_time(t_philo *philo)
{
	struct timeval	now;
	size_t			time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time - philo->start);
}

void	ft_death(t_philo *philo)
{
	*philo->death_status = true;
	pthread_mutex_lock(philo->writing);
	printf("%lu %zu died\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time_now();
	while ((get_time_now() - start) < time)
		usleep(1);
	return (0);
}

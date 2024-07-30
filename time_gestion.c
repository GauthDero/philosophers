/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:11:09 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 18:29:50 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo *philo)
{
	*philo->death_status = true;
	pthread_mutex_lock(philo->writing);
	printf("%lu %zu died\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
}

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

int	sleeping_beauty(size_t time)
{
	size_t	start;

	start = get_time_now();
	while ((get_time_now() - start) < time)
		usleep(1);
	return (0);
}

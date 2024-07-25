/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:42:25 by gdero             #+#    #+#             */
/*   Updated: 2024/07/25 17:50:30 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	one_philo(t_philo *philo)
{
	if (philo->total_philo == 1)
	{
		printf("%lu %zu has taken a fork\n", get_time(philo), philo->nb_philo);
		ft_usleep(philo->death_time);
		return (true);
	}
	return (false);
}

bool	check_death(t_philo *philo)
{
	if (*philo->death_status == true)
		return (true);
	return (false);
}

void	meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->eating = true;
	philo->time_since_eaten = get_time_now();
	philo->meals_eaten++;
	if (philo->meals_eaten >= philo->meals_to_eat)
		philo->eaten_enough = 1;
	pthread_mutex_unlock(philo->meal);
	philo->eating = false;
	ft_usleep(philo->eat_time);
}

bool	death_and_write(t_philo *philo)
{
	if (*philo->death_status == true)
	{
		pthread_mutex_unlock(philo->writing);
		return (true);
	}
	return (false);
}

bool	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_utensil);
	if (*philo->death_status == true)
		return (true);
	pthread_mutex_lock(philo->writing);
	if (death_and_write(philo))
		return (true);
	printf("%lu %zu has taken a fork\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
	if (*philo->death_status == true)
		return (true);
	pthread_mutex_lock(philo->r_utensil);
	if (*philo->death_status == true)
	{
		pthread_mutex_unlock(philo->l_utensil);
		pthread_mutex_unlock(philo->r_utensil);
		return (true);
	}
	pthread_mutex_lock(philo->writing);
	if (death_and_write(philo))
	{
		pthread_mutex_unlock(philo->l_utensil);
		pthread_mutex_unlock(philo->r_utensil);
		return (true);
	}
	printf("%lu %zu has taken a fork\n", get_time(philo), philo->nb_philo);
	printf("%lu %zu is eating\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
	if (*philo->death_status == true)
	{
		pthread_mutex_unlock(philo->l_utensil);
		pthread_mutex_unlock(philo->r_utensil);
		return (true);
	}
	meal_time(philo);
	pthread_mutex_unlock(philo->l_utensil);
	pthread_mutex_unlock(philo->r_utensil);
	return (false);
}

bool	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->writing);
	if (death_and_write(philo))
		return (true);
	printf("%lu %zu is sleeping\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
	ft_usleep(philo->sleep_time);
	return (false);
}

bool	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->writing);
	if (death_and_write(philo))
		return (true);
	printf("%lu %zu is thinking\n", get_time(philo), philo->nb_philo);
	pthread_mutex_unlock(philo->writing);
	return (false);
}

void	*function(void *data_philo)
{
	t_philo	*input;

	input = (t_philo *)data_philo;
	input->ready = true;
	while (*input->start_flag == false)
		usleep(100);
	if (input->nb_philo % 2 == 0)
		usleep(200);
	if (one_philo(input))
		return ((void *)0);
	while (*input->death_status != true)
	{
		if (*input->death_status == true)
			return ((void *)0);
		if (eating(input))
			return ((void *)0);
		if (*input->death_status == true)
			return ((void *)0);
		if (sleeping(input))
			return ((void *)0);
		if (*input->death_status == true)
			return ((void *)0);
		if (thinking(input))
			return ((void *)0);
	}
	return ((void *)0);
}

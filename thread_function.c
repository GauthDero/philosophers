/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:42:25 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 18:30:15 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	philo->time_since_eaten = get_time_now();
	philo->meals_eaten++;
	if (philo->meals_eaten >= philo->meals_to_eat)
		philo->eaten_enough = 1;
	pthread_mutex_unlock(philo->meal);
	sleeping_beauty(philo->eat_time);
}

static bool	print_message(t_philo *philo, char *msg, int condition)
{
	pthread_mutex_lock(philo->writing);
	if (death_and_write(philo, condition))
		return (false);
	printf("%lu %zu %s\n", get_time(philo), philo->nb_philo, msg);
	pthread_mutex_unlock(philo->writing);
	return (true);
}

static bool	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_utensil);
	if (!print_message(philo, FORK, 1))
		return (false);
	if (*philo->death_status == true)
		return (false);
	pthread_mutex_lock(philo->r_utensil);
	if (*philo->death_status == true)
	{
		pthread_mutex_unlock(philo->l_utensil);
		pthread_mutex_unlock(philo->r_utensil);
		return (false);
	}
	if (!print_message(philo, FORK, 2))
		return (false);
	if (!print_message(philo, EAT, 2))
		return (false);
	meal_time(philo);
	pthread_mutex_unlock(philo->l_utensil);
	pthread_mutex_unlock(philo->r_utensil);
	return (true);
}

static bool	sleeping(t_philo *philo)
{
	if (!print_message(philo, SLEEP, 0))
		return (false);
	sleeping_beauty(philo->sleep_time);
	return (true);
}

void	*philo_function(void *data_philo)
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
		if (!eating(input))
			return ((void *)0);
		if (*input->death_status == true)
			return ((void *)0);
		if (!sleeping(input))
			return ((void *)0);
		if (*input->death_status == true)
			return ((void *)0);
		if (!print_message(input, THINK, 0))
			return ((void *)0);
	}
	return ((void *)0);
}

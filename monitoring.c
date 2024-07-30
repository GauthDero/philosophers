/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:10:59 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 17:29:35 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_and_write(t_philo *philo, int condition)
{
	if (*philo->death_status == true)
	{
		pthread_mutex_unlock(philo->writing);
		if (condition == 1)
			pthread_mutex_unlock(philo->l_utensil);
		if (condition == 2)
		{
			pthread_mutex_unlock(philo->l_utensil);
			pthread_mutex_unlock(philo->r_utensil);
		}
		return (true);
	}
	return (false);
}

void	*monit_function2(void *data)
{
	t_data	*input;
	int		index;

	input = (t_data *)data;
	while (input->start_flag == false)
		usleep(500);
	usleep(1000);
	while (1)
	{
		index = 0;
		while (index < input->total_philo)
		{
			if (input->death_status == true)
				return ((void *)0);
			pthread_mutex_lock(&input->meal);
			if (((get_time_now()) - input->philo[index].time_since_eaten) \
			>= input->death_time)
				ft_death(&input->philo[index]);
			pthread_mutex_unlock(&input->meal);
			index++;
		}
	}
}

static void	eating_loop(t_data *data)
{
	int	nb_meals;
	int	index;

	while (1)
	{
		if (data->nb_meal != -2)
		{
			nb_meals = 0;
			index = 0;
			while (index < data->total_philo)
			{
				if (data->philo[index].eaten_enough == 1)
					nb_meals++;
				index++;
			}
			if (nb_meals == data->total_philo)
				data->death_status = true;
		}
		if (data->death_status == true)
			return ;
	}
}

static void	initiate_timers_and_simu(t_data *data, int counter)
{
	int	index;

	if (counter == data->total_philo)
	{
		index = 0;
		data->start_timing = get_time_now();
		data->start_eating = get_time_now();
		while (index < data->total_philo)
		{
			data->philo[index].start = data->start_timing;
			data->philo[index].time_since_eaten = data->start_eating;
			index++;
		}
		data->start_flag = true;
	}
}

void	*monit_function(void *data)
{
	t_data	*input;
	int		index;
	int		counter;

	input = (t_data *)data;
	while (input->start_flag == false)
	{
		index = 0;
		counter = 0;
		while (index < input->total_philo)
		{
			if (input->philo[index].ready == true)
				counter++;
			index++;
		}
		initiate_timers_and_simu(input, counter);
	}
	eating_loop(input);
	return ((void *)0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:30:35 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 17:27:46 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_info(t_data *data, char **argv)
{
	data->start_flag = false;
	data->death_status = false;
	data->total_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -2;
}

void	fill_the_philos(t_data *data, pthread_mutex_t *utensils)
{
	int	index;

	index = 0;
	while (index < data->total_philo)
	{
		data->philo[index].ready = false;
		data->philo[index].start_flag = &data->start_flag;
		data->philo[index].nb_philo = index + 1;
		data->philo[index].death_status = &data->death_status;
		data->philo[index].death_time = data->death_time;
		data->philo[index].eat_time = data->eat_time;
		data->philo[index].sleep_time = data->sleep_time;
		data->philo[index].writing = &data->writing;
		data->philo[index].meal = &data->meal;
		data->philo[index].total_philo = data->total_philo;
		data->philo[index].r_utensil = &utensils[index];
		data->philo[index].meals_to_eat = data->nb_meal;
		data->philo[index].meals_eaten = 0;
		data->philo[index].eaten_enough = 0;
		if (index == 0)
			data->philo[index].l_utensil = &utensils[data->total_philo - 1];
		else
			data->philo[index].l_utensil = &utensils[index - 1];
		index++;
	}
}

int	destroy_all(t_data *data, pthread_mutex_t *utensils, int condition)
{
	int	index;

	index = 0;
	if (condition == 1 || condition == 3)
	{
		free(data->philo);
		if (condition == 1)
			printf("%s\n", MALLOC_ERR);
		return (1);
	}
	while (index < data->total_philo)
	{
		pthread_mutex_destroy(&utensils[index]);
		index++;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->meal);
	free(data->philo);
	free(utensils);
	if (condition == 2)
	{
		printf("%s\n", THREAD_ERR);
		return (1);
	}
	return (0);
}

void	destroy_utens(t_data *data, pthread_mutex_t *ut, int num, int con)
{
	int	index;

	index = 0;
	while (index < num)
	{
		pthread_mutex_destroy(&ut[index]);
		index++;
	}
	free(ut);
	printf("%s\n", MUTEX_ERR);
	if (con == 1)
		return ;
	pthread_mutex_destroy(&data->writing);
	return ;
}

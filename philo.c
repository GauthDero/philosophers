/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:11:30 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 17:44:05 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_t	init_philo(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, philo_function, philo) != 0)
		return (NULL);
	return (tid);
}

static bool	initiate_threads(t_data *data)
{
	int	index;

	index = 0;
	if (pthread_create(&data->monitoring, NULL, monit_function, data) != 0)
		return (false);
	if (pthread_create(&data->monitoring2, NULL, monit_function2, data) != 0)
		return (false);
	while (index < data->total_philo)
	{
		data->philo[index].thread = init_philo(&data->philo[index]);
		if (!data->philo[index].thread)
			return (false);
		index++;
	}
	if (pthread_join(data->monitoring, NULL) != 0)
		return (false);
	if (pthread_join(data->monitoring2, NULL) != 0)
		return (false);
	return (true);
}

static bool	init_mutexes(t_data *data, pthread_mutex_t *utensils)
{
	int	i;

	i = 0;
	while (i < data->total_philo)
	{
		if (pthread_mutex_init(&utensils[i], NULL) != 0)
		{
			destroy_utens(data, utensils, i, 1);
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&data->writing, NULL) != 0)
	{
		destroy_utens(data, utensils, i, 1);
		return (false);
	}
	if (pthread_mutex_init(&data->meal, NULL) != 0)
	{
		destroy_utens(data, utensils, i, 0);
		return (false);
	}
	return (true);
}

static bool	check_everything(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s\n", INPUT_ERR);
		return (false);
	}
	if (!check_args(argc, argv))
	{
		printf("%s\n", INPUT_ERR2);
		return (false);
	}
	fill_info(data, argv);
	if (!last_check(data))
	{
		printf("%s\n", INPUT_ERR3);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data			data;
	int				index;
	pthread_mutex_t	*utensils;

	index = 0;
	if (!check_everything(argc, argv, &data))
		return (1);
	data.philo = malloc((data.total_philo + 1) * sizeof(t_philo));
	if (!data.philo)
		return (printf("%s\n", MALLOC_ERR));
	utensils = malloc((data.total_philo + 1) * sizeof(pthread_mutex_t));
	if (!utensils)
		return (destroy_all(&data, utensils, 1));
	if (!init_mutexes(&data, utensils))
		return (destroy_all(&data, utensils, 3));
	fill_the_philos(&data, utensils);
	if (!initiate_threads(&data))
		return (destroy_all(&data, utensils, 2));
	while (index < data.total_philo)
	{
		if (pthread_join(data.philo[index].thread, NULL) != 0)
			return (destroy_all(&data, utensils, 2));
		index++;
	}
	return (destroy_all(&data, utensils, 0));
}

// !! timings
#include "philo.h"

bool	is_digit_philo(char *string)
{
	int	index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] < 48 || string[index] > 57)
			return (false);
		index++;
	}
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	index;

	index = 1;
	while (index < argc)
	{
		if (!is_digit_philo(argv[index]))
			return (false);
		index++;
	}
	return (true);
}

bool	last_check(t_data *data)
{
	if (data->total_philo < 1 || data->total_philo > 200)
		return (false);
	if (data->death_time < 1)
		return (false);
	if (data->eat_time < 1)
		return (false);
	if (data->sleep_time < 1)
		return (false);
	return (true);
}

pthread_t	init_philo(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, function, philo) != 0)
		return (NULL);
	return (tid);
}

void	fill_the_philos(t_data *data, pthread_mutex_t *utensils)
{
	int	index;

	index = 0;
	while (index < data->total_philo)
	{
		data->philo[index].eating = false;
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

bool	initiate_threads(t_data *data)
{
	int	index;

	index = 0;
	pthread_create(&data->monitoring, NULL, monit_function, data);
	pthread_create(&data->monitoring2, NULL, monit_function2, data);
	while (index < data->total_philo)
	{
		data->philo[index].thread = init_philo(&data->philo[index]);
		if (!data->philo[index].thread)
			return (false);
		index++;
	}
	//pthread_detach(data->monitoring); //SAIS PAS SI IL FAUT
	pthread_join(data->monitoring, NULL); //idem
	pthread_join(data->monitoring2, NULL);
	return (true);
}

void	init_mutexes(t_data *data, pthread_mutex_t *utensils)
{
	int	i;

	i = 0;
	while (i < data->total_philo)
	{
		pthread_mutex_init(&utensils[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	pthread_mutex_t	*utensils;

	data.start_flag = false;
	if (argc != 5 && argc != 6)
		return (printf("%s\n", INPUT_ERR));
	if (!check_args(argc, argv))
		return (printf("%s\n", INPUT_ERR2));
	fill_info(&data, argv);
	if (!last_check(&data))
		return (printf("%s\n", INPUT_ERR3));
	data.philo = malloc((data.total_philo + 1) * sizeof(t_philo));
	if (!data.philo)
		return (printf("%s\n", MALLOC_ERR));
	utensils = malloc((data.total_philo + 1) * sizeof(pthread_mutex_t));
	if (!utensils)
	{
		free(data.philo);
		return (printf("%s\n", MALLOC_ERR));
	}
	init_mutexes(&data, utensils);
	data.death_status = false;
	pthread_mutex_init(&data.writing, NULL);
	pthread_mutex_init(&data.meal, NULL);
	fill_the_philos(&data, utensils);
	if (!initiate_threads(&data))
	{
		free(data.philo);
		free(utensils);
		return (printf("%s\n", THREAD_ERR));
	}
	int j = 0;
	while (j <data.total_philo) //Etrangement, si on enleve, ca passe
	{
		if (pthread_join(data.philo[j].thread, NULL) != 0) //!!! FREES
			return (-1);
		j++;
	}
	j = 0;
	while (j < data.total_philo)
	{
		pthread_mutex_destroy(&utensils[j]);
		j++;
	}
	pthread_mutex_destroy(&data.writing);
	pthread_mutex_destroy(&data.meal);
	free(data.philo);
	free(utensils);
	return (0);
}


//pas bien capte pthread_join - detach


//TOUT PROTEGER
//attention ATOI quand > int max

//Revoir toutes les conditions de mutexlock, faut tout delocker absolument sinon loop infini

//P-E faire une fonction write

//Faut pthread_detach pour kill les threads ?
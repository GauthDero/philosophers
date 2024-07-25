#include "philo.h"

void	unlocking_mutexes(t_data *data)
{
	pthread_mutex_unlock(&data->writing);
	pthread_mutex_unlock(&data->meal);
}
void	*monit_function2(void *data)
{
	t_data	*input;
	int	index;

	input = (t_data *)data;
	while (input->start_flag == false)
		usleep(500);
	//ft_usleep(input->death_time);
	usleep(1000);//Faut attendre que tous soient partis
	while (1)
	{
		index = 0;
		while (index < input->total_philo)
		{
			if (input->full_stomach == true)
				return ((void *)0);
			pthread_mutex_lock(&input->meal);
			if (((get_time_now()) - input->philo[index].time_since_eaten) >= input->death_time && input->philo[index].eating != true)// && !pthread_mutex_lock(&input->meal))
			{
				printf("%lu first timing, %lu second timing\n", get_time_now() - input->philo[index].time_since_eaten, get_time_now() - input->start_eating);
				ft_death(&input->philo[index]);
				pthread_mutex_unlock(&input->meal);
				return ((void *)0);
			}
			pthread_mutex_unlock(&input->meal);
			index++;
		}
	}
}

void	*monit_function(void *data)
{
	t_data	*input;
	int		nb_meals;
	int		index;
	int	counter;

	input = (t_data *)data;
	input->full_stomach = false;
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
		if (counter == input->total_philo)
		{
			index = 0;
			input->start_timing = get_time_now();
			input->start_eating = get_time_now();
			while (index < input->total_philo)
			{
				input->philo[index].start = input->start_timing;
				input->philo[index].time_since_eaten = input->start_eating;
				index++;
			}
			input->start_flag = true;
		}
	}
	while (1)
	{
		if (input->nb_meal != -1)
		{
			nb_meals = 0;
			index = 0;
			while (index < input->total_philo)
			{
				if (input->philo[index].eaten_enough == 1)
					nb_meals++;
				index++;
			}
			if (nb_meals == input->total_philo)
			{
				input->death_status = true;
				input->full_stomach = true;
				unlocking_mutexes(input);
				// pthread_mutex_unlock(&input->writing);
				// pthread_mutex_unlock(&input->meal);
			}
		}
		if (input->death_status == true)
			return ((void *)0);
	}
}

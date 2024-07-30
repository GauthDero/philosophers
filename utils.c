/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:20:31 by gdero             #+#    #+#             */
/*   Updated: 2024/07/30 18:31:02 by gdero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		neg;
	long	result;

	neg = 1;
	result = 0;
	while (*str == 32 || ((*str > 8 && *str < 14)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = neg * -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		result = 10 * result + (*str - '0');
		str++;
	}
	if (result == 2147483648 && neg == -1)
		return (-2147483648);
	if (result > INT_MAX)
		return (-1);
	return (result * neg);
}

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
	if (data->death_time < 1 || data->death_time > INT_MAX)
		return (false);
	if (data->eat_time < 1 || data->eat_time > INT_MAX)
		return (false);
	if (data->sleep_time < 1 || data->sleep_time > INT_MAX)
		return (false);
	if (data->nb_meal == -1 || data->nb_meal == 0)
		return (false);
	return (true);
}

bool	one_philo(t_philo *philo)
{
	if (philo->total_philo == 1)
	{
		printf("%lu %zu %s\n", get_time(philo), philo->nb_philo, FORK);
		sleeping_beauty(philo->death_time);
		return (true);
	}
	return (false);
}

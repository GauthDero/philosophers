/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdero <gdero@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:30:35 by gdero             #+#    #+#             */
/*   Updated: 2024/07/19 18:29:21 by gdero            ###   ########.fr       */
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
		return (1);
	return (result * neg);
}

void	fill_info(t_data *data, char **argv)
{
	data->total_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_meal = ft_atoi(argv[5]);
	else
		data->nb_meal = -1;
}

/*int main(void)
{
	char test[] = "  \016 15";
	printf("%i\n", atoi(test));
	printf("%i\n", ft_atoi(test));
}*/

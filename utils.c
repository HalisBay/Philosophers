/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:17 by hbay              #+#    #+#             */
/*   Updated: 2023/11/24 14:58:18 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

size_t	ft_atoi(char *str)
{
	size_t		sign;
	long long	result;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
		if (str[i] == '-' || str[i] == '+')
			error_message();
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result *= sign;
	if (!(result > -2147483648 && result < 2147483647))
		error_message();
	return (result);
}

void	is_number(char **numbers)
{
	int	i;
	int	k;

	i = 1;
	while (numbers[i])
	{
		k = 0;
		while (numbers[i][k])
		{
			if ((numbers[i][k] == 43) &&
				!(numbers[i][k + 1] >= '0' && numbers[i][k + 1] <= '9'))
				error_message();
			if (!(numbers[i][k] >= 48 && numbers[i][k] <= 57) &&
				numbers[i][k] != 32 && numbers[i][k] != 43)
				error_message();
			if (numbers[i][k] >= '0' && numbers[i][k] <= '9'
				&& (numbers[i][k + 1] == 43))
				error_message();
			if (numbers[i][k] == 45)
				error_message();
			k++;
		}
		i++;
	}
}

long long	time_control(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	time_diff(long long current, long long past)
{
	return (current - past);
}

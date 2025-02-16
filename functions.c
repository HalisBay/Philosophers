/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:05 by hbay              #+#    #+#             */
/*   Updated: 2023/11/24 14:58:06 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_struct *lc)
{
	int	i;

	i = 0;
	while (i < lc->num_of_philo)
	{
		if (pthread_mutex_init(&lc->forks[i], NULL) != 0)
			error_message();
		i++;
	}
	if (pthread_mutex_init(&lc->meal_check, NULL) != 0
		|| pthread_mutex_init(&lc->writing, NULL) != 0
		|| pthread_mutex_init(&lc->must, NULL) != 0
		|| pthread_mutex_init(&lc->lock, NULL) != 0)
	{
		error_message();
	}
}

void	init_philo(t_struct *lc)
{
	int	i;

	i = 0;
	while (i < lc->num_of_philo)
	{
		lc->philo[i].id = i;
		lc->philo[i].count_eat = 0;
		lc->philo[i].left_fork_id = i;
		lc->philo[i].right_fork_id = (i + 1) % lc->num_of_philo;
		lc->philo[i].t_last_meal = 0;
		lc->philo[i].lc = lc;
		i++;
	}
}

void	init_fc(t_struct *lc, char **argv)
{
	lc->num_of_philo = ft_atoi(argv[1]);
	lc->time_to_death = ft_atoi(argv[2]);
	lc->time_to_eat = ft_atoi(argv[3]);
	lc->time_to_sleep = ft_atoi(argv[4]);
	lc->dead = 0;
	if (lc->num_of_philo <= 0 || lc->time_to_death < 0 || lc->time_to_eat < 0
		|| lc->time_to_sleep < 0)
		error_message();
	if (argv[5])
	{
		lc->num_eat = ft_atoi(argv[5]);
		if (lc->num_eat <= 0)
			error_message();
	}
	else
		lc->num_eat = -1;
	init_mutex(lc);
	init_philo(lc);
}

void	smart_sleep(long long time, t_struct *lc)
{
	long long	i;

	i = time_control();
	while (get_dead(lc->philo) == 0)
	{
		if (time_diff(time_control(), i) >= time)
			break ;
		else
			usleep(50);
	}
}

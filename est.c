/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   est.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:58 by hbay              #+#    #+#             */
/*   Updated: 2023/11/24 14:58:00 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

void	tfork(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->lc->forks[philo->left_fork_id]) != 0)
		error_message();
	write_ft("has taken a fork", time_diff(time_control(),
			philo->lc->time_start), philo);
	if (pthread_mutex_lock(&philo->lc->forks[philo->right_fork_id]) != 0)
		error_message();
	write_ft("has taken a fork", time_diff(time_control(),
			philo->lc->time_start), philo);
	eat_ft(philo);
}

void	eat_ft(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->lc->meal_check) != 0)
		error_message();
	write_ft("is eating", time_diff(time_control(),
			philo->lc->time_start), philo);
	pthread_mutex_lock(&philo->lc->lock);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->lc->lock);
	philo->t_last_meal = time_control();
	if (pthread_mutex_unlock(&philo->lc->meal_check) != 0)
		error_message();
	smart_sleep(philo->lc->time_to_eat, philo->lc);
	if (pthread_mutex_unlock(&philo->lc->forks[philo->left_fork_id]) != 0)
		error_message();
	if (pthread_mutex_unlock(&philo->lc->forks[philo->right_fork_id]) != 0)
		error_message();
}

void	write_ft(char *message, long long time, t_philo *philo)
{
	pthread_mutex_lock(&philo->lc->writing);
	if (get_dead(philo) == 0)
	{
		printf("%lld %d %s\n", time, (philo->id) + 1, message);
	}
	pthread_mutex_unlock(&philo->lc->writing);
}

int	get_dead(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->lc->must);
	i = philo->lc->dead;
	pthread_mutex_unlock(&philo->lc->must);
	return (i);
}

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lc->must);
	philo->lc->dead = 1;
	pthread_mutex_unlock(&philo->lc->must);
}

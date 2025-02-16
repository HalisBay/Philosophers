/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:39 by hbay              #+#    #+#             */
/*   Updated: 2023/11/24 14:57:43 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	*philoop(void *arg)
{
	t_philo	*phip;

	phip = (t_philo *)arg;
	if (phip->id % 2)
		usleep(1000);
	while (get_dead(phip) == 0 && lock_count(phip) == 0)
	{
		tfork(phip);
		if (get_dead(phip) || lock_count(phip))
			break ;
		write_ft("is sleeping", time_diff(time_control(),
				phip->lc->time_start), phip);
		smart_sleep(phip->lc->time_to_sleep, phip->lc);
		write_ft("is thinking", time_diff(time_control(),
				phip->lc->time_start), phip);
	}
	return (NULL);
}

void	create_philo(t_struct *lc)
{
	int		i;
	t_philo	*philos;

	philos = lc->philo;
	i = 0;
	lc->time_start = time_control();
	while (i < lc->num_of_philo)
	{
		pthread_create(&lc->philo[i].thread_id, NULL, philoop, &lc->philo[i]);
		pthread_mutex_lock(&lc->meal_check);
		philos[i].t_last_meal = time_control();
		pthread_mutex_unlock(&lc->meal_check);
		i++;
	}
	death_control (lc, philos, -1);
	i = 0;
	while (i < lc->num_of_philo)
	{
		pthread_join(lc->philo[i].thread_id, NULL);
		i++;
	}
	is_dead(lc);
}

void	death_control(t_struct *lc, t_philo *phi, int j)
{
	while (1)
	{
		j = -1;
		while (++j < lc->num_of_philo)
		{
			pthread_mutex_lock(&(lc->meal_check));
			if ((time_diff(time_control(),
						phi[j].t_last_meal) >= lc->time_to_death)
				|| lock_count(phi))
			{
				if (lock_count(phi) == 0)
				{
					write_ft("died", time_diff(time_control(),
							phi->lc->time_start), phi);
					set_dead(phi);
				}
				if (lc->num_of_philo == 1)
					pthread_mutex_unlock(&lc->forks[0]);
			}
			pthread_mutex_unlock(&(lc->meal_check));
			usleep(100);
		}
		if (get_dead(phi) || lock_count(phi))
			break ;
	}
}

void	is_dead(t_struct *lc)
{
	int	i;

	i = -1;
	while (++i < lc->num_of_philo)
		pthread_mutex_unlock(&(lc->forks[i]));
	i = 0;
	while (i < lc->num_of_philo)
	{
		pthread_mutex_destroy(&lc->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(lc->writing));
	pthread_mutex_destroy(&(lc->meal_check));
	pthread_mutex_destroy(&(lc->must));
	pthread_mutex_destroy(&(lc->lock));
}

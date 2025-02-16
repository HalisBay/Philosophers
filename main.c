/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:08 by hbay              #+#    #+#             */
/*   Updated: 2023/12/04 13:09:59 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_struct	lc;

	if (argc == 5 || argc == 6)
	{
		is_number(argv);
		lc.philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		lc.forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		init_fc(&lc, argv);
		create_philo(&lc);
		free(lc.philo);
		free(lc.forks);
	}
	else
		printf("%s", "args error");
	return (0);
}

int	lock_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->lc->lock);
	if (philo->lc->num_eat == philo->count_eat)
	{
		pthread_mutex_unlock(&philo->lc->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->lc->lock);
		return (0);
	}
}

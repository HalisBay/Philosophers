/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbay <hbay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:58:21 by hbay              #+#    #+#             */
/*   Updated: 2023/11/24 14:58:22 by hbay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>	
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					count_eat;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_struct		*lc;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_struct
{
	int					num_of_philo;
	int					time_to_death;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_eat;
	int					dead;
	long long			time_start;
	pthread_mutex_t		lock;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		must;
	t_philo				*philo;
}	t_struct;

void		is_number(char **numbers);
void		error_message(void);
size_t		ft_atoi(char *str);
void		init_fc(t_struct *lc, char **argv);
long long	time_control(void);
void		create_philo(t_struct *lc);
void		tfork(t_philo *philo);
long long	time_diff(long long current, long long past);
void		eat_ft(t_philo *philo);
void		smart_sleep(long long time, t_struct *rules);
void		write_ft(char *message, long long time, t_philo *philo);
void		death_control(t_struct *lc, t_philo *phi, int j);
void		is_dead(t_struct *lc);
void		set_dead(t_philo *philo);
int			get_dead(t_philo *philo);
int			lock_count(t_philo *philo);
#endif
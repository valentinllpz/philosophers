/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:06:25 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/09 12:58:30 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	stop_simulation(t_philo *philo, t_info *info, int timestamp)
{
	pthread_mutex_lock(&(info->stop));
	if (info->death == 1)
	{
		pthread_mutex_unlock(&(info->stop));
		return (1);
	}
	else if (info->time_to_die <= timestamp - philo->last_meal_ts
		&& philo->meal_nb != info->max_meal_nb)
	{
		info->death = 1;
		pthread_mutex_unlock(&(info->stop));
		print_msg(0, philo, timestamp);
		return (1);
	}
	if (info->done == info->philo_nb)
	{
		pthread_mutex_unlock(&(info->stop));
		return (1);
	}
	pthread_mutex_unlock(&(info->stop));
	return (0);
}

int	thinking(t_philo *philo, t_info *info)
{
	int				timestamp;

	timestamp = get_current_time_ms() - info->start;
	if (stop_simulation(philo, info, timestamp))
		return (0);
	print_msg(4, philo, timestamp);
	return (1);
}

int	sleeping(t_philo *philo, t_info *info)
{
	int				timestamp;

	timestamp = get_current_time_ms() - info->start;
	if (stop_simulation(philo, info, timestamp))
		return (0);
	print_msg(3, philo, timestamp);
	waiting(info->start, timestamp, info->time_to_sleep);
	return (1);
}

int	eating(t_philo *philo, t_info *info)
{
	int				timestamp;

	pthread_mutex_lock(&(philo->fork));
	timestamp = get_current_time_ms() - info->start;
	if (stop_simulation(philo, info, timestamp))
		return (0);
	print_msg(1, philo, timestamp);
	if (!philo->next_fork)
		return (let_philo_die(philo, info));
	pthread_mutex_lock(philo->next_fork);
	timestamp = get_current_time_ms() - info->start;
	if (stop_simulation(philo, info, timestamp))
		return (0);
	print_msg(1, philo, timestamp);
	pthread_mutex_lock(&(philo->info->stop));
	philo->last_meal_ts = timestamp;
	pthread_mutex_unlock(&(philo->info->stop));
	philo->meal_nb++;
	print_msg(2, philo, timestamp);
	waiting(info->start, timestamp, info->time_to_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(philo->next_fork);
	return (1);
}

void	*life_cycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->meal_nb != philo->info->max_meal_nb)
	{
		if (!eating(philo, philo->info) || !sleeping(philo, philo->info)
			|| !thinking(philo, philo->info))
			break ;
	}
	pthread_mutex_lock(&(philo->info->stop));
	philo->info->done++;
	pthread_mutex_unlock(&(philo->info->stop));
	return (NULL);
}

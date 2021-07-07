/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:20 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 12:17:25 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// cas 1 philo

int	death(t_philo *philo, t_info *info)
{
	int				timestamp;

	timestamp = get_current_time_ms() - info->start;
	pthread_mutex_lock(&(info->death_lock));
	if (info->death == 1)
	{
		pthread_mutex_unlock(&(info->death_lock));
		return (1);
	}
	else if (info->time_to_die <= timestamp - philo->last_meal_ts)
	{
		info->death = 1;
		pthread_mutex_unlock(&(info->death_lock));
		print_msg(0, info->start, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&(info->death_lock));
	return (0);
}

int	thinking(t_philo *philo, t_info *info)
{
	int				timestamp;

	if (death(philo, info))
		return (0);
	timestamp = get_current_time_ms() - info->start;
	print_msg(4, philo->info->start, philo->id);
	return (1);
}

int	sleeping(t_philo *philo, t_info *info)
{
	int				timestamp;

	if (death(philo, info))
		return (0);
	timestamp = get_current_time_ms() - info->start;
	print_msg(3, info->start, philo->id);
	waiting(info->start, timestamp, info->time_to_sleep);
	return (1);
}

int	eating(t_philo *philo, t_info *info)
{
	int				timestamp;

	if (death(philo, info))
		return (0);
	pthread_mutex_lock(&(philo->fork));
	pthread_mutex_lock(philo->next_fork);
	timestamp = get_current_time_ms() - info->start;
	print_msg(1, info->start, philo->id);
	print_msg(1, info->start, philo->id);
	pthread_mutex_lock(&(philo->info->death_lock));
	philo->last_meal_ts = timestamp;
	pthread_mutex_unlock(&(philo->info->death_lock));
	philo->meal_nb++;
	print_msg(2, info->start, philo->id);
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
	return (NULL);
}

int	start_threads(pthread_t *thread, t_philo **philo, t_info *info)
{
	int		i;

	i = 0;
	info->start = get_current_time_ms();
	while (i < info->philo_nb)
	{
		if (pthread_create(&thread[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	i = 1;
	while (i < info->philo_nb)
	{
		if (pthread_create(&thread[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	return (1);
}

int	philosophers(pthread_t *thread, t_philo **philo, t_info *info)
{
	int		i;

	if (!start_threads(thread, philo, info))
		return (0);
	i = 0;
	while (!death(philo[i], info))
	{
		i++;
		if (i == info->philo_nb)
			i = 0;
	}
	i = 0;
	while (i < info->philo_nb)
	{
		if (pthread_join(thread[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t 	*thread;
	t_philo 	**philo;
	t_info		*info;
	int			ret;

	if (!(ac == 5 || ac == 6))
		return (1);
	info = init_info_struct(ac, av);
	if (!info)
		return (1);
	philo = init_philo_struct(info);
	if (!philo)
		return (1);
	thread = init_threads_array(info->philo_nb);
	if (!thread)
		return (1);
	ret = philosophers(thread, philo, info); // print error message
	return (0);
}

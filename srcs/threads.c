/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:19:01 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 19:24:07 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	everyone_ate(t_info *info)
{
	pthread_mutex_lock(&(info->stop));
	if (info->done == info->philo_nb)
	{
		pthread_mutex_unlock(&(info->stop));
		return (1);
	}
	pthread_mutex_unlock(&(info->stop));
	return (0);
}

void	finish_threads(t_philo **philo, t_info *info)
{
	int		i;

	i = 0;
	while (!death(philo[i], info, get_current_time_ms() - info->start) || everyone_ate(info))
	{
		i++;
		if (i == info->philo_nb)
			i = 0;
	}
}

int	start_threads(pthread_t *threads, t_philo **philo, t_info *info)
{
	int		i;

	i = 0;
	info->start = get_current_time_ms();
	while (i < info->philo_nb)
	{
		if (pthread_create(&threads[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < info->philo_nb)
	{
		if (pthread_create(&threads[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	finish_threads(philo, info);
	return (1);
}

int	join_threads(pthread_t *threads, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->philo_nb)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

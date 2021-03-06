/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:19:01 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/09 12:58:03 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	usleep(420);
	i = 1;
	while (i < info->philo_nb)
	{
		if (pthread_create(&threads[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	return (1);
}

int	finish_threads(pthread_t *threads, t_philo **philo, t_info *info)
{
	int		i;

	i = 0;
	while (1)
	{
		if (stop_simulation(philo[i], info,
				get_current_time_ms() - info->start))
			break ;
		i++;
		if (i == info->philo_nb)
			i = 0;
		usleep(420);
	}
	i = 0;
	while (i < info->philo_nb)
	{
		if (pthread_join(threads[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

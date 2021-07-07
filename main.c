/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:20 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 17:11:02 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
/*
void	end_simulation(t_philo **philo, t_info *info)
{
	int	i;
	int	stop;

	i = 0;
	stop = 0;
	while (!stop && !death(philo[i], info))
	{
		pthread_mutex_lock(&(info->death_lock));
		if (info->done == info->philo_nb)
			stop = 1;
		pthread_mutex_unlock(&(info->death_lock));
		i++;
		if (i == info->philo_nb)
			i = 0;
	}	
}
*/
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
	usleep(100);
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
//	end_simulation(philo, info);
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

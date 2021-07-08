/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:37 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 17:40:04 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	*init_info_struct(int ac, char **av)
{
	t_info	*info;

	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	info->philo_nb = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->max_meal_nb = ft_atoi(av[5]);
	else
		info->max_meal_nb = -1;
	if (pthread_mutex_init(&(info->death_lock), NULL) != 0
		|| pthread_mutex_init(&(info->print_lock), NULL) != 0)
	{
		free(info);
		return (NULL);
	}
	return (info);
}

int	init_forks_mutex(t_philo **philo)
{
	int		i;

	i = 0;
	while (philo[i])
	{
		if (pthread_mutex_init(&(philo[i]->fork), NULL))
			return (0);
		if (philo[i + 1])
			philo[i]->next_fork = &(philo[i + 1]->fork);
		else if (!philo[i + 1] && i == 0)
			philo[i]->next_fork = NULL;
		else
			philo[i]->next_fork = &(philo[0]->fork);
		i++;
	}
	return (1);
}

t_philo	**init_philo_struct(t_info *info)
{
	t_philo		**philo;
	int			i;

	philo = ft_calloc(info->philo_nb + 1, sizeof(t_philo *));
	if (!philo)
		return (free_all(philo, info, NULL));
	i = 0;
	while (i < info->philo_nb)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (free_all(philo, info, NULL));
		philo[i]->id = i + 1;
		philo[i]->info = info;
		i++;
	}
	if (!init_forks_mutex(philo))
		return (free_all(philo, info, NULL));
	return (philo);
}

pthread_t	*init_threads_array(int philo_nb, t_philo **philo, t_info *info)
{
	pthread_t	*threads;

	threads = ft_calloc(philo_nb + 1, sizeof(pthread_t));
	if (!threads)
		return (free_all(philo, info, NULL));
	return (threads);
}

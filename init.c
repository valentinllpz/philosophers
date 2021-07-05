/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:03:37 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/05 19:14:14 by vlugand-         ###   ########.fr       */
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
	if (info->philo_nb < 0 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0) // faire ailleurs pour les retours erreur
		return (NULL);
	return (info);
}

t_philo	**init_philo_struct(t_info *info)
{
	t_philo		**philo;
	int			i;

	philo = ft_calloc(info->philo_nb + 1, sizeof(t_philo *));
	if (!philo)
		return (NULL);
	philo[info->philo_nb] = NULL; // pas besoin si calloc
	i = 0;
	while (i < info->philo_nb)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		philo[i]->id = i + 1;
		philo[i]->info = info;
		i++;
	}
	i = 0;
	while (philo[i])
	{
		if (pthread_mutex_init(&(philo[i]->fork), NULL))
			return (NULL);
		if (philo[i + 1])
			philo[i]->next_fork = &(philo[i + 1]->fork);
		else
			philo[i]->next_fork = &(philo[0]->fork);
		i++;
	}
	return (philo);
}

pthread_t *init_threads_array(int philo_nb)
{
	pthread_t 	*thread;

	thread = ft_calloc(philo_nb + 1, sizeof(pthread_t));
	if (!thread)
		return (0);
	return (thread);
}
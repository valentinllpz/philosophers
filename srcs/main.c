/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:20 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 16:26:10 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_info		*info;
	t_philo		**philo;
	pthread_t	*threads;

	if (usage_error(ac, av))
		return (exit_error(1));
	info = init_info_struct(ac, av);
	if (!info)
		return (exit_error(2));
	philo = init_philo_struct(info);
	if (!philo)
		return (exit_error(2));
	threads = init_threads_array(info->philo_nb, philo, info);
	if (!threads)
		return (exit_error(2));
	if (!start_threads(threads, philo, info) || !join_threads(threads, info))
	{
		free_all(philo, info, threads);
		return (exit_error(3));
	}
	free_all(philo, info, threads);
	return (0);
}

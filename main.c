/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:20 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 20:16:22 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	exit_error(int err_type)
{
	if (err_type == 1)
	{
		write(2, "philo: usage error: arguments should be a ", 44);
		write(2, "[number_of_philosophers] [time_to_die] [time_to_eat] ", 55);
		write(2, "[time_to_sleep] and optionally [number_of_times_each_", 55);
		write(2, "philosopher_must_eat]. Negative values are not accepted\n", 58);
	}
	else if (err_type == 2)
		write(2, "philo: program exited due to an error\n", 39);
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t 	*thread;
	t_philo 	**philo;
	t_info		*info;

	if (!(ac == 5 || ac == 6))
		return (exit_error(1));
	info = init_info_struct(ac, av);
	if (!info)
		return (1);
/*	if (info->philo_nb < 0 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0 || info->max_meal_nb < 0)
		return (exit_error(1));
*/	philo = init_philo_struct(info);
	if (!philo)
		return (1);
	thread = init_threads_array(info->philo_nb);
	if (!thread)
		return (1);
	if (!start_threads(thread, philo, info))
		return (0); // print error message
	if (!join_threads(thread, philo, info))
		return (0); // print error message
	return (0);
}

// philo 1 
// pas plus de 200
// free
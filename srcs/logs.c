/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:23:31 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 17:45:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	exit_error(int err_type)
{
	if (err_type == 1)
	{
		write(2, "philo: usage error: arguments should be a [number_of_", 53);
		write(2, "philosophers] [time_to_die] [time_to_eat] [time_to_sl", 53);
		write(2, "eep] and optionally [number_of_times_each_philosopher", 53);
		write(2, "_must_eat].\nNegative values and 0 are not accepted. ", 52);
		write(2, "Maximum [number_of_philosophers] allowed is 200.\n", 49);
	}
	else if (err_type == 2)
		write(2, "philo: error initializing data\n", 31);
	else if (err_type == 3)
		write(2, "philo: an unexpected error occured\n", 35);
	return (1);
}

void	print_msg(int flag, t_philo *philo, int timestamp)
{
	pthread_mutex_lock(&(philo->info->print_lock));
	if (flag == 0)
		printf("[%i ms] %i died\n", timestamp, philo->id);
	else if (flag == 1)
		printf("[%i ms] %i has taken a fork\n", timestamp, philo->id);
	else if (flag == 2)
		printf("[%i ms] %i is eating\n", timestamp, philo->id);
	else if (flag == 3)
		printf("[%i ms] %i is sleeping\n", timestamp, philo->id);
	else if (flag == 4)
		printf("[%i ms] %i is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(&(philo->info->print_lock));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:23:31 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 17:06:01 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
/*
int	exit_error(int err_no)
{
	if (err_no == 1)
		write(2, "Error: invalid arguments number\n", 34);
	else if (err_no == 2)
		write(2, "Error: negative values are not allowed\n", 41);
	return (err_no);
}
*/

void	print_msg(int flag, t_info *info, t_philo *philo)
{
	int				timestamp;

	timestamp = get_current_time_ms() - info->start;
	if (flag == 0)
		printf("[%i ms] %i died\n", timestamp, philo->id);
//	else if (death(philo, info))
//		return ;
	else if (flag == 1)
		printf("[%i ms] %i has taken a fork\n", timestamp, philo->id);
	else if (flag == 2)
		printf("[%i ms] %i is eating\n", timestamp, philo->id);
	else if (flag == 3)
		printf("[%i ms] %i is sleeping\n", timestamp, philo->id);
	else if (flag == 4)
		printf("[%i ms] %i is thinking\n", timestamp, philo->id);
}

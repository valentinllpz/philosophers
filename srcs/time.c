/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:35:14 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 15:48:14 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	waiting(int start, int wait_from, int time_to_wait)
{
	int	goal;
	int	timestamp;

	goal = time_to_wait + wait_from;
	timestamp = get_current_time_ms() - start;
	while (timestamp < goal)
	{
		usleep(100);
		timestamp = get_current_time_ms() - start;
	}
}

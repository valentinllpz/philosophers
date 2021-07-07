/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:35:14 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 12:01:41 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_current_time_ms()
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (0); // an error occured
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	waiting(int start, int wait_from, int time_to_wait)
{
	int goal;
	int	timestamp;

	goal = time_to_wait + wait_from;
	timestamp = get_current_time_ms() - start;
	while (timestamp < goal)
	{
		usleep(100); // check if -1 returned
		timestamp = get_current_time_ms() - start;
	}
}

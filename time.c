/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:35:14 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/05 20:09:24 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	gettime_in_ms()
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		return (0); // an error occured
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	waiting(int time)
{
	int count;
	
	time *= 1000;
	count = 0;
	while (count < time)
	{
		usleep(420); // check if -1 returned
		count += 420;
	}
}

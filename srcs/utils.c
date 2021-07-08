/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:04:44 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/08 17:42:40 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_all(t_philo **philo, t_info *info, pthread_t *threads)
{
	int		i;

	if (info)
	{
		pthread_mutex_destroy(&(info->death_lock));
		free(info);
	}
	if (philo)
	{
		i = 0;
		while (philo[i])
		{
			pthread_mutex_destroy(&(philo[i]->fork));
			free(philo[i]);
			i++;
		}
		free(philo);
	}
	if (threads)
		free(threads);
	return (NULL);
}

int	usage_error(int ac, char **av)
{
	int		i;

	if (!(ac == 5 || ac == 6))
		return (1);
	if (ft_atoi(av[1]) > 200)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	let_philo_die(t_philo *philo, t_info *info)
{
	int		timestamp;

	timestamp = get_current_time_ms() - info->start;
	print_msg(1, philo, timestamp);
	waiting(info->start, timestamp, info->time_to_die);
	death(philo, info, get_current_time_ms() - info->start);
	return (0);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						sign;
	unsigned long long		res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ((str[i] > 8 && str[i] < 14) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if ((i > 19 || res >= 9223372036854775808ULL) && sign == 1)
		return (-1);
	else if ((i > 19 || res >= 9223372036854775808ULL) && sign == -1)
		return (0);
	return (res * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	n;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	n = count * size;
	while (i < n)
	{
		*((unsigned char *)ptr + i) = 0;
		i++;
	}
	return (ptr);
}

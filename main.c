/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:13:20 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/05 20:45:30 by vlugand-         ###   ########.fr       */
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
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

void	print_msg(int flag, int start, int id)
{
	int				timestamp;
//	pthread_mutex_t lock;

//	pthread_mutex_init(&lock, NULL);
//	pthread_mutex_lock(&lock);
	timestamp = gettime_in_ms() - start;
	if (flag == 0)
		printf("[%i ms] Philosopher no %i died\n", timestamp, id);
	else if (flag == 1)
		printf("[%i ms] Philosopher no %i has taken a fork\n", timestamp, id);
	else if (flag == 2)
		printf("[%i ms] Philosopher no %i is eating\n", timestamp, id);
	else if (flag == 3)
		printf("[%i ms] Philosopher no %i is sleeping\n", timestamp, id);
	else if (flag == 4)
		printf("[%i ms] Philosopher no %i is thinking\n", timestamp, id);
//	pthread_mutex_unlock(&lock);
}

int	death(t_philo *philo, t_info *info)
{
	int				timestamp;

	timestamp = gettime_in_ms() - info->start;
	if (info->time_to_die <= timestamp - philo->last_meal_ts)
	{
		print_msg(0, info->start, philo->id);
		info->death = 1;
		return (1);
	}
	return (0);
}

void	thinking(t_philo *philo, t_info *info)
{
	print_msg(4, philo->info->start, philo->id);
	waiting(philo->info->time_to_sleep);
}

void	sleeping(t_philo *philo, t_info *info)
{
	print_msg(3, info->start, philo->id);
	waiting(info->time_to_sleep);
}

void	eating(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(philo->fork));
	pthread_mutex_lock(philo->next_fork);
	philo->meal_nb++;
	pthread_mutex_lock(&(philo->info->death_lock));
	philo->last_meal_ts = gettime_in_ms() - info->start;
	pthread_mutex_unlock(&(philo->info->death_lock));
	print_msg(1, info->start, philo->id);
	print_msg(2, info->start, philo->id);
	waiting(info->time_to_eat);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(philo->next_fork);
}

void	*life_cycle(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (philo->meal_nb != philo->info->max_meal_nb)
	{
		eating(philo, philo->info);

		sleeping(philo, philo->info);

		thinking(philo, philo->info);

	}
	pthread_mutex_unlock(&(philo->info->death_lock));
	return (NULL);
}

int	start_threads(pthread_t *thread, t_philo **philo, t_info *info, int i)
{
	while (i < info->philo_nb)
	{
		if (pthread_create(&thread[i], NULL, life_cycle, philo[i]))
			return (0);
		i += 2;
	}
	return (1);
}

int	philosophers(pthread_t *thread, t_philo **philo, t_info *info)
{
	int		i;

	info->start = gettime_in_ms();
	if (!start_threads(thread, philo, info, 0) || !start_threads(thread, philo, info, 1))
		return (0);
	i = 0;
	while (i < info->philo_nb)
	{
		pthread_mutex_lock(&(info->death_lock));
		death(philo[i], info);
		if (info->death)
		{
			pthread_mutex_unlock(&(info->death_lock));
			i = 0;
			break ;
		}
		pthread_mutex_unlock(&(info->death_lock));
		i++;
		if (i == info->philo_nb)
			i = 0;
	}

	while (i < info->philo_nb)
	{
		if (pthread_join(thread[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t 	*thread;
	t_philo 	**philo;
	t_info		*info;
	int			ret;

	if (!(ac == 5 || ac == 6))
		return (1);
	info = init_info_struct(ac, av);
	if (!info)
		return (1);
	philo = init_philo_struct(info);
	if (!philo)
		return (1);
	thread = init_threads_array(info->philo_nb);
	if (!thread)
		return (1);
	ret = philosophers(thread, philo, info); // print error message
	return (0);
}

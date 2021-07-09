/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:09:08 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/09 12:57:25 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meal_nb;
	int				start;
	int				done;
	int				death;
	pthread_mutex_t	stop;
	pthread_mutex_t	print;
}				t_info;

typedef struct s_philo
{
	int				id;
	int				meal_nb;
	int				last_meal_ts;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_info			*info;
}				t_philo;

t_info		*init_info_struct(int ac, char **av);
t_philo		**init_philo_struct(t_info *info);
pthread_t	*init_threads_array(int philo_nb, t_philo **philo, t_info *info);

int			start_threads(pthread_t *thread, t_philo **philo, t_info *info);
int			finish_threads(pthread_t *thread, t_philo **philo, t_info *info);

int			get_current_time_ms(void);
void		waiting(int start, int wait_from, int time_to_wait);

void		*life_cycle(void *ptr);
int			eating(t_philo *philo, t_info *info);
int			sleeping(t_philo *philo, t_info *info);
int			thinking(t_philo *philo, t_info *info);
int			stop_simulation(t_philo *philo, t_info *info, int timestamp);

void		*free_all(t_philo **philo, t_info *info, pthread_t *threads);
int			usage_error(int ac, char **av);
int			let_philo_die(t_philo *philo, t_info *info);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);

void		print_msg(int flag, t_philo *philo, int timestamp);
int			exit_error(int err_type);

#endif
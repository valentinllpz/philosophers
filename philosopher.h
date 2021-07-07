/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:09:08 by vlugand-          #+#    #+#             */
/*   Updated: 2021/07/07 11:14:14 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_info
{
	int	philo_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_meal_nb;
	int	start;
	int	death;
	pthread_mutex_t death_lock;
}				t_info;

typedef struct	s_philo
{
	int				id;
	int				meal_nb;
	int				last_meal_ts;
	pthread_mutex_t fork;
	pthread_mutex_t	*next_fork;
	t_info			*info;
}				t_philo;

//init
t_info		*init_info_struct(int ac, char **av);
t_philo		**init_philo_struct(t_info *info);
pthread_t 	*init_threads_array(int philo_nb);

//time
int			get_current_time_ms();
void		waiting(int start, int wait_from, int time_to_wait);

//utils
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

//display.c
void	print_msg(int flag, int start, int id);


// get time soustraction temps present - start
// boucle de petit usleep
// mutex pour les print (les proteger)

 // ID philo (thread), fourchette + pointeur fourchette voisin (derniere pointe sur le premier), nb meal


# endif
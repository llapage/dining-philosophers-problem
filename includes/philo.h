/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:34:21 by llapage           #+#    #+#             */
/*   Updated: 2024/01/10 16:57:58 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include "pthread.h"

typedef struct s_philo {
	int				id;
	pthread_t		tid;
	int				ate;
	int				dead;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	ate_mutex;
	int				fork_taken;
	int				my_fork;
	int				next_fork;
	long			last_eat;
}	t_philo;

typedef struct s_params {
	int	philo_number;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	eat_goal;
	int	eat_goal_set;
}	t_params;

typedef struct s_cont {
	t_philo			*philo;
	int				index;
	t_params		*params;
	pthread_mutex_t	thread_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	taken_mutex;
	pthread_mutex_t	eat_death_mutex;
	struct timeval	time;
	long			ms_now;
	long			ms_start;
	int				dead_msg;
}	t_cont;

int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			set_params(t_params **params, char **argv);
int			set_philos(t_cont **cont);
int			set_forks(t_cont **cont);
int			set_threads(t_cont **cont);
void		*thread_fct(void *data);
int			take_forks(t_cont **cont, int index);
int			check_fed(t_cont **cont);
int			check_death(t_cont **cont);
int			eat_task(t_cont **cont, int index);
int			ft_print(t_cont **cont, int id, char *msg, int mode);
int			sleep_task(t_cont **cont, int index);
int			think_task(t_cont **cont, int index);
int			break_philo(t_cont **cont);
long		get_ms_now(t_cont **cont);
void		destroy_mutex(t_cont **cont);
int			ft_free_all(t_cont **cont, int mode);
int			malloc_fail(void);
void		ft_usleep(t_cont **cont, long target_time);

#endif

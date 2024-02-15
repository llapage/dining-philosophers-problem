/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:27:04 by llapage           #+#    #+#             */
/*   Updated: 2024/01/15 10:48:28 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	routine_philo(t_cont **cont, int index)
{
	pthread_mutex_unlock(&(*cont)->thread_mutex);
	if (index % 2)
	{
		ft_usleep(cont, ft_min((*cont)->params->time_eat,
				(*cont)->params->time_sleep) / 2);
	}
	while (1)
	{
		take_forks(cont, index);
		sleep_task(cont, index);
		think_task(cont, index);
		pthread_mutex_lock(&(*cont)->eat_death_mutex);
		if ((*cont)->dead_msg || check_fed(cont))
		{
			pthread_mutex_unlock(&(*cont)->eat_death_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	}
	return (0);
}

void	*thread_routine(void *args)
{
	t_cont			**cont;
	static int		index = -1;

	cont = (t_cont **)args;
	pthread_mutex_lock(&(*cont)->thread_mutex);
	index++;
	routine_philo(cont, index);
	return (NULL);
}

int	set_threads(t_cont **cont)
{
	int	i;

	if (pthread_mutex_init(&(*cont)->thread_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&(*cont)->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&(*cont)->taken_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&(*cont)->eat_death_mutex, NULL))
		return (1);
	(*cont)->dead_msg = 0;
	i = 0;
	while (i + 1 <= (*cont)->params->philo_number)
		if (pthread_create
			(&(*cont)->philo[i++].tid, NULL, thread_routine, cont))
			return (1);
	return (0);
}

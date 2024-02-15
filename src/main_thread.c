/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:21:22 by llapage           #+#    #+#             */
/*   Updated: 2024/01/15 10:47:40 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	break_philo(t_cont **cont)
{
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&(*cont)->eat_death_mutex);
		if (check_fed(cont))
		{
			pthread_mutex_unlock(&(*cont)->eat_death_mutex);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		}
		if (check_death(cont))
			break ;
	}
	return (1);
}

static int	death_msg(t_cont **cont, long ms_now, int i)
{
	if ((*cont)->dead_msg == 0)
	{
		(*cont)->dead_msg = 1;
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		ms_now = get_ms_now(cont);
		pthread_mutex_lock(&(*cont)->write_mutex);
		printf("%ld %d died\n", ms_now, i + 1);
		pthread_mutex_unlock(&(*cont)->write_mutex);
	}
	else
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	return (1);
}

int	check_death(t_cont **cont)
{
	int		i;
	long	ms_now;

	i = 0;
	while (i < (*cont)->params->philo_number)
	{
		ms_now = get_ms_now(cont);
		pthread_mutex_lock(&(*cont)->eat_death_mutex);
		if (ms_now - (*cont)->philo[i].last_eat >= (*cont)->params->time_die)
			return (death_msg(cont, ms_now, i));
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		i++;
	}
	return (0);
}

int	check_fed(t_cont **cont)
{
	int	i;

	i = 0;
	if ((*cont)->params->eat_goal_set == 0)
		return (0);
	while (i < (*cont)->params->philo_number)
	{
		pthread_mutex_lock(&(*cont)->philo[i].ate_mutex);
		if ((*cont)->philo[i].ate < (*cont)->params->eat_goal)
		{
			pthread_mutex_unlock(&(*cont)->philo[i].ate_mutex);
			return (0);
		}
		pthread_mutex_unlock(&(*cont)->philo[i].ate_mutex);
		i++;
	}
	(*cont)->dead_msg = 1;
	pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	return (1);
}

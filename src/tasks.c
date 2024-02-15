/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:09:09 by llapage           #+#    #+#             */
/*   Updated: 2024/01/15 10:48:16 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	think_task(t_cont **cont, int index)
{
	pthread_mutex_lock(&(*cont)->eat_death_mutex);
	if (!(*cont)->dead_msg && !check_fed(cont))
	{
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		pthread_mutex_lock(&(*cont)->write_mutex);
		printf("%ld %d is thinking\n", get_ms_now(cont), index + 1);
		pthread_mutex_unlock(&(*cont)->write_mutex);
	}
	else
	{
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	}
	return (0);
}

void	ft_usleep(t_cont **cont, long target_time)
{
	while (get_ms_now(cont) < target_time)
		usleep(100);
}

int	sleep_task(t_cont **cont, int index)
{
	pthread_mutex_lock(&(*cont)->eat_death_mutex);
	if (!(*cont)->dead_msg && !check_fed(cont))
	{
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		pthread_mutex_lock(&(*cont)->write_mutex);
		printf("%ld %d is sleeping\n", get_ms_now(cont), index + 1);
		pthread_mutex_unlock(&(*cont)->write_mutex);
		ft_usleep(cont, get_ms_now(cont) + (*cont)->params->time_sleep);
	}
	else
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	return (0);
}

int	eat_task(t_cont **cont, int index)
{
	long	ms_now;

	pthread_mutex_lock(&(*cont)->philo[index].ate_mutex);
	(*cont)->philo[index].ate += 1;
	pthread_mutex_unlock(&(*cont)->philo[index].ate_mutex);
	ms_now = get_ms_now(cont);
	pthread_mutex_lock(&(*cont)->eat_death_mutex);
	(*cont)->philo[index].last_eat = ms_now;
	if (!(*cont)->dead_msg && (!check_fed(cont)
			|| (*cont)->philo[index].ate == (*cont)->params->eat_goal))
	{
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		pthread_mutex_lock(&(*cont)->write_mutex);
		printf("%ld %d is eating\n",
			get_ms_now(cont), (*cont)->philo[index].id);
		pthread_mutex_unlock(&(*cont)->write_mutex);
	}
	else
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	ft_usleep(cont, get_ms_now(cont) + (*cont)->params->time_eat);
	pthread_mutex_unlock(&(*cont)->philo[index].fork_mutex);
	pthread_mutex_unlock
		(&(*cont)->philo[(*cont)->philo[index].next_fork].fork_mutex);
	return (0);
}

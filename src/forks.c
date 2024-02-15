/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:26:41 by llapage           #+#    #+#             */
/*   Updated: 2024/01/15 10:48:32 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_cont **cont, int index)
{
	pthread_mutex_lock(&(*cont)->philo[index].fork_mutex);
	pthread_mutex_lock
		(&(*cont)->philo[(*cont)->philo[index].next_fork].fork_mutex);
	pthread_mutex_lock(&(*cont)->eat_death_mutex);
	if (!(*cont)->dead_msg && !check_fed(cont))
	{
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
		pthread_mutex_lock(&(*cont)->write_mutex);
		printf("%ld %d has taken a fork\n", get_ms_now(cont),
			(*cont)->philo[index].id);
		printf("%ld %d has taken a fork\n", get_ms_now(cont),
			(*cont)->philo[index].id);
		pthread_mutex_unlock(&(*cont)->write_mutex);
	}
	else
		pthread_mutex_unlock(&(*cont)->eat_death_mutex);
	eat_task(cont, index);
	return (1);
}

int	set_forks(t_cont **cont)
{
	int				i;

	i = 0;
	while (i < (*cont)->params->philo_number)
		if (pthread_mutex_init(&(*cont)->philo[i++].fork_mutex, NULL))
			return (1);
	return (0);
}

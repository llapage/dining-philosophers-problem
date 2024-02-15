/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:14:28 by llapage           #+#    #+#             */
/*   Updated: 2024/01/10 16:58:06 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	fill_philo(t_cont **cont, int i)
{
	(*cont)->philo[i].id = i + 1;
	(*cont)->philo[i].ate = 0;
	(*cont)->philo[i].dead = 0;
	(*cont)->philo[i].fork_taken = 0;
	(*cont)->philo[i].my_fork = (*cont)->philo[i].id - 1;
	(*cont)->philo[i].last_eat = 0;
	if ((*cont)->philo[i].id == (*cont)->params->philo_number)
		(*cont)->philo[i].next_fork = 0;
	else
		(*cont)->philo[i].next_fork = (*cont)->philo[i].id;
	if (pthread_mutex_init(&(*cont)->philo[i].ate_mutex, NULL))
		return (1);
	return (0);
}

int	set_philos(t_cont **cont)
{
	int			i;

	(*cont)->philo = malloc(sizeof(t_philo) * (*cont)->params->philo_number);
	if (!(*cont)->philo)
		return (malloc_fail());
	i = 0;
	while (i < (*cont)->params->philo_number)
	{
		if (fill_philo(cont, i))
			return (1);
		i++;
	}
	return (0);
}

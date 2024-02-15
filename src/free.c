/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:37:01 by llapage           #+#    #+#             */
/*   Updated: 2024/01/09 11:43:28 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	malloc_fail(void)
{
	printf("Cannot allocate memory\n");
	return (1);
}

int	ft_free_all(t_cont **cont, int mode)
{
	int	i;

	i = 0;
	if (mode > 1)
	{
		while (i < (*cont)->params->philo_number)
			pthread_join((*cont)->philo[i++].tid, NULL);
	}
	if (mode > 0)
		destroy_mutex(cont);
	free((*cont)->params);
	free((*cont)->philo);
	free(*cont);
	return (mode);
}

void	destroy_mutex(t_cont **cont)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(*cont)->thread_mutex);
	pthread_mutex_destroy(&(*cont)->write_mutex);
	pthread_mutex_destroy(&(*cont)->taken_mutex);
	pthread_mutex_destroy(&(*cont)->eat_death_mutex);
	while ((i < (*cont)->params->philo_number))
	{
		if ((*cont)->philo)
		{
			pthread_mutex_destroy(&(*cont)->philo[i].fork_mutex);
			pthread_mutex_destroy(&(*cont)->philo[i].ate_mutex);
		}
		i++;
	}
}

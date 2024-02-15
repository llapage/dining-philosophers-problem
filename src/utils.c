/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:03:51 by llapage           #+#    #+#             */
/*   Updated: 2024/01/04 13:07:45 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1)
		if (*s1++ != *s2++)
			return (*--s1 - *--s2);
	return (*s1 - *s2);
}

long	get_ms_now(t_cont **cont)
{
	long	ms_now;

	gettimeofday(&(*cont)->time, NULL);
	ms_now = ((*cont)->time.tv_sec * 1000 + (*cont)->time.tv_usec / 1000)
		- (*cont)->ms_start;
	return (ms_now);
}

int	ft_print(t_cont **cont, int id, char *msg, int mode)
{
	pthread_mutex_lock(&(*cont)->write_mutex);
	(*cont)->ms_now = get_ms_now(cont);
	if (mode && !check_fed(cont) && !check_death(cont))
		printf("%ld %d %s\n", (*cont)->ms_now, id, msg);
	else
	{
		pthread_mutex_unlock(&(*cont)->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*cont)->write_mutex);
	return (0);
}

static int	check_max(size_t result, int negative)
{
	if (negative == -1)
	{
		if (result <= INT_MAX)
			return (result);
		else
			return (0);
	}
	else
	{
		if (result > INT_MAX)
			return (-1);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int			negative;
	int			i;
	size_t		result;

	negative = 1;
	i = 0;
	result = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < 48 || 57 < str[i])
			break ;
		else
			result = (result * 10) + (int)(str[i] - '0');
		i++;
	}
	return (check_max(result, negative) * negative);
}

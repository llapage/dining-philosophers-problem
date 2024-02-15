/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:51:43 by llapage           #+#    #+#             */
/*   Updated: 2024/01/12 11:20:15 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	set_params(t_params **params, char **argv)
{
	*params = malloc(sizeof(t_params));
	if (!(*params))
		return (malloc_fail());
	(*params)->philo_number = ft_atoi(argv[1]);
	(*params)->time_die = ft_atoi(argv[2]);
	(*params)->time_eat = ft_atoi(argv[3]);
	(*params)->time_sleep = ft_atoi(argv[4]);
	if ((*params)->philo_number <= 0 || (*params)->time_die <= 0
		|| (*params)->time_eat <= 0 || (*params)->time_sleep <= 0
		|| !str_is_num(argv[1]) || !str_is_num(argv[2])
		|| !str_is_num(argv[3]) || !str_is_num(argv[4])
		|| (argv[5] && !str_is_num(argv[5])))
	{
		printf("Error: arguments\n");
		return (1);
	}
	if (argv[5])
	{
		(*params)->eat_goal_set = 1;
		(*params)->eat_goal = ft_atoi(argv[5]);
	}
	else
		(*params)->eat_goal_set = 0;
	return (0);
}

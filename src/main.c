/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:59:54 by llapage           #+#    #+#             */
/*   Updated: 2024/01/12 10:40:41 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 0)
	{
		printf("Error: arguments\n");
		return (1);
	}
	return (0);
}

int	check_philo(char **argv)
{
	if (!ft_strcmp(argv[1], "1"))
	{
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (1);
	}
	return (0);
}

static void	init_null(t_cont **cont)
{
	(*cont)->philo = NULL;
	(*cont)->params = NULL;
}

int	main(int argc, char **argv)
{
	t_cont	*cont;

	cont = malloc(sizeof(t_cont));
	if (!cont)
		return (malloc_fail());
	init_null(&cont);
	if (gettimeofday(&(cont->time), NULL))
		return (ft_free_all(&cont, 0));
	cont->ms_start = (cont->time.tv_sec * 1000 + cont->time.tv_usec / 1000);
	if (check_args(argc, argv))
		return (ft_free_all(&cont, 0));
	if (set_params(&cont->params, argv))
		return (ft_free_all(&cont, 0));
	if (check_philo(argv))
		return (ft_free_all(&cont, 0));
	if (set_philos(&cont))
		return (ft_free_all(&cont, 1));
	if (set_forks(&cont))
		return (ft_free_all(&cont, 1));
	if (set_threads(&cont))
		return (ft_free_all(&cont, 2));
	if (break_philo(&cont))
		ft_free_all(&cont, 2);
	return (0);
}

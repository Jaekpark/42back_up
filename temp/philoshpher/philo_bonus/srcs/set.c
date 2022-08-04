/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:43 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:37 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	set_time(t_time *time, char **argv)
{
	if (!time || !argv)
		return (-1);
	time->die = ft_atoll(argv[2]);
	time->eat = ft_atoll(argv[3]);
	time->sleep = ft_atoll(argv[4]);
	return (0);
}

t_config	*set_config(int argc, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!argv)
		return (NULL);
	init_config(config);
	config->philo_cnt = ft_atoll(argv[1]);
	config->forks = malloc(sizeof(pthread_mutex_t) * (config->philo_cnt));
	set_time(&(config->time), argv);
	init_mutex(config);
	if (argc == 6)
		config->must_eat = ft_atoll(argv[5]);
	return (config);
}

t_philo	*set_philo(t_config *config)
{
	int		i;
	t_philo	*philos;

	if (!config)
		return (NULL);
	i = -1;
	philos = malloc(sizeof(t_philo) * (config->philo_cnt));
	init_philo(philos, config);
	return (philos);
}

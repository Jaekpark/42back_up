/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:43 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:27:52 by jaekpark         ###   ########.fr       */
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

int	set_config(int argc, char **argv, t_config *config)
{
	if (!argv)
		return (FALSE);
	init_config(config);
	config->philo_cnt = ft_atoll(argv[1]);
	set_time(&(config->time), argv);
	if (argc == 6)
		config->must_eat = ft_atoll(argv[5]);
	init_semaphore(config);
	return (TRUE);
}

int	set_philo(t_config *config)
{
	int	i;

	i = -1;
	config->philo = malloc(sizeof(t_philo) * config->philo_cnt);
	if (!config || !config->philo)
		return (FALSE);
	while (++i < config->philo_cnt)
	{
		config->philo[config->id].pid = 0;
		config->philo[config->id].ate_count = 0;
		config->philo[config->id].last_ate = 0;
	}
	return (TRUE);
}

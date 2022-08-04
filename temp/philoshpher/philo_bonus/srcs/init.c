/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:38 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:56:00 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_config(t_config *config)
{
	config->philo_cnt = 0;
	config->time.die = 0;
	config->time.eat = 0;
	config->time.sleep = 0;
	config->must_eat = 0;
	config->forks = NULL;
	config->died = 0;
	config->full = 0;
	config->start_time = 0;
}

int	init_philo(t_philo *philos, t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->philo_cnt)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % config->philo_cnt;
		philos[i].ate_count = 0;
		philos[i].tid = 0;
		philos[i].last_ate = 0;
		philos[i].config = config;
		philos[i].status = 0;
	}
	return (0);
}

int	init_mutex(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->philo_cnt)
		pthread_mutex_init(&(config->forks[i]), NULL);
	pthread_mutex_init(&(config->console), NULL);
	return (0);
}

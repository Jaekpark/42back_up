/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:33 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 14:17:59 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	pickup_fork(t_config *config)
{
	sem_wait(config->fork_s);
	sem_wait(config->console);
	console_log(config, PICKUP_FORK);
	sem_post(config->console);
}

static void	eating(t_config *config)
{
	pickup_fork(config);
	pickup_fork(config);
	sem_wait(config->console);
	console_log(config, EAT);
	sem_post(config->console);
	config->philo.last_ate = get_time();
	config->philo.ate_count += 1;
	if (config->philo.ate_count == config->must_eat)
		sem_post(config->full);
	eating_time(config);
	sem_post(config->fork_s);
	sem_post(config->fork_s);
}

static void	sleeping(t_config *config)
{
	sem_wait(config->console);
	console_log(config, SLEEP);
	sem_post(config->console);
	sleeping_time(config);
}

static void	thinking(t_config *config)
{
	sew_wait(config->console);
	console_log(config, THINK);
	sem_post(config->console);
}

void	*routine(void *arg)
{
	t_config *config;

	config = (t_config *)arg;
	config->start_time = get_time();
	while (1)
	{
		eating(config);
		sleeping(config);
		thinking(config);
	}
	return (NULL);
}

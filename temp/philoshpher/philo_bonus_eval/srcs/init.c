/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:38 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:28:23 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_config(t_config *config)
{
	config->id = 0;
	config->philo_cnt = 0;
	config->must_eat = 0;
	config->start_time = 0;
	config->forks = NULL;
	config->console = NULL;
	config->stop = NULL;
	config->full = NULL;
	config->time.die = 0;
	config->time.eat = 0;
	config->time.sleep = 0;
	config->philo = NULL;
}

void	init_semaphore(t_config *config)
{
	sem_unlink("/forks");
	config->forks = sem_open("/forks", O_CREAT, 0644, config->philo_cnt);
	sem_unlink("/console");
	config->console = sem_open("/console", O_CREAT, 0644, 1);
	sem_unlink("/stop");
	config->stop = sem_open("/stop", O_CREAT, 0644, 0);
	if (config->must_eat > 0)
	{
		sem_unlink("/full");
		config->full = sem_open("full", O_CREAT, 0644, 0);
	}
}

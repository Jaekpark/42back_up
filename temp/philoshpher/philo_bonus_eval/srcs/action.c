/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:33 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:46:09 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_eat(t_config *config)
{
	int	i;

	i = config->id;
	console_log(config, EAT, 0);
	config->philo[i].last_ate = get_time();
	++config->philo[i].ate_count;
	eating_time(config);
	if (config->must_eat && config->philo[i].ate_count == config->must_eat)
		if (sem_post(config->full) == -1)
			sem_post(config->stop);
}

void	philo_sleep(t_config *config)
{
	console_log(config, SLEEP, 0);
	sleeping_time(config);
}

void	philo_think(t_config *config)
{
	console_log(config, THINK, 0);
}

void	pickup_fork(t_config *config)
{
	if (sem_wait(config->forks) == -1)
		sem_post(config->stop);
	console_log(config, PICKUP_FORK, 0);
	if (sem_wait(config->forks) == -1)
		sem_post(config->stop);
	console_log(config, PICKUP_FORK, 0);
}

void	put_down_fork(t_config *config)
{
	if (sem_post(config->forks) == -1)
		sem_post(config->stop);
	if (sem_post(config->forks) == -1)
		sem_post(config->stop);
}

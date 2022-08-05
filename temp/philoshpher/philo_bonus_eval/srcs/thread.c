/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:46 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:32:37 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*check_full(void *arg)
{
	int			i;
	t_config	*config;

	i = 0;
	config = (t_config *)arg;
	while (TRUE)
	{
		if (sem_wait(config->full) == -1)
			sem_post(config->stop);
		if (++i && i == config->philo_cnt)
		{
			console_full(config);
			sem_post(config->stop);
		}
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	long long	end;
	t_config	*config;

	config = (t_config *)arg;
	timer(0, config->time.die - 10);
	while (TRUE)
	{
		end = get_time();
		if ((end - config->philo[config->id].last_ate) > config->time.die)
		{
			console_die(config);
			sem_post(config->stop);
		}
	}
	return (NULL);
}

void	routine(t_config *config)
{
	int		i;

	i = config->id;
	if (pthread_create(&config->philo[i].mo, NULL, monitor, config)
		|| pthread_detach(config->philo[i].mo))
		sem_post(config->stop);
	if ((i) % 2)
		timer(0, 100);
	config->philo[i].last_ate = get_time();
	while (TRUE)
	{
		pickup_fork(config);
		philo_eat(config);
		put_down_fork(config);
		philo_sleep(config);
		philo_think(config);
	}
}

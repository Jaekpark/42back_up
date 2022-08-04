/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:36 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:56:05 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	console_log(t_philo *philo, char *status)
{
	pthread_mutex_lock(&(philo->config->console));
	if (philo->status != DIED && philo->config->died <= 0)
	{
		printf("\e[1;34m%8llu\e[0m ", get_time() - philo->config->start_time);
		printf("\e[1m%3d\e[0m %s\n", philo->id, status);
	}
	pthread_mutex_unlock(&(philo->config->console));
}

void	console_die(t_philo *philo)
{
	pthread_mutex_lock(&(philo->config->console));
	if (philo->config->died == 1)
	{
		printf("\e[1;34m%8llu\e[0m ", get_time() - philo->config->start_time);
		printf("\e[1m%3d\e[0m %s\n", philo->id, DEAD);
	}
	pthread_mutex_unlock(&(philo->config->console));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:33 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:54:14 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->config->forks[philo->left_fork]));
	console_log(philo, PICKUP_FORK);
	pthread_mutex_lock(&(philo->config->forks[philo->right_fork]));
	console_log(philo, PICKUP_FORK);
	console_log(philo, EAT);
	philo->last_ate = get_time();
	philo->ate_count++;
	eating_time(philo);
	if (philo->ate_count == philo->config->must_eat)
		philo->status = FULL;
	pthread_mutex_unlock(&(philo->config->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->config->forks[philo->right_fork]));
}

void	philo_sleep(t_philo *philo)
{
	if (philo->config->died <= 0)
	{
		console_log(philo, SLEEP);
		sleeping_time(philo);
	}
}

void	philo_think(t_philo *philo)
{
	if (philo->config->died <= 0)
		console_log(philo, THINK);
}

void	philo_die(t_philo *philo)
{
	philo->status = DIED;
	philo->config->died++;
	console_die(philo);
	pthread_mutex_unlock(&(philo->config->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->config->forks[philo->right_fork]));
}

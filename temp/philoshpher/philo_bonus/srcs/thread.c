/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:46 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:42 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	check_death(t_philo *philos, int i)
{
	long long	start;
	long long	end;

	end = get_time();
	start = philos[i].last_ate;
	if ((end - start) > philos->config->time.die)
	{
		philo_die(&philos[i]);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	int			i;
	t_philo		*philos;

	philos = (t_philo *)data;
	while (philos->config->full != philos->config->philo_cnt)
	{
		i = -1;
		while (++i < philos->config->philo_cnt)
		{
			if (philos[i].status == FULL)
			{
				philos->config->full++;
				break ;
			}
			if (check_death(philos, i))
				return (NULL);
		}
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if ((philo->id - 1) % 2)
		usleep(100);
	while (!philo->config->died && philo->status != DIED)
	{
		philo_eat(philo);
		if (philo->status == FULL)
		{
			console_log(philo, FULLED);
			return (NULL);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	join_all_thread(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->config->philo_cnt)
		if (pthread_join(philos[i].tid, NULL))
			return (ERROR);
	if (pthread_join(philos->config->mo, NULL))
		return (ERROR);
	return (TRUE);
}

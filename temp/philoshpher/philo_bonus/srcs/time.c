/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:49 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:46 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * MILLI_SEC) + (time.tv_usec / MILLI_SEC);
	return (ret);
}

void	eating_time(t_philo *philo)
{
	long long	start;
	long long	end;

	start = get_time();
	end = 0;
	while (1)
	{
		if (philo->config->died)
			return ;
		end = get_time();
		if ((end - start) >= philo->config->time.eat)
			break ;
		usleep(10);
	}
}

void	sleeping_time(t_philo *philo)
{
	long long	start;
	long long	end;

	start = get_time();
	end = 0;
	while (1)
	{
		if (philo->config->died)
			return ;
		end = get_time();
		if ((end - start) >= philo->config->time.sleep)
			break ;
		usleep(10);
	}
}

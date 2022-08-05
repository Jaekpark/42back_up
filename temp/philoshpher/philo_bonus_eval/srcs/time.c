/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:49 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:28:00 by jaekpark         ###   ########.fr       */
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

void	eating_time(t_config *config)
{
	long long	start;
	long long	end;

	start = get_time();
	end = 0;
	while (1)
	{
		end = get_time();
		if ((end - start) >= config->time.eat)
			break ;
		usleep(10);
	}
}

void	sleeping_time(t_config *config)
{
	long long	start;
	long long	end;

	start = get_time();
	end = 0;
	while (1)
	{
		end = get_time();
		if ((end - start) >= config->time.sleep)
			break ;
		usleep(10);
	}
}

void	timer(long long start, long long end)
{
	long long	now;

	if (!start)
		start = get_time();
	while (TRUE)
	{
		now = get_time();
		if (now - start >= end)
			break ;
		usleep(10);
	}
}

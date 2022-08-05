/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:36 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:27:33 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	console_log(t_config *config, char *status, int post)
{
	sem_wait(config->console);
	printf("\e[1;34m%8llu\e[0m ", get_time() - config->start_time);
	printf("\e[1m%3d\e[0m %s\n", config->id, status);
	if (post)
		return ;
	sem_post(config->console);
}

void	console_die(t_config *config)
{
	sem_wait(config->console);
	printf("\e[1;34m%8llu\e[0m ", get_time() - config->start_time);
	printf("\e[1m%3d\e[0m %s\n", config->id, DEAD);
}

void	console_full(t_config *config)
{
	sem_wait(config->console);
	printf("\e[1;34m%8llu\e[0m ", get_time() - config->start_time);
	printf("  All philosophers are full\n");
}

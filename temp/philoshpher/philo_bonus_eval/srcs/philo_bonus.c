/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:14 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:51:41 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	terminate_simulation(t_config *config, int ret)
{
	int	i;

	i = -1;
	sem_unlink("forks");
	sem_unlink("console");
	sem_unlink("full");
	sem_unlink("stop");
	while (++i < config->philo_cnt)
	{
		kill(config->philo[config->id].pid, SIGKILL);
		waitpid(config->philo[config->id].pid, NULL, WNOHANG);
	}
	free(config->philo);
	return (ret);
}

int	start_simulation(t_config *config)
{
	int	i;

	i = -1;
	if (!config)
		return (console_error("Data structure error.\n"));
	if (config->must_eat > 0)
		if (pthread_create(&config->mo, NULL, check_full, config)
			|| pthread_detach(config->mo))
			return (FALSE);
	config->start_time = get_time();
	while (++i < config->philo_cnt)
	{
		config->id = i;
		config->philo[i].pid = fork();
		if (config->philo[i].pid < 0)
			return (FALSE);
		else if (config->philo[i].pid == 0)
		{
			routine(config);
			exit(0);
		}
	}
	if (sem_wait(config->stop) == -1)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_config	config;

	memset(&config, 0, sizeof(t_config));
	if (!check_arg(argc, argv))
		return (ERROR);
	if (!set_config(argc, argv, &config))
		return (ERROR);
	if (!check_philo(&config) || !set_philo(&config))
		return (ERROR);
	if (!start_simulation(&config))
		return (terminate_simulation(&config, 1));
	return (terminate_simulation(&config, 0));
}

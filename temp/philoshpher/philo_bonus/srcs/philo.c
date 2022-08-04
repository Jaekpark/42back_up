/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:08:14 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 13:55:29 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	exit_error(t_philo *philos)
{
	if (philos)
		terminate_simulation(philos);
	return (ERROR);
}

static void	free_config(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->philo_cnt)
		pthread_mutex_destroy(&(config->forks[i]));
	pthread_mutex_destroy(&(config->console));
	free(config->forks);
	free(config);
}

int	terminate_simulation(t_philo *philos)
{
	int			i;
	t_config	*config;

	i = -1;
	if (!philos)
		return (FALSE);
	config = philos->config;
	if (!config)
		return (FALSE);
	while (++i < config->philo_cnt)
		philos[i].config = NULL;
	free(philos);
	free_config(config);
	return (TRUE);
}

int	start_simulation(t_philo *philos)
{
	int	i;

	i = -1;
	if (!philos)
		return (console_error("Data structure error.\n"));
	philos->config->start_time = get_time();
	while (++i < philos->config->philo_cnt)
	{
		philos[i].last_ate = get_time();
		if (pthread_create(&(philos[i].tid), NULL, routine, (void *)&philos[i]))
			return (console_error("pthread_create error.\n"));
	}
	if (pthread_create(&(philos->config->mo), NULL, monitor, (void *)philos))
		return (console_error("pthread_create error.\n"));
	if (!join_all_thread(philos))
		return (console_error("pthread_join error.\n"));
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_config	*config;

	if (!check_arg(argc, argv))
		return (ERROR);
	config = set_config(argc, argv);
	philos = set_philo(config);
	if (!check_philo(philos))
		return (ERROR);
	if (!philos || !config)
		return (ERROR);
	if (!start_simulation(philos))
		return (exit_error(philos));
	terminate_simulation(philos);
	return (0);
}

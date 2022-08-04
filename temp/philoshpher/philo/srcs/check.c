/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:55:35 by jaekpark          #+#    #+#             */
/*   Updated: 2022/03/28 15:01:54 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	console_error(char *err)
{
	ft_putstr_fd(STDERR_FILENO, err);
	return (FALSE);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || !argv)
		return (console_error("Please enter at least four parameters.\n"));
	if (argc > 6)
		return (console_error("Too many parameters.\n"));
	while (argv[++i])
		if (!ft_strdigit(argv[i]))
			return (console_error("Please enter only (+)numbers.\n"));
	return (TRUE);
}

int	check_philo(t_philo *philos)
{
	t_time	time;

	if (!philos)
		return (console_error("Data structure error.\n"));
	if (!philos->config)
		return (console_error("Data structure error.\n"));
	time = philos->config->time;
	if (philos->config->philo_cnt <= 0)
		return (console_error("The program requires at least 1 philos.\n"));
	if (time.die <= 0 || time.eat <= 0 || time.sleep <= 0)
		return (console_error("Zero or negative numbers are not allowed.\n"));
	if (philos->config->must_eat < 0)
		return (console_error("Negative numbers are not allowed.\n"));
	return (TRUE);
}

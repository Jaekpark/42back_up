/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:37:58 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/04 14:19:53 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

# define MILLI_SEC 1000

# define PICKUP_FORK "\033[0;36mhas taken a fork\033[0m"
# define EAT "\033[0;33mis eating\033[0m"
# define SLEEP "\033[0;35mis sleeping\033[0m"
# define THINK "\033[0;34mis thinking\033[0m"
# define DEAD "\033[0;31;43mdied\033[0m"
# define FULLED "\033[0;30;42mis full, He dances happily\033[0m"
# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct s_time
{
	long long	die;
	long long	eat;
	long long	sleep;
}	t_time;

typedef struct s_philosophers
{
	pthread_t	tid;
	sem_t		*action;
	int			id;
	int			ate_count;
	long long	last_ate;
	int			eat_limit;
}	t_philo;

typedef struct s_configure 
{
	pthread_t	tid;
	pid_t		pid;
	t_time		time;
	long long	start_time;
	int			must_eat;
	int 		philo_count;
	sem_t		*console;
	sem_t		*fork_s;
	sem_t		*stop;
	sem_t		*full;
	t_philo		philo;
}	t_config;

void		init_config(t_config *config);
int			init_philo(t_philo *philos, t_config *config);
int			init_mutex(t_config *config);
int			set_time(t_time *time, char **argv);
t_config	*set_config(int argc, char **argv);
t_philo		*set_philo(t_config *config);
long long	get_time(void);
void		eating_time(t_philo *philo);
void		sleeping_time(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_die(t_philo *philo);
void		console_philo(t_philo *philo, char *status);
void		console_log(t_philo *philo, char *status);
void		console_die(t_philo *philo);
int			console_error(char *err);
void		*routine(void *data);
void		*monitor(void *data);
int			check_arg(int argc, char **argv);
int			check_philo(t_philo *philos);
int			ft_strlen(char *str);
int			ft_isdigit(char c);
int			ft_strdigit(char *str);
void		ft_putstr_fd(int fd, char *str);
long long	ft_atoll(const char *str);
int			terminate_simulation(t_philo *philos);
int			join_all_thread(t_philo *philos);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:37:58 by jaekpark          #+#    #+#             */
/*   Updated: 2022/08/05 09:51:52 by jaekpark         ###   ########.fr       */
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
# include <memory.h>

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

typedef enum e_state
{
	BORN,
	DIED,
	FULL
}	t_state;

typedef struct s_time
{
	long long	die;
	long long	eat;
	long long	sleep;
}	t_time;

typedef struct s_philosopher
{
	pid_t		pid;
	pthread_t	mo;
	int			ate_count;
	long long	last_ate;
}	t_philo;

typedef struct s_configure
{
	int				id;
	int				philo_cnt;
	int				must_eat;
	long long		start_time;
	pthread_t		mo;
	sem_t			*forks;
	sem_t			*console;
	sem_t			*full;
	sem_t			*stop;
	t_time			time;
	t_philo			*philo;
}	t_config;

void		init_config(t_config *config);
int			set_time(t_time *time, char **argv);
int			set_config(int argc, char **argv, t_config *config);
int			set_philo(t_config *config);
long long	get_time(void);
void		eating_time(t_config *config);
void		sleeping_time(t_config *config);
void		*check_death(void *arg);
void		init_semaphore(t_config *config);
void		philo_eat(t_config *config);
void		philo_sleep(t_config *config);
void		philo_think(t_config *config);
void		console_log(t_config *config, char *status, int post);
void		console_die(t_config *config);
int			console_error(char *err);
void		routine(t_config *config);
void		*monitor(void *arg);
int			check_arg(int argc, char **argv);
int			check_philo(t_config *conf);
int			ft_strlen(char *str);
int			ft_isdigit(char c);
int			ft_strdigit(char *str);
void		ft_putstr_fd(int fd, char *str);
long long	ft_atoll(const char *str);
void		timer(long long start, long long end);
void		console_full(t_config *config);
void		pickup_fork(t_config *config);
void		put_down_fork(t_config *config);
void		*check_full(void *arg);

#endif

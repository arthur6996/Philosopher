/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 16:40:16 by abourbou          #+#    #+#             */
/*   Updated: 2021/02/18 11:07:41 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct	s_lmutex
{
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_speak;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_eating;
}				t_lmutex;

typedef struct	s_vars
{
	long	number_phil;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meal;
	long	*compt_meal;
	long	*last_meal;
	int		stop;
	long	start_time;
}				t_vars;

typedef struct	s_kit
{
	t_vars		*vars;
	t_lmutex	*lmutex;
	long		my_number;
	long		number_meal;
}				t_kit;

/*
** TOOLS
*/
long			ft_atoi(char *str);
long			get_time(void);
void			ft_putstr(char *str);
void			ft_putnbr(long nbr);
long			sleep_with_one_eye(t_vars *glob_var, long time_sleep);

/*
**LAUNCH THREADS
*/
int				launch_threads(t_vars *global_var, t_lmutex *lst_mutex,
												long number_phil);

/*
** MANAGEMENT_VAR
*/
int				init_glob(t_vars **glob_var, int argc, char **argv);
t_lmutex		*init_mutex(long number_phil, int i);
void			destroy_glob(t_vars *glob_var, t_lmutex *lmutex, int i);

/*
** CYCLE_THREAD
*/
void			*cycle_thread(void *vkit);
void			philo_speak(t_kit *kit, long start_time, long my_number,
													char *message);

/*
** MONITORING_THREADS
*/
void			*monitoring_threads(void *pkit);
#endif

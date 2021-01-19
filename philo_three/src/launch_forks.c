/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:42:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/17 21:36:19 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			destroy_fork(pid_t *tab_pid, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (tab_pid[i])
			kill(tab_pid[i], SIGINT);
		i++;
	}
}

void		find_fork(pid_t *tab_pid, int max, pid_t id)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (tab_pid[i] == id)
		{
			tab_pid[i] = 0;
			break;
		}
		i++;
	}
}

int				launch_forks(t_vars *global_var, t_lsem *lst_sem, long number_phil)
{
	int		i;
	pid_t	*tab_pid;
	pid_t	pid_ret;
	t_kit	kit;
	int		status;

	memset(&kit, 0, sizeof(kit));
	kit.vars = global_var;
	kit.l_sem = lst_sem;
	if (!(tab_pid = malloc(sizeof(pid_t) * number_phil)))
		return (0);
	kit.vars->start_time = get_time();
	i = 0;
	while (i < number_phil)
	{
		if ((tab_pid[i] = fork()) < 0)
		{
			destroy_fork(tab_pid, i);
			ft_putstr("Error creation fork\n");
			return (-1);
		}
		if (tab_pid[i] == 0)
		{
			kit.my_number = i;
			cycle_fork(&kit);
			exit(2);
		}
		i++;
	}
	i = 0;
	while (i < number_phil)
	{
		pid_ret = waitpid(-1, &status, 0);
		find_fork(tab_pid, number_phil, pid_ret);
		if (status % 255 == 1)
		{
			destroy_fork(tab_pid, number_phil);
			break;
		}
		i++;
	}
	free(tab_pid);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:09:01 by abourbou          #+#    #+#             */
/*   Updated: 2021/02/18 11:10:27 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	verif_glob(t_vars *glob_var, int argc)
{
	if ((glob_var->number_phil <= 1 || glob_var->number_phil > 1000) ||
		glob_var->time_to_die <= 0 || glob_var->time_to_eat <= 0 ||
		glob_var->time_to_sleep <= 0 || (argc == 6 && glob_var->max_meal <= 0))
		return (-1);
	return (1);
}

t_lsem		*init_sem(long number_phil)
{
	t_lsem	*lstsem;

	if (!(lstsem = malloc(sizeof(t_lsem))))
	{
		ft_putstr("Malloc error\n");
		return (0);
	}
	sem_unlink("sem_fork");
	sem_unlink("sem_speak");
	sem_unlink("sem_meal");
	sem_unlink("sem_eating");
	lstsem->s_fork = sem_open("sem_fork", O_CREAT, 00777, (int)number_phil);
	lstsem->s_speak = sem_open("sem_speak", O_CREAT, 00777, 1);
	lstsem->s_meal = sem_open("sem_meal", O_CREAT, 00777, 1);
	lstsem->s_eating = sem_open("sem_eating", O_CREAT, 00777, 1);
	if (lstsem->s_fork == SEM_FAILED || lstsem->s_meal == SEM_FAILED
	|| lstsem->s_speak == SEM_FAILED || lstsem->s_eating == SEM_FAILED)
	{
		ft_putstr("Error : sem_open failed\n");
		free(lstsem);
		return (0);
	}
	return (lstsem);
}

static void	init_fix_glob(t_vars *glob_var, int argc, char **argv)
{
	glob_var->number_phil = ft_atoi(argv[1]);
	glob_var->time_to_die = ft_atoi(argv[2]);
	glob_var->time_to_eat = ft_atoi(argv[3]);
	glob_var->time_to_sleep = ft_atoi(argv[4]);
	glob_var->max_meal = (argc == 6) ? ft_atoi(argv[5]) : -1;
	glob_var->compt_meal = 0;
	glob_var->stop = 0;
	glob_var->last_meal = 0;
	glob_var->start_time = 0;
}

/*
**	return 1 if it is a success
**	return 0 if malloc error
**	return -1 if bad variables
*/

int			init_glob(t_vars **pglob_var, int argc, char **argv)
{
	t_vars	*glob_var;

	if (!(glob_var = malloc(sizeof(t_vars))))
		return (0);
	*pglob_var = glob_var;
	init_fix_glob(glob_var, argc, argv);
	if (verif_glob(glob_var, argc) != 1)
		return (-1);
	if (!(glob_var->last_meal = malloc(sizeof(long) * glob_var->number_phil)))
		return (0);
	memset(glob_var->last_meal, 0, sizeof(long) * glob_var->number_phil);
	if (argc == 6)
	{
		if ((glob_var->compt_meal = malloc(sizeof(long) *
		(glob_var->number_phil + 1))) == 0)
			return (0);
		memset(glob_var->compt_meal, 0, glob_var->number_phil * sizeof(long));
		glob_var->compt_meal[glob_var->number_phil] = -1;
	}
	return (1);
}

void		destroy_glob(t_vars *glob_var, t_lsem *lsem)
{
	if (!glob_var)
		return ;
	if (glob_var->compt_meal)
		free(glob_var->compt_meal);
	if (glob_var->last_meal)
		free(glob_var->last_meal);
	if (lsem)
	{
		sem_unlink("sem_fork");
		sem_unlink("sem_speak");
		sem_unlink("sem_meal");
		sem_unlink("sem_eating");
		free(lsem);
	}
	free(glob_var);
}

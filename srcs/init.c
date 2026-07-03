/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:12:37 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 16:08:28 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** get_rules:
**     Initializes and sets default values in t_rules struct
**
**     @param *rules  Pointer to t_rules structure
**	   @param **av	  Arguments string array
**     @return true if everything is fine / false if not
*/
bool	get_rules(t_rules *rules, char **av)
{
	rules->forks = NULL;
	rules->philosophers_nb = atoi(av[1]);
	rules->time_to_die = atoi(av[2]);
	rules->time_to_eat = atoi(av[3]);
	rules->time_to_sleep = atoi(av[4]);
	rules->launch_time = get_time_ms();
	rules->must_eat_number = -1;
	if (av[5])
		rules->must_eat_number = atoi(av[5]);
	if ((rules->philosophers_nb < 1 || rules->time_to_die < 1
			|| rules->time_to_eat < 1 || rules->time_to_sleep < 1)
		|| (av[5] && rules->must_eat_number < 1))
		return (false);
	rules->print_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!rules->print_mutex)
		return (false);
	if (pthread_mutex_init(rules->print_mutex, NULL))
	{
		free(rules->print_mutex);
		rules->print_mutex = NULL;
		return (false);
	}
	return (true);
}

/*
** alloc_forks:
**     Initialized mutex for every fork
**
**     @param *forks  Pointer to fork array
**     @return true / false if failure
*/
bool	alloc_forks(pthread_mutex_t *forks, int n)
{
	int	i;
	int	r;
	int	j;

	if (!forks)
		return (false);
	i = 0;
	while (i < n)
	{
		r = 0;
		r = pthread_mutex_init(&forks[i], NULL);
		if (r > 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&forks[j]);
				j++;
			}
			return (false);
		}
		i++;
	}
	return (true);
}

/*
** _terminate_philos:
**     Way to early tell the manager to terminate philo if an error occured 
**	   while spawning threads
*/
static void	_terminate_philos(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philosophers_nb)
	{
		if (philos[i].meal_mutex)
		{
			pthread_mutex_lock(philos[i].meal_mutex);
			philos[i].should_die = true;
			pthread_mutex_unlock(philos[i].meal_mutex);
		}
		i++;
	}
}

/*
** initialize_threads:
**     Initializes philosopher threads + manager thread.
**     NB: needed to create a custom struct to pass data to manager thread
**
**     @return true / false if error.
*/
bool	initialize_threads(t_philo *philos, t_rules *rules, \
pthread_mutex_t *forks)
{
	rules->forks = forks;
	if (!spawn_philos(philos, rules->philosophers_nb, rules, forks))
	{
		_terminate_philos(philos, rules);
		return (false);
	}
	if (pthread_create(&rules->manager, NULL, &manage_philo, philos))
	{
		_terminate_philos(philos, rules);
		return (false);
	}
	return (true);
}

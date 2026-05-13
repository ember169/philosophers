/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:12:37 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:28:26 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

bool	get_rules(t_rules *rules, char **av)
{
	rules->manager = NULL;
	rules->philosophers_nb = atoi(av[1]);
	rules->time_to_die = atoi(av[2]);
	rules->time_to_eat = atoi(av[3]);
	rules->time_to_sleep = atoi(av[4]);
	rules->launch_time = get_time_ms();
	if (av[5])
		rules->must_eat_number = atoi(av[5]);
	// TODO: implem les limites aux regles donnees
		// Notes:
			// dans tout les cas  : time_to_die > time_to_eat + time_to_sleep
			// ET
			// Pour n pair : time_to_die > 2 * time_to_eat
			// Pour n impair : time_to_die > (2 * NB) / (NB -1)) * time_to_eat
	if ((rules->philosophers_nb < 1 || rules->time_to_die < 1 || \
rules->time_to_eat < 1 || rules->time_to_sleep < 1) || \
(av[5] && rules->must_eat_number < 1))
		return (false);
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

	if (!forks)
		return (false);
	i = 0;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (i);
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
	if (!create_threads(philos, rules->philosophers_nb, rules, forks))
		return (false);
	if (!pthread_create(&rules->manager, NULL, &manage_philo, philos))
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:59:17 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:21:14 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"


static int	_check_death(t_philo philo, t_rules rules)
{
	int	res;
	int	time_since_meal;

	res = 0;
	time_since_meal = get_time_since_launch(&rules) - philo.last_meal_time;
	pthread_mutex_lock(philo.meal_mutex);
	if (time_since_meal > rules.time_to_die)
	{
		philo.should_die = 1;
		res++;
	}
	pthread_mutex_unlock(philo.meal_mutex);
	return (res);
}

/*
** manage_philo:
**     Makes sure all philosopher are alive, calls exit when not
**
**     @param *philos  Pointer to philosopher structure
**     @param rules    Rules structure
**     @param *forks   Pointer to forks structure
*/
void	*manage_philo(
			t_philo *philos,
			t_rules rules,
			pthread_mutex_t *forks)
{
	int	i;
	int	j;

	if (!philos || !forks)
		return (NULL);
	j = 0;
	while (j < rules.philosophers_nb)
	{
		i = 0;
		while (i < rules.philosophers_nb)
			j += _check_death(philos[i++], rules);
	}
	printf(PF_RED"[i] All philos died, exiting\n"PF_RESET);
	return (clean_exit(philos, forks), NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:59:17 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/24 14:11:34 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// check death condition for a single philo
static bool	_is_dead(t_philo *philo, t_rules *rules)
{
	bool	res;
	int		time_since_meal;

	res = false;
	pthread_mutex_lock(philo->meal_mutex);
	time_since_meal = get_uptime(rules) - philo->last_meal_time;
	if (philo->should_die == 1 || time_since_meal > rules->time_to_die)
	{
		philo->should_die = 1;
		res = true;
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (res);
}

// check death condition for every philos
static bool	_are_dead(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philosophers_nb)
	{
		if (_is_dead(&philos[i], rules))
			return (true);
		i++;
	}
	return (false);
}

void	*manage_philo(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;

	philos = arg;
	rules = philos[0].rules;
	while (!_are_dead(philos, rules))
		usleep(1000);
	return (NULL);
}

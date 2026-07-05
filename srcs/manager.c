/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:59:17 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 14:28:49 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** _is_dead:
**     Returns true when all one thread need to be terminated
**
**     @return true / false.
*/
static bool	_is_dead(t_philo *philo, t_rules *rules)
{
	bool	res;
	double	time_since_meal;
	double	death_time;

	res = false;
	pthread_mutex_lock(philo->meal_mutex);
	if (!philo->ate_enough)
	{
		time_since_meal = get_uptime(rules) - philo->last_meal_time;
		if (time_since_meal > rules->time_to_die)
		{
			philo->should_die = true;
			death_time = get_uptime(philo->rules);
			print_state(philo->rules, death_time, philo->id, "died");
		}
	}
	if (philo->should_die == true)
		res = true;
	pthread_mutex_unlock(philo->meal_mutex);
	return (res);
}

/*
** _all_are_dead:
**     Returns true when all the threads need to be terminated
**
**     @return true / false.
*/
static bool	_all_are_dead(t_philo *philos, t_rules *rules)
{
	int	i;
	int	j;

	i = 0;
	while (i < rules->philosophers_nb)
	{
		if (_is_dead(&philos[i], rules))
		{
			j = 0;
			while (j < rules->philosophers_nb)
			{
				pthread_mutex_lock(philos[j].meal_mutex);
				philos[j].should_die = true;
				pthread_mutex_unlock(philos[j].meal_mutex);
				j++;
			}
			return (true);
		}
		i++;
	}
	return (false);
}

/*
** _all_ate_enough:
**     Returns true when all the threads made the maximum cycle number
**
**     @return true / false.
*/
static bool	_all_ate_enough(t_philo *philos, t_rules *rules)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rules->philosophers_nb)
	{
		pthread_mutex_lock(philos[i].meal_mutex);
		if (philos[i].meals_eaten == rules->must_eat_number
			|| philos[i].ate_enough == true)
		{
			philos[i].ate_enough = true;
			j++;
		}
		pthread_mutex_unlock(philos[i].meal_mutex);
		i++;
	}
	if (j == rules->philosophers_nb)
		return (true);
	return (false);
}

/*
** manage_philo:
**     Thread manager: checks periodically if they are or should be terminated.
**	   Returns when all need to be terminated.
**
**     @param arg	uncasted pointer to t_philo structure.
*/
void	*manage_philo(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		k;

	philos = arg;
	rules = philos[0].rules;
	while (true)
	{
		if (_all_are_dead(philos, rules))
			break ;
		if (_all_ate_enough(philos, rules))
		{
			k = 0;
			while (k < rules->philosophers_nb)
			{
				pthread_mutex_lock(philos[k].meal_mutex);
				philos[k].should_die = true;
				pthread_mutex_unlock(philos[k].meal_mutex);
				k++;
			}
		}
		usleep(1000);
	}
	return (NULL);
}

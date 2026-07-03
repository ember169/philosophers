/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:45:21 by mskn              #+#    #+#             */
/*   Updated: 2026/06/11 16:09:11 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** _dispatch_single:
**     Manages the edge case of only one Philosopher. Since he has no right to
**     take both forks, he takes one and loops until starvation.
**
**     @param *philo	Pointer to current philosopher structure.
**     @return always false.
*/
static bool	_dispatch_single(t_philo *philo)
{
	if (philo && philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->rules, get_uptime(philo->rules),
			philo->id, "has taken a fork");
		while (true)
		{
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
			{
				pthread_mutex_unlock(philo->meal_mutex);
				break ;
			}
			pthread_mutex_unlock(philo->meal_mutex);
			usleep(1000);
		}
		pthread_mutex_unlock(philo->left_fork);
	}
	return (false);
}

/*
** _eat:
**     Changes last_meal_time, meals_eaten, prints eat log and sleeps
**
**     @param *philo	Pointer to current philosopher structure.
*/
static bool	_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	philo->last_meal_time = get_uptime(philo->rules);
	philo->meals_eaten++;
	print_state(philo->rules, philo->last_meal_time,
		philo->id, "is eating");
	pthread_mutex_unlock(philo->meal_mutex);
	c_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

/*
** _dispatch_even:
**	   Takes left and right fork, checks if should die, print logs, call _eat()
**
**     @param *philo	Pointer to current philosopher structure.
**     @return false if should_die == 1 or _eat() == 0 // else true.
*/
static bool	_dispatch_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
		return (pthread_mutex_unlock(philo->meal_mutex),
			pthread_mutex_unlock(philo->left_fork), false);
	print_state(philo->rules, get_uptime(philo->rules),
		philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
	{
		return (pthread_mutex_unlock(philo->meal_mutex),
			pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), false);
	}
	print_state(philo->rules, get_uptime(philo->rules),
		philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->meal_mutex);
	return (_eat(philo));
}

/*
** _dispatch_odd:
**	   Takes right and left fork, checks if should die, print logs, call _eat()
**
**     @param *philo	Pointer to current philosopher structure.
**     @return false if should_die == 1 or _eat() == 0 // else true.
*/
static bool	_dispatch_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
		return (pthread_mutex_unlock(philo->meal_mutex),
			pthread_mutex_unlock(philo->right_fork), false);
	print_state(philo->rules, get_uptime(philo->rules),
		philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
		return (pthread_mutex_unlock(philo->meal_mutex),
			pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), false);
	print_state(philo->rules, get_uptime(philo->rules),
		philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->meal_mutex);
	return (_eat(philo));
}

/*
** could_eat:
**	   Dispatches according to current case (only 1 philosopher || even / odd id)
**	   Next functions return true or false if they could or couldnt eat
**
**     @param *philo	Pointer to current philosopher structure.
**     @return true / false if coudnt eat.
*/
bool	could_eat(t_philo *philo)
{
	if (!philo || !philo->left_fork || !philo->right_fork)
		return (false);
	if (philo->rules->philosophers_nb == 1)
		return (_dispatch_single(philo));
	if (philo->id % 2 == 0)
		return (_dispatch_even(philo));
	else
		return (_dispatch_odd(philo));
}

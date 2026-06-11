/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 13:13:17 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** try_to_eat_one:
**     Manages the case of only one Philosopher
**
**     @param *philo	Pointer to current philosopher structure.
**     @return true / false if coudnt eat.
*/
static bool	try_to_eat_one(t_philo *philo)
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
** try_to_eat:
**     Each thread will try to lock both forks, when success will lock "meal"
	   mutex, update last meal time, print meal, wait, unlock mutexes
**
**     @param *philo	Pointer to current philosopher structure.
**     @return true / false if coudnt eat.
*/
static bool	try_to_eat(t_philo *philo)
{
	bool	res;

	res = true;
	if (!philo || !philo->left_fork || !philo->right_fork)
		return (false);
	if (philo->rules->philosophers_nb == 1)
		res = try_to_eat_one(philo);
	else
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex),
					pthread_mutex_unlock(philo->left_fork), false);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex),
					pthread_mutex_unlock(philo->right_fork),
					pthread_mutex_unlock(philo->left_fork), false);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex),
					pthread_mutex_unlock(philo->right_fork), false);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex),
					pthread_mutex_unlock(philo->left_fork),
					pthread_mutex_unlock(philo->right_fork), false);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "has taken a fork");
		}
		pthread_mutex_lock(philo->meal_mutex);
		philo->last_meal_time = get_uptime(philo->rules);
		philo->meals_eaten++;
		print_state(philo->rules, philo->last_meal_time,
			philo->id, "is eating");
		pthread_mutex_unlock(philo->meal_mutex);
		c_sleep(philo->rules->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (res);
}

/*
** routine:
**     What every thread will do as soon as born: try to eat, sleep, think
**		Returns immediately without dying if ate_enough
*/
static void	*routine(void *arg)
{
	t_philo	*philo;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	if (philo->id > 1 && philo->rules->philosophers_nb > 1)
	{
		c_sleep((philo->id - 1) * philo->rules->time_to_eat
			/ philo->rules->philosophers_nb);
		pthread_mutex_lock(philo->meal_mutex);
		philo->last_meal_time = get_uptime(philo->rules);
		pthread_mutex_unlock(philo->meal_mutex);
	}
	while (true)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->should_die)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->meal_mutex);
		if (try_to_eat(philo))
		{
			if (philo->rules->must_eat_number > 0
				&& (philo->meals_eaten >= philo->rules->must_eat_number))
			{
				pthread_mutex_lock(philo->meal_mutex);
				philo->ate_enough = true;
				pthread_mutex_unlock(philo->meal_mutex);
				return (NULL);
			}
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex), NULL);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "is sleeping");
			c_sleep(philo->rules->time_to_sleep);
			pthread_mutex_lock(philo->meal_mutex);
			if (philo->should_die)
				return (pthread_mutex_unlock(philo->meal_mutex), NULL);
			pthread_mutex_unlock(philo->meal_mutex);
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "is thinking");
		}
		else
			usleep(1000);
	}
	return (NULL);
}

/*
** create_threads:
**     Allocate and initializes everything needed for each thread:
**		- Philosopher ID
**		- Mutex for meal printf
**		- Last time philosopher ate (atm born time)
**		- Rules structure pointer
**		- Left fork mutex pointer
**		- Right fork mutex pointer
**
**     @param *philos 	Pointer to philosopher structure
**     @param n  		Number of thread to create
**     @param *rules	Pointer to rules structure
**     @param *forks	Pointer to forks array
**     @return true / false if failure.
*/
bool	spawn_philos(
	t_philo *philos,
	int n,
	t_rules *rules,
	pthread_mutex_t *forks)
{
	int	i;

	if (!philos || !rules || !forks)
		return (false);
	i = 0;
	while (i < n)
	{
		philos[i].id = i + 1;
		philos[i].should_die = false;
		philos[i].ate_enough = false;
		philos[i].meals_eaten = 0;
		philos[i].meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philos[i].meal_mutex)
			return (false);
		pthread_mutex_init(philos[i].meal_mutex, NULL);
		philos[i].last_meal_time = get_uptime(rules);
		philos[i].rules = rules;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % n];
		if (pthread_create(&philos[i].thread_id, NULL, &routine, &philos[i])
			!= 0)
			return (false);
		i++;
	}
	return (true);
}

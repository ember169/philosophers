/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 16:08:40 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** _needs_termination:
**     Checks if max cycles has been reached (ate_enough) and should die is true
*/
static bool	_needs_termination(t_philo *philo)
{
	if (philo->rules->must_eat_number > 0
		&& (philo->meals_eaten >= philo->rules->must_eat_number))
	{
		pthread_mutex_lock(philo->meal_mutex);
		philo->ate_enough = true;
		pthread_mutex_unlock(philo->meal_mutex);
		return (true);
	}
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->should_die)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (false);
}

/*
** _routine_loop:
**     Checks if max cycles has been reached (ate_enough) and should die is true
*/
static void	_routine_loop(t_philo *philo)
{
	while (true)
	{
		if (_needs_termination(philo))
			break ;
		if (could_eat(philo))
		{
			if (_needs_termination(philo))
				break ;
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "is sleeping");
			c_sleep(philo->rules->time_to_sleep);
			if (_needs_termination(philo))
				break ;
			print_state(philo->rules, get_uptime(philo->rules),
				philo->id, "is thinking");
		}
		else
			usleep(1000);
	}
}

/*
** routine:
**     Sets last_meal_time at startup time, then call the thread loop
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
	_routine_loop(philo);
	return (NULL);
}

static bool	_set_philo_up(t_philo *philo, int i, int n, t_rules *rules,
	pthread_mutex_t *forks)
{
	philo->id = i + 1;
	philo->should_die = false;
	philo->ate_enough = false;
	philo->meals_eaten = 0;
	philo->meal_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!philo->meal_mutex)
		return (false);
	if (pthread_mutex_init(philo->meal_mutex, NULL))
	{
		free(philo->meal_mutex);
		philo->meal_mutex = NULL;
		return (false);
	}
	philo->last_meal_time = get_uptime(rules);
	philo->rules = rules;
	philo->left_fork = &forks[i];
	philo->right_fork = &forks[(i + 1) % n];
	return (true);
}

/*
** spawn_philos:
**     Allocate and initializes everything needed for each thread:
**	   ID, Mutexes, Last meal (atm born time), structures pointer, ...
**
**     @param *philos 	Pointer to philosopher structure
**     @param n  		Number of thread to create
**     @param *rules	Pointer to rules structure
**     @param *forks	Pointer to forks array
**     @return true / false if failure.
*/
bool	spawn_philos(t_philo *philos, int n, t_rules *rules,
	pthread_mutex_t *forks)
{
	int	i;

	if (!philos || !rules || !forks)
		return (false);
	i = 0;
	while (i < n)
	{
		if (!_set_philo_up(&philos[i], i, n, rules, forks))
			return (false);
		if (pthread_create(&philos[i].thread_id, NULL, &routine, &philos[i]))
			return (false);
		i++;
	}
	return (true);
}

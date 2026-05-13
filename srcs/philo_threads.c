/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:09:39 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

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
	if (!philo || !philo->left_fork || !philo->right_fork)
		return (false);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_time_since_launch(philo->rules);
	printf("%f:.2f %d is eating\n", philo->last_meal_time, philo->id);
	pthread_mutex_unlock(philo->meal_mutex);
	c_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

/*
** routine:
**     What every thread will do as soon as born: try to eat, sleep, think
*/
static void	*routine(void *arg)
{
	t_philo	*philo;
	int		ate;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	printf(PF_GREEN"%f %d is born"PF_RESET"\n", \
get_time_since_launch(philo->rules), philo->id);
	while (!philo->should_die)
	{
		ate = try_to_eat(philo);
		if (ate)
		{
			printf("%f:.2f %d is sleeping\n", \
get_time_since_launch(philo->rules), philo->id);
			c_sleep(philo->rules->time_to_sleep);
			printf("%f:.2f %d is thinking\n", \
get_time_since_launch(philo->rules), philo->id);
		}
	}
	printf(PF_RED"%f %d died\n"PF_RESET, \
get_time_since_launch(philo->rules), philo->id);
	pthread_join(philo->thread_id, NULL);
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
bool	create_threads(
	t_philo *philos,
	int n,
	t_rules *rules,
	pthread_mutex_t *forks)
{
	int	i;
	int	res;

	if (!philos || !rules || !forks)
		return (false);
	i = 0;
	while (i < n)
	{
		philos[i].id = i + 1;
		philos[i].should_die = 0;
		philos[i].meal_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philos[i].meal_mutex)
			return (false);
		pthread_mutex_init(philos[i].meal_mutex, NULL);
		philos[i].last_meal_time = get_time_since_launch(rules);
		philos[i].rules = rules;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % n];
		res = pthread_create(&philos[i].thread_id, NULL, &routine, &philos[i]);
		if (res != 0)
			return (false);
		i++;
	}
	return (true);
}

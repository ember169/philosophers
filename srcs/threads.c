/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/16 15:56:30 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	try_to_eat(t_philo *philosopher)
{
	if (!pthread_mutex_lock(*philosopher->left_fork) &&\
!pthread_mutex_lock(*philosopher->left_fork))
		return (0);

	philosopher->last_meal_time = get_time();
	printf("%ld %d is eating\n", get_time(), philosopher->id);
	usleep(philosopher->rules->time_to_eat);
	pthread_mutex_unlock(*philosopher->left_fork);
	pthread_mutex_unlock(*philosopher->right_fork);
	return (1);
}

static void	*routine(void *arg)
{
	t_philo	*philosopher;
	int		ate;

	philosopher = (t_philo *)arg;
	printf(PF_GREEN"%ld %d is born"PF_RESET"\n", get_time(), philosopher->id);
	while (1)
	{
		ate = try_to_eat(philosopher);
		if (ate)
		{
			printf("%ld %d is sleeping\n", get_time(), philosopher->id);
			usleep(philosopher->rules->time_to_sleep);
			printf("%ld %d is thinking\n", get_time(), philosopher->id);
		}
	}
	return (NULL);
}

int	create_threads(t_philo *philosophers, int n, t_rules *rules, \
pthread_mutex_t **forks)
{
	t_philo			*this;
	int				i;

	i = 1;
	while (i <= n)
	{
		this = &philosophers[i];
		this->id = i;
		this->last_meal_time = get_time();
		this->rules = rules;
		this->left_fork = &forks[i];
		if (i == n)
			this->right_fork = &forks[0];
		else
			this->right_fork = &forks[i + 1];
		if (pthread_create(&this->thread_id, NULL, &routine, this) != 0)
			return (-1);
		i++;
	}
	return (1);
}

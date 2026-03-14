/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/13 20:43:50 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	while (1)
	{
		printf("> Philosopher id=%d\n", philosopher->id);
		usleep(20000);
	}
	return (philosopher);
}

int	create_thread(t_philo *philosophers, int n, t_rules *rules)
{
	t_philo	*this;
	int		i;

	i = 0;
	while (i < n)
	{
		this = &philosophers[i];
		this->id = i;
		this->has_fork = 0;
		this->rules = rules;
		if (pthread_create(&this->thread_id, NULL, &routine, this) != 0)
		{
			printf("[!] ERROR: pthread create failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

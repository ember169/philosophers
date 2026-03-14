/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/14 10:24:37 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philosopher;
	time_t	time_since_launch;

	philosopher = (t_philo *)arg;
	time_since_launch = get_time() - philosopher->rules->launch_time;
	printf(PF_GREEN"%ld %d is born"PF_RESET"\n", get_time(), philosopher->id);
	while (philosopher->rules->time_to_die < time_since_launch)
	{
		printf("%ld %d is thinking\n", get_time(), philosopher->id);
		time_since_launch = philosopher->rules->launch_time - get_time();
	}
	printf(PF_RED"%ld %d died"PF_RESET"\n", get_time(), philosopher->id);
	pthread_detach(philosopher->thread_id);
	return (NULL);
}

int	create_thread(t_philo *philosophers, int n, t_rules *rules)
{
	t_philo	*this;
	int		i;

	i = 1;
	while (i <= n)
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

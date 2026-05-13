/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:18 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:26:37 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** main:
**     Creates:
		- rule set structure
		- philosophers structure
		- fork structure
		- philosopher manager thread
	   Asks to:
		- allocate fork and initialize mutexes
		- create philosophers threads
*/
int	main(int ac, char **av)
{
	t_philo			*philosophers;
	t_rules			rules;
	pthread_mutex_t	*forks;

	if (ac < 5)
		return (1);

	if (!get_rules(&rules, av))
		return (1);

	philosophers = malloc(rules.philosophers_nb * sizeof(t_philo));
	if (!philosophers)
		return (1);

	forks = malloc(rules.philosophers_nb * sizeof(pthread_mutex_t));
	if (!forks || !alloc_forks(forks, rules.philosophers_nb))
		return (clean_exit(philosophers, forks), 1);

	if (!initialize_threads(philosophers, &rules, forks))
		return (clean_exit(philosophers, forks), 1);

	pthread_join(rules.manager, NULL);
	return (clean_exit(philosophers, forks), 0);
}

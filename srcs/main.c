/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:18 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 14:11:17 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
** main:
**     Creates:
**		- rule set structure
**		- philosophers structure
**		- fork structure
**		- philosopher manager thread
**	   Asks to:
**		- allocate fork and initialize mutexes
**		- create philosophers threads
**	   Waits for:
**		- Manager end
*/
int	main(int ac, char **av)
{
	t_philo			*philosophers;
	t_rules			rules;
	pthread_mutex_t	*forks;

	if (!valid_args(ac, av))
		return (1);
	if (!get_rules(&rules, av))
		return (1);
	philosophers = ft_calloc(rules.philosophers_nb, sizeof(t_philo));
	if (!philosophers)
	{
		pthread_mutex_destroy(rules.print_mutex);
		return (free(rules.print_mutex), 1);
	}
	forks = ft_calloc(rules.philosophers_nb, sizeof(pthread_mutex_t));
	if (!forks || !alloc_forks(forks, rules.philosophers_nb))
		return (clean_exit(philosophers, forks, &rules), 1);
	if (!initialize_threads(philosophers, &rules, forks))
	{
		printf("Couldnt init threads\n");
		return (clean_exit(philosophers, forks, &rules), 1);
	}
	pthread_join(rules.manager, NULL);
	return (clean_exit(philosophers, forks, &rules), 0);
}

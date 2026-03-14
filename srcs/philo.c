/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:18 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/14 10:07:04 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_exit(t_philo *philosophers, int threads_nb)
{
	int	i;

	if (!philosophers)
		exit (1);
	i = 0;
	while (i < threads_nb && philosophers[i].thread_id)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
	free(philosophers);
	printf("[i] Quitting...\n");
	exit(1);
}

int	main(int ac, char **av)
{
	t_philo		*philosophers;
	t_rules		rules;

	if (ac < 5)
		return (1);
	if (!get_rules(&rules, av))
		return (1);
	philosophers = malloc(rules.philosophers_nb * sizeof(t_philo));
	if (!philosophers)
		return (1);
	create_thread(philosophers, rules.philosophers_nb, &rules);
	clean_exit(philosophers, rules.philosophers_nb);
	return (0);
}

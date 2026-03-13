/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:18 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/13 16:56:52 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_exit(pthread_t *threads, int threads_nb)
{
	int	i;

	printf("[i] Quitting...\n");
	if (!threads)
		exit (1);
	i = 0;
	while (i < threads_nb && threads[i])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	exit(1);
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_rules		rules;

	if (ac < 5)
		return (1);
	if (!get_rules(&rules, av))
		return (1);
	threads = malloc(rules.philosophers_nb * sizeof(pthread_t));
	create_thread(threads, rules.philosophers_nb);
	clean_exit(threads, rules.philosophers_nb);
	return (0);
}

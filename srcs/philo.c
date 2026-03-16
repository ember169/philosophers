/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:18 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/16 15:58:05 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	clean_exit(t_philo *philosophers, pthread_mutex_t **forks)
{
	int	i;

	if (!philosophers)
		exit (1);
	i = 0;
	while (i < philosophers->rules->philosophers_nb && \
philosophers[i].thread_id)
	{
		pthread_join(philosophers[i].thread_id, NULL);
		i++;
	}
	free(philosophers);
	i = 0;
	while (i < philosophers[i].rules->philosophers_nb)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
	printf("[i] Quitting...\n");
	exit(1);
}

void	manage_philo(t_philo *philosophers, t_rules rules)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < rules.philosophers_nb && philosophers[i].thread_id)
		{
			if ((rules.time_to_die - get_time()) > philosophers[i].last_meal_time)
			{
				pthread_detach(philosophers[i].thread_id);
				philosophers[i].thread_id = NULL;
				printf(PF_RED"%ld %d died", get_time(), i);
			}
			i++;
		}
		if (i == 0)
			break ;
	}
}

void	alloc_forks(pthread_mutex_t **forks, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*philosophers;
	t_rules			rules;
	pthread_mutex_t	**forks;

	if (ac < 5)
		return (1);

	if (!get_rules(&rules, av))
		return (1);

	philosophers = malloc(rules.philosophers_nb * sizeof(t_philo));
	if (!philosophers)
		return (1);

	forks = malloc(rules.philosophers_nb * sizeof(pthread_mutex_t));
	if (!forks)
		return (free(philosophers), 1);
	alloc_forks(forks, rules.philosophers_nb);

	create_threads(philosophers, rules.philosophers_nb, &rules, forks);
	manage_philo(philosophers, rules);
	clean_exit(philosophers, forks);
	return (0);
}

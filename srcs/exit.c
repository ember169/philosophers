/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:12:37 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 16:08:28 by lgervet             ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void _destroy_philos(t_philo *philos, t_rules *rules)
{
    int	i;

	if (philos)
	{
		i = 0;
		while (i < rules->philosophers_nb)
		{
			if (philos[i].thread_id)
				pthread_join(philos[i].thread_id, NULL);
            if (philos[i].meal_mutex)
            {
                pthread_mutex_destroy(philos[i].meal_mutex);
                free(philos[i].meal_mutex);
            }
            i++;
		}
	}
	free(philos);
}

static void _destroy_forks(pthread_mutex_t *forks, t_rules *rules)
{
    int	i;

	if (rules->forks)
	{
		i = 0;
		while (i < rules->philosophers_nb)
        {
			pthread_mutex_destroy(&forks[i]);
            i++;
        }
	}
	free(forks);
}

/*
** clean_exit:
**     Exit wrapper in order to join every thread and free all allocated memory
**
**     @param *philo	Pointer to philos structure
**     @param *forks	Pointer to forks structure
**     @param *rules	Pointer to rules structure
*/
void	clean_exit(t_philo *philos, pthread_mutex_t *forks, t_rules *rules)
{
	_destroy_philos(philos, rules);
    _destroy_forks(forks, rules);
	pthread_mutex_destroy(rules->print_mutex);
	free(rules->print_mutex);
}

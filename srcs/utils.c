/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:04:59 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	clean_exit(t_philo *philos, pthread_mutex_t *forks)
{
	int	i;
	int	philos_nb;

	if (!philos || !forks)
		return ;
	i = 0;
	philos_nb = philos->rules->philosophers_nb;
	while (i < philos_nb - 1)
	{
		printf("Waiting for thread %d to join\n", i);
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
	printf("[i] All threads joined\n");
	free(philos);
	printf("[i] All philo freed\n");
	i = 0;
	while (i < philos_nb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return ;
}

/*
** c_sleep:
**     Custom sleep that converts ms to us
**
**     @param param  Description.
**     @return Valeur retour.
*/
void	c_sleep(double ms)
{
	usleep(ms * 1000);
}



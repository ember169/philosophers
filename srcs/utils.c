/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/10 10:48:05 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	clean_exit(t_philo *philos, pthread_mutex_t *forks, t_rules *rules)
{
	int	i;
	int	philos_nb;

	if (!philos || !forks)
		return ;
	i = 0;
	philos_nb = rules->philosophers_nb;
	while (i < philos_nb)
	{
		pthread_join(philos[i].thread_id, NULL);
		free(philos[i].meal_mutex);
		i++;
	}
	free(philos);
	i = 0;
	while (i < philos_nb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	pthread_mutex_destroy(rules->print_mutex);
	free(rules->print_mutex);
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

void	print_state(t_rules *rules, double t, int id, const char *msg)
{
	pthread_mutex_lock(rules->print_mutex);
	printf("%ld %d %s\n", (long)t, id, msg);
	pthread_mutex_unlock(rules->print_mutex);
}

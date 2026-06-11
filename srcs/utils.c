/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/11 16:08:55 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static bool	_is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

/*
** valid_args:
**     Checks if passed arguments are valid (5 or 6 of them, numerical only)
**
**     @param ac	argument number.
**     @param **av	argument string array
**	   @return true / false
*/
bool	valid_args(int ac, char **av)
{
	int	i;

	if ((ac < 5 || ac > 6) || !av)
		return (false);
	i = 1;
	while (av[i])
	{
		if (strlen(av[i]) > 9 || !_is_num(av[i]))
			return (false);
		i++;
	}
	return (true);
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
**     Custom sleep loop that usleep(100) until ms is reached
**
**     @param ms  value in ms.
*/
void	c_sleep(double ms)
{
	double	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(100);
}

/*
** print_state:
**     Wraps printf inside pthread_mutex locks
**
**     @param *rules	pointer to t_rules structure.
**     @param t  		time to print (in ms).
**     @param id  		philosopher id to print.
**     @param msg  		msg to print.

*/
void	print_state(t_rules *rules, double t, int id, const char *msg)
{
	pthread_mutex_lock(rules->print_mutex);
	printf("%ld %d %s\n", (long)t, id, msg);
	pthread_mutex_unlock(rules->print_mutex);
}

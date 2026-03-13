/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/13 15:58:38 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	get_rules(t_rules *rules, char **av)
{
	rules->philosophers_nb = atoi(av[1]);
	rules->time_to_die = atoi(av[2]);
	rules->time_to_eat = atoi(av[3]);
	rules->time_to_sleep = atoi(av[4]);
	if (av[5])
		rules->must_eat_number = atoi(av[5]);
	// TODO: implem les limites aux regles donnees
	if ((rules->philosophers_nb < 1 || rules->time_to_die < 1 || \
rules->time_to_eat < 1 || rules->time_to_sleep < 1) || \
(av[5] && rules->must_eat_number < 1))
		return (0);
	return (1);
}

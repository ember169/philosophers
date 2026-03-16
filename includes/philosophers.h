/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:04 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/16 14:56:34 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "includes.h"

int		create_threads(t_philo *philosophers, int n, t_rules *rules, \
pthread_mutex_t **forks);
int		get_rules(t_rules *rules, char **av);
time_t	get_time(void);

#endif
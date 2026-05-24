/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:04 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/24 14:12:13 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

bool	get_rules(t_rules *rules, char **av);
bool	alloc_forks(pthread_mutex_t *forks, int n);
bool	initialize_threads(
			t_philo *philos,
			t_rules *rules,
			pthread_mutex_t *forks);
bool	spawn_philos(t_philo *philo,
			int n,
			t_rules *rules,
			pthread_mutex_t *forks);
void	*manage_philo(void *arg);
double	get_time_ms(void);	
double	get_uptime(t_rules *rules);
void	c_sleep(double ms);
void	clean_exit(t_philo *philos, pthread_mutex_t *forks, t_rules *rules);
void	print_state(t_rules *rules, double t, int id, const char *msg);

#endif
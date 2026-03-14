/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:19 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/14 09:54:41 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_fork
{
	int	id;
	int	taken;
}	t_fork;

typedef struct s_rules
{
	time_t	launch_time;
	int		philosophers_nb;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_number;
	t_fork	*forks;
}	t_rules;

typedef struct s_philosopher
{
	int			id;
	int			has_fork;
	t_rules		*rules;
	pthread_t	thread_id;
}	t_philo;

#endif
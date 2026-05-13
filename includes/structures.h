/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:19 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 10:26:03 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_rules
{
	double		launch_time;
	int			philosophers_nb;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_number;
	pthread_t	*manager;
}	t_rules;

typedef struct s_philosopher
{
	int					id;
	int					should_die;
	double				last_meal_time;
	pthread_mutex_t		*meal_mutex;
	t_rules				*rules;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

#endif
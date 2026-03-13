/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 18:18:19 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/13 16:56:50 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_rules
{
	int	philosophers_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_number;
}	t_rules;

#endif
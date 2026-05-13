/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:15:48 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/13 17:02:24 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// Seconds : tv.tv_sec
// Microseconds: tv.tv_usec
// Minutes west of Greenwich: tz.tz_minuteswest

double	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

double	get_time_since_launch(t_rules *rules)
{
	return (get_time_ms() - rules->launch_time);
}

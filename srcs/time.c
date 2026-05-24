/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:15:48 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/21 11:49:41 by mskn             ###   ########.fr       */
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

double	get_uptime(t_rules *rules)
{
	return (get_time_ms() - rules->launch_time);
}

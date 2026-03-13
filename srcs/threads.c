/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:50:55 by lgervet           #+#    #+#             */
/*   Updated: 2026/03/13 16:56:54 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*run(void *arg)
{
	pthread_t	this;

	this = pthread_self();
	while (1)
	{
		printf("> thread %lu running...\n", (unsigned long)this);
		usleep(5000);
	}
	return (arg);
}

int	create_thread(pthread_t *threads, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&threads[i], NULL, &run, NULL) != 0)
		{
			printf("[!] ERROR: pthread create failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

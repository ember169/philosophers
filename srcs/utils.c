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

/*
** ft_calloc:
**     Allocates memory and memset it to zero
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*buffer;
	int				total_size;
	unsigned char	*str;

	if (nmemb == 0 && size == 0)
		return (NULL);
	total_size = nmemb * size;
	buffer = malloc(total_size);
	if (!buffer)
		return (NULL);
	str = (unsigned char *) buffer;
	while (total_size--)
		*str++ = 0;
	return (buffer);
}

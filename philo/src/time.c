/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:32:52 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/16 12:45:59 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

time_t	timeval_to_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @returns the elapsed time in milliseconds since the given time.
 */
time_t	get_elapsed_time_ms(struct timeval start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (current.tv_sec < start.tv_sec || (current.tv_sec == start.tv_sec
			&& current.tv_usec < start.tv_usec))
	{
		return (0);
	}
	return (timeval_to_ms(current) - timeval_to_ms(start));
}
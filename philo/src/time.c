/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:32:52 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/18 19:31:41 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

time_t	timeval_to_ms(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

/**
 * @returns the elapsed time in milliseconds since the given time.
 * If the current time is before the given time, it returns 0.
 */
time_t	get_elapsed_time_ms(struct timeval start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (timeval_to_ms(current) - timeval_to_ms(start));
}

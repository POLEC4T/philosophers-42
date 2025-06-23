/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/23 10:16:18 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

bool	is_philo_dead(t_philo *philo)
{
	if (get_elapsed_time_ms(philo->last_meal_time) >= philo->ctx->time_to_die)
	{
		philo->is_dead = true;
		return (true);
	}
	return (false);
}

/**
 * @brief make the thread "wait" ms_to_sleep while checking if the philo is dead
 */
int	my_wait(t_philo *philo, time_t ms_to_sleep, t_philo_state philo_state)
{
	struct timeval	func_start_time;

	gettimeofday(&func_start_time, NULL);
	while (get_elapsed_time_ms(func_start_time) < ms_to_sleep)
	{
		if (philo_state != EATING &&
			(is_philo_dead(philo) || philo->ctx->somebody_died))
			return (SOMEBODY_DIED);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

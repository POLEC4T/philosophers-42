/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/16 13:26:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

bool	is_philo_dead(t_philo *philo)
{
	if (timeval_to_ms(philo->last_meal_time) == -1)
		return (false);
	if (get_elapsed_time_ms(philo->last_meal_time) >= philo->ctx->time_to_die)
		return (true);
	return (false);
}

int	my_sleep(t_philo *philo, time_t ms_to_sleep, t_philo_state philo_state)
{
	struct timeval	start_time;
	time_t			elapsed_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		elapsed_time = get_elapsed_time_ms(start_time);
		if (philo_state != EATING)
		{
			philo->is_dead = is_philo_dead(philo);
			if (philo->is_dead)
				return (SOMEBODY_DIED);
		}
		if (get_somebody_died(philo->ctx))
			return (SOMEBODY_DIED);
		if (elapsed_time >= ms_to_sleep)
			break ;
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

/**
 * @returns true if a philosopher has died, false otherwise.
 * Done to avoid deadlock when checking if a philosopher has died.
 */
bool	get_somebody_died(t_context *ctx)
{
	pthread_mutex_lock(ctx->somebody_died_lock);
	if (ctx->somebody_died)
	{
		pthread_mutex_unlock(ctx->somebody_died_lock);
		return (true);
	}
	pthread_mutex_unlock(ctx->somebody_died_lock);
	return (false);
}

/**
 * @brief Sets the state of somebody_died in the context to true
 */
void	set_somebody_died_true(t_context *ctx)
{
	pthread_mutex_lock(ctx->somebody_died_lock);
	ctx->somebody_died = true;
	pthread_mutex_unlock(ctx->somebody_died_lock);
}

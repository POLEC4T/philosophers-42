/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:08 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/19 12:07:00 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

bool	is_philo_dead(t_philo *philo)
{
	if (philo->last_meal_time.tv_usec == -1000)
		return (false);
	if (get_elapsed_time_ms(philo->last_meal_time) >= philo->ctx->time_to_die)
	{
		philo->is_dead = true;
		return (true);
	}
	return (false);
}

int	my_sleep(t_philo *philo, time_t ms_to_sleep, t_philo_state philo_state)
{
	struct timeval	start_time_val;

	gettimeofday(&start_time_val, NULL);
	while (get_elapsed_time_ms(start_time_val) < ms_to_sleep)
	{
		if (philo_state != EATING)
		{
			if (is_philo_dead(philo))
				return (SOMEBODY_DIED);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

// int	my_sleep(t_philo *philo, time_t ms_to_sleep, t_philo_state philo_state)
// {
// 	struct timeval	start_time_val;
// 	time_t			time_before_dead;

// 	(void)philo_state;
// 	gettimeofday(&start_time_val, NULL);
// 	if (philo->last_meal_time.tv_usec == -1000)
// 	{
// 		time_before_dead = philo->ctx->time_to_die;
// 	}
// 	else
// 	{
// 		time_before_dead = timeval_to_ms(philo->last_meal_time)
// 			+ philo->ctx->time_to_die - timeval_to_ms(start_time_val);
// 	}
// 	if (time_before_dead < ms_to_sleep && philo_state != EATING)
// 	{
// 		while (get_elapsed_time_ms(start_time_val) < time_before_dead)
// 		{
// 			usleep(100);
// 		}
// 		philo->is_dead = true;
// 		return (SOMEBODY_DIED);
// 	}
// 	else
// 	{
// 		while (get_elapsed_time_ms(start_time_val) < ms_to_sleep)
// 		{
// 			usleep(100);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }

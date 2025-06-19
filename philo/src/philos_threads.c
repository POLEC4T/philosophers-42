/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:11 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/19 13:17:52 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

static int	philo_eat(t_philo *philo)
{
	print_lock_mutex(EAT, philo->ctx->print_lock, philo->ctx, philo->id);
	gettimeofday(&philo->last_meal_time, NULL);
	if (my_sleep(philo, philo->ctx->time_to_eat, EATING) == SOMEBODY_DIED)
		return (SOMEBODY_DIED);
	return (EXIT_SUCCESS);
}

static int	has_eaten_all_meals(t_philo *philo)
{
	if (philo->ctx->max_meals != -2)
	{
		philo->num_meals_eaten++;
		if (philo->num_meals_eaten == philo->ctx->max_meals)
			return (true);
	}
	return (false);
}

static int	philo_sleep(t_philo *philo)
{
	print_lock_mutex(SLEEP, philo->ctx->print_lock, philo->ctx, philo->id);
	if (my_sleep(philo, philo->ctx->time_to_sleep, SLEEPING) == SOMEBODY_DIED)
		return (SOMEBODY_DIED);
	return (EXIT_SUCCESS);
}

static int	philo_think(t_philo *philo)
{
	print_lock_mutex(THINK, philo->ctx->print_lock, philo->ctx, philo->id);
	if (philo->ctx->num_philos % 2 == 1 && philo->id % 2 == 0)
	{
		if (my_sleep(philo, philo->ctx->time_to_eat * 0.5,
				THINKING) == SOMEBODY_DIED)
		{
			return (SOMEBODY_DIED);
		}
	}
	return (EXIT_SUCCESS);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		if (my_sleep(philo, philo->ctx->time_to_eat * 0.5,
				THINKING) == SOMEBODY_DIED)
			return ;
	while (philo->ctx->somebody_died == false)
	{
		if (lock_forks(philo) == SOMEBODY_DIED)
			break ;
		if (philo_eat(philo) == SOMEBODY_DIED)
		{
			release_forks(philo);
			break ;
		}
		release_forks(philo);
		if (has_eaten_all_meals(philo))
			break ;
		if (philo_sleep(philo) == SOMEBODY_DIED)
			break ;
		if (philo_think(philo) == SOMEBODY_DIED)
			break ;
	}
}

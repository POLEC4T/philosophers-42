/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:11 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/16 13:14:24 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

static int	lock_fork(t_philo *philo, t_fork *fork)
{
	while (fork->is_available == false)
	{
		philo->is_dead = is_philo_dead(philo);
		if (get_somebody_died(philo->ctx) || philo->is_dead)
			return (SOMEBODY_DIED);
		usleep(100);
	}
	pthread_mutex_lock(fork->mutex);
	fork->is_available = false;
	print_lock_mutex(HAS_TAKEN_FORK, philo->ctx->print_lock, philo->ctx,
		philo->id);
	return (EXIT_SUCCESS);
}

static int	lock_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (lock_fork(philo, first_fork) == SOMEBODY_DIED)
		return (SOMEBODY_DIED);
	if (lock_fork(philo, second_fork) == SOMEBODY_DIED)
	{
		pthread_mutex_unlock(first_fork->mutex);
		first_fork->is_available = true;
		return (SOMEBODY_DIED);
	}
	return (EXIT_SUCCESS);
}

static int	philo_eat(t_philo *philo)
{
	print_lock_mutex(EAT, philo->ctx->print_lock, philo->ctx, philo->id);
	gettimeofday(&philo->last_meal_time, NULL);
	if (my_sleep(philo, philo->ctx->time_to_eat, EATING) == SOMEBODY_DIED)
		return (SOMEBODY_DIED);
	return (EXIT_SUCCESS);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork->mutex);
	philo->right_fork->is_available = true;
	pthread_mutex_unlock(philo->left_fork->mutex);
	philo->left_fork->is_available = true;
}

static int	has_eaten_all_meals(t_philo *philo)
{
	if (get_somebody_died(philo->ctx))
		return (false);
	if (philo->ctx->max_meals > 0)
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

// pistes en commentaires :
static int	philo_think(t_philo *philo)
{
	print_lock_mutex(THINK, philo->ctx->print_lock, philo->ctx, philo->id);
	if (philo->ctx->num_philos % 2 == 1 && philo->id % 2 == 1) //faire sleep que les impairs ?
		if (my_sleep(philo, philo->ctx->time_to_eat / 2, THINKING) == SOMEBODY_DIED) // faire sleep moins longtemps si num_philos impair ?
			return (SOMEBODY_DIED);
	return (EXIT_SUCCESS);
}

void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 1)
		if (my_sleep(philo, philo->ctx->time_to_eat / 2, THINKING) == SOMEBODY_DIED)
			return ;
	while (true)
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
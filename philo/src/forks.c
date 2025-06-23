/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:29:29 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/23 10:05:36 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

static void	release_fork(t_fork *fork_to_release)
{
	pthread_mutex_unlock(fork_to_release->mutex);
	fork_to_release->is_available = true;
}

static int	kill_philo_alone(t_philo *philo, t_fork *fork_to_release)
{
	usleep(philo->ctx->time_to_die * 1000);
	philo->is_dead = true;
	release_fork(fork_to_release);
	return (SOMEBODY_DIED);
}

static int	lock_fork(t_philo *philo, t_fork *fork)
{
	while (fork->is_available == false)
	{
		if (is_philo_dead(philo) || philo->ctx->somebody_died)
			return (SOMEBODY_DIED);
		usleep(100);
	}
	pthread_mutex_lock(fork->mutex);
	fork->is_available = false;
	print_lock_mutex(HAS_TAKEN_FORK, philo->ctx->print_lock, philo->ctx,
		philo->id);
	return (EXIT_SUCCESS);
}
int	lock_forks(t_philo *philo)
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
	if (philo->ctx->num_philos == 1)
		return (kill_philo_alone(philo, first_fork));
	if (lock_fork(philo, second_fork) == SOMEBODY_DIED)
	{
		release_fork(first_fork);
		return (SOMEBODY_DIED);
	}
	return (EXIT_SUCCESS);
}

void	release_forks(t_philo *philo)
{
	release_fork(philo->left_fork);
	release_fork(philo->right_fork);
}

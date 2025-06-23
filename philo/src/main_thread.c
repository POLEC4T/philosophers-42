/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:49:58 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/23 10:20:13 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/**
 * @brief Checks any dead philo or if philo have finished eating the maximum 
 * number of meals.
 * If a philosopher dies, it prints the death message and exits the loop.
 * If all philosophers have finished eating, it exits the loop as well.
 */
void	loop_check_threads(t_context *ctx, t_philo *philos)
{
	int	i;
	int	num_philo_finished;

	num_philo_finished = 0;
	while (1)
	{
		i = -1;
		while (++i < ctx->num_philos)
		{
			if (philos[i].is_dead)
			{
				ctx->somebody_died = true;
				print_lock_mutex(DEAD, ctx->print_lock, ctx, philos[i].id);
				return ;
			}
			if (ctx->max_meals != -2)
				if (philos[i].num_meals_eaten == ctx->max_meals)
					if (++num_philo_finished == ctx->num_philos)
						return ;
		}
		usleep(100);
	}
}

int	start_threads(t_context *ctx, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < ctx->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, (void *)&philo_routine,
				&philos[i]) != 0)
		{
			ctx->somebody_died = true;
			return (return_write_error("start_threads: Failed to create philo t\
hreads\n"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * This is done to be sure all threads finish to print what they have to
 * before the program exits.
 */
void	join_threads(t_context *ctx, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < ctx->num_philos && philos[i].thread != 0)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

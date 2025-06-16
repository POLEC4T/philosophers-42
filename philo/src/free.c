/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:42:36 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/12 18:55:53 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

static void	free_forks(t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->forks[i])
	{
		if (ctx->forks[i]->mutex)
			pthread_mutex_destroy(ctx->forks[i]->mutex);
		free(ctx->forks[i]);
		i++;
	}
	free(ctx->forks);
	ctx->forks = NULL;
}

void	free_all(t_context *ctx, t_philo *philos)
{
	if (philos)
		free(philos);
	if (ctx->forks)
		free_forks(ctx);
	if (ctx->print_lock)
		pthread_mutex_destroy(ctx->print_lock);
}
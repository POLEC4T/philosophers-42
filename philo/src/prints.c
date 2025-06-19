/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:04:04 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/19 14:16:54 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/**
 * @returns EXIT_FAILURE
 */
int	return_write_error(const char *message)
{
	write(STDERR_FILENO, "philo: ", 7);
	write(STDERR_FILENO, message, strlen(message));
	return (EXIT_FAILURE);
}

void	print_lock_mutex(t_print_type print_type, pthread_mutex_t *print_mutex,
		t_context *ctx, int philo_id)
{
	if (ctx->somebody_died && print_type != DEAD)
		return ;
	pthread_mutex_lock(print_mutex);
	if (print_type == EAT)
		printf("%ld %d is \e[0;32meating\e[0m\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	else if (print_type == SLEEP)
		printf("%ld %d is \e[0;35msleeping\e[0m\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	else if (print_type == THINK)
		printf("%ld %d is \e[0;33mthinking\e[0m\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	else if (print_type == DEAD)
		printf("%ld %d \e[0;31mdied\e[0m\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	else if (print_type == HAS_TAKEN_FORK)
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	pthread_mutex_unlock(print_mutex);
}

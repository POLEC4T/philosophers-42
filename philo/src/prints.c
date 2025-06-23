/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:04:04 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/23 10:15:16 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/**
 * @returns EXIT_FAILURE
 */
int	return_write_error(char *message)
{
	write(STDERR_FILENO, "philo: ", 7);
	write(STDERR_FILENO, message, ft_strlen(message));
	return (EXIT_FAILURE);
}

void	print_lock_mutex(t_print_type print_type, pthread_mutex_t *print_mutex,
		t_context *ctx, int philo_id)
{
	if (ctx->somebody_died && print_type != DEAD)
		return ;
	pthread_mutex_lock(print_mutex);
	if (print_type == EAT)
		printf("%ld %d is %seating%s\n",
			get_elapsed_time_ms(ctx->start_time), philo_id, GREEN, END_COLOR);
	else if (print_type == SLEEP)
		printf("%ld %d is %ssleeping%s\n",
			get_elapsed_time_ms(ctx->start_time), philo_id, VIOLET, END_COLOR);
	else if (print_type == THINK)
		printf("%ld %d is %sthinking%s\n",
			get_elapsed_time_ms(ctx->start_time), philo_id, ORANGE, END_COLOR);
	else if (print_type == DEAD)
		printf("%ld %d %sdied%s\n",
			get_elapsed_time_ms(ctx->start_time), philo_id, RED, END_COLOR);
	else if (print_type == HAS_TAKEN_FORK)
		printf("%ld %d has taken a fork\n",
			get_elapsed_time_ms(ctx->start_time), philo_id);
	pthread_mutex_unlock(print_mutex);
}

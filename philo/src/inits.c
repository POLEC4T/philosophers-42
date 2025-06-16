/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:33:59 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/16 13:10:29 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

static void	clean_init_ctx(t_context *ctx)
{
	ctx->num_philos = -2;
	ctx->time_to_die = -2;
	ctx->time_to_eat = -2;
	ctx->time_to_sleep = -2;
	ctx->max_meals = -2;
	ctx->forks = NULL;
	ctx->start_time.tv_sec = 0;
	ctx->start_time.tv_usec = 0;
	ctx->somebody_died = false;
	ctx->somebody_died_lock = NULL;
	ctx->print_lock = NULL;
}

static int	init_forks(t_context *ctx)
{
	int	i;

	ctx->forks = malloc(sizeof(t_fork *) * (ctx->num_philos + 1));
	if (ctx->forks == NULL)
		return (return_write_error("init_forks: Mem alloc failed\n"));
	memset(ctx->forks, 0, sizeof(t_fork *) * (ctx->num_philos + 1));
	i = -1;
	while (++i < ctx->num_philos)
	{
		ctx->forks[i] = malloc(sizeof(t_fork));
		if (ctx->forks[i] == NULL)
			return (return_write_error("init_forks: Mem alloc failed\n"));
		ctx->forks[i]->mutex = malloc(sizeof(pthread_mutex_t));
		if (ctx->forks[i]->mutex == NULL)
			return (return_write_error("init_forks: Mutex alloc failed\n"));
		if (pthread_mutex_init(ctx->forks[i]->mutex, NULL) != 0)
		{
			free(ctx->forks[i]->mutex);
			ctx->forks[i]->mutex = NULL;
			return (return_write_error("init_forks: Mutex init failed\n"));
		}
		ctx->forks[i]->is_available = true;
	}
	return (EXIT_SUCCESS);
}

static int init_mutex(pthread_mutex_t **mutex_ptr)
{
	*mutex_ptr = malloc(sizeof(pthread_mutex_t));
	if (*mutex_ptr == NULL)
		return (return_write_error("init_ctx: Mutex alloc failed\n"));
	if (pthread_mutex_init(*mutex_ptr, NULL) != 0)
	{
		free(*mutex_ptr);
		*mutex_ptr = NULL;
		return (return_write_error("init_ctx: Mutex init failed\n"));
	}
	return (EXIT_SUCCESS);
}

static int	init_ctx(t_context *ctx, char **argv)
{
	ctx->num_philos = ft_atoi(argv[1]);
	ctx->time_to_die = ft_atoi(argv[2]);
	ctx->time_to_eat = ft_atoi(argv[3]);
	ctx->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ctx->max_meals = ft_atoi(argv[5]);
	if (ctx->num_philos <= 1 || ctx->time_to_die <= 0 || ctx->time_to_eat <= 0
		|| ctx->time_to_sleep <= 0 || (argv[5] && ctx->max_meals <= 0))
	{
		return (return_write_error("Invalid arguments\n"));
	}
	gettimeofday(&ctx->start_time, NULL);
	if (init_forks(ctx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex(&ctx->print_lock) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex(&ctx->somebody_died_lock) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_philos(t_context *ctx, t_philo **philos_ptr)
{
	int	i;

	*philos_ptr = malloc(sizeof(t_philo) * ctx->num_philos);
	if (!*philos_ptr)
		return (return_write_error("init_philos: Mem alloc failed\n"));
	i = -1;
	while (++i < ctx->num_philos)
	{
		(*philos_ptr)[i].id = i + 1;
		(*philos_ptr)[i].thread = 0;
		(*philos_ptr)[i].ctx = ctx;
		(*philos_ptr)[i].last_meal_time = (struct timeval){0, -1000};
		(*philos_ptr)[i].num_meals_eaten = 0;
		(*philos_ptr)[i].is_dead = false;
		(*philos_ptr)[i].left_fork = ctx->forks[i];
		(*philos_ptr)[i].right_fork = ctx->forks[(i + 1) % ctx->num_philos];
	}
	return (EXIT_SUCCESS);
}

int	init_all(t_context *ctx, t_philo **philos_ptr, char **argv)
{
	clean_init_ctx(ctx);
	*philos_ptr = NULL;
	if (init_ctx(ctx, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(ctx, philos_ptr) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
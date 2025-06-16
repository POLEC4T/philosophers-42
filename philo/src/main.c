/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:12 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/12 14:57:10 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

int	main(int argc, char **argv)
{
	t_context	ctx;
	t_philo		*philos;

	if (argc < 5 || argc > 6)
		return (return_write_error(USAGE_STR));
	if (init_all(&ctx, &philos, argv) == EXIT_SUCCESS)
	{
		start_threads(&ctx, philos);
		loop_check_threads(&ctx, philos);
		join_threads(&ctx, philos);
	}
	free_all(&ctx, philos);
	return (EXIT_SUCCESS);
}

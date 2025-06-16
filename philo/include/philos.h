/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:02:53 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/16 13:11:36 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SOMEBODY_DIED 1
# define I_DIED 1
# define USAGE_STR \
	"Usage: ./philosophers num_philos time_to_die time_to_eat \
time_to_sleep [max_meals]\n"

typedef enum e_print_type
{
	EAT,
	DEAD,
	SLEEP,
	THINK,
	HAS_TAKEN_FORK,
}						t_print_type;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
}						t_philo_state;

typedef struct fork
{
	pthread_mutex_t		*mutex;
	int					is_available;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	struct timeval		last_meal_time;
	int					num_meals_eaten;
	t_fork				*left_fork;
	t_fork				*right_fork;
	bool				is_dead;
	struct s_context	*ctx;
}						t_philo;

typedef struct s_context
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	pthread_mutex_t		*print_lock;
	t_fork				**forks;
	struct timeval		start_time;
	bool				somebody_died;
	pthread_mutex_t		*somebody_died_lock;
}						t_context;

int						ft_atoi(const char *nptr);

void					philo_routine(t_philo *philo);

// inits
int						init_all(t_context *ctx, t_philo **philos, char **argv);

// frees
void					free_all(t_context *ctx, t_philo *philos);

// main_thread
int						start_threads(t_context *ctx, t_philo *philos);
int						join_threads(t_context *ctx, t_philo *philos);
void					loop_check_threads(t_context *ctx, t_philo *philos);

// time
time_t					timeval_to_ms(struct timeval time);
time_t					get_elapsed_time_ms(struct timeval start);

// utils
bool					get_somebody_died(t_context *ctx);
void					set_somebody_died_true(t_context *ctx);
int						my_sleep(t_philo *philo, time_t ms_to_sleep,
							t_philo_state philo_state);
bool						is_philo_dead(t_philo *philo);

// prints
void					print_lock_mutex(t_print_type print_type,
							pthread_mutex_t *print_mutex, t_context *ctx,
							int philo_id);
int						return_write_error(const char *msg);

#endif

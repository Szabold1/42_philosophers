/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/17 09:56:05 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

/* ************************************************************ Define macros */
# define OK 0
# define ERR -1
# define MAX_INT 2147483647

// error messages
# define MUTEX_INIT_ERR "pthread_mutex_init failed"
# define THREAD_CREATE_ERR "pthread_create failed"
# define MALLOC_ERR "malloc failed"

/* ********************************************************** Data structures */
// struct for one philosopher
typedef struct s_philo
{
	int				id; // starts at 1
	int				fork_left_index; // index of the left fork
	int				fork_right_index; // index of the right fork
	long long		last_meal_time; // time of the last meal
	int				meals_eaten; // number of meals eaten so far
	pthread_t		thread_id; // thread id
	struct s_data	*data; // pointer to the data struct
}	t_philo;

// struct for all data
typedef struct s_data
{
	int				nb_of_philos; // number of philosophers
	int				time_to_die; // time to die in milliseconds
	int				time_to_eat; // time to eat in milliseconds
	int				time_to_sleep; // time to sleep in milliseconds
	int				nb_of_meals; // number of meals each philosopher must eat
	long long		start_time; // start time in milliseconds
	int				nb_of_full_philos; // number of philosophers that ate all meals
	bool			died; // true if a philosopher died (time_to_die exceeded)
	pthread_mutex_t	*forks; // array of mutexes for the forks
	pthread_mutex_t	print_lock; // mutex for printing
	pthread_mutex_t	lock; // mutex for general use
	t_philo			*philos; // array of philosophers
}	t_data;


/* ****************************************************** Function prototypes */
// File: clean_up.c
void		clean_up(t_data *data);
// File: eat.c
int			philo_eat(t_philo *philo);
// File: forks.c
void		take_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
// File: init.c
int			init(char *argv[], t_data *data);
// File: routine.c
void		*routine(void *arg);
// File: simulation.c
int			simulation(t_data *data);
// File: utils.c
void		err_msg(char *msg);
int			atoi_philo(char *str);
long long	get_current_time(void);
void		print_status(t_philo *philo, char *status);
void		sleep_ms(int time);

#endif